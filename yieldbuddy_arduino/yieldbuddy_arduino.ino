
#include <dht.h>   // Latest DHTnn library
//#include <PCF8583.h>
#include <Time.h>
//#include <PString.h>
#include <EEPROM.h>
#include "E2P_Map.h"
#include <Wire.h>
#include <DS1307RTC.h>
#include <avr/pgmspace.h>
#include "Arduino.h"

/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!VARIABLES!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
//String Serial_inString = "";
boolean stringComplete = false;
int serialcounter = 0;
int serialincounter = 0;

char SerialBuffer[80] = { 1,1,1,1,1,1,1,1,1,1,              // Testing, until the problem with PString() was found
                          2,2,2,2,2,2,2,2,2,2,
                          3,3,3,3,3,3,3,3,3,3,
                          4,4,4,4,4,4,4,4,4,4,
                          5,5,5,5,5,5,5,5,5,5,
                          6,6,6,6,6,6,6,6,6,6,
                          7,7,7,7,7,7,7,7,7,7,
                          8,8,8,8,8,8,8,8,8,8
                          };
int  pSerialBuffer = 0;
char* message[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};      // Maximum 16 elements in array
  
char longdate[25] = "Nov  1, 2016 12:00:00 AM";
char pH1_char[6] = "00.00";
char pH2_char[6] = "00.00";
char Temp_char[8]= "";
char RH_char[7] = "00.00%";
char TDS1_char[10] = "0000.0ppm";
char TDS2_char[11] = "0000.0ppm";
char CO2_char[7] = "00.00%";
char Light_char[7] = "00.00%";

//Temporary placeholders for Time Settings Screen
int tmp_month;
int tmp_day;
int tmp_year;
int tmp_hour;
int tmp_minute;
int tmp_second;
int last_minute;  // Flag for current time to be flushed to e2p

//Temporary placeholders for Light Schedule Screen
int tmp_send;
int tmp_Light_ON_hour;
int tmp_Light_ON_min;
int tmp_Light_OFF_hour;
int tmp_Light_OFF_min;
//Committed Light Settings
int Light_ON_hour = 18;
int Light_ON_min = 0;
int Light_OFF_hour = 6;
int Light_OFF_min = 0;

//Temporary placeholders for Pump Schedule Screen
int tmp_Pump_start_hour;
int tmp_Pump_start_min;
boolean tmp_Pump_start_isAM = true;
int tmp_Pump_every_hours;
int tmp_Pump_every_mins;
int tmp_Pump_for; //In Minutes
int tmp_Pump_repeat; //Number of times per day

int tmp_Pump_hour_array[16];
int tmp_Pump_min_array[16];
boolean tmp_Pump_isAM_array[16];
//Committed Pump Schedule Settings
int Pump_start_hour = 7;
int Pump_start_min = 15;
boolean Pump_start_isAM = true;
int Pump_every_hours = 2;
int Pump_every_mins = 0;
int Pump_for = 15; //In Minutes
int Pump_repeat = 1; //Number of times per day

// Allow for pump schedules (Set in E2P_Map.h)
int Pump_hour_array[MAXREPEAT];
int Pump_min_array[MAXREPEAT];
boolean Pump_isAM_array[MAXREPEAT];

/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!SENSOR VARIABLES!!SENSOR VARIABLES!!SENSOR VARIABLES!!SENSOR VARIABLES!!SENSOR VARIABLES!!SENSOR VARIABLES!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
//Values the arduino sees
int pH1RawValue = 0;
int pH2RawValue = 0;
int TempRawValue = 0;
int RHRawValue = 0;
int TDS1RawValue = 0;
int TDS2RawValue = 0;
int CO2RawValue = 0;
int LightRawValue = 0;

//Values the humans see (after it has been calculated using raw values above ^^^ and their respected formulas)
float pH1Value = 0;
float pH2Value = 0;
float TempValue = 0;
float RHValue = 0;
float TDS1Value = 0;
float TDS2Value = 0;
float CO2Value = 0;
float LightValue = 0;

//PH
//Status Indicator Values
char  pH1_Status[4] = "OK";
float pH1Value_Low = 5.60;
float pH1Value_High = 6.10;
char  pH2_Status[4] = "OK";
float pH2Value_Low = 5.60;
float pH2Value_High = 6.10;

//Temp
char  Temp_Status[4] = "OK";
float TempValue_Low = 21.00;
float TempValue_High = 29.00;
//Accessory ON/OFF Values
float Heater_ON = 21.00;
float Heater_OFF = 25.00;
float AC_ON = 29.00;
float AC_OFF = 25.00;

