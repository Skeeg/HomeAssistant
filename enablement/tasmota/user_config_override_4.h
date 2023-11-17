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
#define STA_PASS1         "PASSWORDHERE"     // [Password1] Wifi password

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

#define WIFI_CONFIG_TOOL       WIFI_RETRY        // [WifiConfig] Default tool if Wi-Fi fails to connect (default option: 4 - WIFI_RETRY)
                                                 // (WIFI_RESTART, WIFI_MANAGER, WIFI_RETRY, WIFI_WAIT, WIFI_SERIAL, WIFI_MANAGER_RESET_ONLY)
                                                 // The configuration can be changed after first setup using WifiConfig 0, 2, 4, 5, 6 and 7.

#ifdef SONOFF_SERIAL_LOG
  #undef SERIAL_LOG_LEVEL
  #define SERIAL_LOG_LEVEL       LOG_LEVEL_NONE    // [SerialLog] (LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE)
#endif

#define USE_RULES   // Ensure Rules can be used

#ifdef FIRMWARE_MINIMAL

  #ifdef USE_PROMETHEUS
    #undef USE_PROMETHEUS
  #endif

  #ifdef USE_HOME_ASSISTANT
    #undef USE_HOME_ASSISTANT
  #endif 

  #ifdef USE_RULES
    #undef USE_RULES
  #endif

#endif


#endif  // _USER_CONFIG_OVERRIDE_H_
