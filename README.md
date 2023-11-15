# HomeAssistant

Basic statement for this project is that I run all of this off a 64 bit enabled Raspberry Pi OS using Docker.  Most of the process to get this setup is documented in the enablement folder here, roughly captured in numbered `.sh` script files.  There may be some steps missed here, but trying to capture at least some decent documentation for the few years of evolution of this project.

I am using some custom integrations that are available in alternate git repositories than this project, but everything needs to stay together for home assistant.  To keep this running from a basic clone and following the processes from this project, I am using git bare and sparse configs, which requires a later version of git than is natively available on raspberry pi.  Please read/execute `enablement/002_build_git_2.42.0.sh` to get the newer git ready.

## Firmware building with PlatformIO and delivering the data

Key thing here, is that I use the `platformio_override.ini` and the `user_config_override.h` files to define customized build models.  Be very careful to not include so many features that your uncompressed firmware file is too large on the 1mb storage device to allow a reflash to the minimal version.  I have a few devices where the firmware is locked to an older release that I can't OTA flash and will need to break the device open to do a raw flash.

### Basic Setup

#### Clone repo

```bash
git clone git@github.com:arendst/Tasmota.git "$REPOPATH/tasmota"
```

#### Symlink the override files into the tasmota project directory

```bash
ln -sf $REPOPATH/homeassistant/enablement/tasmota/platformio_override_1.ini $REPOPATH/tasmota/platformio_override.ini
ln -sf $REPOPATH/homeassistant/enablement/tasmota/user_config_override_4.h $REPOPATH/tasmota/tasmota/user_config_override.h
```

### Use PlatformIO in VSCode

Not going to go into the detail here.  Basic summary is that with the `platformio_override.ini` and the `user_config_override.h` files linked in, there is a defined set of environments that are going to be built with all the desired features enabled for each device scenario.  

TL:DR; Make sure the symlinks are in place, and hit the checkmark/build button in VSCode

#### Copy compiled firmware to the Raspberry Pi

```bash
scp $REPOPATH/tasmota/build_output/firmware/* pi@$PI_ADDRESS:docker/homeassistant/firmware/
```

## Various scripts and bash references

### Summary

There are times when a full Python project can make a lot of sense, and there is code here in the repo to do some neat things, but then there's time that just some sweet old bash kungfu can be all you need.  

Also, the combination of a Ubiquiti controller and querying the API's there to find what devices are online right now can save a ton of effort in general ping sweep/scanning nonsense.

#### Symlink the shell functions to the [dotfiles](https://github.com/Skeeg/.dotfiles) profile path to be made available in your shells:

```bash
ln -sf $REPOPATH/homeassistant/enablement/tasmota/tasmota.plugin.zsh $HOME/.profile.d/tasmota.plugin.zsh
```

#### Login to the unifi controller

```bash
udm-login $UNIFI_ADDRESS "$(secret get UDM_USERNAME)" "$(secret get UDM_PASSWORD)"
```

#### Build a json data array from data queried from the Ubiquiti controller, return mac and ip address

```bash
get-active-tasmota-json | jq -cr '.[]'
```

#### Return the IP's and some information from the Status output

```bash
for IP in $(get-active-tasmota-json | jq -cr '.[].ip'); 
do 
  printf "%s on $IP\n" $(curl "http://$IP/cm?cmnd=Status%202" --silent | jq -c .StatusFWR.Version)
done
```

#### Return the template configured for the IP and the IP, sorted.

```bash
for IP in $(get-active-tasmota-json | jq -cr '.[].ip'); 
do 
  printf "%s: $IP\n" "$(curl "http://$IP/cm?cmnd=template" --silent | jq .NAME)"
done | sort
```

#### Some longer line formatting examples

```bash
for IP in $(get-active-tasmota-json | jq -cr '.[].ip'); 
do 
  printf "$IP: "
  printf "%s " "$(curl "http://$IP/cm?cmnd=template" --silent | jq .NAME)"
  printf "%s " "$(curl "http://$IP/cm?cmnd=Status%200" --silent | jq -c .StatusFWR.Version)"
  printf "\n"
done
```

#### Manual upgrade of a IP to a file hosted on the server:

```bash
  IP="10.3.3.99"
  MINIMAL_FIRMWARE="http://firmware:2020/1mb-minimal.bin.gz"
  MODEL_FIRMWARE="http://firmware:2020/1mb-simple.bin.gz"
  curl --silent "http://$IP/cm?cmnd=otaurl%20$MINIMAL_FIRMWARE"\;
  curl --silent "http://$IP/u1?o=$MINIMAL_FIRMWARE"
  sleep 30
  curl --silent "http://$IP/cm?cmnd=otaurl%20$MODEL_FIRMWARE"\;
  curl --silent "http://$IP/u1?o=$MODEL_FIRMWARE"
```

