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

# Sonoff Power Switch
`backlog template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0;`

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
10.2.4.65
10.2.4.66
10.2.4.67
10.2.4.68
10.2.4.69
10.2.4.70
10.2.4.71
10.2.4.72
10.2.4.73
10.2.4.83
10.2.4.89
10.2.4.90
10.2.4.91
10.2.4.92
10.2.4.93
10.2.4.96
10.2.4.97
10.2.4.98
10.2.4.99
10.2.4.100
10.2.4.101
10.2.4.102
10.2.4.103
10.2.4.104
10.2.4.105
10.2.4.109
10.2.4.111
EOF
```

```!bash
#!/bin/bash
#Add IP Address to json payload, then create CSV with IP address and DeviceName
for n in $(cat ./iplist.txt)
do
    moduleName=`curl "http://$n/cm?cmnd=module" -s | jq .Module.\"0\"`
    curl "http://$n/cm?cmnd=status%200" -s |\
        jq --raw-output ". += {"Module": $moduleName} | [.StatusNET.IPAddress, .Status.DeviceName, (\"Module:\" + (.Status.Module|tostring)), .Module] | @csv"
done
```

```!bash
#!/bin/bash
for n in $(cat ./badiplist.txt)
do
    printf "%s" "waiting for $n ..."
    while ! timeout 0.2 ping -c 1 -n $n &> /dev/null
    do
        printf "%c" "."
    done
    moduleName=`curl "http://$n/cm?cmnd=module" -s | jq .Module.\"0\"`
    curl "http://$n/cm?cmnd=status%200" -s |\
        jq --raw-output ". += {"Module": $moduleName} | [.StatusNET.IPAddress, .Status.DeviceName, (\"Module:\" + (.Status.Module|tostring)), .Module] | @csv"
done
```


```!bash
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
```

```!bash
#Check inline data without IP Address
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=grouptopic"
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=hostname";
    echo -e '\r'
done
```

```!bash
#Check setoption
for n in $(cat ./iplist.txt)
do
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=setoption19";
    curl "http://$n/cm?cmnd=devicename";
    echo -e '\r'
done
```

```!bash
#Check inline data without IP Address
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=topic"
    echo -e '\r'
done
```

```!bash
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=sleep%20200"
    curl "http://$n/cm?cmnd=powerretain%200"
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=hostname";
    echo -e '\r'
done
```

```!bash
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=friendlyname1"
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=hostname";
    echo -e '\r'
done
```

```!bash
do
    curl "http://$n/cm?cmnd=friendlyname1" -s | \
      jq --raw-output .FriendlyName1 | sed 's/\([^[:blank:]]\)\([[:upper:]]\)/\1 \2/g';
    printf '{"IPAddress":"'$n'"}' | jq --raw-output .IPAddress
    m=$(curl "http://$n/cm?cmnd=hostname" -s \
      | jq --raw-output .Hostname | \
      sed 's/\([^[:blank:]]\)\([[:upper:]]\)/\1 \2/g';);
      echo $m; echo $n; echo $m;
    echo -e '\r'
done
```

```!bash
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=devicename" -s | jq --raw-output .DeviceName;
    curl "http://$n/cm?cmnd=friendlyname" -s | jq --raw-output .FriendlyName1;
    printf '{"IPAddress":"'$n'"}' | jq --raw-output .IPAddress
    m=$(curl "http://$n/cm?cmnd=hostname" -s | \
      jq --raw-output .Hostname \
      | sed 's/\([^[:blank:]]\)\([[:upper:]]\)/\1%20\2/g';);
    echo $m;
done
```

```!bash
for n in $(cat ./iplist.txt)
do
    unset m
    m=$(curl -m 2 "http://$n/cm?cmnd=hostname" -s | \
      jq --raw-output .Hostname | \
      sed 's/\([^[:blank:]]\)\([[:upper:]]\)/\1%20\2/g';);
    if [ -z $m ];
        then echo "var failed for $n";
        else curl "http://$n/cm?cmnd=friendlyname1%20$m";
    fi
done
```

```!bash
#Get rules
for n in $(cat ./iplist.txt)
do
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=rule1" -s | jq -c '[.Rule1,.Rules]'
done
```

```!bash
#Disable Autodiscover
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=setoption19%200"
    printf '{"IPAddress":"'$n'"}' | jq .;
    curl "http://$n/cm?cmnd=hostname" -s | jq .;
    curl "http://$n/cm?cmnd=friendlyname1" -s | jq .;
    echo -e '\r'
