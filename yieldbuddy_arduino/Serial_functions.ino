#include "Arduino.h"
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!SEND SERIAL MESSAGE!!!!SEND SERIAL MESSAGE!!SEND SERIAL MESSAGE!!SEND SERIAL MESSAGE!!SEND SERIAL MESSAGE!!SEND SERIAL MESSAGE!!SEND SERIAL MESSAGE!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void sendserialmessages(){

  //The purpose of 'serialcounter' is so that serial messages are not sent as one big chunk of data every 'loop()', instead they are split up
  //into 3 chunks, and those chunks are then sent every second loop (over a period of a total of 5 'loop()s')
  //However, Sensors and Relay values are sent every 1st and 4th messages.

  if (serialcounter == 1 || serialcounter == 4 || serialcounter == 7){
    //SEND TIMESTAMP
    updatelongdate();
    
    Serial.print("Time,");
    Serial.print(longdate);
    Serial.print(",");
    Serial.print(month());
    Serial.print(",");
    Serial.print(day());
    Serial.print(",");
    Serial.print(year());
    Serial.print(",");
    Serial.print(hour());
    Serial.print(",");
    Serial.print(minute());
    Serial.print(",");
    Serial.println(second());
    //SENSOR VALUES
    Serial.print("Sensors,");
    Serial.print(pH1Value);
    Serial.print(",");
    Serial.print(pH1Value);     // jma sb pH2
    Serial.print(",");
    Serial.print(TempValue);
    Serial.print(",");
    Serial.print(RHValue);
    Serial.print(",");
    Serial.print(TDS1Value);
    Serial.print(",");
    Serial.print(TDS1Value);    // jma sb TDS2
    Serial.print(",");
    Serial.print(CO2Value);
    Serial.print(",");
    Serial.println(LightValue);
  
    sendRelayMessages(); //<<---- Relays and Relay_isAutoMessages
  }
  
 
  if (serialcounter == 3) { 

    //LIGHTS
    Serial.print("Light_Schedule,");
    Serial.print(Light_ON_hour);
    Serial.print(",");
    Serial.print(Light_ON_min);
    Serial.print(",");
    Serial.print(Light_OFF_hour);
    Serial.print(",");
    Serial.println(Light_OFF_min);
    //WATERING
    Serial.print("Watering_Schedule,");
    Serial.print(Pump_start_hour);
    Serial.print(",");
    Serial.print(Pump_start_min);
    Serial.print(",");
    if (Pump_start_isAM == true) {
      Serial.print("1,");
    } 
    else {
      Serial.print("0,");
    }
    Serial.print(Pump_every_hours);
    Serial.print(",");
    Serial.print(Pump_every_mins);
    Serial.print(",");
    Serial.print(Pump_for);
    Serial.print(",");
    Serial.println(Pump_repeat);
  }

  if (serialcounter == 4) {
    //SETPOINTS
    //pH1
    Serial.print("SetPoint_pH1,");
    Serial.print(pH1Value_Low);
    Serial.print(",");
    Serial.print(pH1Value_High);
    Serial.print(",");
    Serial.println(pH1_Status);
  }
/* jma  
  if (serialcounter == 5) { 

    //pH2
    Serial.print("SetPoint_pH2,");
    Serial.print(pH2Value_Low);
    Serial.print(",");
    Serial.print(pH2Value_High);
    Serial.print(",");
    Serial.println(pH1_Status);
  }
*/
  if (serialcounter == 6) { 
    //Temp
    Serial.print("SetPoint_Temp,");
    Serial.print(TempValue_Low);
    Serial.print(",");
    Serial.print(TempValue_High);
    Serial.print(",");
    Serial.print(Heater_ON);
    Serial.print(",");
    Serial.print(Heater_OFF);
    Serial.print(",");
    Serial.print(AC_ON);
    Serial.print(",");
    Serial.print(AC_OFF);
    Serial.print(",");
    Serial.println(Temp_Status);
  } 
  if (serialcounter == 7) { 
    //RH
    Serial.print("SetPoint_RH,");
    Serial.print(RHValue_Low);
    Serial.print(",");
    Serial.print(RHValue_High);
    Serial.print(",");
    Serial.print(Humidifier_ON);
    Serial.print(",");
    Serial.print(Humidifier_OFF);
    Serial.print(",");
    Serial.print(Dehumidifier_ON);
    Serial.print(",");
    Serial.print(Dehumidifier_OFF);
    Serial.print(",");        
    Serial.println(RH_Status);
  }

  if (serialcounter == 8) {
    //TDS1
    Serial.print("SetPoint_TDS1,");
    Serial.print(TDS1Value_Low);
    Serial.print(",");
    Serial.print(TDS1Value_High);
    Serial.print(",");
    Serial.print(NutePump1_ON);
    Serial.print(",");
    Serial.print(NutePump1_OFF);
    Serial.print(",");
    Serial.print(MixPump1_Enabled);
    Serial.print(",");
    Serial.println(TDS1_Status);
  }
/* jma
  if (serialcounter == 9) { 
    //TDS2
    Serial.print("SetPoint_TDS2,");
    Serial.print(TDS2Value_Low);
    Serial.print(",");
    Serial.print(TDS2Value_High);
    Serial.print(",");
    Serial.print(NutePump2_ON);
    Serial.print(",");
    Serial.print(NutePump2_OFF);
    Serial.print(",");
    Serial.print(MixPump2_Enabled);
    Serial.print(",");
    Serial.println(TDS2_Status);
  }

  if (serialcounter == 10) { 
    //CO2
    Serial.print("SetPoint_CO2,");
    Serial.print(CO2Value_Low);
    Serial.print(",");
    Serial.print(CO2Value_High);
    Serial.print(",");
    Serial.print(CO2_ON);
    Serial.print(",");
    Serial.print(CO2_OFF);
    Serial.print(",");
    Serial.print(CO2_Enabled);
    Serial.print(",");
    Serial.println(CO2_Status);
  }
*/
  if (serialcounter == 11) { 
    //Light
    Serial.print("SetPoint_Light,");
    Serial.print(LightValue_Low);
    Serial.print(",");
    Serial.print(LightValue_High);
    Serial.print(",");
    Serial.println(Light_Status); 

    serialcounter = 0;
  }
  serialcounter++;
//  Serial.println(serialcounter);
}

