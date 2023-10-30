# Standard Devices

## Newer method using straight lookups from network hardware

```bash
for IP in $(active-tasmotas | jq -r .ip)
do
  OTAURL=$(curl --silent "http://$IP/cm?cmnd=otaurl" | jq -r '.OtaUrl')
  if [[ $OTAURL == "http://10.2.2.4:2020/1mb/tasmota.bin.gz" ]]
  then
    echo $OTAURL-$IP
    curl --silent "http://$IP/cm?cmnd=otaurl%20http%3A%2F%2Ffirmware%3A2020%2F1mb%2Ftasmota.bin.gz";
    curl --silent "http://$IP/cm?cmnd=otaurl" | jq -r '.OtaUrl';
    curl --silent "http://$IP/u1?o=http%3A%2F%2Ffirmware%3A2020%2F1mb%2Ftasmota.bin.gz";
  fi
done
```

```bash
for IP in $(active-tasmotas | jq -r .ip)
do
  OTAURL=$(curl --silent "http://$IP/cm?cmnd=otaurl" | jq -r '.OtaUrl')
  echo $OTAURL-$IP
done
```

## Older crap done documenting the evolution of things done until the current state.

This includes some crap that has "broken" some of the devices by flashing versions of firmware that take too much active space on the chip and now they can't be OTA flashed.

```bash
for IP in 10.3.3.20 10.3.2.80 10.3.3.53 10.3.3.32 10.3.3.196 10.3.2.203 10.3.3.83 10.3.2.28 10.3.2.174 10.3.2.175 10.3.3.18 10.3.3.98 10.3.2.36 10.3.3.224 10.3.3.133 10.3.3.121 10.3.2.21 10.3.2.39 10.3.2.142 10.3.3.191 10.3.3.7 10.3.2.135 10.3.3.138 10.3.3.183 10.3.2.156 10.3.2.249 10.3.2.48 10.3.3.160 10.3.3.94 10.3.3.50 10.3.2.126 10.3.2.141 10.3.2.87 10.3.3.114 10.3.2.85 10.3.3.3 10.3.3.246 10.3.2.111 10.3.2.113 10.3.2.103 10.3.3.16 10.3.3.147 10.3.3.189 10.3.3.4 10.3.2.110 10.3.3.194 10.3.2.217 10.3.3.41 10.3.3.203 10.3.2.159 10.3.2.202 10.3.2.197 10.3.2.22 10.3.2.204 10.3.2.89 10.3.2.235 10.3.3.74 10.3.2.86 10.3.2.102 10.3.2.43 10.3.2.185 10.3.3.24 10.3.3.57 10.3.2.187 10.3.2.180 10.3.3.36 10.3.3.153 10.3.3.39;
do curl http://$IP/u1?o=http%3A%2F%2F10.2.2.4%3A2020%2F1mb%2Ftasmota.bin.gz; echo $IP; done
```

```bash
for IP in 10.3.3.20 10.3.2.80 10.3.3.53 10.3.3.32 10.3.3.196 10.3.2.203 10.3.3.83 10.3.2.28 10.3.2.174 10.3.2.175 10.3.3.18 10.3.3.98 10.3.2.36 10.3.3.224 10.3.3.133 10.3.3.121 10.3.2.21 10.3.2.39 10.3.2.142 10.3.3.191 10.3.3.7 10.3.2.135 10.3.3.138 10.3.3.183 10.3.2.156 10.3.2.249 10.3.2.48 10.3.3.160 10.3.3.94 10.3.3.50 10.3.2.126 10.3.2.141 10.3.2.87 10.3.3.114 10.3.2.85 10.3.3.3 10.3.3.246 10.3.2.111 10.3.2.113 10.3.2.103 10.3.3.16 10.3.3.147 10.3.3.189 10.3.3.4 10.3.2.110 10.3.3.194 10.3.2.217 10.3.3.41 10.3.3.203 10.3.2.159 10.3.2.202 10.3.2.197 10.3.2.22 10.3.2.204 10.3.2.89 10.3.2.235 10.3.3.74 10.3.2.86 10.3.2.102 10.3.2.43 10.3.2.185 10.3.3.24 10.3.3.57 10.3.2.187 10.3.2.180 10.3.3.36 10.3.3.153 10.3.3.39;
do curl http://$IP/cm?cmnd=; echo $IP; done
```

