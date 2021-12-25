# Control Device Template:
This basically tells the device that it does have a Relay so that it will accept power on commands 
Doing this enables the LED, but will sends 5v to the wrong (dead end) GPIO, which doesn't engage the mechanical relay

```
backlog template {"NAME":"Gosund KS-602S","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0;
```
# Active Device Template:
Send voltage for a power on event to a correct GPIO

```
backlog template {"NAME":"Gosund KS-602S","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0;
```
# Power Calibration
Have to run https://tasmota.github.io/docs/Power-Monitoring-Calibration/ process in console.
Get values from the Kill-A-Watt device

```
PowerSet 53.0
VoltageSet 120.0
CurrentSet 430
```

#####################################################################

# From the Command Line

Useful commands:

```!bash
#!/bin/bash
#sed split long word at capitals
echo "FreakingHeckStuffREALLY" | sed 's/\([^[:blank:]]\)\([[:upper:]]\)/\1 \2/g'
#Result:
#Freaking Heck Stuff RE AL LY
```
# Get all Firmware versions from dumped configs:
```!bash
while IFS= read -r line
do
  echo $line; 
  jq '.tasmotas[]' -c < $HOME/Downloads/2021-09-19-tasmota-information.json | \
    grep "\"$line\"" | \
    jq '."Status 0".StatusFWR' -c
done < <(cat $HOME/Downloads/2021-09-19-tasmota-information.json | jq '.tasmotas[]."Status 0".StatusNET.IPAddress' -cr)
```

```!bash
#Check for machine stuck on minimal firmware
for n in $(cat $HOME/Downloads/2021-09-19-tasmota-information.json | jq '.tasmotas[]."Status 0".StatusNET.IPAddress' -cr)
do
    echo -e "$n\r"; 
    curl -s http://$n | grep "MINIMAL firmware"
done
```

# Firmware updates via hosted firmeware files
Backlog OtaUrl http://10.2.2.4/tasmota-minimal.bin.gz;

```!bash
# current method of firmware
# sudo cp python-firmware-webserver.service /etc/systemd/system/python-firmware-webserver.service
# sudo systemctl daemon-reload
# sudo systemctl enable python-firmware-webserver.service
# sudo systemctl start python-firmware-webserver.service


for ip in $(cat $HOME/Downloads/2021-09-19-tasmota-information.json | jq '.tasmotas[]."Status 0".StatusNET.IPAddress' -cr)
do
  jqstr=".tasmotas.\"$ip\" | . += {\"IP\": \"$ip\"}"
  devicedata=$(jq $jqstr -c < $HOME/repo/homeassistant/tasmota-declared-config.json)

  ####
  # check what the defined otaURL is expected to be.  Uncomment the curl if you want to actually update.
  ####

  standardstring="http://10.2.2.4:2020/tasmota.bin.gz"
  if [[ $(echo $devicedata | jq -r '.OtaUrl') == $standardstring ]] 
  then
    echo $devicedata | jq '. | {IP, OtaUrl}' -c
    # curl "http://$ip/u1?o=http%3A%2F%2F10.2.2.4%3A2020%2Ftasmota.bin.gz"
  fi

  sensorstring="http://10.2.2.4:2020/tasmota-sensors.bin.gz"
  if [[ $(echo $devicedata | jq -r '.OtaUrl') == $sensorstring ]] 
  then
    echo $devicedata | jq '. | {IP, OtaUrl}' -c
    # curl "http://$ip/u1?o=http%3A%2F%2F10.2.2.4%3A2020%2Ftasmota-minimal.bin.gz"
    # curl "http://$ip/u1?o=http%3A%2F%2F10.2.2.4%3A2020%2Ftasmota-sensors.bin.gz"
  fi
done
```



# !!!!! REMEMBER TO RESET COUNTERS _AND_ TIMERS ON W-US002S MODULES !!!!!
# Energy Counter Reset on all sensor based devices
```!bash
for ip in $(jq -c '.tasmotas[]' < $HOME/Downloads/2021-09-22-tasmota-information.json | grep "(sensors)" | jq -rc '."Status 0".StatusNET.IPAddress');
do
curl "http://$ip/cm?cmnd=energyreset%200" -s | jq -c .
curl "http://$ip/cm?cmnd=energyreset2%200" -s | jq -c .
curl "http://$ip/cm?cmnd=energyreset3%200" -s | jq -c .
done
```

# Mass Reboots
```!bash
for ip in $(jq -c '.tasmotas[]' < $HOME/Downloads/2021-09-22-tasmota-information.json | jq -rc '."Status 0".StatusNET.IPAddress');
do
  curl "http://$n/cm?cmnd=restart%201" -s | jq .
done
```

# Sorting for easier differentials
  jq --sort-keys '.' < $repopath/homeassistant/tasmota-declared-config3.json > $repopath/homeassistant/tasmota-declared-config-sorted3.json
  jq --sort-keys '.' < $HOME/Downloads/2021-10-04-tasmota-information.json > $HOME/Downloads/2021-10-04-tasmota-information-sorted.json
  jq --sort-keys '.' < $repopath/homeassistant/tasmota-declared-config.json > $repopath/homeassistant/tasmota-declared-config-sorted.json
  jq --sort-keys '.' < $HOME/Downloads/2021-10-19-tasmota-information.json > $HOME/Downloads/2021-10-19-tasmota-information-sorted.json