#### Mass update and refresh going through a minimal file update first

```bash
for IP in $(active-tasmotas | jq -r .ip)
do
  MODEL_FIRMWARE=$(printf "%s" "$(curl "http://$IP/cm?cmnd=template" --silent | jq -r .NAME)")
  #Translation table
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`Generic`http://firmware:2020/1mb-simple.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`Feit DIM/WIFI`http://firmware:2020/1mb-simple.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`Gosund KS-602S Active`http://firmware:2020/1mb-three-way-switch.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`Gosund KS-602S Control`http://firmware:2020/1mb-three-way-switch.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`Maxcio Active`http://firmware:2020/1mb-three-way-switch.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`Maxcio Control`http://firmware:2020/1mb-three-way-switch.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`Sonoff Basic`http://firmware:2020/1mb-simple.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`Sonoff+I2C`http://firmware:2020/1mb-sonoff-bme280.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`Sonoff S31`http://firmware:2020/1mb-smart-plug.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`W-US002S`http://firmware:2020/1mb-smart-plug.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`NodeMCU`http://firmware:2020/4mb-loaded.bin.gz`g')
  MODEL_FIRMWARE=$(echo $MODEL_FIRMWARE | sed 's`WemoD1Mini`http://firmware:2020/4mb-loaded.bin.gz`g')
  if [[ "$MODEL_FIRMWARE" == "http://firmware:2020/4mb-loaded.bin.gz" ]]; then
    MINIMAL_FIRMWARE="http://firmware:2020/4mb-minimal.bin.gz"
  else
    MINIMAL_FIRMWARE="http://firmware:2020/1mb-minimal.bin.gz"
  fi
  printf "\n\nUpdating %s to %s \n" $IP $MINIMAL_FIRMWARE
  curl --silent "http://$IP/cm?cmnd=otaurl%20$MINIMAL_FIRMWARE"\;
  curl --silent "http://$IP/u1?o=$MINIMAL_FIRMWARE"\;
  sleep 30
  printf "\nUpdating %s to %s \n" $IP $MODEL_FIRMWARE
  curl --silent "http://$IP/cm?cmnd=otaurl%20$MODEL_FIRMWARE"\;
  curl --silent "http://$IP/u1?o=$MODEL_FIRMWARE"\;
done
```

#### Mass cycle HomeAssistant config to refresh device list and config

`SetOption19 0` will have native Tasmota discovery enabled.  Cycling this to 1 should force a disconnect and back to 0 should rediscover, but I have seen Home Assistant not refresh without cycling through twice.  Also, some other configurations that are desired are `SetOption30 1` to have the relay show up as a light and not a switch.

```bash
for IP in $(active-tasmotas | jq -r .ip)
do
  printf "\n\nUpdating %s \n" $IP
  curl --silent "http://$IP/cm?cmnd=setoption19%201"
  MODEL_SETTING=$(printf "%s" "$(curl "http://$IP/cm?cmnd=template" --silent | jq -r .NAME)")
  #Translation table
  MODEL_SETTING=$(echo $MODEL_SETTING | sed 's`Feit DIM/WIFI`SetOption30%201`g')
  MODEL_SETTING=$(echo $MODEL_SETTING | sed 's`Gosund KS-602S Active`SetOption30%201`g')
  MODEL_SETTING=$(echo $MODEL_SETTING | sed 's`Gosund KS-602S Control`SetOption30%201`g')
  MODEL_SETTING=$(echo $MODEL_SETTING | sed 's`Maxcio Active`SetOption30%201`g')
  MODEL_SETTING=$(echo $MODEL_SETTING | sed 's`Maxcio Control`SetOption30%201`g')
  if [[ "$MODEL_SETTING" == "SetOption30%201" ]]; then
    # echo $MODEL_SETTING
  else
    MODEL_SETTING="SetOption30%200"
    # echo $MODEL_SETTING
  fi
  sleep 3
  # curl --silent "http://$IP/cm?cmnd=$MODEL_SETTING"
  # curl --silent "http://$IP/cm?cmnd=devicename%201"
  curl --silent "http://$IP/cm?cmnd=setoption19%200"
done
```

#### Ensure HomeAssistant Desired Discovery Mode is Set

```bash
for IP in $(active-tasmotas | jq -r .ip)
do
  printf "\n\nUpdating %s \n" $IP
  curl --silent "http://$IP/cm?cmnd=setoption19%200"
done
```
