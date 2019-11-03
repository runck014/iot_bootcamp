// GEMS Agroinformatics Initiatve
// University of Minnesota
// 2019
 
// Contributors: Bryan Chantigian, Thor Solberg, Pete Marchetto, Bryan Runck
#include <SPI.h>    //This library allows for SPI communications to be used for the radio module as well as any other sensors that use SPI
#include <LoRa.h>   //The LoRa library allows for the LoRa communications to function. It imports all the initalization functions as well as the packet sending and recieving abilities
#include <MD_TCS230.h>  //This library allows for the LoRa32u4 to communicate with the PAR sensor
//#include <FreqCount.h>  //I don't believe this library is used, most likely can be commended out
#include <Wire.h>   //This library allows for I2C communications on the LoRa board
#include <OneWire.h>  //This library allows for the LoRa to communicate with the DS18B20 temp sensor using onewire protocol
#include <DallasTemperature.h>  //This libaray also is required to communicate with the DS18B20 for the temperature measurments
#include <cactus_io_BME280_I2C.h>   //Allows for the BME280 to work with the LoRa32u4 and to pull data from the BME280
#include <EEPROM.h> //Allows for interaction with the EEPROM of the LoRa32u4, mainly for the UID assigning

//SPI setup for the radio module on LoRa32u4
//the numbers are set pins on the radio module to allow for communication between the LoRa32u4 microcontroller and radio module
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

//sets onewire comm pin. This may change depending on physical build
#define oneWire_Bus A0

//sets moisure sensor pin. This may change depending on physical build
#define soilMoisture A1

//sets CAPACITIVE soil moisture sensor. This may change depending on physical build
#define soilMoistCAP A2

//sets color sensor pins. These may change depending on physical build
#define S2 13
#define S3 12
#define OE 11

BME280_I2C bme(0x76);   //configures the address for the bme280
OneWire onewire(oneWire_Bus);   //configures the OneWire Bus
DallasTemperature tempSensor(&onewire); //configures temp sensor to onewire bus

int uid;

//This function sets the PAR sensor to sense different colors by changing the selection pins It returns the the time of the low signal in microseconds
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
  LoRa.begin((long)BAND);  //This line may need to have PABOOST deleted before uploading, some weird things happen sometimes

  // Starts bme and temp sensor
  bme.begin();
  tempSensor.begin();

  //sets cap soil moist to input
  pinMode(soilMoistCAP, INPUT);

  //setup Color Sensor pins
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OE, INPUT);
}

void loop()
{
  bme.readSensor();   //required to get separate readings, this sends a request for data retrieval
  tempSensor.requestTemperatures();   //sends bit-stream to request temp readings

  //CAP SOIL moist
  int SMCAP = analogRead(soilMoistCAP);

  //get Color data
  int red = senseColor('R');    //outputs time of low signal read in microseconds using the pulseIn function
  int blue = senseColor('B');
  int green = senseColor('G');
  int white = senseColor('W');

  //LoRa comms
  //These lines of code will construct and send the packet via LoRa protocol
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


  //Serial port writing for debugging
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

