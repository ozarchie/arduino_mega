/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!RESTORE DEFAULTS!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void RestoreDefaults() {
  int i;
  //Temporary placeholders for Time Settings Screen
  tmp_month = 11;
  tmp_day = 3;
  tmp_year = 2016;
  tmp_hour = 12;
  tmp_minute = 0;
  tmp_second = 0;

  //Note: Committed Time Settings are stored as their associated month(), day(), year(), etc... as per <Time.h>
  tmp_Light_ON_hour = 18;    // 6PM
  tmp_Light_ON_min = 0;
  tmp_Light_OFF_hour = 6;    // 6AM
  tmp_Light_OFF_min = 0;

  //Committed Light Settings
  Light_ON_hour = 18;
  Light_ON_min = 0;
  Light_OFF_hour = 6;
  Light_OFF_min = 0;

  //Temporary placeholders for Pump Schedule Screen
  tmp_Pump_start_hour = 7;
  tmp_Pump_start_min = 15;
  tmp_Pump_start_isAM = true;
  tmp_Pump_every_hours = 2;
  tmp_Pump_every_mins = 0;
  tmp_Pump_for = 15; //In Minutes
  tmp_Pump_repeat = 1; //Number of times per day

  //Committed Pump Schedule Settings
  Pump_start_hour = 7;
  Pump_start_min = 15;
  Pump_start_isAM = true;
  Pump_every_hours = 2;
  Pump_every_mins = 0;
  Pump_for = 15; //In Minutes
  Pump_repeat = 1; //Number of times per day

  //SENSOR VARIABLES

  //Values the arduino sees
  pH1RawValue = 0;
  // jma pH2RawValue = 0;
  TempRawValue = 0;
  RHRawValue = 0;
  TDS1RawValue = 0;
  // jma TDS2RawValue = 0;
  CO2RawValue = 0;
  LightRawValue = 0;

  //Values the humans see
  pH1Value = 0;
  // jma pH2Value = 0;
  TempValue = 0;
  RHValue = 0;
  TDS1Value = 0;
  // jma TDS2Value = 0;
  CO2Value = 0;
  LightValue = 0;

  //Status Indicators and Limits
  strcpy(pH1_Status,"OK");
  pH1Value_Low = 5.60;
  pH1Value_High = 6.10;
/* jma
  strcpy(pH1_Status,"OK");
  pH2Value_Low = 5.60;
  pH2Value_High = 6.10;
jma */
  strcpy(Temp_Status,"OK");
  TempValue_Low = 21.00;
  TempValue_High = 29.00;

  strcpy(RH_Status,"OK");
  RHValue_Low = 30.00;
  RHValue_High = 80.00;

  //TDS2
  strcpy(TDS1_Status,"OK");
  TDS1Value_Low = 500.0;
  TDS1Value_High = 800.0;
/* jma
  strcpy(TDS2_Status,"OK");
  TDS2Value_Low = 500.0;
  TDS2Value_High = 800.0;
*/

//Accessory ON/OFF Values
  strcpy(CO2_Status,"OK");
  CO2Value_Low = 60.00;
  CO2Value_High= 75.00;

  strcpy(Light_Status,"OK");
  LightValue_Low = 20.00;
  LightValue_High = 95.00;

  //Accessory ON/OFF Values
  Heater_ON = 21.00;
  Heater_OFF = 25.00;
  AC_ON = 29.00;
  AC_OFF = 25.00;
  Humidifier_ON = 40.00;
  Humidifier_OFF = 60.00;
  Dehumidifier_ON = 80.00;
  Dehumidifier_OFF = 60.00;
  NutePump1_ON = 500.0;
  NutePump1_OFF = 800.0;
  MixPump1_Enabled = false;
/* jma
  NutePump2_ON = 500.0;
  NutePump2_OFF = 800.0;
  MixPump2_Enabled = false;
*/
  CO2_ON = 40.00;
  CO2_OFF = 60.00 ;
  CO2_Enabled = false;
  
  //Turn all relays off and set to manual mode by default
  //Relay_States
  for (i = 1; i < 7; i++) {
    turnRelay(i, 0);
  }
  
  for (i = 0; i < 6; i++) {
    Relay_State[i] = 0;
    Relay_isAuto[i] = 0;
  }

  saveE2PValues();
/* jma
  setTime(tmp_hour,tmp_minute,tmp_second,tmp_day,tmp_month,tmp_year);
  setSyncProvider(RTC.get);
*/

}

