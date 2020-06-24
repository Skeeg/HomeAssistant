# This basically tells the device that it does have a Relay so that it will accept power on commands 
# This enables the LED, but it sends 5v to the wrong (dead end) GPIO,
# which doesn't engage the mechanical relay

# Control Device Template:
`{"NAME":"Gosund KS-602S","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}`

# Send the voltage to the right GPIO
# Active Device Template:
`backlog template {"NAME":"Gosund KS-602S","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0;`

# Maxcio Power Switch
`backlog template {"NAME":"W-US002S","GPIO":[0,90,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0;`

Then have to run https://tasmota.github.io/docs/Power-Monitoring-Calibration/ process in console.
Get values from the Kill-A-Watt device

`PowerSet 60.0`
`VoltageSet 115`
`CurrentSet 500`

#######################
# From the Command Line

From https://tasmota.github.io/docs/Buttons-and-Switches/#button

# Rule Enablement for Multi switch control.  
# Disables the button from turning on the relay directly and instead sends the command to the MQTT
# server to set the state for all of the paired group switches.
`Rule1 on Switch1#state do Publish homeassistant/cmnd/EntryCansGroup/POWER %value% endon`
`Rule1 1`

```!bash
cat << EOF > ./iplist.txt
10.2.4.13
10.2.4.14
10.2.4.16
10.2.4.17
10.2.4.18
10.2.4.19
10.2.4.20
10.2.4.21
10.2.4.22
10.2.4.23
10.2.4.24
10.2.4.26
10.2.4.27
10.2.4.28
10.2.4.29
10.2.4.30
10.2.4.31
10.2.4.32
10.2.4.33
10.2.4.34
10.2.4.35
10.2.4.36
10.2.4.37
10.2.4.38
10.2.4.39
10.2.4.40
10.2.4.41
10.2.4.42
10.2.4.43
10.2.4.44
10.2.4.45
10.2.4.46
10.2.4.47
10.2.4.48
10.2.4.49
10.2.4.50
10.2.4.51
10.2.4.52
10.2.4.53
10.2.4.54
10.2.4.55
10.2.4.56
10.2.4.57
10.2.4.58
10.2.4.59
10.2.4.60
10.2.4.61
10.2.4.62
10.2.4.63
10.2.4.64
10.2.4.65
10.2.4.66
10.2.4.67
10.2.4.68
10.2.4.69
10.2.4.70
10.2.4.71
10.2.4.72
10.2.4.73
EOF

#Get separated data with IP address
for n in $(cat ./iplist.txt)
do
    echo -e "$n\r"
    curl "http://$n/cm?cmnd=hostname";
    echo -e '\r'
    curl "http://$n/cm?cmnd=grouptopic"
    echo -e '\r'
    echo -e '\r'
done

#Check inline data without IP Address
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=grouptopic"
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=hostname";
    echo -e '\r'
done

#Check setoption
for n in $(cat ./iplist.txt)
do
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=setoption19";
    curl "http://$n/cm?cmnd=devicename";
    echo -e '\r'
done

#Check inline data without IP Address
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=topic"
    echo -e '\r'
done


for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=sleep%20200"
    curl "http://$n/cm?cmnd=powerretain%200"
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=hostname";
    echo -e '\r'
done

for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=friendlyname1"
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=hostname";
    echo -e '\r'
done


do
    curl "http://$n/cm?cmnd=friendlyname1" -s | jq --raw-output .FriendlyName1 | sed 's/\([^[:blank:]]\)\([[:upper:]]\)/\1 \2/g';
    printf '{"IPAddress":"'$n'"}' | jq --raw-output .IPAddress
    m=$(curl "http://$n/cm?cmnd=hostname" -s | jq --raw-output .Hostname | sed 's/\([^[:blank:]]\)\([[:upper:]]\)/\1 \2/g';); echo $m; echo $n; echo $m;
    echo -e '\r'
done

for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=devicename" -s | jq --raw-output .DeviceName;
    curl "http://$n/cm?cmnd=friendlyname" -s | jq --raw-output .FriendlyName1;
    printf '{"IPAddress":"'$n'"}' | jq --raw-output .IPAddress
    m=$(curl "http://$n/cm?cmnd=hostname" -s | jq --raw-output .Hostname | sed 's/\([^[:blank:]]\)\([[:upper:]]\)/\1%20\2/g';);
    echo $m;
done

for n in $(cat ./iplist.txt)
do
    unset m
    m=$(curl -m 2 "http://$n/cm?cmnd=hostname" -s | jq --raw-output .Hostname | sed 's/\([^[:blank:]]\)\([[:upper:]]\)/\1%20\2/g';);
    if [ -z $m ];
        then echo "var failed for $n";
        else curl "http://$n/cm?cmnd=friendlyname1%20$m";
    fi
done

#Disable Autodiscover
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=setoption19%200"
    printf '{"IPAddress":"'$n'"}' | jq .;
    curl "http://$n/cm?cmnd=hostname" -s | jq .;
    curl "http://$n/cm?cmnd=friendlyname1" -s | jq .;
    echo -e '\r'
done

#Enable Autodiscover
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=setoption19%201"
    printf '{"IPAddress":"'$n'"}' | jq .;
    curl "http://$n/cm?cmnd=hostname" -s | jq .;
    curl "http://$n/cm?cmnd=friendlyname1" -s | jq .;
    echo -e '\r'
done


#Wipe Wifi Calibration, Counters, and Bootcount
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=hostname"
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=friendlyname1"
    curl "http://$n/cm?cmnd=backlog%20reset%203%3B%20reset%2099%3B"
    echo -e '\r'
done


#Roll all devices firmware
for n in $(cat ./iplist.txt)
do
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=hostname";
    echo -e '\r\r\r'
    echo -e "Starting Minimal for $n\r"
    curl -F 'u2=@/Users/ryan-peay/Downloads/skg-tasmota-minimal.bin' http://$n/u2 -o /Users/ryan-peay/Downloads/firmware/$n.minimal.txt
    echo -e '\r\r\r'
    echo -e "Sleep 15\r"
    sleep 15
    echo -e "Starting Standard for $n\r"
    curl -F 'u2=@/Users/ryan-peay/Downloads/skg-tasmota.bin' http://$n/u2 -o /Users/ryan-peay/Downloads/firmware/$n.standard.txt
    echo -e "Done with $n\r\r\r"
done

#Check for machine stuck on minimal firmware
for n in $(cat ./iplist.txt)
do
    echo -e "$n\r"; 
    curl -s http://$n | grep "MINIMAL firmware"
done

#Check for machine stuck on minimal firmware
for n in $(cat ./iplist.txt)
do
    echo -e "$n\r"; 
    curl -s http://$n | grep "MINIMAL firmware"
done

#Just Minimal Firmware
for n in $(cat ./iplist.txt)
do
    printf '{"IPAddress":"'$n'"}'
    echo -e "\rStarting Minimal for $n\r"
    curl -F 'u2=@/Users/ryan-peay/Downloads/skg-tasmota-minimal.bin' http://$n/u2 -o /Users/ryan-peay/Downloads/firmware/$n.standard.txt
    echo -e "Done with $n\r\r\r"
done

#Just Standard Firmware
for n in $(cat ./iplist.txt)
do
    printf '{"IPAddress":"'$n'"}'
    echo -e "\rStarting Standard for $n\r"
    curl -F 'u2=@/Users/ryan-peay/Downloads/skg-tasmota.bin' http://$n/u2 -o /Users/ryan-peay/Downloads/firmware/$n.standard.txt
    echo -e "Done with $n\r\r\r"
done

rm -f iplist.txt
```

