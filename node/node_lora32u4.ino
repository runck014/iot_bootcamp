// GEMS Agroinformatics Initiatve
// University of Minnesota
// 2019
 
// Contributors: Bryan Chantigian, Thor Solberg, Pete Marchetto, Bryan Runck

#include <LoRa.h>
#include <SoftwareSerial.h>

//Setup LORA
#define SCK     15
#define MISO    14
#define MOSI    16
#define SS      8
#define RST     4
#define DIO     7
//#define BAND    433E6   //for 433MHz board
//#define BAND 868E6    //for 868MHz
#define BAND 915E6    //for 915MHz
#define PABOOST true 

#define NODE_SIZE 2
#define ARRAY_SIZE 200

int dataPos = 0;
char data[ARRAY_SIZE];
String particleData;

SoftwareSerial uart(0, 1);  //RX, TX

void clearBuffer(void)
{
  for(int j = 0; j < ARRAY_SIZE; j++)
  {
    data[j] = 0;
  }
}

void setup() {  
  Serial.begin(9600);
  uart.begin(115200);     //UART baud rate, match with photon baud rate

  LoRa.setPins(SS,RST,DIO);
  LoRa.begin((long)BAND, PABOOST);
}

void loop() {

  int packetLength = LoRa.parsePacket();

  if(packetLength)    //if the packet length > 0 then read data
  {
        Serial.print("Recieved Packet Size: ");
        Serial.println(packetLength);
        
        for(int i = 0; i < packetLength; i++)       //stores each char in part of the data array
        {
             data[i] = LoRa.read();
        }

        particleData = data;        //changes char array to string
        
        clearBuffer();

        uart.print(particleData);
        Serial.println(particleData);
        Serial.println(" ");
    }  

}
