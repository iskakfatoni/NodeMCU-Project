#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#define  UTAMA  D0
#define  TERAS  D1
#define  KAMAR  D2
#define  KIPAS  D3

// Setting koneksi WiFi
const char* ssid     = "annisa@RUMAH";
const char* password = "";
WiFiClient client;

//Setting data Thingspeak
unsigned long channelID = 297700;
const char * writeAPIKey = "666B91KCBSI1ZCAN";
const char * myReadAPIKey = "A46ZT3K5HKSIFP5X";
int dataUtama, dataTeras, dataKamar, dataKipasAngin;

void setup() {
  Serial.begin(9600);  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Mengkoneksikan ke : ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.print("WiFi terkoneksi ke : ");
  Serial.println(ssid);
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);
  // Setting Relay
  pinMode(UTAMA, OUTPUT);
  pinMode(KAMAR, OUTPUT);
  pinMode(TERAS, OUTPUT);
  pinMode(KIPAS, OUTPUT);
}

void loop() {
  Serial.println("");
  dataUtama=ThingSpeak.readIntField(channelID, 1, myReadAPIKey);
  dataTeras=ThingSpeak.readIntField(channelID, 2, myReadAPIKey);
  dataKamar=ThingSpeak.readIntField(channelID, 3, myReadAPIKey);
  dataKipasAngin=ThingSpeak.readIntField(channelID, 4, myReadAPIKey);
  //CEK KONDISI LAMPU KAMAR UTAMA
  Serial.println("================================");
  Serial.print("Data Lampu Kamar Utama : ");
  if(dataUtama==100)
  {
    Serial.println("NYALA");
    digitalWrite(UTAMA, LOW);
  }
  else
  {
    Serial.println("PADAM");
    digitalWrite(UTAMA, HIGH);
  }

  //CEK KONDISI LAMPU TERAS
  Serial.print("Data Lampu Teras       : ");
  if(dataTeras==100)
  {
    Serial.println("NYALA");
    digitalWrite(TERAS, LOW);
  }
  else
  {
    Serial.println("PADAM");
    digitalWrite(TERAS, HIGH);
  }

  //CEK KONDISI LAMPU KAMAR
  Serial.print("Data Lampu Kamar       : ");
  if(dataKamar==100)
  {
    Serial.println("NYALA");
    digitalWrite(KAMAR, LOW);
  }
  else
  {
    Serial.println("PADAM");
    digitalWrite(KAMAR, HIGH);
  }

  //CEK KONDISI KIPAS ANGIN
  Serial.print("Data Kipas Angin       : ");
  if(dataKipasAngin==100)
  {
    Serial.println("NYALA");
    digitalWrite(KIPAS, LOW);
  }
  else
  {
    Serial.println("PADAM");
    digitalWrite(KIPAS, HIGH);
  }
  Serial.println("================================");
  delay(1000);
}
