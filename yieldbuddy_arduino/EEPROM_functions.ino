/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 !!EEPROM READ/WRITE FUNCTIONS!!EEPROM READ/WRITE FUNCTIONS!!EEPROM READ/WRITE FUNCTIONS!!EEPROM READ/WRITE FUNCTIONS!!EEPROM READ/WRITE FUNCTIONS!!EEPROM READ/WRITE FUNCTIONS!!EEPROM READ/WRITE FUNCTIONS!!EEPROM READ/WRITE FUNCTIONS!!EEPROM READ/WRITE FUNCTIONS!!
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void eepromClear() {  
  //Clear the EEPROM
  for (int i = 0; i < 4096; i++) {
    EEPROM.write(i, 0);
  }
  delay(100);
}

int eepromReadInt(int address){
  int value = 0x0000;
  value = value | (EEPROM.read(address) << 8);
  value = value | EEPROM.read(address+1);
  return value;
}

void eepromWriteInt(int address, int value){
  EEPROM.write(address, (value >> 8) & 0xFF );
  EEPROM.write(address+1, value & 0xFF);
}

float eepromReadFloat(int address){
  union u_tag {
    byte b[4];
    float fval;
  } 
  u;   
  u.b[0] = EEPROM.read(address);
  u.b[1] = EEPROM.read(address+1);
  u.b[2] = EEPROM.read(address+2);
  u.b[3] = EEPROM.read(address+3);
  return u.fval;
}

void eepromWriteFloat(int address, float value){
  union u_tag {
    byte b[4];
    float fval;
  } 
  u;
  u.fval=value;

  EEPROM.write(address  , u.b[0]);
  EEPROM.write(address+1, u.b[1]);
  EEPROM.write(address+2, u.b[2]);
  EEPROM.write(address+3, u.b[3]);
}