```json
{"FlashChipId":"144051","ProgramSize":525,"Free":476,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"ChristmasTree"}10.3.3.20
{"FlashChipId":"144051","ProgramSize":525,"Free":476,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"KitchenTable"}10.3.2.80
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Feit DIM/WIFI"}}{"Hostname":"FamilyDimmer"}10.3.3.53
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Feit DIM/WIFI"}}{"Hostname":"LilysDimmer"}10.3.3.32
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"DadsLights"}10.3.3.196
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"EntryCans"}10.3.2.203
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"EntryChandelier"}10.3.3.83
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"ExteriorSide"}10.3.2.28
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"GarageLights_C1"}10.3.2.174
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"GarageLights"}10.3.2.175
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"KidsSink"}10.3.3.18
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"KitchenCans"}10.3.3.98
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"KitchenSink"}10.3.2.36
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"LibraryLights"}10.3.3.224
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"LilyHall"}10.3.3.133
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"MainHall"}10.3.3.121
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"PorchLights"}10.3.2.21
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"PowderHall"}10.3.2.39
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Control"}}{"Hostname":"EntryCans_C1"}10.3.2.142
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Control"}}{"Hostname":"EntryCans_C2"}10.3.3.191
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Control"}}{"Hostname":"KitchenCans_C1"}10.3.3.7
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Control"}}{"Hostname":"KitchenSink_C1"}10.3.2.135
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Control"}}{"Hostname":"LilyHall_C1"}10.3.3.138
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Control"}}{"Hostname":"LilyHall_C2"}10.3.3.183
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Control"}}{"Hostname":"MainHall_C1"}10.3.2.156
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Control"}}{"Hostname":"MainHall_C2"}10.3.2.249
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"Blower"}10.3.2.48
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"BuffetDecor"}10.3.3.160
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"CurtainLights"}10.3.3.94
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"DadsFan"}10.3.3.50
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"DadsLamp"}10.3.2.126
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"ElectricFence"}10.3.2.141
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"ElectronicsWorkstation"}10.3.2.87
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"FirePlace"}10.3.3.114
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"GazeboLights"}10.3.2.85
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"HotTubLights"}10.3.3.3
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"LavaLamp"}10.3.3.246
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"LeftMantle"}10.3.2.111
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"OctoPi"}10.3.2.113
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"PatioFountain"}10.3.2.103
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"PiHole"}10.3.3.16
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"RailingLights"}10.3.3.147
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff+I2C"}}{"Hostname":"GarageLamp"}10.3.3.189
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff+I2C"}}{"Hostname":"InternetRouter"}10.3.3.4
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"1":"Sonoff Basic"}}{"Hostname":"%s-%04d"}10.3.2.110
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"1":"Sonoff Basic"}}{"Hostname":"%s-%04d"}10.3.3.194
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"1":"Sonoff Basic"}}{"Hostname":"MasterPi"}10.3.2.217
{"FlashChipId":"144051","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"2":"Sonoff RF"}}{"Hostname":"MantleDecor"}10.3.3.41
{"FlashChipId":"144051","ProgramSize":559,"Free":444,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Feit DIM/WIFI"}}{"Hostname":"AustinsDimmer"}10.3.3.203
{"FlashChipId":"144051","ProgramSize":559,"Free":444,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Active"}}{"Hostname":"AustinHall"}10.3.2.159
{"FlashChipId":"144051","ProgramSize":559,"Free":444,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Gosund KS-602S Control"}}{"Hostname":"AustinHall_C1"}10.3.2.202
{"FlashChipId":"1440C8","ProgramSize":525,"Free":476,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"RightMantle"}10.3.2.197
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"BasementLights"}10.3.2.22
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"ChristmasPackage"}10.3.2.204
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"DiningLights"}10.3.2.89
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"EveLights"}10.3.2.235
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"ExteriorGarageLights"}10.3.3.74
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"FamilyFan"}10.3.2.86
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"FamilyLights"}10.3.2.102
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"KidsBathroomFan"}10.3.2.43
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"KidsShower"}10.3.2.185
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"KidsToilet"}10.3.3.24
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"PatioLights"}10.3.3.57
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"PowderFan"}10.3.2.187
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"PowderLights"}10.3.2.180
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Active"}}{"Hostname":"StudyLights"}10.3.3.36
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Maxcio Control"}}{"Hostname":"StudyFan"}10.3.3.153
{"FlashChipId":"1440C8","ProgramSize":544,"Free":456,"ProgramFlashSize":1024,"FlashSize":1024}{"Module":{"0":"Sonoff Basic"}}{"Hostname":"EndTable"}10.3.3.39
```

## Sensor Devices

## Running correct firmware

