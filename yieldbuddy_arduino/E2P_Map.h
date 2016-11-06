// Time
#define E2P_hr    0
#define E2P_min    1
#define E2P_sec    2
#define E2P_day    3
#define E2P_month  4
#define E2P_year    5

// Relay State
#define MAXRELAYS 6

#define E2P_Relay_State    6
#define E2P_Relay_isAuto    211

//EEPROM Water Pump Schedule
#define MAXREPEAT 16

#define E2P_Pump_start_hour  21
#define E2P_Pump_start_min    22
#define E2P_Pump_every_hours  23
#define E2P_Pump_every_mins    24
#define E2P_Pump_for          25
#define E2P_Pump_repeat        26

//EEPROM Light Schedule
#define E2P_Light_ON_hour    76
#define E2P_Light_ON_min      209
#define E2P_Light_OFF_hour    77
#define E2P_Light_OFF_min    210

//EEPROM Light Settings
#define E2P_LightValue_Low    172
#define E2P_LightValue_High    E2P_LightValue_Low+4

//EEPROM pH Settings
#define E2P_pH1Value_Low      78
#define E2P_pH1Value_High      E2P_pH1Value_Low+4
#define E2P_pH2Value_Low      180
#define E2P_pH2Value_High      E2P_pH2Value_Low+4

//EEPROM Temp Settings
#define E2P_TempValue_Low      86
#define E2P_TempValue_High     E2P_TempValue_Low+4
#define E2P_Heater_ON          E2P_TempValue_High+4
#define E2P_Heater_OFF         E2P_Heater_ON+4
#define E2P_AC_ON              E2P_Heater_OFF+4
#define E2P_AC_OFF             E2P_AC_ON+4

//EEPROM RH Settings
#define E2P_RHValue_Low        110
#define E2P_RHValue_High       E2P_RHValue_Low+4
#define E2P_Humidifier_ON      E2P_RHValue_High+4
#define E2P_Humidifier_OFF     E2P_Humidifier_ON+4
#define E2P_Dehumidifier_ON    E2P_Humidifier_OFF+4
#define E2P_Dehumidifier_OFF   E2P_Dehumidifier_ON+4

//EEPROM TDS1 Settings
#define E2P_TDS1Value_Low      134
#define E2P_TDS1Value_High     E2P_TDS1Value_Low+5
#define E2P_NutePump1_ON       E2P_TDS1Value_High+5
#define E2P_NutePump1_OFF      E2P_NutePump1_ON+5

#define E2P_MixPump1           E2P_NutePump1_OFF+5

//EEPROM TDS2 Settings
#define E2P_TDS2Value_Low      188
#define E2P_TDS2Value_High     E2P_TDS2Value_Low+5
#define E2P_NutePump2_ON       E2P_TDS2Value_High+5
#define E2P_NutePump2_OFF      E2P_NutePump2_ON+5

#define E2P_MixPump2           E2P_NutePump2_OFF+5

//EEPROM CO2 Settings
#define E2P_CO2Value_Low       155
#define E2P_CO2Value_High      E2P_CO2Value_Low+4
#define E2P_CO2_ON             E2P_CO2Value_High+4
#define E2P_CO2_OFF            E2P_CO2_ON+4
#define E2P_CO2_Enabled        E2P_CO2_OFF+4

