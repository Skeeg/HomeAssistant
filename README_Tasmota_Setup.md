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

# Maxcio Power Switch
```
backlog template {"NAME":"W-US002S","GPIO":[0,90,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}; module 0;
```

# Sonoff Power Switch
```
backlog template {"NAME":"Sonoff Basic","GPIO":[17,255,255,255,255,0,0,0,21,56,255,0,0],"FLAG":0,"BASE":1}; module 0;
```

# Power Calibration
Have to run https://tasmota.github.io/docs/Power-Monitoring-Calibration/ process in console.
Get values from the Kill-A-Watt device

```
PowerSet 60.0
VoltageSet 115
CurrentSet 500
```

#####################################################################

# From the Command Line

From https://tasmota.github.io/docs/Buttons-and-Switches/#button

# Rule Enablement for Multi switch control.  
Disables the button from turning on the relay directly and instead sends the command to the MQTT server to set the state for all of the paired group switches.

```
Rule1 on Switch1#state do Publish homeassistant/cmnd/EntryCansGroup/POWER %value% endon
Rule1 1
```

Useful commands:
```!bash
#!/bin/bash
for cmnd in "status%200 hostname"
curl http://$ip/cm?cmnd=$cmnd
```

```!bash
#!/bin/bash
#sed split long word at capitals
echo "FreakingHeckStuffREALLY" | sed 's/\([^[:blank:]]\)\([[:upper:]]\)/\1 \2/g'
#Result:
#Freaking Heck Stuff RE AL LY
```

```!bash
#NonPower Monitors Only
for n in `awk 'NR >= 1 && NR <= 470' ~/repo/grafana-prometheus/prometheus/config/prometheus.yml | \
  grep 10.2.4 | \
  grep -v '#' | \
  cut -d"'" -f 2 | \
  cut -d":" -f 1`;
do
  curl "http://$n/cm?cmnd=status%200" -s | \
    jq --raw-output '[.StatusFWR.BuildDateTime, .StatusFWR.Version, .StatusNET.IPAddress, .StatusNET.Hostname] | @csv';
  echo -e "Starting Standard for $n\r"
  curl -F 'u2=@/Users/ryan-peay/repo/tasmota/build_output/firmware/tasmota.bin.gz' http://$n/u2 -s > /dev/null
done
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
for n in $(echo "10.2.4.14 10.2.4.15")
do
    printf '{"IPAddress":"'$n'"}'
    echo -e "\rStarting v2 for $n\r"
    curl -F 'u2=@/Users/ryan-peay/Downloads/tasmota 9.1.0/skeeg-v2/tasmota.bin.gz' \
      http://$n/u2 -o /Users/ryan-peay/Downloads/tasmota\ 9.1.0/skeeg-v2//$n.txt
    echo -e "Done with $n\r\r\r"
done
```

# !!!!! REMEMBER TO RESET COUNTERS _AND_ TIMERS ON W-US002S MODULES !!!!!

```!bash
do
  echo $n
  curl "http://$n/cm?cmnd=EnergyReset3%200"
  curl "http://$n/cm?cmnd=Timers%200"
done
```

```!bash
do
  echo $n
  curl "http://$n/cm?cmnd=restart%201" -s | jq .
done
```

# Check for live device
Needs gnu coreutils

`brew install coreutils` 

```!bash
do
    printf "%s" "waiting for $n ..."
    while ! gtimeout 0.2 ping -c 1 -n $n &> /dev/null
    do
        printf "%c" "."
    done
    moduleName=`curl "http://$n/cm?cmnd=module" -s | jq .Module.\"0\"`
    curl "http://$n/cm?cmnd=status%200" -s |\
        jq --raw-output ". += {"Module": $moduleName} | [.StatusNET.IPAddress, .Status.DeviceName, (\"Module:\" + (.Status.Module|tostring)), .Module] | @csv"
done
```