done
```

```!bash
#Enable Autodiscover
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=setoption19%201"
    printf '{"IPAddress":"'$n'"}' | jq .;
    curl "http://$n/cm?cmnd=hostname" -s | jq .;
    curl "http://$n/cm?cmnd=friendlyname1" -s | jq .;
    echo -e '\r'
done
```

```!bash
#Wipe Wifi Calibration, Counters, and Bootcount
for n in $(cat ./iplist.txt)
do
    curl "http://$n/cm?cmnd=hostname"
    printf '{"IPAddress":"'$n'"}'
    curl "http://$n/cm?cmnd=friendlyname1"
    curl "http://$n/cm?cmnd=backlog%20reset%203%3B%20reset%2099%3B"
    echo -e '\r'
done
```

```!bash
#Roll all devices firmware - use alternate shell script file
# for n in $(cat ./iplist.txt)
# do
#     printf '{"IPAddress":"'$n'"}'
#     curl "http://$n/cm?cmnd=hostname";
#     echo -e '\r\r\r'
#     echo -e "Starting Minimal for $n\r"
#     curl -F 'u2=@/Users/ryan-peay/Downloads/skg-tasmota-minimal.bin' \
#       http://$n/u2 -o /Users/ryan-peay/Downloads/firmware/$n.minimal.txt
#     echo -e '\r\r\r'
#     echo -e "Sleep 15\r"
#     sleep 15
#     echo -e "Starting Standard for $n\r"
#     curl -F 'u2=@/Users/ryan-peay/Downloads/skg-tasmota.bin' \
 #       http://$n/u2 -o /Users/ryan-peay/Downloads/firmware/$n.standard.txt
#     echo -e "Done with $n\r\r\r"
# done
```

```!bash
#Check for machine stuck on minimal firmware
for n in $(cat ./iplist.txt)
do
    echo -e "$n\r"; 
    curl -s http://$n | grep "MINIMAL firmware"
done
```

```!bash
#Check for machine stuck on minimal firmware
for n in $(cat ./iplist.txt)
do
    echo -e "$n\r"; 
    curl -s http://$n | grep "MINIMAL firmware"
done
```

```!bash
#Just Minimal Firmware
for n in $(cat ./iplist.txt)
do
    printf '{"IPAddress":"'$n'"}'
    echo -e "\rStarting Minimal for $n\r"
    curl -F 'u2=@/Users/ryan-peay/Downloads/skg-tasmota-minimal.bin' \
      http://$n/u2 -o /Users/ryan-peay/Downloads/firmware/$n.standard.txt
    echo -e "Done with $n\r\r\r"
done
```

```!bash
#Just Standard Firmware
for n in $(cat ./iplist.txt)
do
    printf '{"IPAddress":"'$n'"}'
    echo -e "\rStarting Standard for $n\r"
    curl -F 'u2=@/Users/ryan-peay/Downloads/skg-tasmota.bin' \
      http://$n/u2 -o /Users/ryan-peay/Downloads/firmware/$n.standard.txt
    echo -e "Done with $n\r\r\r"
done
```

```!bash
#Roll to new skeeg-v2 firmware
for n in $(cat ./iplist.txt)
for n in $(echo "10.2.4.14 10.2.4.15")
do
    printf '{"IPAddress":"'$n'"}'
    echo -e "\rStarting v2 for $n\r"
    curl -F 'u2=@/Users/ryan-peay/Downloads/tasmota 9.1.0/skeeg-v2/tasmota.bin.gz' \
      http://$n/u2 -o /Users/ryan-peay/Downloads/tasmota\ 9.1.0/skeeg-v2//$n.txt
    echo -e "Done with $n\r\r\r"
done


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

