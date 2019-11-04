#include <SPI.h>    //This library allows for SPI communications to be used for the radio module as well as any other sensors that use SPI
#include <LoRa.h>   //The LoRa library allows for the LoRa communications to function. It imports all the initalization functions as well as the packet sending and recieving abilities
#include <EEPROM.h> //Allows for interaction with the EEPROM of the LoRa32u4, mainly for the UID assigning

//SPI setup for the radio module on LoRa32u4
//the numbers are set pins on the radio module to allow for communication between the LoRa32u4 microcontroller and radio module
#define SCK     15
#define MISO    14
#define MOSI    16
#define SS      8
#define RST     4
#define DI0     7
#define BAND 915E6    //for 915MHz (can also be on 433MHz or 868MHz
#define PABOOST true

//sets onewire comm pin. This may change depending on physical build
#define oneWire_Bus A0

int uid;
int count;

void setup() {
  uid = EEPROM.read(0x0000);//declares unique ID
  Serial.begin(9600);
  LoRa.setPins(SS,RST,DI0);
  LoRa.begin(BAND,PABOOST);
  if(!LoRa.begin(BAND,PABOOST))
  {
    Serial.println("Error with LoRa");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Working code\n");
  Serial.print("Count: ");
  Serial.println(count);
  
  //LoRa comms
  //These lines of code will construct a JSON packet and send it via LoRa protocol
  LoRa.beginPacket();

  LoRa.print("{ \"sensor\":\"Hello World\",");
  LoRa.print("\"count\":\""); 
  LoRa.print(count);
  
  LoRa.print("\", sensorID\":\"");           //JSON string for UID
  LoRa.print(uid);

  LoRa.print("\" }");
  LoRa.endPacket();

  count = count + 1;

  delay(3000);
}
