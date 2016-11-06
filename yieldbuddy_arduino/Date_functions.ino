/*
/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 /!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!UPDATE LONG DATE!!
 /!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
void updatelongdate() {

  //MONTH
  char month_buffer[4];
  int monthint = month();

  switch (monthint) {
  case 1:
    strcpy(month_buffer,"Jan");
    break;
  case 2:
    strcpy(month_buffer,"Feb");
    break;  
  case 3:
    strcpy(month_buffer,"Mar");
    break; 
  case 4:
    strcpy(month_buffer,"Apr");
    break;
  case 5:
    strcpy(month_buffer,"May");
    break; 
  case 6:
    strcpy(month_buffer,"Jun");
    break;
  case 7:
    strcpy(month_buffer,"Jul");
    break;
  case 8:
    strcpy(month_buffer,"Aug");
    break;
  case 9:
    strcpy(month_buffer,"Sep");
    break;
  case 10:
    strcpy(month_buffer,"Oct");
    break;
  case 11:
    strcpy(month_buffer,"Nov");
    break;
  case 12:
    strcpy(month_buffer,"Dec");
    break;
  }

  //DAY
  char day_buffer[3];
  int dayint = day();
  UIToStr(day_buffer, dayint, 2, 0);
  //YEAR
  char year_buffer[5];
  int yearint = year();
  UIToStr(year_buffer, yearint, 4, 0);
  //HOUR
  char hour_buffer[3];
  int hourint = hour();
  if (hourint > 12) {
    hourint = hourint - 12; 
  }
  UIToStr(hour_buffer, hourint, 2, 0);
  //MINUTE
  char minute_buffer[3];
  int minuteint = minute();
  UIToStr(minute_buffer, minuteint, 2, 0);
  //SECOND
  char second_buffer[3];
  int secondint = second();
  UIToStr(second_buffer, secondint, 2, 0);
  // AM/PM
  char am_pm_buffer[3];
  if (isAM() ==true){
    strcpy(am_pm_buffer, "AM");
  } 
  else if (isAM()==false) {
    strcpy(am_pm_buffer, "PM");
  }

  //COMBINED LONG FORMAT DATE
  // char longdate[25] = "Nov  1, 2016 12:00:00 AM";
  // updates char longdate[22];
  strcpy (longdate,month_buffer);
  strcat (longdate," ");
  strcat (longdate,day_buffer);
  strcat (longdate," ");
  strcat (longdate,year_buffer);
  strcat (longdate," ");
  strcat (longdate,hour_buffer);
  strcat (longdate,":");
  strcat (longdate,minute_buffer);
  strcat (longdate,":");
  strcat (longdate,second_buffer);
  strcat (longdate," ");
  strcat (longdate,am_pm_buffer);

// Write current Date/Time to e2p when minute() changes
  if (last_minute != minute()) {
/* jma    
    EEPROM.write(0,hour());
    EEPROM.write(1,minute());
    EEPROM.write(2,second());
    EEPROM.write(3,day());
    EEPROM.write(4,month());
    EEPROM.write(5,year());
*/
    last_minute = minute();
  }
  
}