10.2.4.47
{"Hostname":"ChristmasPackage"}
`Backlog hostname ChristmasPackage; DeviceName ChristmasPackage; topic ChristmasPackage; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 ExteriorDecorations; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ChristmasPackage/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

10.2.4.48
{"Hostname":"BasementLights"}
`Backlog hostname BasementLights; DeviceName BasementLights; topic BasementLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/BasementLights/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[9,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 0;`

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

10.2.4.38
{"Hostname":"ComputerAustin"}
`Backlog hostname ComputerAustin; DeviceName ComputerAustin; topic ComputerAustin; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ComputerAustin/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.58
{"Hostname":"ComputerLily"}
`Backlog hostname ComputerLily; DeviceName ComputerLily; topic ComputerLily; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ComputerLily/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.59
{"Hostname":"MainTV"}
`Backlog hostname MainTV; DeviceName MainTV; topic MainTV; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/MainTV/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

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

10.2.4.83
{"Hostname":"EntryChandelier"}
`Backlog hostname EntryChandelier; DeviceName EntryChandelier; topic EntryChandelier; friendlyname Entry Chandelier; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights;  setoption19 1;`

Mass Flash:
`Backlog fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/%topic%/POWER %value% endon; Rule1 0; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}; module 0; powerretain 0;`


backlog grouptopic AllStandard; grouptopic2 InteriorDecorations; Timer1 {"Arm":1,"Mode":0,"Time":"07:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":1}; Timer2 {"Arm":1,"Mode":0,"Time":"23:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":0};


Mass Sonoff
`backlog hostname replace; DeviceName replace; topic replace; friendlyname replace; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1; Timer1 {"Arm":1,"Mode":0,"Time":"07:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":1}; Timer2 {"Arm":1,"Mode":0,"Time":"23:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":0};`

backlog hostname EndTable; DeviceName EndTable; topic EndTable; friendlyname End Table; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1; Timer1 {"Arm":1,"Mode":0,"Time":"07:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":1}; Timer2 {"Arm":1,"Mode":0,"Time":"23:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":0};

backlog hostname KitchenTable; DeviceName KitchenTable; topic KitchenTable; friendlyname Kitchen Table; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1; Timer1 {"Arm":1,"Mode":0,"Time":"07:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":1}; Timer2 {"Arm":1,"Mode":0,"Time":"23:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":0};

backlog hostname ChristmasRailing; DeviceName ChristmasRailing; topic ChristmasRailing; friendlyname Christmas Railing; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1; Timer1 {"Arm":1,"Mode":0,"Time":"07:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":1}; Timer2 {"Arm":1,"Mode":0,"Time":"23:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":0};

backlog hostname IslandDecorations; DeviceName IslandDecorations; topic IslandDecorations; friendlyname Island Decorations; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1; Timer1 {"Arm":1,"Mode":0,"Time":"07:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":1}; Timer2 {"Arm":1,"Mode":0,"Time":"23:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":0}; Timers 1;


10.2.4.96
backlog hostname MediaRemote; DeviceName MediaRemote; topic MediaRemote; friendlyname Media Remote; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"NodeMCU","GPIO":[255,255,255,255,255,255,255,255,255,255,255,255,255],"FLAG":15,"BASE":18}; module 0; setoption19 1;

10.2.4.109
backlog hostname DadsTest; DeviceName DadsTest; topic DadsTest; friendlyname Dads Test; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"WemoD1Mini","GPIO":[255,255,255,255,255,255,255,255,255,255,255,255,255],"FLAG":15,"BASE":18}; module 0; setoption19 1;

10.2.4.110
backlog hostname Test2; DeviceName Test2; topic Test2; friendlyname Test2; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"WemoD1Mini","GPIO":[255,255,255,255,255,255,255,255,255,255,255,255,255],"FLAG":15,"BASE":18}; module 0;

backlog Timer1 {"Arm":1,"Mode":0,"Time":"07:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":1}; Timer2 {"Arm":1,"Mode":0,"Time":"23:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":0}; Timers 1;


SomethingNothingSomething
backlog hostname replace; DeviceName replace; topic replace; friendlyname replace; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1; Timer1 {"Arm":1,"Mode":0,"Time":"07:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":1}; Timer2 {"Arm":1,"Mode":0,"Time":"23:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":0}; Timers 1;


backlog setoption19 0; EnergyReset3 0; hostname GroundDecor; DeviceName GroundDecor; topic GroundDecor; friendlyname Ground Decor; setoption19 1;
backlog setoption19 0; EnergyReset3 0; hostname TopChristmas; DeviceName TopChristmas; topic TopChristmas; friendlyname Top Christmas; setoption19 1;
backlog setoption19 0; EnergyReset3 0; hostname BottomChristmas; DeviceName BottomChristmas; topic BottomChristmas; friendlyname Bottom Christmas; setoption19 1;