void loadE2PValues(void) {
/* jma
int i;
  //EEPROM TIME
  int eeprom_hr = EEPROM.read(E2P_hr);
  int eeprom_min = EEPROM.read(E2P_min);
  int eeprom_sec = EEPROM.read(E2P_sec);
  int eeprom_day = EEPROM.read(E2P_day);
  int eeprom_month = EEPROM.read(E2P_month);
  int eeprom_yr = EEPROM.read(E2P_year);

  //EEPROM Relay Saved Values
  for(i = 0; i < MAXRELAYS; i++){
    Relay_State[i] =  EEPROM.read(i+E2P_Relay_State);
    Relay_isAuto[i] = EEPROM.read(i+E2P_Relay_isAuto);

  // If Relay is not set for automatic mode, then resume last saved state 
  // (ie. Set relay as it was saved before a power failure?)
    if (Relay_isAuto[i] == 0) {
     turnRelay(i+1, Relay_State[i]); 
    }
  }

  //EEPROM Water Pump Schedule
  Pump_start_hour = EEPROM.read(E2P_Pump_start_hour);
  Pump_start_min = EEPROM.read(E2P_Pump_start_min);
  Pump_every_hours = EEPROM.read(E2P_Pump_every_hours);
  Pump_every_mins = EEPROM.read(E2P_Pump_every_mins);
  Pump_for = EEPROM.read(E2P_Pump_for);
  Pump_repeat = EEPROM.read(E2P_Pump_repeat);

  for(i = 0; i < MAXREPEAT; i++){
    Pump_hour_array[i] =  EEPROM.read(i+E2P_Pump_repeat+1);
    Pump_min_array[i] = EEPROM.read(i+E2P_Pump_repeat+1+MAXREPEAT);
    Pump_isAM_array[i] = EEPROM.read(i+E2P_Pump_repeat+1+2*MAXREPEAT);
  }

  //EEPROM Light Schedule
  Light_ON_hour = EEPROM.read(E2P_Light_ON_hour);
  Light_ON_min = EEPROM.read(E2P_Light_ON_min);
  Light_OFF_hour = EEPROM.read(E2P_Light_OFF_hour);
  Light_OFF_min = EEPROM.read(E2P_Light_OFF_min);
  
  //EEPROM Light Settings
  LightValue_Low = eepromReadFloat(E2P_LightValue_Low);
  LightValue_High = eepromReadFloat(E2P_LightValue_High);

  //EEPROM pH Settings
  pH1Value_Low = eepromReadFloat(E2P_pH1Value_Low);
  pH1Value_High = eepromReadFloat(E2P_pH1Value_High);
  pH2Value_Low = eepromReadFloat(E2P_pH2Value_Low);
  pH2Value_High = eepromReadFloat(E2P_pH2Value_High);

  //EEPROM Temp Settings
  TempValue_Low  = eepromReadFloat(E2P_TempValue_Low);
  TempValue_High = eepromReadFloat(E2P_TempValue_High);
  Heater_ON = eepromReadFloat(E2P_Heater_ON);
  Heater_OFF =eepromReadFloat(E2P_Heater_OFF);
  AC_ON = eepromReadFloat(E2P_AC_ON);
  AC_OFF = eepromReadFloat(E2P_AC_OFF);

  //EEPROM RH Settings
  RHValue_Low = eepromReadFloat(E2P_RHValue_Low);
  RHValue_High = eepromReadFloat(E2P_RHValue_High);
  Humidifier_ON = eepromReadFloat(E2P_Humidifier_ON);
  Humidifier_OFF = eepromReadFloat(E2P_Humidifier_OFF);
  Dehumidifier_ON = eepromReadFloat(E2P_Dehumidifier_ON);
  Dehumidifier_OFF = eepromReadFloat(E2P_Dehumidifier_OFF);

  //EEPROM TDS1 Settings
  TDS1Value_Low = eepromReadFloat(E2P_TDS1Value_Low);
  TDS1Value_High = eepromReadFloat(E2P_TDS1Value_High);
  NutePump1_ON = eepromReadFloat(E2P_NutePump1_ON);
  NutePump1_OFF = eepromReadFloat(E2P_NutePump1_OFF);
  if (EEPROM.read(E2P_MixPump1) == 1){
    MixPump1_Enabled = true;
  } 
  else {
    MixPump1_Enabled = false;
  }
  
  TDS2Value_Low = eepromReadFloat(E2P_TDS2Value_Low);
  TDS2Value_High = eepromReadFloat(E2P_TDS2Value_High);
  NutePump2_ON = eepromReadFloat(E2P_NutePump2_ON);
  NutePump2_OFF = eepromReadFloat(E2P_NutePump2_OFF);
  if (EEPROM.read(E2P_MixPump2) == 1){
    MixPump2_Enabled = true;
  } 
  else {
    MixPump2_Enabled = false;
  }

  //EEPROM CO2 Settings
  CO2Value_Low = eepromReadFloat(E2P_CO2Value_Low);
  CO2Value_High = eepromReadFloat(E2P_CO2Value_High);
  CO2_ON = eepromReadFloat(E2P_CO2_ON);
  CO2_OFF = eepromReadFloat(E2P_CO2_OFF);
  if (EEPROM.read(E2P_CO2_Enabled) == 1){
    CO2_Enabled = true;
  } 
  else {
    CO2_Enabled = false;
  }
*/
}