```json
{"FlashChipId":"16405E","ProgramSize":682,"Free":1364,"ProgramFlashSize":4096,"FlashSize":4096}{"Module":{"0":"NodeMCU"}}{"Hostname":"MediaRemote"}10.3.3.56
{"FlashChipId":"16405E","ProgramSize":877,"Free":1168,"ProgramFlashSize":4096,"FlashSize":4096}{"Module":{"1":"Sonoff Basic"}}{"Hostname":"%s-%04d"}10.3.3.115
{"FlashChipId":"1640EF","ProgramSize":877,"Free":1168,"ProgramFlashSize":4096,"FlashSize":4096}{"Module":{"0":"Sonoff S31"}}{"Hostname":"Unused001"}10.3.3.247
{"FlashChipId":"1640EF","ProgramSize":877,"Free":1168,"ProgramFlashSize":4096,"FlashSize":4096}{"Module":{"0":"Sonoff S31"}}{"Hostname":"Unused002"}10.3.3.118
{"FlashChipId":"1640EF","ProgramSize":877,"Free":1168,"ProgramFlashSize":4096,"FlashSize":4096}{"Module":{"0":"Sonoff S31"}}{"Hostname":"Unused003"}10.3.2.68
```

## Testing

```json
{"FlashChipId":"1640D8","ProgramSize":610,"Free":1436,"ProgramFlashSize":4096,"FlashSize":4096}{"Module":{"0":"Generic"}}{"Hostname":"LilysVigil"}10.3.3.190
```

## Manual Redos

Hosed W-US002S's: {"Hostname":"3dPrinter"}10.3.2.30
Hosed W-US002S's: {"Hostname":"DouglasLights"}10.3.2.168

Manual Flash S31: {"Hostname":"%s-%04d"}10.3.2.122
Manual Flash S31: {"Hostname":"%s-%04d"}10.3.3.245
Manual Flash S31: {"Hostname":"%s-%04d"}10.3.3.37
Manual Flash S31: {"Hostname":"%s-%04d"}10.3.3.95
Manual Flash S31: {"Hostname":"JeremyLight"}10.3.2.88
Manual Flash S31: {"Hostname":"UpstairsColor"}10.3.3.117

```bash
#for IP in 10.3.2.205 10.3.3.99 10.3.2.250 10.3.2.55 10.3.3.60 10.3.2.182 10.3.2.93 10.3.2.200 10.3.3.199 10.3.3.97 10.3.3.164 10.3.2.42 10.3.3.73 10.3.3.103 10.3.3.202 10.3.3.35 10.3.2.106 10.3.3.116 10.3.2.160 10.3.3.175; do echo $IP; curl http://$IP/cm?cmnd=otaurl%20http%3A%2F%2F10.2.2.4%3A2020%2F11%2Ftasmota-sensors.bin.gz; done
for IP in 10.3.2.205 10.3.3.99 10.3.2.250 10.3.2.55 10.3.3.60 10.3.2.182 10.3.2.93 10.3.2.200 10.3.3.199 10.3.3.97 10.3.3.164 10.3.2.42 10.3.3.73 10.3.3.103 10.3.3.202 10.3.3.35 10.3.2.106 10.3.3.116 10.3.2.160 10.3.3.175;
do curl http://$IP/u1?o=http%3A%2F%2Ffirmware%3A2020%2F1mb%2Ftasmota-sensors.bin.gz; echo $IP; done
```

## Done

Pin to 11: {"Hostname":"KitchenFridge"}10.3.2.205
Pin to 11: {"Hostname":"BasementFridge"}10.3.3.99
Pin to 11: {"Hostname":"ComputerAustin"}10.3.2.250
Pin to 11: {"Hostname":"ComputerLily"}10.3.2.55
Pin to 11: {"Hostname":"ComputerMob"}10.3.3.60
Pin to 11: {"Hostname":"DadsWorkspace"}10.3.2.182
Pin to 11: {"Hostname":"DeepFreeze"}10.3.2.93
Pin to 11: {"Hostname":"EntryDecorations"}10.3.2.200
Pin to 11: {"Hostname":"FrontTree"}10.3.3.199
Pin to 11: {"Hostname":"GarageFreezer"}10.3.3.97
Pin to 11: {"Hostname":"GarageFridge"}10.3.3.164
Pin to 11: {"Hostname":"GroundDecor"}10.3.2.42
Pin to 11: {"Hostname":"HeatBlankets"}10.3.3.73
Pin to 11: {"Hostname":"HotTub"}10.3.3.103
Pin to 11: {"Hostname":"MainTV"}10.3.3.202
Pin to 11: {"Hostname":"MasterTV"}10.3.3.35
Pin to 11: {"Hostname":"NetworkEquipment"}10.3.2.106
Pin to 11: {"Hostname":"PetLights"}10.3.3.116
Pin to 11: {"Hostname":"ServerDisks"}10.3.2.160
Pin to 11: {"Hostname":"Unused02"}10.3.3.175
