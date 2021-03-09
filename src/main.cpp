#include <Config.h>
#include <CustomChars.h>
#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <arduino-timer.h>


/**
 * Global VARS
 * 
 */ 
OneWire ourWire(TEMP_SENSOR);                //Se establece el pin 2  como bus OneWire 
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
LiquidCrystal_I2C	lcd(I2C_ADDR,LCD_COL,LCD_ROW);
auto timer = timer_create_default(); // create a timer with default settings
float ph = 0.0;
float temperature = 0.0;
bool balancing = false;

/**
 * Funtions declaration
 * 
 */
float readPh();
float readTemp();
bool isPHBalanced();
void printStatus();
void balance();
void unlockBalance();




void setup() {
  Serial.begin(9600);
  sensors.begin();
  Wire.begin();
  pinMode(OUTPUT_1,OUTPUT);
  pinMode(OUTPUT_2,OUTPUT);
  pinMode(OUTPUT_3,OUTPUT);
  pinMode(OUTPUT_4,OUTPUT);
  digitalWrite(OUTPUT_1,INACTIVE);
  digitalWrite(OUTPUT_2,INACTIVE);
  digitalWrite(OUTPUT_3,INACTIVE);
  digitalWrite(OUTPUT_4,INACTIVE);
  lcd.init();  
  lcd.backlight();
  lcd.createChar(0,deltaChar);
  lcd.print("Inicializando ...");
}

void loop() {
  ph = readPh();
  temperature = readTemp();
  if ( ! isPHBalanced() );
    balance();
  printStatus();
  timer.tick();
}

float readPh(){
  unsigned long int avgValue = 0;  //Store the average value of the sensor feedback
  for(int i=0;i<SAMPLE_SIZE;i++)   //Get 10 sample value from the sensor for smooth the value
  { 
    avgValue+=analogRead(A0);
    delay(10);
  }
  float phValue = (float)avgValue*MODULE_VOLTAGE/1024/SAMPLE_SIZE; //convert the analog into millivolt
  phValue = 3.5*phValue;                      //convert the millivolt into pH value
  #ifdef DEBUG
    Serial.print("[ " + millis());
    Serial.print(" ]");
    Serial.print("Ph: ");
    Serial.print(phValue);
    Serial.print("\n");
  #endif
  return phValue;
}

float readTemp(){
  sensors.requestTemperatures();   
  float t =  sensors.getTempCByIndex(0);
  #ifdef DEBUG
    Serial.print("[ " + millis());
    Serial.print(" ]");
    Serial.print("Temp: ");
    Serial.print(t);
    Serial.print(" °C\n");
  #endif
}

void printStatus(){       
  lcd.home (); 
  lcd.print("Ph: ");
  lcd.print(ph);
  lcd.print(" > ");
  lcd.print(PH_TARGET);
  lcd.write(0);
  lcd.print(PH_MAX_UNBALANCE);
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0,2);
  char outputs[100] = {'\0'};
  sprintf(outputs,"OUT_1: %s  OUT_2: %s",digitalRead(OUTPUT_1) ? "NO" : "SI", digitalRead(OUTPUT_2)? "NO" : "SI");
  lcd.print(outputs);
  lcd.setCursor(0,3);
  sprintf(outputs,"OUT_3: %s  OUT_4: %s",digitalRead(OUTPUT_3)? "NO" : "SI", digitalRead(OUTPUT_4)? "NO" : "SI");
  lcd.print(outputs);
}

bool isPHBalanced(){
  return  ph > PH_TARGET + PH_MAX_UNBALANCE || ph < PH_TARGET - PH_MAX_UNBALANCE;
}

void balance(){
  if (balancing)
    return;
  if(ph > ( PH_TARGET + PH_MAX_UNBALANCE ) ){
    digitalWrite(PH_HIGH_OUTPUT,ACTIVE);
    printStatus();
    delay(PH_BALANCE_ACTION_RUN);
    digitalWrite(PH_HIGH_OUTPUT,INACTIVE);
    balancing = true;
    timer.in(PH_BALANCE_ACTION_INTERVAL * 1000 , unlockBalance);
  }
  if(ph < ( PH_TARGET - PH_MAX_UNBALANCE ) ){
    digitalWrite(PH_LOW_OUTPUT,ACTIVE);
    printStatus();
    delay(PH_BALANCE_ACTION_RUN);
    digitalWrite(PH_LOW_OUTPUT,INACTIVE);
    balancing = true;
    timer.in(PH_BALANCE_ACTION_INTERVAL * 1000 , unlockBalance);
  }
}

void unlockBalance(){
  balancing = false;
}