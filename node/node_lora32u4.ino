// GEMS Agroinformatics Initiatve
// University of Minnesota
// 2019
 
// Contributors: Bryan Chantigian, Thor Solberg, Pete Marchetto, Bryan Runck

#include <SPI.h>
#include <LoRa.h>
#include <MD_TCS230.h>
#include <FreqCount.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <cactus_io_BME280_I2C.h>
#include <EEPROM.h>

//LoR32u4 915MHz V1.2 (white board)
#define SCK     15
#define MISO    14
#define MOSI    16
#define SS      8
#define RST     4
#define DI0     7
//#define BAND    433E6   //for 433MHz board
//#define BAND 868E6    //for 868MHz
#define BAND 915E6    //for 915MHz
#define PABOOST true

//sets onewire comm pin
#define oneWire_Bus A0

//sets moisure sensor pin
#define soilMoisture A1

//sets CAPACITIVE soil moisture sensor
#define soilMoistCAP A2

//sets color sensor pins
#define S2 13
#define S3 12
#define OE 11

BME280_I2C bme(0x76);   //configures the address for the bme280
OneWire onewire(oneWire_Bus);   //configures the OneWire Bus
DallasTemperature tempSensor(&onewire); //configures temp sensor to onewire bus

int uid;

//This function sets the PAR sensor to sense different colors by changing the selection pins
long senseColor(char color)
{
  if (color == 'W')
  {
    digitalWrite(S2, HIGH);
    digitalWrite(S3, LOW);
    return pulseIn(OE, LOW);
  }
  else if (color == 'R')
  {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    return pulseIn(OE, LOW);
  }
  else if (color == 'G')
  {
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    return pulseIn(OE, LOW);
  }
  else if (color == 'B')
  {
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    return pulseIn(OE, LOW);
  }
}

void setup()
{
  //******************************************************************************************************************************************************************************************************
//    EEPROM.write(0x0000,0x001F); //declares unique ID     MAKE SURE THIS IS DISABLED WHEN NOT ASSIGNING VALUES!!!!!!!!!!!!!!!! UPDATE EACH DEVICE WHEN MAKING A NEW NODE   //LAST UPDATE 0X0032
  //******************************************************************************************************************************************************************************************************
  uid = EEPROM.read(0x0000);
  
  //Sets Transmit power of LoRa
  LoRa.setTxPower(20);

  //sets the pins for LoRa comms
  Serial.begin(9600);
  LoRa.setPins(SS, RST, DI0);
  LoRa.begin((long)BAND, PABOOST);  //This line may need to have PABOOST deleted before uploading, some weird things happen sometimes

  // Starts bme and temp sensor
  bme.begin();
  tempSensor.begin();

  //sets cap soil moist to input
  pinMode(soilMoistCAP, INPUT);

  //setup Color Sensor
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OE, INPUT);
}

void loop()
{
  bme.readSensor();   //required to get separate readings
  tempSensor.requestTemperatures();   //sends bit-stream to request temp readings

  //CAP SOIL moist
  int SMCAP = analogRead(soilMoistCAP);

  //get Color data
  int red = senseColor('R');    //outputs time of low signal read in microseconds
  int blue = senseColor('B');
  int green = senseColor('G');
  int white = senseColor('W');

  //LoRa comms
  LoRa.beginPacket();
  LoRa.print("{ \"sensor\":\"WASECA\",");

  LoRa.print(" \"airtempC\":\"");             //JSON string for temp
  LoRa.print(bme.getTemperature_C());
  LoRa.print("\", ");

  LoRa.print("\"P\":\"");             //JSON stirng for pressure
  LoRa.print(bme.getPressure_HP());
  LoRa.print("\", ");

  LoRa.print("\"H\":\"");             //JSON string for humidity
  LoRa.print(bme.getHumidity());
  LoRa.print("\", ");

  LoRa.print("\"soilmoistureGyps\":\"");           //JSON string for soil Moisture
  LoRa.print(analogRead(soilMoisture));
  LoRa.print("\", ");

  LoRa.print("\"soilmoistureCap\":\"");   //JSON string for cap soil moist
  LoRa.print(analogRead(soilMoistCAP));
  LoRa.print("\", ");

  LoRa.print("\"soiltempC\":\"");           //JSON string for temp
  LoRa.print(tempSensor.getTempCByIndex(0));
  LoRa.print("\", ");

  LoRa.print("\"R\":\"");           //JSON string for red light value
  LoRa.print(red);
  LoRa.print("\", ");

  LoRa.print("\"B\":\"");           //JSON string for blue light value
  LoRa.print(blue);
  LoRa.print("\", ");

  LoRa.print("\"G\":\"");           //JSON string for green light value
  LoRa.print(green);
  LoRa.print("\", ");

  LoRa.print("\"W\":\"");           //JSON string for white light value
  LoRa.print(white);
  LoRa.print("\", ");

  LoRa.print("\"sensorID\":\"");           //JSON string for UID
  LoRa.print(uid);
  LoRa.print("\" }");
  LoRa.endPacket();

  Serial.print("TempBME: ");
  Serial.print(bme.getTemperature_C());
  Serial.print("\t");
  Serial.print(uid);
  //  Serial.print("\t");
  //  Serial.println(SMCAP);
  //  Serial.print("\t Pressure (kP): ");
  //  Serial.print(bme.getPressure_HP());
  //  Serial.print("\t Humidity: ");
  //  Serial.print(bme.getHumidity());
  //  Serial.print("\t Soil Moisture: ");
  //  Serial.print(analogRead(soilMoisture));
  Serial.print("\t TempDS18B20: ");
  Serial.print(tempSensor.getTempCByIndex(0));  //ByIndex refers to which IC is on the bus. Since there is only one the index is 0 since it is the first one
  ////  Serial.print("\t Red (us): ");    //returning times
  ////  Serial.print(red);
  ////  Serial.print("\t Blue (us): ");
  ////  Serial.print(blue);
  ////  Serial.print("\t Green (us): ");
  ////  Serial.print(green);
  ////  Serial.print("\t White (us): ");
  ////  Serial.println(white);
  Serial.print("\t Red (us): ");   //returning intensities
  Serial.print(red);
  Serial.print("\t Blue (us): ");
  Serial.print(blue);
  Serial.print("\t Green (us): ");
  Serial.print(green);
  Serial.print("\t White (us): ");
  Serial.println(white);

  delay(5000);
}
