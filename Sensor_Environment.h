#ifndef _SENSOR_ENVIRONMENT_H_
#define _SENSOR_ENVIRONMENT_H_

/* ------------------------------------------------------------------------- */

#include "Arduino.h"
#include "Pin_Connect.h"

/* ------------------------------------------------------------------------- */

#include <EEPROM.h>

#include "DFRobot_PH.h"
#include "GravityTDS.h"

#include <LiquidCrystal_I2C.h>
// #include <SoftwareSerial.h>

/* -------------- DEBUG (uncomment to open the Debug function) ------------- */

// #define ENABLE_DEBUG

#if defined(ENABLE_DEBUG)
#define Debug Serial
#define DEBUG_BEGIN(...) Debug.begin(__VA_ARGS__)
#define DEBUG_WRITE(...) Debug.write(__VA_ARGS__)
#define DEBUG_PRINT(...) Debug.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Debug.println(__VA_ARGS__)
#else
#define DEBUG_BEGIN(...)
#define DEBUG_WRITE(...)
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif

/* ------------------------------------------------------------------------- */

float convert_vol_to_NTU(float vol);
float ACS712_5A(byte pin);
float vol_divider_res(byte pin);

void display_LCD(LiquidCrystal_I2C *lcdPtr, float pH, float tds, float ntu, float cur, float vol);

// void reportToESP(SoftwareSerial *dataPtr, float pH, float tds, float ntu, float cur, float vol);
void reportToESP(HardwareSerial *dataPtr, float pH, float tds, float ntu, float cur, float vol);

/* ------------------------------------------------------------------------- */

#endif