/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!serialEvent!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void serialEvent() {

  int i, j, r, n = 0;
  while ((Serial.available() > 0) && (stringComplete == false)) {
    // get the new byte:
    char inChar = (char)Serial.read();

    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
    else {
      SerialBuffer[pSerialBuffer++] = inChar;
      SerialBuffer[pSerialBuffer] = 0x00;
    }
  }
  // Found a string, so parse it and action
  // --------------------------------------
  if (stringComplete == true) {
   stringComplete = false;
//   Serial.print("Command: ");
   Serial.println(SerialBuffer);
   
   // Parse
   // Scan string buffer and separate into sub-strings (if any)
   pSerialBuffer = 0;
   while ((SerialBuffer[pSerialBuffer] != 0) && (i < 16)) {
     message[i]=&SerialBuffer[pSerialBuffer];
     i += 1;
     while ((SerialBuffer[pSerialBuffer] != ',') && (SerialBuffer[pSerialBuffer] != 0)){
       pSerialBuffer += 1;
     }
     if (SerialBuffer[pSerialBuffer] != 0 ) {
       SerialBuffer[pSerialBuffer] = 0; // Null terminate sub-string
       pSerialBuffer += 1;              // Go past
     }
   }
   i -= 1;
   pSerialBuffer = 0;
/*
   Serial.print("Cmd: ");
   Serial.println(message[0]);
   Serial.println(message[1]);
   Serial.println(message[2]);
   Serial.println(message[3]);
   Serial.println(message[4]);
   Serial.println(message[5]);
   Serial.println(message[6]);
   Serial.println(i);   
*/
   // Action
      j = 99;
    if (strcmp(message[0], "Relay1 on") == 0) {
      j = 0;
      r = 0;
    }
    else if (strcmp(message[0], "Relay1 off") == 0) {
      j = 1;
      r = 0;
    }
    else if (strcmp(message[0], "Relay2 on") == 0) {
      j = 2;
      r = 1;
    }
    else if (strcmp(message[0], "Relay2 off") == 0) {
      j = 3;
      r = 1;
    }
    else if (strcmp(message[0], "Relay6 on") == 0) {
      j = 10;
      r = 5;
    }
    else if (strcmp(message[0], "Relay6 off") == 0) {
      j = 11;
      r = 5;
    }
    else if (strcmp(message[0], "Relay1 isAuto 1") == 0) {
      j = 12;
      r = 0;
    }
    else if (strcmp(message[0], "Relay1 isAuto 0") == 0) {
      j = 13;
      r = 0;
    }
    else if (strcmp(message[0], "Relay2 isAuto 1") == 0) {
      j = 14;
      r = 1;
    }
    else if (strcmp(message[0], "Relay2 isAuto 0") == 0) {
      j = 15;
      r = 1;
    }
    else if (strcmp(message[0], "Relay6 isAuto 1") == 0) {
      j = 22;
      r = 5;
    }
    else if (strcmp(message[0], "Relay6 isAuto 0") == 0) {
      j = 23;
      r = 5;
    }
    else if (strcmp(message[0], "restoredefaults") == 0) {
      j = 24;
    }
    else if (strcmp(message[0], "setdate") == 0) {
      j = 25;
      n = 6;
    }
    else if (strcmp(message[0], "setlightschedule") == 0) {
      j = 26;
      n = 4;
    }
    else if (strcmp(message[0], "setwateringschedule") == 0) {
      j = 27;
      n = 6;
    }
    else if (strcmp(message[0], "setpH1") == 0) {
      j = 28;
      r = 0;
      n = 2;
    }
    else if (strcmp(message[0], "setpH2") == 0) {
      j = 29;
      r = 1;
      n = 2;
    }
    else if (strcmp(message[0], "setTemp") == 0) {
      j = 30;
      n = 6;
    }
    else if (strcmp(message[0], "setRH") == 0) {
      j = 31;
      n = 6;
    }
    else if (strcmp(message[0], "setTDS1") == 0) {
      j = 32;
      r = 0;
      n = 5;
    }
    else if (strcmp(message[0], "setTDS2") == 0) {
      j = 33;
      r = 1;
      n = 5;
    }
    else if (strcmp(message[0], "setCO2") == 0) {
      j = 34;
      n = 5;
    }
    else if (strcmp(message[0], "setLight") == 0) {
      j = 35;
      n = 5;
    }

/*
   Serial.print("CmdIndex: ");
   Serial.println(j);
   Serial.print("Options : ");
   Serial.println(i);
   Serial.print("Command : ");
   Serial.println(message[0]);
*/
// Execute the commands
// ====================

    switch(j) {
    // Relays On/Off
     case 0:
     case 2:
     case 10:
     case 1:
     case 3:
     case 11:
       if (i == 0) {
          if ((j & 1) == 0) {
            Relay_State[r] = 1;
  //        EEPROM.write((E2P_Relay_State+r),1);
            turnRelay((r+1), 1);
          }
          else {
            Relay_State[r] = 0;
  //        EEPROM.write((E2P_Relay_State+r),0);
            turnRelay((r+1), 0);
          }
          sendRelayMessages();
       }
       else j = 98;
       break;
    // Relays Auto On/Off
     case 12:
     case 14:
     case 22:
     case 13:
     case 15:
     case 23:
       if (i == 0) {
          if ((j & 1) == 0) {
            Relay_isAuto[r] = 1;
  //        EEPROM.write((E2P_Relay_isAuto+r),1);
            turnRelay((r+1), 1);
          }
          else {
            Relay_isAuto[r] = 0;
  //        EEPROM.write((E2P_Relay_isAuto+r),0);
            turnRelay((r+1), 0);
          }
          sendRelayMessages();
       }
       else j = 98;
       break;
    // Restore defaults
     case 24:
       if (i == 0) {
         RestoreDefaults();
       }
       else j = 98;
       break;
    // Set Date
     case 25:
       if (i == n) {
         int parsed_month = atoi(message[1]);
         int parsed_day = atoi(message[2]);
         int parsed_year = atoi(message[3]);
         int parsed_hour = atoi(message[4]);
         int parsed_minute = atoi(message[5]);
         int parsed_second = atoi(message[6]);
      
         setTime(parsed_hour,parsed_minute,parsed_second,parsed_day,parsed_month,parsed_year);
         now();
         tmp_hour=hour();
         tmp_minute=minute();
         tmp_second=second();
         tmp_day=day();
         tmp_month=month();
         tmp_year=year();
       }
       else j = 98;
       break;
    // Set Light Schedule
     case 26:
       if (i == n) {
        int parsed_Light_ON_hour = atoi(message[1]);
        int parsed_Light_ON_min = atoi(message[2]);
        int parsed_Light_OFF_hour = atoi(message[3]);
        int parsed_Light_OFF_min = atoi(message[4]);

        Light_ON_hour = parsed_Light_ON_hour;
        Light_ON_min = parsed_Light_ON_min;
        Light_OFF_hour = parsed_Light_OFF_hour;
        Light_OFF_min = parsed_Light_OFF_min;
/* jma
        EEPROM.write(E2P_Light_ON_hour, Light_ON_hour);
        EEPROM.write(E2P_Light_OFF_hour, Light_OFF_hour);
        EEPROM.write(E2P_Light_ON_min, Light_ON_min);
        EEPROM.write(E2P_Light_OFF_min, Light_OFF_min);
*/
       }
       else j = 98;
       break;
    // Set Watering Schedule
     case 27:
       if ( i == n) {
          int parsed_Pump_start_hour = atoi(message[1]);
          int parsed_Pump_start_min = atoi(message[2]);
          int parsed_Pump_every_hours = atoi(message[3]);
          int parsed_Pump_every_mins = atoi(message[4]);
          int parsed_Pump_for = atoi(message[5]);
          int parsed_Pump_repeat = atoi(message[6]);
  
          Pump_start_hour = parsed_Pump_start_hour;
          Pump_start_min = parsed_Pump_start_min;
          Pump_every_hours = parsed_Pump_every_hours;
          Pump_every_mins = parsed_Pump_every_mins;
          Pump_for = parsed_Pump_for;
          Pump_repeat = parsed_Pump_repeat;
  /* jma
          EEPROM.write(E2P_Pump_start_hour,Pump_start_hour);
          EEPROM.write(E2P_Pump_start_min,Pump_start_min);
          EEPROM.write(E2P_Pump_every_hours,Pump_every_hours);
          EEPROM.write(E2P_Pump_every_mins,Pump_every_mins);
          EEPROM.write(E2P_Pump_for,Pump_for);
          EEPROM.write(E2P_Pump_repeat,Pump_repeat);
  */
          FillPumpTimesArrays(Pump_start_hour, Pump_start_min, Pump_every_hours, Pump_every_mins, Pump_for, Pump_repeat);

          i = 0;
          for(i = 0; i < Pump_repeat; i++){
            Pump_hour_array[i]=  tmp_Pump_hour_array[i];
            Pump_min_array[i] = tmp_Pump_min_array[i];
            Pump_isAM_array[i] = tmp_Pump_isAM_array[i];
//            EEPROM.write((i+E2P_Pump_repeat+1),Pump_hour_array[i]);
//            EEPROM.write((i+E2P_Pump_repeat+1+MAXREPEAT),Pump_min_array[i]);
//            EEPROM.write((i+E2P_Pump_repeat+1+2*MAXREPEAT),Pump_isAM_array[i]);
          }
          i = 0;
       }
       else j = 98;
       break;
    // Set pH Limits
     case 28:
     case 29:
       if ( i == n) {
         if ((j & 1) == 0) {
          float parsed_pH1Value_Low = atof(message[1]);
          float parsed_pH1Value_High = atof(message[2]);
          pH1Value_Low = parsed_pH1Value_Low;
          pH1Value_High = parsed_pH1Value_High;
  /* jma
          eepromWriteFloat(E2P_pH1Value_Low, parsed_pH1Value_Low);
          eepromWriteFloat(E2P_pH1Value_High, parsed_pH1Value_High);  
  
         }
         else {
          float parsed_pH2Value_Low = atof(message[1]);
          float parsed_pH2Value_High = atof(message[2]);
          pH1Value_Low = parsed_pH2Value_Low;
          pH1Value_High = parsed_pH2Value_High;
  /* jma
          eepromWriteFloat(E2P_pH2Value_Low, parsed_pH2Value_Low);
          eepromWriteFloat(E2P_pH2Value_High, parsed_pH2Value_High);  
  */
         }
       }
       else j = 98;
       break;
    // Set Temperature Limits
     case 30:
       if (n == i) {

        float parsed_TempValue_Low = atof(message[1]);
        float parsed_TempValue_High = atof(message[2]);
        float parsed_Heater_ON = atof(message[3]);
        float parsed_Heater_OFF = atof(message[4]);
        float parsed_AC_ON = atof(message[5]);
        float parsed_AC_OFF = atof(message[6]);

        TempValue_Low = parsed_TempValue_Low;
        TempValue_High = parsed_TempValue_High;
        Heater_ON = parsed_Heater_ON;
        Heater_OFF = parsed_Heater_OFF;
        AC_ON = parsed_AC_ON;
        AC_OFF = parsed_AC_OFF;
/* jma
        eepromWriteFloat(E2P_TempValue_Low, parsed_TempValue_Low);
        eepromWriteFloat(E2P_TempValue_High, parsed_TempValue_High);  
        eepromWriteFloat(E2P_Heater_ON, parsed_Heater_ON);
        eepromWriteFloat(E2P_Heater_OFF, parsed_Heater_OFF);  
        eepromWriteFloat(E2P_AC_ON, parsed_AC_ON);
        eepromWriteFloat(E2P_AC_OFF, parsed_AC_OFF);  
*/           
       }
       else j = 98;
       break;
    // Set Relative Humidity Limits
     case 31:
       if (n == i) {
        float parsed_RHValue_Low = atof(message[1]);
        float parsed_RHValue_High = atof(message[2]);
        float parsed_Humidifier_ON = atof(message[3]);
        float parsed_Humidifier_OFF = atof(message[4]);
        float parsed_Dehumidifier_ON = atof(message[5]);
        float parsed_Dehumidifier_OFF = atof(message[6]);

        RHValue_Low = parsed_RHValue_Low;
        RHValue_High = parsed_RHValue_High;
        Humidifier_ON = parsed_Humidifier_ON;
        Humidifier_OFF = parsed_Humidifier_OFF;
        Dehumidifier_ON = parsed_Dehumidifier_ON;
        Dehumidifier_OFF = parsed_Dehumidifier_OFF;
/* jma
        eepromWriteFloat(E2P_RHValue_Low, parsed_RHValue_Low);
        eepromWriteFloat(E2P_RHValue_High, parsed_RHValue_High);  
        eepromWriteFloat(E2P_Humidifier_ON, parsed_Humidifier_ON);
        eepromWriteFloat(E2P_Humidifier_OFF, parsed_Humidifier_OFF);  
        eepromWriteFloat(E2P_Dehumidifier_ON, parsed_Dehumidifier_ON);
        eepromWriteFloat(E2P_Dehumidifier_OFF, parsed_Dehumidifier_OFF);  
*/         
       }
       else j = 98;
       break;
    // Set TDS Limits
     case 32:
     case 33:
       if (n == i) {

         float parsed_TDSValue_Low = atof(message[1]);
         float parsed_TDSValue_High = atof(message[2]);
         float parsed_NutePump_ON = atof(message[3]);
         float parsed_NutePump_OFF = atof(message[4]);
         int parsed_MixPump_Enabled = atoi(message[5]);
          
         if ((j & 1) == 0) {  
          TDS1Value_Low = parsed_TDSValue_Low;
          TDS1Value_High = parsed_TDSValue_High;
          NutePump1_ON = parsed_NutePump_ON;
          NutePump1_OFF = parsed_NutePump_OFF;
  
          if (parsed_MixPump_Enabled == 1) {
            MixPump1_Enabled = true;
  //          EEPROM.write(E2P_MixPump1, 1);
          } 
          else if(parsed_MixPump_Enabled == 0) {
            MixPump1_Enabled = false;
  //          EEPROM.write(E2P_MixPump1, 0);            
          }
  /* jma
          eepromWriteFloat(E2P_TDS1Value_Low, parsed_TDS1Value_Low);
          eepromWriteFloat(E2P_TDS1Value_High, parsed_TDS1Value_High);  
          eepromWriteFloat(E2P_NutePump1_ON, parsed_NutePump1_ON);
          eepromWriteFloat(E2P_NutePump1_OFF, parsed_NutePump1_OFF);  
       
         }
        else {
          TDS2Value_Low = parsed_TDSValue_Low;
          TDS2Value_High = parsed_TDSValue_High;
          NutePump2_ON = parsed_NutePump_ON;
          NutePump2_OFF = parsed_NutePump_OFF;
  
          if (parsed_MixPump_Enabled == 1) {
            MixPump2_Enabled = true;
  //          EEPROM.write(E2P_MixPump2, 1);
          } 
          else if(parsed_MixPump_Enabled == 0) {
            MixPump2_Enabled = false;
  //          EEPROM.write(E2P_MixPump2, 0);            
          }
  /* jma
          eepromWriteFloat(E2P_TDS2Value_Low, parsed_TDS2Value_Low);
          eepromWriteFloat(E2P_TDS2Value_High, parsed_TDS2Value_High);  
          eepromWriteFloat(E2P_NutePump2_ON, parsed_NutePump2_ON);
          eepromWriteFloat(E2P_NutePump2_OFF, parsed_NutePump2_OFF);  
  */          
        }         
       }
       else j = 98;
       break;
    // Set/Enable CO2 Limits
     case 34:
       if (n == i) {
        float parsed_CO2Value_Low = atof(message[1]);
        float parsed_CO2Value_High = atof(message[2]);
        float parsed_CO2_ON = atof(message[3]);
        float parsed_CO2_OFF = atof(message[4]);
        int parsed_CO2_Enabled = atoi(message[5]);

        CO2Value_Low = parsed_CO2Value_Low;
        CO2Value_High = parsed_CO2Value_High;
        CO2_ON = parsed_CO2_ON;
        CO2_OFF = parsed_CO2_OFF;
/* jma
        eepromWriteFloat(E2P_CO2Value_Low, parsed_CO2Value_Low);
        eepromWriteFloat(E2P_CO2Value_High, parsed_CO2Value_High);  
        eepromWriteFloat(E2P_CO2_ON, parsed_CO2_ON);
        eepromWriteFloat(E2P_CO2_OFF, parsed_CO2_OFF);  
*/
        if (parsed_CO2_Enabled == 1) {
          CO2_Enabled = true;
//          EEPROM.write(E2P_CO2_Enabled, 1);
        } 
        else if(parsed_CO2_Enabled == 0) {
          CO2_Enabled = false;
//          EEPROM.write(E2P_CO2_Enabled, 0);            
        }
       }
       else j = 98;
       break;
    // Set Light Times
     case 35:
       if (i == n) {
        float parsed_LightValue_Low = atof(message[1]);
        float parsed_LightValue_High = atof(message[2]);
        LightValue_Low = parsed_LightValue_Low;
        LightValue_High = parsed_LightValue_High;
/* jma
        eepromWriteFloat(E2P_LightValue_Low, parsed_LightValue_Low);
        eepromWriteFloat(E2P_LightValue_High, parsed_LightValue_High);  
*/
       }
       else j = 98;
       break;
    // Bad command
     default:
       j = 0;
       break;
    }
  }
}
      

void sendRelayMessages() {
  int i;
  //RELAYS
    Serial.print("Relays");
    for (i = 0; i < 5; i++) {
      Serial.print(",");
      if (digitalRead(Relay_Pin[i]) == LOW){
        Serial.print(1);
      }
      else if (digitalRead(Relay_Pin[i]) == HIGH){
        Serial.print(0);
      }
    }
    //The SSR is opposite
    Serial.print(",");
    if (digitalRead(Relay_Pin[i]) == LOW){
      Serial.print(0);
    }
    else if (digitalRead(Relay_Pin[i]) == HIGH){
      Serial.print(1);
    }

    Serial.print("\n");
    //Relay_isAuto Values (Modes)
    Serial.print("Relay_isAuto");
    for (i = 0; i < 6; i++) {
      Serial.print(",");
      Serial.print(Relay_isAuto[i]);
    } 
    Serial.print("\n");
}