Temp Config Maxcio

Backlog hostname TempConfig; DeviceName TempConfig; topic TempConfig; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/TempConfig/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0;

Temp Config Gosund

Backlog hostname TempConfig; DeviceName TempConfig; topic TempConfig; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/TempConfig/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;


10.2.4.11
#TestTuya - Needs to be programmed
`Backlog hostname TestTuya; DeviceName TestTuya; topic TestTuya; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/TestTuya/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`


10.2.4.13
{"Hostname":"FamilyLights"}
`Backlog hostname FamilyLights; DeviceName FamilyLights; topic FamilyLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/FamilyLights/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18} module 0; powerretain 0;`

10.2.4.14
{"Hostname":"FamilyFan"}
`Backlog hostname FamilyFan; DeviceName FamilyFan; topic FamilyFan; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorFans; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/FamilyFan/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18} module 0; powerretain 0;`

10.2.4.17
{"Hostname":"EntryCans_C1"}
`Backlog hostname EntryCans_C1; DeviceName EntryCans_C1; topic EntryCans_C1; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 EntryCansGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/EntryCansGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.18
{"Hostname":"EntryCans"}
`Backlog hostname EntryCans; DeviceName EntryCans; topic EntryCans; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 EntryCansGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/EntryCansGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.19
{"Hostname":"EntryCans_C2"}
`Backlog hostname EntryCans_C2; DeviceName EntryCans_C2; topic EntryCans_C2; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 EntryCansGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/EntryCansGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.22
{"Hostname":"DadsLights"}
`Backlog hostname DadsLights; DeviceName DadsLights; topic DadsLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/DadsLights/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.24
{"Hostname":"PorchLights"}
`Backlog hostname PorchLights; DeviceName PorchLights; topic PorchLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 ExteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/PorchLights/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.28
{"Hostname":"MainHall_C1"}
`Backlog hostname MainHall_C1; DeviceName MainHall_C1; topic MainHall_C1; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 MainHallGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/MainHallGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.29
{"Hostname":"MainHall"}
`Backlog hostname MainHall; DeviceName MainHall; topic MainHall; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 MainHallGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/MainHallGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.30
{"Hostname":"MainHall_C2"}
`Backlog hostname MainHall_C2; DeviceName MainHall_C2; topic MainHall_C2; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 MainHallGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/MainHallGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.31
{"Hostname":"KitchenCans"}
`Backlog hostname KitchenCans; DeviceName KitchenCans; topic KitchenCans; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 KitchenCansGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/KitchenCansGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.32
{"Hostname":"KitchenSink"}
`Backlog hostname KitchenSink; DeviceName KitchenSink; topic KitchenSink; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 KitchenSinkGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/KitchenSinkGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.33
{"Hostname":"KitchenSink_C1"}
`Backlog hostname KitchenSink_C1; DeviceName KitchenSink_C1; topic KitchenSink_C1; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 KitchenSinkGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/KitchenSinkGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.34
{"Hostname":"KitchenCans_C1"}
`Backlog hostname KitchenCans_C1; DeviceName KitchenCans_C1; topic KitchenCans_C1; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 KitchenCansGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/KitchenCansGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.35
{"Hostname":"PowderHall"}
`Backlog hostname PowderHall; DeviceName PowderHall; topic PowderHall; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/PowderHall/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.36
{"Hostname":"StudyLights"}
`Backlog hostname StudyLights; DeviceName StudyLights; topic StudyLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 StudyLightsGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/StudyLightsGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.37
{"Hostname":"LibraryLights"}
`Backlog hostname LibraryLights; DeviceName LibraryLights; topic LibraryLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/LibraryLights/POWER %value% endon; Rule1 1; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.39
{"Hostname":"Blower"}
`Backlog hostname Blower; DeviceName Blower; topic Blower; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/Blower/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.40
{"Hostname":"CurtainLights"}
`Backlog hostname CurtainLights; DeviceName CurtainLights; topic CurtainLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/CurtainLights/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45} module 0; powerretain 0; sensorretain 1;`

