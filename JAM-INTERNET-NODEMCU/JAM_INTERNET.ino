// JAM INTERNET
// NODEMCU
// LCD 2004 I2C
#include <NTPtimeESP.h>
//#include <ESP8266WiFi.h>
//#include <Wire.h>               // needed if you use esp8266
#include <LiquidCrystal_I2C.h>  //i2C LCD Library

//Persiapan LCD 20x4 I2C
LiquidCrystal_I2C lcd( 20, 4);

//Persiapan data NTP
NTPtime NTPch("id.pool.ntp.org");   // Pool NTP server Indonesia
char *ssid      = "annisa@RUMAH";   // WiFi SSID
char *password  = "";               // WiFi password
strDateTime dateTime;
String bulan[12]={"JAN","FEB","MAR","APR","MEI","JUN","JUL","AUG","SEP","OKT","NOP","DES"};

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin (ssid, password);
  //auto set i2c lcd address
  lcd.autoAddress();
  //memulai lcd
  lcd.begin();
  lcd.clear();
  // ============================================= // 
  lcd.print("    JAM INTERNET");
  lcd.setCursor(0,1);
  lcd.print("Mengkoneksikan");
  lcd.setCursor(0,2);
  while (WiFi.status() != WL_CONNECTED) {
    lcd.print(".");
    delay(500);
  }
  lcd.setCursor(0,1);
  lcd.print("Terkoneksi ke : ");
  lcd.setCursor(0,2);
  lcd.print(ssid);
  delay(500);
}

void loop() {
  //lcd.clear();
  //lcd.home();
  // first parameter: Time zone in floating point (for India); second parameter: 1 for European summer time; 2 for US daylight saving time (contributed by viewwer, not tested by me)
  dateTime = NTPch.getNTPtime(6, 2);
  
  // check dateTime.valid before using the returned time
  // Use "setSendInterval" or "setRecvTimeout" if required
  if(dateTime.valid){
    //NTPch.printDateTime(dateTime);
    byte actualHour = dateTime.hour;
    byte actualMinute = dateTime.minute;
    byte actualSecond = dateTime.second;
    int actualYear = dateTime.year;
    byte actualMonth = dateTime.month;
    byte actualDay =dateTime.day;
    byte actualdayofWeek = dateTime.dayofWeek;
    lcd.setCursor(0,3);
    //lcd.print("      "0 );
    lcd.print(actualHour);
    lcd.print(":");
    if(actualMinute<10)
      lcd.print("0");
    lcd.print(actualMinute);
    lcd.print(":");
    if(actualSecond<10)
      lcd.print("0");
    lcd.print(actualSecond);
    lcd.print(" ");
    if(actualDay<10)
      lcd.print("0");
    lcd.print(actualDay);
    lcd.print(":");
    actualMonth--;
    lcd.print(bulan[actualMonth]);
    lcd.print(":");
    lcd.print(actualYear);
  }
}
