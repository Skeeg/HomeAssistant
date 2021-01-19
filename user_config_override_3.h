/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2020  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

#define CUSTOM_IMAGE_STR "custom-skeeg-v4"

// force the compiler to show a warning to confirm that this file is included
#warning **** user_config_override.h: Using Settings from this File ****

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) #define your own settings below
 *   (3) for platformio:
 *         #define USE_CONFIG_OVERRIDE as a build flags.
 *         ie1 : export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE'
 *       for Arduino IDE:
 *         enable #define USE_CONFIG_OVERRIDE in my_user_config.h
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER #defines will only override flash settings if you change #define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/#undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major #define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/



// -- Master parameter control --------------------
#undef  CFG_HOLDER
#define CFG_HOLDER        4617                   // [Reset 1] Change this value to load SECTION1 configuration parameters to flash

// -- Setup your own Wifi settings  ---------------
#undef  STA_SSID1
#define STA_SSID1         "WIFI2"             // [Ssid1] Wifi SSID

#undef  STA_PASS1
#define STA_PASS1         "ENTERPASSWORD"     // [Password1] Wifi password

// -- Setup your own MQTT settings  ---------------
#undef  MQTT_HOST
#define MQTT_HOST         "10.2.2.4" // [MqttHost]

#undef  MQTT_PORT
#define MQTT_PORT         1883                   // [MqttPort] MQTT port (10123 on CloudMQTT)

#undef  MQTT_USER
#define MQTT_USER         "Admin"         // [MqttUser] Optional user

#undef  MQTT_PASS
#define MQTT_PASS         "Admin"         // [MqttPassword] Optional password

// You might even pass some parameters from the command line ----------------------------
// Ie:  export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE -DMY_IP="192.168.1.99" -DMY_GW="192.168.1.1" -DMY_DNS="192.168.1.1"'

#ifdef LATITUDE
  #undef LATITUDE
#endif
#define LATITUDE 40.297297

#ifdef LONGITUDE
  #undef LONGITUDE
#endif
#define LONGITUDE -111.878340

#ifdef TIME_DST_HEMISPHERE
  #undef TIME_DST_HEMISPHERE
#endif
#define TIME_DST_HEMISPHERE    North

#ifdef TIME_DST_WEEK
  #undef TIME_DST_WEEK
#endif
#define TIME_DST_WEEK          Second

#ifdef TIME_DST_DAY
  #undef TIME_DST_DAY
#endif
#define TIME_DST_DAY           Sun

#ifdef TIME_DST_MONTH
  #undef TIME_DST_MONTH
#endif
#define TIME_DST_MONTH         Mar

#ifdef TIME_DST_HOUR
  #undef TIME_DST_HOUR
#endif
#define TIME_DST_HOUR          2

#ifdef TIME_DST_OFFSET
  #undef TIME_DST_OFFSET
#endif
#define TIME_DST_OFFSET        -360              // (UTC-6) Offset from UTC in minutes

#ifdef TIME_STD_HEMISPHERE
  #undef TIME_STD_HEMISPHERE
#endif
#define TIME_STD_HEMISPHERE    North

#ifdef TIME_STD_WEEK
  #undef TIME_STD_WEEK
#endif
#define TIME_STD_WEEK          First

#ifdef TIME_STD_DAY
  #undef TIME_STD_DAY
#endif
#define TIME_STD_DAY           Sun

#ifdef TIME_STD_MONTH
  #undef TIME_STD_MONTH
#endif
#define TIME_STD_MONTH         Nov

#ifdef TIME_STD_HOUR
  #undef TIME_STD_HOUR
#endif
#define TIME_STD_HOUR          2

#ifdef TIME_STD_OFFSET
  #undef TIME_STD_OFFSET
#endif
#define TIME_STD_OFFSET        -420              // (UTC-7) Offset from UTC in minutes

#ifdef APP_TIMEZONE
  #undef APP_TIMEZONE
#endif
#define APP_TIMEZONE           99                // 99 = use TIME_DST/TIME_STD
 
// Temperature units
#ifdef TEMP_CONVERSION
  #undef TEMP_CONVERSION
#endif
#define TEMP_CONVERSION        1                 // 1 = Fahrenheit

#ifdef NTP_SERVER1
  #undef NTP_SERVER1
#endif
#define NTP_SERVER1 "0.pool.ntp.org"

#ifdef NTP_SERVER2
  #undef NTP_SERVER2