//Humidty(RH)
char  RH_Status[4] = "OK";
float RHValue_Low = 30.00;
float RHValue_High = 80.00;
//Accessory ON/OFF Values
float Humidifier_ON = 40.00;
float Humidifier_OFF = 60.00;
float Dehumidifier_ON = 80.00;
float Dehumidifier_OFF = 60.00;

//TDS1
char  TDS1_Status[4] = "OK";
float TDS1Value_Low = 500.0;
float TDS1Value_High = 800.0;
//Accessory ON/OFF Values
float NutePump1_ON = 500.0;
float NutePump1_OFF = 800.0;
boolean MixPump1_Enabled = true;

//TDS2
char  TDS2_Status[4] = "OK";
float TDS2Value_Low = 500.0;
float TDS2Value_High = 800.0;
//Accessory ON/OFF Values
float NutePump2_ON = 500.0;
float NutePump2_OFF = 800.0;
boolean MixPump2_Enabled = true;

//CO2
char  CO2_Status[4] = "OK";
float CO2Value_Low = 60.00;
float CO2Value_High= 75.00;
//Accessory ON/OFF Values
float CO2_ON = 40.00;
float CO2_OFF = 60.00 ;
boolean CO2_Enabled = true;

//Light
char  Light_Status[4] = "OK";
float LightValue_Low = 20.00;
float LightValue_High = 95.00;


/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!PIN DEFINITIONS!!PIN DEFINITIONS!!PIN DEFINITIONS!!PIN DEFINITIONS!!PIN DEFINITIONS!!PIN DEFINITIONS!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
 
 // Analog pins
int pH1Pin = A2;
//int pH2Pin = A3;
// int TempPin = A0;
int TDS1Pin = A4;
//int TDS2Pin = A5;
int CO2Pin = A0;
int LightPin = A1;

// Digital pins
//RH
#define DHTPIN 2
dht DHT;
// Termperature sensors

// Relays, SSR
// Currently 6 relays, MAXRELAYS set in E2P_Map.h
// Only relay 6 is SSR

// Relay1_Pin = 3;  //Water Pump 1
// Relay2_Pin = 4;  //Water Pump 2
// Relay3_Pin = 5;  //Free
// Relay4_Pin = 6;  //Free
// Relay5_Pin = 7;  //Free
// Relay6_Pin = 8;  //SSR (Light/Ballast)
#define SSR 5
#define WP1 0
#define WP2 1

int Relay_Pin[6] = { 3, 4, 5, 6, 7, 8 };
int Relay_State[6] = { 1, 1, 0, 0, 0, 0 };
int Relay_isAuto[6] = { 1, 1, 0, 0, 0, 1 };

// Utility functions
// =================
void UIToStr(char *str, unsigned int val, unsigned char len, unsigned int dp)
{
    str += len;          // Point to end of string
    if (dp) str += 1;    //  add '.' if required
    *str = '\0';         // NULL terminate

    while (len--)
    {
        *--str = (val % 10) + '0';
        val /= 10;
        if ((--dp) == 0) *--str = '.'; 
    }
}
/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!SETUP!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void setup()
{
  int i;
  //Set Pin Modes
  for (i = 0; i < 6; i++) {
    pinMode(Relay_Pin[i], OUTPUT);
  }

  //Safe-Route ---> Disregard last known states and turn all relays off (auto will take over):
  for (i = 1; i < 7; i++) {
    turnRelay(i, 0);
  }


  //------------------------------------------------------------------------------

  //Load default time first, then try the RTC.
  //Set-Time  setTime(hr,min,sec,day,month,yr);
  setTime(12,0,0,3,11,2016);
  //jma setSyncProvider(RTC.get);
  RestoreDefaults();
  Serial.begin(9600);
  Serial.println("YB Firmware V2.1");
}


/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!LOOP!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void loop()
{
//  Serial.println("loop"); 
  while (1){
    turnRelay(3, 0);
//  Serial.print("1.");
    updatelongdate();
//  Serial.print("2.");
    updateSensorValues();
//  Serial.print("3.");
    serialEvent();
//  Serial.print("4.");
    sendserialmessages();
//  Serial.print("5.");
//  CheckTimers();
//  Serial.print("6.");
//  serialEvent();
//  Serial.print("7.");
//  CheckSetPoints();
    turnRelay(3, 1);
    delay(1000);
  }
}











