
#include <SPI.h>
#include <MFRC522.h>
#include <String.h>
//#include <WiFiClient.h>
#include<ESP8266WiFi.h>

#define RST_PIN         0          // Configurable, see typical pin layout above
#define SS_PIN          2         // Configurable, see typical pin layout above
#define valid           4
#define invalid         5

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
String uidString;
char ssid[] = "Manthan";      // your network SSID (name)
char password[] = "manthan2299";   // your network password
char server[] = "192.168.43.169";
char valid_uid[]="461267867";
int status = WL_IDLE_STATUS;
WiFiClient client;

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();
  pinMode(valid,OUTPUT);
  pinMode(invalid,OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
                    // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring or change I2C address!");
   
  }  
}
void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( mfrc522.PICC_IsNewCardPresent()) {
    readRFID();
    delay(1500);
    return;
  }
  
}
void readRFID() {
  mfrc522.PICC_ReadCardSerial();
  Serial.print("Tag UID: ");
  uidString = String(mfrc522.uid.uidByte[0])  + String(mfrc522.uid.uidByte[1])  + 
    String(mfrc522.uid.uidByte[2])  + String(mfrc522.uid.uidByte[3]);
  Serial.println(uidString);
  if(uidString==valid_uid){
  
  digitalWrite(valid,HIGH);
  delay(2000);
  digitalWrite(valid,LOW);
  
  if (client.connect(server, 81)) {
    Serial.println("--> connection ok\n");
     // And this is what we did in the testing section above. We are making a GET request just like we would from our browser but now with live data from the senso  
  
  client.print("GET /post_data.php?"); // This
  client.print("value="); // This
  client.print(uidString);
  client.println(" HTTP/1.1"); // Part of the GET request
  client.print( "Host: " );
  client.println(server);
  client.println("Connection: close");
  client.println(); // Empty line
  client.println(); // Empty line
  client.stop();   
  }
  else{
     // If Arduino can't connect to the server (your computer or web page)
    Serial.println("--> connection failed\n");
  }}
  else{
     digitalWrite(invalid,HIGH);
     delay(2000);
     digitalWrite(invalid,LOW);
    
  }
  // Sound the buzzer when a card is read
  
}