#OldFirePlace
10.2.4.66
{"Hostname":"FirePlace"}
`Backlog hostname FirePlace; DeviceName FirePlace; topic FirePlace; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/FirePlace/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.103
{"Hostname":"FirePlace"}
`Backlog seriallog 0; setoption19 0; hostname FirePlace; DeviceName FirePlace; topic FirePlace; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; switchmode 3; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;`


#Clear grouptopics
grouptopic 0; 

#OldBlower
10.2.4.39
{"Hostname":"Blower"}
`Backlog hostname Blower; DeviceName Blower; topic Blower; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/Blower/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`


10.2.4.104
{"Hostname":"Blower"}
`Backlog seriallog 0; setoption19 0; hostname Blower; DeviceName Blower; topic Blower; fulltopic homeassistant/%prefix%/%topic%/; grouptopic1 0; switchmode 3; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;`


#OldGarageLamp
10.2.4.49
`Backlog hostname GarageLamp; DeviceName GarageLamp; topic GarageLamp; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 GarageLightsGroup; switchmode 3; latitude 40.297297; longitude -111.878340; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sleep 75;`


10.2.4.102
backlog seriallog 0; setoption19 0; hostname GarageLamp; DeviceName GarageLamp; topic GarageLamp; friendlyname Garage Lamp; grouptopic AllStandard; grouptopic2 GarageLightsGroup; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff+I2C","GPIO":[17,5,0,6,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;

#OldCurtainLights
10.2.4.40
{"Hostname":"CurtainLights"}
`Backlog hostname CurtainLights; DeviceName CurtainLights; topic CurtainLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/CurtainLights/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45} module 0; powerretain 0; sensorretain 1;`

10.2.4.101
backlog seriallog 0; setoption19 0; hostname CurtainLights; DeviceName CurtainLights; topic CurtainLights; friendlyname Curtain Lights; grouptopic AllStandard; grouptopic2 InteriorDecorations; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1};; module 0; setoption19 1;

#OldBuffet
10.2.4.55
{"Hostname":"BuffetDecor"}
`Backlog hostname BuffetDecor; DeviceName BuffetDecor; topic BuffetDecor; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/BuffetDecor/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

10.2.4.98
backlog seriallog 0; setoption19 0; hostname BuffetDecor; DeviceName BuffetDecor; topic BuffetDecor; friendlyname Buffet Decor; grouptopic AllStandard; grouptopic2 InteriorDecorations; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;

#OldMantle
10.2.4.70
backlog setoption19 0; EnergyReset3 0; hostname LeftMantle; DeviceName LeftMantle; topic LeftMantle; friendlyname Left Mantle; setoption19 1;

10.2.4.105
backlog seriallog 0; setoption19 0; hostname LeftMantle; DeviceName LeftMantle; topic LeftMantle; friendlyname Left Mantle; grouptopic AllStandard; grouptopic2 InteriorDecorations; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;

#OldEntryDecor
10.2.4.71
backlog setoption19 0; EnergyReset3 0; hostname EntryDecorations; DeviceName EntryDecorations; topic EntryDecorations; friendlyname EntryDecorations; setoption19 1;

10.2.4.99
backlog seriallog 0; setoption19 0; hostname EntryDecorations; DeviceName EntryDecorations; topic EntryDecorations; friendlyname Entry Decorations; grouptopic AllStandard; grouptopic2 InteriorDecorations; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;

#FrontTree
10.2.4.65
backlog setoption19 0; EnergyReset3 0; hostname FrontTree; DeviceName FrontTree; topic FrontTree; friendlyname Front Tree; setoption19 1;

10.2.4.111
backlog seriallog 0; setoption19 0; hostname FrontTree; DeviceName FrontTree; topic FrontTree; friendlyname Front Tree; grouptopic AllStandard; grouptopic2 InteriorDecorations; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;

#OldRailingLights
10.2.4.45
{"Hostname":"RailingLights"}
`Backlog hostname RailingLights; DeviceName RailingLights; topic RailingLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorDecorations; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/RailingLights/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1`

10.2.4.100
backlog seriallog 0; setoption19 0; hostname RailingLights; DeviceName RailingLights; topic RailingLights; friendlyname Railing Lights; grouptopic AllStandard; grouptopic2 InteriorDecorations; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;


