#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>


#define SAMPLE_SIZE 100
#define MODULE_VOLTAGE 5 
#define I2C_ADDR    0x3F  // Define I2C Address where the SainSmart LCD is
#define LCD_ROW 4
#define LCD_COL 20

#define PH_SENSOR A0
#define EC_SENSOR A1
#define TEMP_SENSOR 3

#define OUTPUT_1 50 // Relay 1
#define OUTPUT_2 51 // Relay 2
#define OUTPUT_3 52 // Relay 3
#define OUTPUT_4 53 // Relay 4

#define ACTIVE LOW
#define INACTIVE HIGH

#define PH_TARGET 5.8
#define PH_MAX_UNBALANCE 0.2
#define PH_BALANCE_ACTION_RUN 500 //MILISECONDS
#define PH_BALANCE_ACTION_INTERVAL 120 //SECONDS
#define PH_LOW_OUTPUT OUTPUT_1 // IF ph low activate realy 1
#define PH_HIGH_OUTPUT OUTPUT_2 // IF ph high activate relay 2


#define DEBUG
#endif