10.2.4.41
{"Hostname":"EveLights"}
`Backlog hostname EveLights; DeviceName EveLights; topic EveLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 ExteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/EveLights/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.42
{"Hostname":"PowderFan"}
`Backlog hostname PowderFan; DeviceName PowderFan; topic PowderFan; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorFans; grouptopic3 BathroomFans; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/PowderFan/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.43
{"Hostname":"StudyFan"}
`Backlog hostname StudyFan; DeviceName StudyFan; topic StudyFan; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 StudyLightsGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/StudyLightsGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Control","GPIO":[9,0,0,0,0,0,0,0,0,56,0,0,21],"FLAG":0,"BASE":18}; module 0; powerretain 0;`


10.2.4.44
{"Hostname":"PowderLights"}
`Backlog hostname PowderLights; DeviceName PowderLights; topic PowderLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/PowderLights/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.45
{"Hostname":"RailingLights"}
`Backlog hostname RailingLights; DeviceName RailingLights; topic RailingLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/RailingLights/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1`


10.2.4.46
#DadsLamp
`Backlog hostname DadsLamp; DeviceName DadsLamp; topic DadsLamp; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/DadsLamp/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0;`


10.2.4.47
{"Hostname":"ChristmasPackage"}
`Backlog hostname ChristmasPackage; DeviceName ChristmasPackage; topic ChristmasPackage; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 ExteriorDecorations; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ChristmasPackage/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.48
{"Hostname":"BasementLights"}
`Backlog hostname BasementLights; DeviceName BasementLights; topic BasementLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/BasementLights/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

#GarageLamp
10.2.4.49
`Backlog hostname GarageLamp; DeviceName GarageLamp; topic GarageLamp; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 GarageLightsGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/GarageLamp/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sleep 75;`

10.2.4.50
`Backlog hostname DiningLights; DeviceName DiningLights; topic DiningLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/DiningLights/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18} module 0; powerretain 0; sleep 75;`

10.2.4.51
`Backlog hostname PatioLights; DeviceName PatioLights; topic PatioLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 ExteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/PatioLights/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18} module 0; powerretain 0; sleep 75;`

10.2.4.52
`Backlog hostname GarageLights; DeviceName GarageLights; topic GarageLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 GarageLightsGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/GarageLightsGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0; sleep 75;`

10.2.4.53
`Backlog hostname ExteriorGarageLights; DeviceName ExteriorGarageLights; topic ExteriorGarageLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 ExteriorFrontLights; grouptopic3 ExteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ExteriorFrontLights/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18} module 0; powerretain 0; sleep 75;`

10.2.4.54
`Backlog hostname KidsBathroomFan; DeviceName KidsBathroomFan; topic KidsBathroomFan; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorFans; grouptopic3 BathroomFans; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/KidsBathroomFan/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.55
{"Hostname":"BuffetDecor"}
`Backlog hostname BuffetDecor; DeviceName BuffetDecor; topic BuffetDecor; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/BuffetDecor/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.56
{"Hostname":"HotTub"}
`Backlog hostname HotTub; DeviceName HotTub; topic HotTub; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/HotTub/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.57
{"Hostname":"ElectricFence"}
`Backlog hostname ElectricFence; DeviceName ElectricFence; topic ElectricFence; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ElectricFence/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.38
{"Hostname":"ComputerAustin"}
`Backlog hostname ComputerAustin; DeviceName ComputerAustin; topic ComputerAustin; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ComputerAustin/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.58
{"Hostname":"ComputerLily"}
`Backlog hostname ComputerLily; DeviceName ComputerLily; topic ComputerLily; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ComputerLily/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.59
{"Hostname":"MainTV"}
`Backlog hostname MainTV; DeviceName MainTV; topic MainTV; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/MainTV/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.60
{"Hostname":"MantleDecor"}
`Backlog hostname MantleDecor; DeviceName MantleDecor; topic MantleDecor; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/MantleDecor/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.61
{"Hostname":"MasterTV"}
`Backlog hostname MasterTV; DeviceName MasterTV; topic MasterTV; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/MasterTV/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1; setoption19 1;`

10.2.4.62
{"Hostname":"ComputerServer"}
`Backlog hostname ComputerServer; DeviceName ComputerServer; topic ComputerServer; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ComputerServer/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.63
{"Hostname":"ComputerMedia"}
`Backlog hostname ComputerMedia; DeviceName ComputerMedia; topic ComputerMedia; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ComputerMedia/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.64
{"Hostname":"LilyFan"}
`Backlog hostname LilyFan; DeviceName LilyFan; topic LilyFan; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/LilyFan/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`


10.2.4.65
{"Hostname":"Spare1"}
`Backlog hostname Spare1; DeviceName Spare1; topic Spare1; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/Spare1/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.66
{"Hostname":"FirePlace"}
`Backlog hostname FirePlace; DeviceName FirePlace; topic FirePlace; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/FirePlace/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.67
{"Hostname":"ExteriorSide"}
`Backlog hostname ExteriorSide; DeviceName ExteriorSide; topic ExteriorSide; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 ExteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ExteriorSide/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0; sleep 75;`

10.2.4.68
{"Hostname":"GarageLights_C1"}
`Backlog hostname GarageLights_C1; DeviceName GarageLights_C1; topic GarageLights_C1; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 GarageLightsGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/GarageLightsGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0; sleep 75;`

10.2.4.69
{"Hostname":"PetLights"}
`Backlog hostname PetLights; DeviceName PetLights; topic PetLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/PetLights/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.70
{"Hostname":"Spare2"}
`Backlog hostname Spare2; DeviceName Spare2; topic Spare2; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/Spare2/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.71
{"Hostname":"Spare3"}
`Backlog hostname Spare3; DeviceName Spare3; topic Spare3; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/Spare3/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.72
KidsToilet
`Backlog hostname KidsToilet; DeviceName KidsToilet; topic KidsToilet; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/KidsToilet/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0; setoption19 1;`

