#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>


#define SAMPLE_SIZE 100
#define MODULE_VOLTAGE 5 
#define I2C_ADDR    0x3F  // Define I2C Address where the SainSmart LCD is
#define LCD_ROW 4
#define LCD_COL 20
#define TEMP_SENSOR A1

#define OUTPUT_1 46 // PH LOW MOTOR
#define OUTPUT_2 48 // PH UP  MOTOR
#define OUTPUT_3 50
#define OUTPUT_4 52

#define ACTIVE LOW
#define INACTIVE HIGH

#define PH_TARGET 5.8
#define PH_MAX_UNBALANCE 0.2
#define PH_BALANCE_ACTION_RUN 500 //MILISECONDS
#define PH_BALANCE_ACTION_INTERVAL 120 //SECONDS

#define DEBUG
#endif