#endif
#define NTP_SERVER2 "1.pool.ntp.org"

#ifdef NTP_SERVER3
  #undef NTP_SERVER3
#endif
#define NTP_SERVER3 "2.pool.ntp.org"

#ifdef WIFI_CONFIG_TOOL
  #undef WIFI_CONFIG_TOOL
#endif
#define WIFI_CONFIG_TOOL WIFI_MANAGER

// #Remove seriallogging for Sonoff RX/TX pin use
#ifdef SERIAL_LOG_LEVEL
  #undef SERIAL_LOG_LEVEL
#endif
#define SERIAL_LOG_LEVEL       LOG_LEVEL_NONE    // [SerialLog] (LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE)

// #Enable Home Assistant
#ifndef USE_HOME_ASSISTANT
  #define USE_HOME_ASSISTANT                        
#endif

// #Sensors
#define USE_I2C                                  // I2C using library wire (+10k code, 0k2 mem, 124 iram)
#define USE_BH1750                               // [I2cDriver11] Enable BH1750 sensor (I2C address 0x23 or 0x5C) (+0k5 code)
#define USE_BMP                                  // [I2cDriver10] Enable BMP085/BMP180/BMP280/BME280 sensors (I2C addresses 0x76 and 0x77) (+4k4 code)
  #define USE_BME680                             // Enable support for BME680 sensor using Bosch BME680 library (+4k code)
#define USE_SR04                                 // Add support for HC-SR04 ultrasonic devices (+1k code)
#define USE_IR_REMOTE                            // Send IR remote commands using library IRremoteESP8266 and ArduinoJson (+4k code, 0k3 mem, 48 iram)
  #define USE_IR_RECEIVE                         // Support for IR receiver (+5k5 code, 264 iram)
#define USE_LIGHT                                // Add Dimmer/Light support
#define USE_WS2812                               // WS2812 Led string using library NeoPixelBus (+5k code, +1k mem, 232 iram) - Disable by //
//  #define USE_WS2812_DMA                         // DMA supports only GPIO03 (= Serial RXD) (+1k mem). When USE_WS2812_DMA is enabled expect Exceptions on Pow
#ifndef USE_WS2812_HARDWARE
  #define USE_WS2812_HARDWARE  NEO_HW_WS2812     // Hardware type (NEO_HW_WS2812, NEO_HW_WS2812X, NEO_HW_WS2813, NEO_HW_SK6812, NEO_HW_LC8812, NEO_HW_APA106)
#endif
#ifndef USE_WS2812_CTYPE
  #define USE_WS2812_CTYPE     NEO_GRB           // Color type (NEO_RGB, NEO_GRB, NEO_BRG, NEO_RBG, NEO_RGBW, NEO_GRBW)
#endif

#define USE_COUNTER                              // Enable counters
#undef USE_ADC_VCC                               // Add Analog input on selected devices

// #Remove Stuff
#ifdef USE_DISCOVERY
  #undef USE_DISCOVERY                             // Disable mDNS (+8k code or +23.5k code with core 2_5_x, +0.3k mem)
#endif 

#ifdef USE_DOMOTICZ
  #undef USE_DOMOTICZ                              // Disable Domoticz
#endif 

#ifdef USE_EMULATION
  #undef USE_EMULATION                             // Disable Belkin WeMo and Hue Bridge emulation for Alexa (-16k code, -2k mem)
#endif 

#ifdef USE_EMULATION_HUE
  #undef USE_EMULATION_HUE                         // Disable Hue Bridge emulation for Alexa (+14k code, +2k mem common)
#endif 

#ifdef USE_EMULATION_WEMO
  #undef USE_EMULATION_WEMO                        // Disable Belkin WeMo emulation for Alexa (+6k code, +2k mem common)
#endif 

#ifndef USE_PROMETHEUS
  #define USE_PROMETHEUS                            // Enable support for https://prometheus.io/ metrics exporting over HTTP /metrics endpoint
#endif 


#undef ROTARY_V1                                 // Disable support for MI Desk Lamp
#undef USE_SONOFF_RF                             // Disable support for Sonoff Rf Bridge (+3k2 code)
  #undef USE_RF_FLASH                            // Disable support for flashing the EFM8BB1 chip on the Sonoff RF Bridge. C2CK must be connected to GPIO4, C2D to GPIO5 on the PCB
