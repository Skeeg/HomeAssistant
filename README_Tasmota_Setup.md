# This basically tells the device that it does have a Relay so that it will accept power on commands 
# This enables the LED, but it sends 5v to the wrong (dead end) GPIO,
# which doesn't engage the mechanical relay

# Control Device Template:
`{"NAME":"Gosund KS-602S","GPIO":[17,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}`

# Send the voltage to the right GPIO
# Active Device Template:
`{"NAME":"Gosund KS-602S","GPIO":[17,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}`

# Maxcio Power Switch
`{"NAME":"W-US002S","GPIO":[0,90,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45}`

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

#Gosund, Active Device - Switch Instead of Button
`Backlog hostname EntryCans_1; grouptopic EntryCansGroup; fulltopic homeassistant/%prefix%/%topic%/; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/EntryCansGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Active","GPIO":[9,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18};`

#Gosund, Control Device - Switch Instead of Button
`Backlog hostname EntryCans_DS; grouptopic EntryCansGroup; fulltopic homeassistant/%prefix%/%topic%/; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/EntryCansGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18};`

#Gosund, Control Device - Switch Instead of Button
`Backlog hostname TestTuya; grouptopic tasmotas; fulltopic homeassistant/%prefix%/%topic%/; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/TestTuya/POWER %value% endon; Rule1 1; Template {"NAME":"Gosund KS-602S Control","GPIO":[9,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18};`

#Maxcio, Active Device - Switch Instead of Button
`Backlog hostname FamilyLights; grouptopic tasmotas; fulltopic homeassistant/%prefix%/%topic%/; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/FamilyLights/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio","GPIO":[17,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}`

#Maxcio, Active Device - Switch Instead of Button
`Backlog hostname FamilyFan; grouptopic tasmotas; fulltopic homeassistant/%prefix%/%topic%/; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/FamilyFan/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio","GPIO":[17,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}`

#Switch1n instead of button
`Backlog hostname CurtainLights; grouptopic tasmotas; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/CurtainLights/POWER %value% endon; Rule1 1; Template {"NAME":"W-US002S","GPIO":[0,82,0,52,133,132,0,0,130,53,21,0,0],"FLAG":0,"BASE":45};`

`Backlog hostname PowderFan; DeviceName PowderFan; topic PowderFan; fulltopic homeassistant/%prefix%/%topic%/; grouptopic tasmotas; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/PowderFan/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[17,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 1;`


`Backlog hostname PowderLights; DeviceName PowderLights; topic PowderLights; fulltopic homeassistant/%prefix%/%topic%/; grouptopic tasmotas; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/PowderLights/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[17,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 1;`


`Backlog hostname ChristmasPackage; DeviceName ChristmasPackage; topic ChristmasPackage; fulltopic homeassistant/%prefix%/%topic%/; grouptopic tasmotas; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/ChristmasPackage/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Active","GPIO":[17,0,0,0,0,0,0,0,21,56,0,0,0],"FLAG":0,"BASE":18}; module 0; powerretain 1;`


`Backlog hostname StudyFan; DeviceName StudyFan; topic StudyFan; fulltopic homeassistant/%prefix%/%topic%/; grouptopic StudyLightsGroup; timedst 0; timestd 0; timezone 99; switchmode 3; latitude 40.297297; longitude -111.878340; Rule1 on Switch1#state do Publish homeassistant/cmnd/StudyLightsGroup/POWER %value% endon; Rule1 1; Template {"NAME":"Maxcio Control","GPIO":[17,0,0,0,0,0,0,0,0,56,0,0,21],"FLAG":0,"BASE":18}; module 0; powerretain 1;`




From https://tasmota.github.io/docs/MQTT/#grouptopic

#Join the group MQTT topic - Causes a reboot
`GroupTopic EntryCansGroup`