void saveE2PValues(void) {
/* jma
  int i;
// Relay States
// Relay isAuto
  for(i = 0; i < MAXRELAYS; i++){
    EEPROM.write(i+E2P_Relay_State,Relay_State[i]);
    EEPROM.write(i+E2P_Relay_isAuto,Relay_isAuto[i]);
  }

  //pH
  eepromWriteFloat(E2P_pH1Value_Low,pH1Value_Low);
  eepromWriteFloat(E2P_pH1Value_High,pH1Value_High);
  eepromWriteFloat(E2P_pH2Value_Low,pH2Value_Low);
  eepromWriteFloat(E2P_pH2Value_High,pH2Value_High);

  //Temp
  eepromWriteFloat(E2P_TempValue_Low,TempValue_Low);
  eepromWriteFloat(E2P_TempValue_High,TempValue_High);
  eepromWriteFloat(E2P_Heater_ON,Heater_ON);
  eepromWriteFloat(E2P_Heater_OFF,Heater_OFF);
  eepromWriteFloat(E2P_AC_ON,AC_ON);
  eepromWriteFloat(E2P_AC_OFF,AC_OFF);

  //RH
  eepromWriteFloat(E2P_RHValue_Low,RHValue_Low);
  eepromWriteFloat(E2P_RHValue_High,RHValue_High);
  eepromWriteFloat(E2P_Humidifier_ON,Humidifier_ON);
  eepromWriteFloat(E2P_Humidifier_OFF,Humidifier_OFF);
  eepromWriteFloat(E2P_Dehumidifier_ON,Dehumidifier_ON);
  eepromWriteFloat(E2P_Dehumidifier_OFF,Dehumidifier_OFF);

  //TDS1
  eepromWriteFloat(E2P_TDS1Value_Low,TDS1Value_Low);
  eepromWriteFloat(E2P_TDS1Value_High,TDS1Value_High);
  eepromWriteFloat(E2P_NutePump1_ON,NutePump1_ON);
  eepromWriteFloat(E2P_NutePump1_OFF,NutePump1_OFF);
  if (MixPump1_Enabled == true) {
    EEPROM.write(E2P_MixPump1,1);
  } 
  else {
    EEPROM.write(E2P_MixPump1,0);
  }

  //TDS2
  eepromWriteFloat(E2P_TDS2Value_Low,TDS2Value_Low);
  eepromWriteFloat(E2P_TDS2Value_High,TDS2Value_High);
  eepromWriteFloat(E2P_NutePump2_ON,NutePump2_ON);
  eepromWriteFloat(E2P_NutePump2_OFF,NutePump2_OFF);
  if (MixPump2_Enabled == true) {
    EEPROM.write(E2P_MixPump2,1);
  } 
  else {
    EEPROM.write(E2P_MixPump2,0);
  }

  //CO2
  eepromWriteFloat(E2P_CO2Value_Low,CO2Value_Low);
  eepromWriteFloat(E2P_CO2Value_High,CO2Value_High);
  eepromWriteFloat(E2P_CO2_ON,CO2_ON);
  eepromWriteFloat(E2P_CO2_OFF,CO2_OFF);
  if (CO2_Enabled == true) {
    EEPROM.write(E2P_CO2_Enabled,1);
  } 
  else {
    EEPROM.write(E2P_CO2_Enabled,0);
  }
  //Light
  eepromWriteFloat(E2P_LightValue_Low,LightValue_Low);
  eepromWriteFloat(E2P_LightValue_High,LightValue_High);

  EEPROM.write(E2P_Light_ON_hour, Light_ON_hour);
  EEPROM.write(E2P_Light_ON_min, Light_ON_min);
  EEPROM.write(E2P_Light_OFF_hour, Light_OFF_hour);
  EEPROM.write(E2P_Light_OFF_min, Light_OFF_min);

  //Pump
  EEPROM.write(E2P_Pump_start_hour,Pump_start_hour);
  EEPROM.write(E2P_Pump_start_min,Pump_start_min);
  EEPROM.write(E2P_Pump_every_hours,Pump_every_hours);
  EEPROM.write(E2P_Pump_every_mins,Pump_every_mins);
  EEPROM.write(E2P_Pump_for,Pump_for);
  EEPROM.write(E2P_Pump_repeat,Pump_repeat);

  for(i = 0; i < tmp_Pump_repeat; i++){
    Pump_hour_array[i]=  tmp_Pump_hour_array[i];
    Pump_min_array[i] = tmp_Pump_min_array[i];
    Pump_isAM_array[i] = tmp_Pump_isAM_array[i];
    EEPROM.write((i+E2P_Pump_repeat+1),Pump_hour_array[i]);
    EEPROM.write((i+E2P_Pump_repeat+1+MAXREPEAT),Pump_min_array[i]);
    EEPROM.write((i+E2P_Pump_repeat+1+2*MAXREPEAT),Pump_isAM_array[i]);
  }

  //Save Time Settings
  EEPROM.write(E2P_hr,tmp_hour);
  EEPROM.write(E2P_min,tmp_minute);
  EEPROM.write(E2P_sec,tmp_second);
  EEPROM.write(E2P_day,tmp_day);
  EEPROM.write(E2P_month,tmp_month);
  EEPROM.write(E2P_year,tmp_year);
*/
}

