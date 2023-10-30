import json
import requests
import typer
import ipaddress
import os.path
import random
import paho.mqtt.client as mqtt_client
from collections import OrderedDict

broker = '10.2.2.4'
port = 1883
client_id = f'python-mqtt-{random.randint(0, 1000)}'

def connect_mqtt():
  def on_connect(client, userdata, flags, rc):
    if rc == 0:
      print("Connected to MQTT Broker!")
    else:
      print("Failed to connect, return code %d\n", rc)
  # Set Connecting Client ID
  client = mqtt_client.Client(client_id)
  client.username_pw_set("Admin", "Admin")
  client.on_connect = on_connect
  client.connect(broker, port)
  return client

def publish(client, topic, msg, qos, retain):
  result = client.publish(topic, msg, qos, retain)
  status = result[0]
  if status == 0:
    print(f"Topic: `{topic}`, QOS: `{qos}`, Retained: `{retain}`")
    print(f"Published `{msg}`")
  else:
    print(f"Failed to send message to topic {topic}")

def compileTasmotaDict(tasIpAddr: str, tasCommand: str, baseDict: dict, sortDict: bool):
  cmdBasePath = 'http://' + tasIpAddr + '/cm?cmnd=' + tasCommand
  response = requests.get(cmdBasePath)
  response.raise_for_status()
  jsonResponse = response.json()
  commandDict = { tasCommand : {}}
  baseDict[tasIpAddr].update(commandDict)
  baseDict[tasIpAddr][tasCommand].update(jsonResponse)
  if sortDict == False:
    return baseDict
  else:
    sortedDict = baseDict
    sortedDict[tasIpAddr] = OrderedDict(sorted(baseDict[tasIpAddr].items()))
    return sortedDict

def configureDefinedTopic(tasIpAddr: str, definedTopic: str):
  cmdPath = 'http://' + tasIpAddr + '/cm?cmnd=topic%20' + definedTopic
  print( tasIpAddr + ": " + cmdPath )
  response = requests.get(cmdPath)
  response.raise_for_status()
  jsonResponse = str(response.json())
  print ("result: " + jsonResponse )

def exportConfiguration(
  commandDict: dict, 
  auditDict: dict,
  exportConfigFile: str,
  appendData: bool):
  if appendData == True:
    with open(exportConfigFile, "r") as exportedDataObj:
      configData = json.loads(exportedDataObj.read())
  else:
    configData = { "tasmotas" : {}}
  
  for device in auditDict["tasmotas"]:
    baseDict = { str(device) : {} }
    for mapData in commandDict["ExportMapping"]:
      indexedData = auditDict["tasmotas"][device]
      for item in commandDict["ExportMapping"][mapData]:
        indexedData = indexedData[item]
      # print('"' + mapData + '" : ' + json.dumps(indexedData))
      mapDataDict = {mapData : indexedData}
      # mapDataDict = { str(mapData) : {}}
      baseDict[device].update(mapDataDict)
    #Establish Specific Configuration Topic
    mapDataDict = {"ConfigurationTopic" : auditDict["tasmotas"][device]["Status 0"]["Status"]["Topic"]}
    baseDict[device].update(mapDataDict)
    mapDataDict = {"DefinedTopic" : auditDict["tasmotas"][device]["OrigTopic"]["OrigTopic"]}
    baseDict[device].update(mapDataDict)
    mapDataDict = {"MacAddress" : auditDict["tasmotas"][device]["MacAddress"]["MacAddress"]}
    baseDict[device].update(mapDataDict)
    # #Update final output dictionary
    configData["tasmotas"].update(baseDict)

  # #Sort and update results to file as JSON
  configDataSorted = OrderedDict(sorted(configData.items()))
  with open(exportConfigFile, "w") as outputfile:
    json.dump(configDataSorted, outputfile, indent=2)

