# This basically tells the device that it does have a Relay so that it will accept power on commands 
# This enables the LED, but it sends 5v to the wrong (dead end) GPIO,
# which doesn't engage the mechanical relay
#
# Dummy Device Template:
`{"NAME":"Gosund KS-602S","GPIO":[17,56,0,0,0,0,0,0,0,0,0,21,158],"FLAG":0,"BASE":18}`

# Send the voltage to the right GPIO
#
# Real Device Template:
`{"NAME":"Gosund KS-602S","GPIO":[17,56,0,0,0,0,0,0,0,0,21,0,158],"FLAG":0,"BASE":18}`

#######################
# From the Command Line

From https://tasmota.github.io/docs/Buttons-and-Switches/#button

# Rule Enablement for Multi switch control.  
# Disables the button from turning on the relay directly and instead sends the command to the MQTT
# server to set the state for all of the paired group switches.
`Rule1 on Button1#state do Publish homeassistant/cmnd/EntryCansGroup/POWER %value% endon`
`Rule1 1`

From https://tasmota.github.io/docs/MQTT/#grouptopic

#Join the group MQTT topic - Causes a reboot
`GroupTopic EntryCansGroup`