#undef USE_SONOFF_SC                             // Disable support for Sonoff Sc (+1k1 code)
//#undef USE_TUYA_MCU                              // Disable support for Tuya Serial MCU
#undef USE_ARMTRONIX_DIMMERS                     // Disable support for Armtronix Dimmers (+1k4 code)
#undef USE_PS_16_DZ                              // Disable support for PS-16-DZ Dimmer and Sonoff L1 (+2k code)
#undef USE_SONOFF_IFAN                           // Disable support for Sonoff iFan02 and iFan03 (+2k code)
#undef USE_BUZZER                                // Disable support for a buzzer (+0k6 code)
#undef USE_ARILUX_RF                             // Disable support for Arilux RF remote controller
#undef USE_SHUTTER                               // Disable Shutter support for up to 4 shutter with different motortypes (+6k code)
#undef USE_EXS_DIMMER                            // Disable support for EX-Store WiFi Dimmer

#undef USE_PWM_DIMMER                            // Disable support for MJ-SD01/acenx/NTONPOWER PWM dimmers (+4k5 code)
#undef USE_PWM_DIMMER_REMOTE                     // Disbale support for remote switches to PWM Dimmer
#undef USE_KEELOQ                                // Disable support for Jarolift rollers by Keeloq algorithm (+4k5 code)
#undef USE_SONOFF_D1                             // Disable support for Sonoff D1 Dimmer (+0k7 code)

#undef USE_MY92X1                                // Disable support for MY92X1 RGBCW led controller as used in Sonoff B1, Ailight and Lohas
#undef USE_SM16716                               // Disable support for SM16716 RGB LED controller (+0k7 code)
#undef USE_SM2135                                // Disable support for SM2135 RGBCW led control as used in Action LSC (+0k6 code)
#undef USE_SONOFF_L1                             // Disable support for Sonoff L1 led control
#undef USE_ELECTRIQ_MOODL                        // Disable support for ElectriQ iQ-wifiMOODL RGBW LED controller
#undef USE_LIGHT_PALETTE                         // Disable support for color palette (+0k9 code)
#undef USE_DGR_LIGHT_SEQUENCE                    // Disable support for device group light sequencing (requires USE_DEVICE_GROUPS) (+0k2 code)

#undef USE_DS18x20                               // Disable DS18x20 sensor
#undef USE_MHZ19                                 // Disable support for MH-Z19 CO2 sensor
#undef USE_SENSEAIR                              // Disable support for SenseAir K30, K70 and S8 CO2 sensor
#undef USE_PMS5003                               // Disable support for PMS5003 and PMS7003 particle concentration sensor
#undef USE_NOVA_SDS                              // Disable support for SDS011 and SDS021 particle concentration sensor
#undef USE_HPMA                                  // Disable support for Honeywell HPMA115S0 particle concentration sensor
#undef USE_DYP                                   // Disable support for DYP ME-007 ultrasonic distance sensor, serial port version (+0k5 code)
#undef USE_SERIAL_BRIDGE                         // Disable support for software Serial Bridge
#undef USE_TCP_BRIDGE                            // DIsable support for Serial to TCP bridge (+1.3k code)
#undef USE_MP3_PLAYER                            // Disable DFPlayer Mini MP3 Player RB-DFR-562 commands: play, volume and stop
#undef USE_AZ7798                                // Disable support for AZ-Instrument 7798 CO2 datalogger
#undef USE_PN532_HSU                             // Disable support for PN532 using HSU (Serial) interface (+1k8 code, 140 bytes mem)
#undef USE_ZIGBEE                                // Disable serial communication with Zigbee CC2530 flashed with ZNP
#undef USE_RDM6300                               // Disable support for RDM6300 125kHz RFID Reader (+0k8)
#undef USE_IBEACON                               // Disable support for bluetooth LE passive scan of ibeacon devices (uses HM17 module)
#undef USE_HM10                                  // (ESP8266 only) Disable support for HM-10 as a BLE-bridge for the LYWSD03 (+5k1 code)
#undef USE_MI_ESP32                              // (ESP32 only) Disable support for ESP32 as a BLE-bridge (+9k2 mem, +292k flash)
#undef USE_HRXL                                  // Disable support for MaxBotix HRXL-MaxSonar ultrasonic range finders (+0k7)
#undef USE_TASMOTA_CLIENT                        // Disable support for Arduino Uno/Pro Mini via serial interface including flashing (+2k3 code, 44 mem)
#undef USE_OPENTHERM                             // Disable support for OpenTherm (+15k code)
#undef USE_MIEL_HVAC                             // Disable support for Mitsubishi Electric HVAC serial interface (+5k code)