#NewHotTub
10.2.4.71
Backlog timers 0; timer1 0; timer2 0; EnergyReset3 0; hostname HotTub; DeviceName HotTub; friendlyname Hot Tub; topic HotTub; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; switchmode 3; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 1; sensorretain 1; setoption19 1; Rule1 on Switch1#state do Publish homeassistant/cmnd/%topic%/POWER 1 endon; Rule1 1;

#NewKitchenFridge
10.2.4.70
Backlog timers 0; timer1 0; timer2 0; EnergyReset3 0; hostname KitchenFridge; DeviceName KitchenFridge; friendlyname Kitchen Fridge; topic KitchenFridge; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; switchmode 3; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 1; sensorretain 1; setoption19 1; Rule1 on Switch1#state do Publish homeassistant/cmnd/%topic%/POWER 1 endon; Rule1 1;

#GarageFridge
10.2.4.49
Backlog timers 0; timer1 0; timer2 0; EnergyReset3 0; hostname GarageFridge; DeviceName GarageFridge; friendlyname Garage Fridge; topic GarageFridge; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; switchmode 3; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 1; sensorretain 1; setoption19 1; Rule1 on Switch1#state do Publish homeassistant/cmnd/%topic%/POWER 1 endon; Rule1 1;

#GarageFreezer
10.2.4.45
Backlog timers 0; timer1 0; timer2 0; EnergyReset3 0; hostname GarageFreezer; DeviceName GarageFreezer; friendlyname Garage Freezer; topic GarageFreezer; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; switchmode 3; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 1; sensorretain 1; setoption19 1; Rule1 on Switch1#state do Publish homeassistant/cmnd/%topic%/POWER 1 endon; Rule1 1;

#DeepFreeze
10.2.4.39
Backlog timers 0; timer1 0; timer2 0; EnergyReset3 0; hostname DeepFreeze; DeviceName DeepFreeze; friendlyname Deep Freeze; topic DeepFreeze; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; switchmode 3; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 1; sensorretain 1; setoption19 1; Rule1 on Switch1#state do Publish homeassistant/cmnd/%topic%/POWER 1 endon; Rule1 1;