10.2.4.73
KidsShower
`Backlog hostname KidsShower; DeviceName KidsShower; topic KidsShower; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/KidsShower/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0; setoption19 1;`

10.2.4.20
KidsSink
`Backlog hostname KidsSink; DeviceName KidsSink; topic KidsSink; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/KidsSink/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0; setoption19 1;`

10.2.4.16
LilyHall
`Backlog hostname LilyHall; DeviceName LilyHall; topic LilyHall; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 LilyHallGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/LilyHallGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0; setoption19 1;`

10.2.4.21
AustinHall
`Backlog hostname AustinHall; DeviceName AustinHall; topic AustinHall; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 AustinHallGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/AustinHallGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0; setoption19 1;`

10.2.4.23
LilyHall_c1
`Backlog hostname LilyHall_C1; DeviceName LilyHall_C1; topic LilyHall_C1; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 LilyHallGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/LilyHallGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0; powerretain 0; setoption19 1;`

10.2.4.26
AustinHall_c1
`Backlog hostname AustinHall_C1; DeviceName AustinHall_C1; topic AustinHall_C1; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 AustinHallGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/AustinHallGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0; powerretain 0; setoption19 1;`

10.2.4.27
LilyHall_c2
`Backlog hostname LilyHall_C2; DeviceName LilyHall_C2; topic LilyHall_C2; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; grouptopic3 LilyHallGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/LilyHallGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}; module 0; powerretain 0; setoption19 1;`

10.2.4.25 - DEAD
{"Hostname":"EntryChandelier"}
`Backlog hostname EntryChandelier; DeviceName EntryChandelier; topic EntryChandelier; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/EntryChandelier/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0; setoption19 1;`