def configureDevices(
  commandDict: dict, 
  declaredConfigFile: str,
  pushConfigs: bool):
  client = connect_mqtt()
  client.loop_start()
  if os.path.isfile(declaredConfigFile):
    with open(declaredConfigFile, "r") as declaredConfigFileObj:
      declaredConfigData = json.loads(declaredConfigFileObj.read())
  else:
    print("--configFileToApply file not found or invalid")
    exit()
  
  for device in declaredConfigData["tasmotas"]:
    backlogStr = str("")

    for backlogCommand in commandDict["BacklogCapableCommands"]:
      # Quotes with a string are interpreted literally and should be excluded
      commandSetting = json.dumps(declaredConfigData["tasmotas"][device][backlogCommand]).strip('"')
      # If a setting double quotes, it will have gotten stripped and will be '', which needs to be corrected.
      if commandSetting == '':
        commandSetting = '0'
      # backlogStr = backlogStr + str(backlogCommand) + " " + json.dumps(declaredConfigData["tasmotas"][device][backlogCommand]) + "; " # + " " + str(configData["tasmotas"][device][backlogCommand] + ";"))
      backlogStr = backlogStr + str(backlogCommand) + " " + commandSetting + "; " # + " " + str(configData["tasmotas"][device][backlogCommand] + ";"))

    ruleStr = str("")
    for ruleNumber in commandDict["Rules"]:
        for ruleCommand in commandDict["Rules"][ruleNumber]:
          if ruleCommand == "Rules":
            ruleStr = json.dumps(declaredConfigData["tasmotas"][device][ruleNumber][ruleNumber][ruleCommand]).strip('"')
            if ruleStr == "":
              ruleStr = str('""')
            if pushConfigs == True:
              configurationTopic = declaredConfigData["tasmotas"][device]["ConfigurationTopic"]
              publishTopic = str("cmnd/" + configurationTopic + "/" + ruleNumber)
              publish(client, publishTopic, ruleStr, 0, False)
          else:
            if ruleCommand == "State":
              ruleBaseVal = 0
            if ruleCommand == "Once":
              ruleBaseVal = 4
            if ruleCommand == "StopOnError":
              ruleBaseVal = 8
            if json.dumps(declaredConfigData["tasmotas"][device][ruleNumber][ruleNumber][ruleCommand]).strip('"') == "ON":
              ruleVal = ruleBaseVal + 1
            else:
              ruleVal = ruleBaseVal
            backlogRules = str( ruleNumber + " " + str(ruleVal) )
            backlogStr = backlogStr + backlogRules + "; "
          # ruleStr = ruleStr + json.dumps(declaredConfigData["tasmotas"][device][ruleNumber][ruleNumber][ruleCommand]).strip('"')

    if pushConfigs == True:
      configurationTopic = declaredConfigData["tasmotas"][device]["ConfigurationTopic"]
      # for individualCommand in commandDict["IndividualCommands"]:
      #   publishTopic = str("cmnd/" + configurationTopic + "/" + individualCommand)
      #   commandSetting = json.dumps(declaredConfigData["tasmotas"][device][individualCommand]).strip('"')
      #   if commandSetting == '':
      #     commandSetting = '""'
      #   publish(client, publishTopic, commandSetting, 0, False)
      publishTopic = str("cmnd/" + configurationTopic + "/backlog")
      publish(client, publishTopic, backlogStr, 0, False)
        
    else:
      print(device + ": backlog " + backlogStr)

def main(
#input parameters
hostlistfile: typer.FileText = typer.Option(..., mode="r"),
tasmotacommandfile: typer.FileText = typer.Option(..., mode="r"),
auditDevices: bool = False,
importPriorAudit: bool = False,
auditExportFile: str = "",
exportConfig: bool = False,
exportConfigFile: str = "",
appendExportedAudit: bool = False,
appendExportedConfig: bool = False,
applyDefinedTopic: bool = False,
configFileToApply: str = "",
pushConfigs: bool = False,
sortedCommandOutput: bool = False
):

  #Bring in JSON formatted host list.
  tasList = json.load(hostlistfile)
  
  #Bring in JSON formatted command set.
  tasCommands = json.load(tasmotacommandfile)

  if importPriorAudit == True:
    if auditExportFile == "":
        print("--auditExportFile option required")
        exit()
    if os.path.isfile(auditExportFile):
      with open(auditExportFile, "r") as auditFile:
        auditData = json.loads(auditFile.read())
  
  if auditDevices == True:
    if auditExportFile == "":
        print("--auditExportFile option required")
        exit()
    
    if appendExportedAudit == True:
      if os.path.isfile(auditExportFile):
        with open(auditExportFile, "r") as auditFile:
          auditData = json.loads(auditFile.read())
      else:
        auditData = { "tasmotas" : {}}
    else:
      auditData = { "tasmotas" : {}}

    #Build or load initial dictionary for all devices.
    
    #Loop hosts in subnet range
    for tasDevice in tasList:
      
      ipAddressString = str(format(ipaddress.IPv4Address(tasDevice["ip"])))
      macAddressString = str(tasDevice["mac"])
      DefinedTopic = "tasmota_" + macAddressString.replace(":","")[-6:]

      print(ipAddressString + " collecting Tasmota device configurations for: " + macAddressString)
      
      #Setup device specific dictionary
      dictUpdate = { str(ipAddressString) : {} }

      #Iterate over commands to query data and update device specific dictionary
      for command in tasCommands["Commands"]:
        dictUpdate = compileTasmotaDict(ipAddressString, command, dict(dictUpdate), sortedCommandOutput)
        
      dictUpdate[ipAddressString].update({"OrigTopic":{"OrigTopic" : DefinedTopic}})
      dictUpdate[ipAddressString].update({"MacAddress":{"MacAddress" : macAddressString}})
      # dictUpdate[ipAddressString]['Topic'].update({ "Topic" : DefinedTopic })
      #Update final output dictionary
      auditData["tasmotas"].update(dictUpdate)
    
      # #Update results to file as JSON.  
      # #Don't wait until end so that it builds what is accessible
      auditDataSorted = OrderedDict(sorted(auditData.items()))

      with open(auditExportFile, "w") as outputfile:
        json.dump(auditDataSorted, outputfile, indent=2)

  if exportConfig == True:
    if exportConfigFile == "":
      print("--exportconfigfile definition needed")
      exit()
    else:
      if auditExportFile == "":
        print("--auditexportfile option required")
        exit()
      else:
        with open(auditExportFile, "r") as inputFile:
          auditData = json.loads(inputFile.read())
      exportConfiguration(tasCommands, auditData, exportConfigFile, appendExportedConfig)
  
  if applyDefinedTopic == True:

    if exportConfigFile == "":
      print("--exportconfigfile definition needed")
      exit()
    else:
      with open(exportConfigFile, "r") as exportedDataObj:
        configData = json.loads(exportedDataObj.read())
      for device in configData['tasmotas']:
        configureDefinedTopic(device, configData['tasmotas'][device]["DefinedTopic"])

  if configFileToApply != "":
    configureDevices(tasCommands, configFileToApply, pushConfigs)


if __name__ == "__main__":
  typer.run(main)