#OldElectricFence
10.2.4.57
{"Hostname":"ElectricFence"}
`Backlog hostname ElectricFence; DeviceName ElectricFence; topic ElectricFence; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ElectricFence/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

#ElectricFence
10.2.4.114
backlog seriallog 0; setoption19 0; hostname ElectricFence; DeviceName ElectricFence; topic ElectricFence; friendlyname Electric Fence;  grouptopic 0; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;

#OldMantleDecor
10.2.4.60
{"Hostname":"MantleDecor"}
`Backlog hostname MantleDecor; DeviceName MantleDecor; topic MantleDecor; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/MantleDecor/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0; sensorretain 1;`

#NewMantleDecor
backlog seriallog 0; setoption19 0; hostname MantleDecor; DeviceName MantleDecor; topic MantleDecor; friendlyname Mantle Decor; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1; Timer1 {"Arm":1,"Mode":0,"Time":"07:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":1}; Timer2 {"Arm":1,"Mode":0,"Time":"23:00","Window":0,"Days":"1111111","Repeat":1,"Output":1,"Action":0}; Timers 1; grouptopic AllStandard; grouptopic2 InteriorDecorations; 


#OldDadsLamp
10.2.4.46
`Backlog hostname DadsLamp; DeviceName DadsLamp; topic DadsLamp; fulltopic homeassistant/%prefix%/%topic%/; grouptopic AllStandard; grouptopic2 InteriorLights; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/DadsLamp/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 0;`

10.2.4.117
backlog seriallog 0; setoption19 0; hostname DadsLamp; DeviceName DadsLamp; topic DadsLamp; friendlyname Dads Lamp; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1; grouptopic 0;

#NewDadsFan
10.2.4.113
backlog seriallog 0; setoption19 0; hostname DadsFan; DeviceName DadsFan; topic DadsFan; friendlyname Dads Fan; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1; grouptopic 0;


backlog seriallog 0; setoption19 0; hostname Spare1; DeviceName Spare1; topic Spare1; friendlyname Spare1; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; module 0; grouptopic 0;


10.2.4.112
backlog seriallog 0; setoption19 0; hostname RetroPi; DeviceName RetroPi; topic RetroPi; friendlyname Retro Pi; grouptopic 0; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff+I2C","GPIO":[17,5,0,6,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;


#NewDadsWorkspace
10.2.4.70
Backlog timers 0; timer1 0; timer2 0; EnergyReset3 0; hostname DadsWorkspace; DeviceName DadsWorkspace; friendlyname Dads Workspace; topic DadsWorkspace; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; switchmode 3; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 1; sensorretain 1; setoption19 1; Rule1 on Switch1#state do Publish homeassistant/cmnd/%topic%/POWER 1 endon; Rule1 1;

#NewBasementWorkspaceMonitor
10.2.4.109
backlog hostname WorkspaceMonitor; DeviceName WorkspaceMonitor; topic WorkspaceMonitor; friendlyname Workspace Monitor; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"WemoD1Mini","GPIO":[255,255,255,255,255,255,255,255,255,255,255,255,255],"FLAG":15,"BASE":18}; module 0; setoption19 1;


InternetRouter
10.2.4.118
backlog seriallog 0; setoption19 0; hostname InternetRouter; DeviceName InternetRouter; topic InternetRouter; friendlyname Internet Router; grouptopic2 0; grouptopic 0; switchmode 3; fulltopic homeassistant/%prefix%/%topic%/; template {"NAME":"Sonoff+I2C","GPIO":[17,5,0,6,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":1}; module 0; setoption19 1;

#NewNetworkEquipment
10.2.4.46
Backlog timers 0; timer1 0; timer2 0; EnergyReset3 0; hostname NetworkEquipment; DeviceName NetworkEquipment; friendlyname Network Equipment; topic NetworkEquipment; fulltopic homeassistant/%prefix%/%topic%/; grouptopic 0; switchmode 3; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0; powerretain 1; sensorretain 1; setoption19 1; Rule1 on Switch1#state do Publish homeassistant/cmnd/%topic%/POWER 1 endon; Rule1 1;


######!!!!!REMEMBER TO RESET TIMERS _AND_ COUNTERS ON W-US002S MODULES!!!!!######

for n in `echo "10.2.4.69 10.2.4.63 10.2.4.38 10.2.4.59 10.2.4.58 10.2.4.61"`
do
  curl "http://$n/cm?cmnd=EnergyReset3%200"
done


for n in `echo "10.2.4.69 10.2.4.63 10.2.4.38 10.2.4.59 10.2.4.58 10.2.4.61 10.2.4.100 10.2.4.111 10.2.4.99 10.2.4.105 10.2.4.98 10.2.4.101 10.2.4.102 10.2.4.104 10.2.4.103"`
do
    echo -e '\r\r\r'
    curl "http://$n/cm?cmnd=setoption19%200"
    echo -e '\r\r\r'
    echo -e "Sleep 15\r"
    sleep 15
    echo -e "Starting Standard for $n\r"
    curl "http://$n/cm?cmnd=setoption19%201"
    echo -e '\r\r\r'
done



for n in `cat  ./iplist.txt`
do
    curl "http://$n/cm?cmnd=setoption19%200"
    echo -e '\r'
    curl "http://$n/cm?cmnd=setoption19%201"
    echo -e '\r\r'
done



for n in `echo "10.2.4.105 10.2.4.111 10.2.4.116 10.2.4.100 10.2.4.101 10.2.4.99 10.2.4.98 10.2.4.93"`
do
  curl "http://$n/cm?cmnd=backlog%20grouptopic%20AllStandard%3B%20grouptopic2%20InteriorDecorations%3B%20Timer1%20%7B%22Enable%22%3A1%2C%22Mode%22%3A0%2C%22Time%22%3A%2207%3A00%22%2C%22Window%22%3A0%2C%22Days%22%3A%221111111%22%2C%22Repeat%22%3A1%2C%22Output%22%3A1%2C%22Action%22%3A1%7D%3B%20Timer2%20%7B%22Enable%22%3A1%2C%22Mode%22%3A0%2C%22Time%22%3A%2223%3A00%22%2C%22Window%22%3A0%2C%22Days%22%3A%221111111%22%2C%22Repeat%22%3A1%2C%22Output%22%3A1%2C%22Action%22%3A0%7D%3B%20Timers%201%3B%20Power%201%3B"
done

for n in `echo "10.2.4.105 10.2.4.111 10.2.4.116 10.2.4.100 10.2.4.101 10.2.4.99 10.2.4.98 10.2.4.93"`
do
    curl "http://$n/cm?cmnd=timers" -s | jq .
done