#undef USE_PZEM004T                              // Disable PZEM004T energy sensor
#undef USE_PZEM_AC                               // Disable PZEM014,016 Energy monitor
#undef USE_PZEM_DC                               // Disable PZEM003,017 Energy monitor
#undef USE_MCP39F501                             // Disable MCP39F501 Energy monitor as used in Shelly 2
#undef USE_SDM120                                // Disable support for Eastron SDM120-Modbus energy meter
#undef USE_SDM630                                // Disable support for Eastron SDM630-Modbus energy monitor (+0k6 code)
#undef USE_DDS2382                               // Disable support for Hiking DDS2382 Modbus energy monitor (+0k6 code)
#undef USE_DDSU666                               // Disable support for Chint DDSU666 Modbus energy monitor (+0k6 code)
#undef USE_SOLAX_X1                              // Disable support for Solax X1 series Modbus log info (+3k1 code)
#undef USE_LE01MR                                // Disable support for F&F LE-01MR Modbus energy meter (+2k code)
#undef USE_TELEINFO                              // Disable support for French Energy Provider metering telemetry
#undef USE_IEM3000                               // Disable support for Schneider Electric iEM3000-Modbus series energy monitor (+0k8 code)
#undef USE_WE517                                 // Disable support for Orno WE517-Modbus energy monitor (+1k code)

#undef USE_DHT                                   // Disable support for DHT11, AM2301 (DHT21, DHT22, AM2302, AM2321) and SI7021 Temperature and Humidity sensor
#undef USE_MAX31855                              // Disable MAX31855 K-Type thermocouple sensor using softSPI
#undef USE_MAX31865                              // Disable support for MAX31865 RTD sensors using softSPI
#undef USE_LMT01                                 // Disable support for TI LMT01 temperature sensor, count pulses on single GPIO (+0k5 code)
#undef USE_TM1638                                // Disable support for TM1638 switches copying Switch1 .. Switch8
#undef USE_HX711                                 // Disable support for HX711 load cell
#undef USE_TX20_WIND_SENSOR                      // Disable support for La Crosse TX20 anemometer
#undef USE_TX23_WIND_SENSOR                      // Disable support for La Crosse TX23 anemometer
#undef USE_WINDMETER                             // Disable support for analog anemometer (+2k2 code)
#undef USE_RC_SWITCH                             // Disable support for RF transceiver using library RcSwitch
#undef USE_RF_SENSOR                             // Disable support for RF sensor receiver (434MHz or 868MHz) (+0k8 code)
#undef USE_HRE                                   // Disable support for Badger HR-E Water Meter (+1k4 code)
#undef USE_A4988_STEPPER                         // Disable support for A4988_Stepper

#ifdef CODE_IMAGE_STR
  #undef CODE_IMAGE_STR
#endif

#ifdef FIRMWARE_SENSORS
  #undef CODE_IMAGE_STR
  #define USE_ENERGY_SENSOR                        // Add energy sensors (-14k code)
  #define USE_ADE7953                            // [I2cDriver7] Enable ADE7953 Energy monitor as used on Shelly 2.5 (I2C address 0x38) (+1k5)
  #define CODE_IMAGE_STR CUSTOM_IMAGE_STR"_sensors"
#endif

#ifdef FIRMWARE_IR
  #undef CODE_IMAGE_STR
  #undef USE_ENERGY_SENSOR
  #undef USE_ADE7953
  #define CODE_IMAGE_STR CUSTOM_IMAGE_STR"_ir"
#endif

#ifdef FIRMWARE_MINIMAL
  #undef CODE_IMAGE_STR
  #undef USE_ENERGY_SENSOR
  #undef USE_ADE7953
  #define CODE_IMAGE_STR CUSTOM_IMAGE_STR"_minimal"
#endif

#ifdef FIRMWARE_IR_CUSTOM
  #undef CODE_IMAGE_STR
  #undef USE_ENERGY_SENSOR
  #undef USE_ADE7953
  #define CODE_IMAGE_STR CUSTOM_IMAGE_STR"_ir_custom"
#endif

#ifndef CODE_IMAGE_STR
  #undef USE_ENERGY_SENSOR
  #undef USE_ADE7953
  #define CODE_IMAGE_STR CUSTOM_IMAGE_STR"_standard"
#endif

#endif  // _USER_CONFIG_OVERRIDE_H_
