#

; List of modules I have for sure used
USE_I2C              // I2C using library wire (+10k code, 0k2 mem, 124 iram)
USE_ADE7953          // [I2cDriver7] Enable ADE7953 Energy monitor as used on Shelly 2.5 (I2C address 0x38) (+1k5)
USE_BMP              // [I2cDriver10] Enable BMP085/BMP180/BMP280/BME280 sensors (I2C addresses 0x76 and 0x77) (+4k4 code)
USE_BH1750           // [I2cDriver11] Enable BH1750 sensor (I2C address 0x23 or 0x5C) (+0k5 code)
USE_LIGHT            // Add Dimmer/Light support
USE_WS2812           // WS2812 Led string using library NeoPixelBus (+5k code, +1k mem, 232 iram)
USE_ENERGY_SENSOR    // Add energy sensors (-14k code)
SUPPORT_IF_STATEMENT // Add support for IF statement in rules (+4k2 code, -332 bytes mem)
USE_IR_REMOTE_FULL   // Support all IR protocols from IRremoteESP8266
USE_IR_RECEIVE       // Support for IR receiver (+5k5 code, 264 iram)
USE_IR_REMOTE        // Send IR remote commands using library IRremoteESP8266 and ArduinoJson (+4k code, 0k3 mem, 48 iram)

; List of modules that I have used before, but I don't think I have actually rolled out.
USE_SR04                          // Add support for HC-SR04 ultrasonic devices (+1k code)
USE_BME680                        // Enable support for BME680 sensor using Bosch BME680 library (+4k code)
USE_COUNTER                       // Enable counters
USE_WS2812_HARDWARE NEO_HW_WS2812 // Hardware type (NEO_HW_WS2812, NEO_HW_WS2812X, NEO_HW_WS2813, NEO_HW_SK6812, NEO_HW_LC8812, NEO_HW_APA106)
USE_WS2812_CTYPE NEO_GRB          // Color type (NEO_RGB, NEO_GRB, NEO_BRG, NEO_RBG, NEO_RGBW, NEO_GRBW)
USE_EXPRESSION                    // Add support for expression evaluation in rules (+3k2 code, +64 bytes mem) 

;   3 "Feit DIM/WIFI"          // 1mb-simple or 1mb-three-way-switch
;  17 "Gosund KS-602S Active"  // 1mb-simple or 1mb-three-way-switch
;   7 "Gosund KS-602S Control" // 1mb-simple or 1mb-three-way-switch
;  14 "Maxcio Active"          // 1mb-simple or 1mb-three-way-switch
;   1 "Maxcio Control"         // 1mb-simple or 1mb-three-way-switch
;  24 "Sonoff Basic"           // 1mb-simple or 1mb-three-way-switch
;   4 "Sonoff+I2C"             // 1mb-sonoff-bme280
;   6 "Sonoff S31"             // 1mb-smart-plug
;  21 "W-US002S"               // 1mb-smart-plug
;   1 "NodeMCU"                // 4mb-loaded
;   1 "WemoD1Mini"             // 4mb-loaded
;   1 "Generic"                // 4mb-loaded ?
