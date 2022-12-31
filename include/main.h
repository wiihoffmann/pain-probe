#ifndef MAIN_H_
#define MAIN_H_

//DEFINES-----------------------------------------------------------------------------------

//#define PROBE_DEBUG                                           //enable to view more messages on serial and oled display

#define DEFAULT_CALIBRATION_FACTOR 500.00
#define DEFAULT_VAS_FREQ 1 
#define DEFAULT_TARGET_ROC 50.0
#define DEFAULT_MAX_PRESSURE 1000
#define DEFAULT_KNOWN_WEIGHT 0.050
#define DEFAULT_UNIQUE_ID 3545338634
#define DEFAULT_PREV_UNIQUE_ID 3545338634
#define DEFAULT_PREV_TEST 1
#define DEFAULT_PREV_SUB 0
#define DEFAULT_INTERVAL 1000
#define DEFAULT_SITE_LABEL "undefined"

#define SCREEN_WIDTH 128                                        // OLED display width, in pixels
#define SCREEN_HEIGHT 64                                        // OLED display height, in pixels
#define OLED_RESET 4

#define HX711_DATA 26
#define HX711_CLK 25

//DEFINES END--------------------------------------------------------------------------------

//INCLUDES---------------------------------------------------------------------------------
#include <Arduino.h>
#include <FS.h>                   //this needs to be first, or it all crashes and burns...

// #include <esp_system.h>
// #include <EEPROM.h>


// #define ARDUINOJSON_USE_LONG_LONG 1     
// #include <ArduinoJson.h>
#include "SPIFFS.h"

#include <SPI.h>
#include <Wire.h>
#include "Adafruit_I2CDevice.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Circular_Gauge.h"                         //https://github.com/ximon/Circular-Gauge-Demo
#include <HX711.h>                                  //https://github.com/SensorsIot/Weight-Sensors/tree/master/HX711

//INCLUDES END------------------------------------------------------------------------------

//GLOBAL CLASSES-----------------------------------------------------------------------------
extern Adafruit_SSD1306 Display;
extern Circular_Gauge Gauge;
extern HX711 Probe;


#endif