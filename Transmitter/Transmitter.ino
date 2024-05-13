#include <RH_NRF24.h>
//#include "DHT.h"
#include <EEPROM.h>
 
// RH_NRF24 nrf24(2, 4); // use this for NodeMCU Amica/AdaFruit Huzzah ESP8266 Feather
RH_NRF24 nrf24(8, 7); // use this with Arduino UNO/Nano
 
//#define DHTPIN D1
////#define DHTPIN 2
// 
//#define DHTTYPE DHT11 
//DHT dht(DHTPIN, DHTTYPE);


 
int deviceID = EEPROM.read(0);
int humidity;
 
void setup()
{
  Serial.begin(115200);
//   dht.begin();
  while (!Serial)
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init()) 
  {
    Serial.println("init failed");
 
  }
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(3)) 
  {
    Serial.println("setChannel failed");
  }
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm)) {
    Serial.println("setRF failed");
  }
  Serial.println("Transmitter started");
}
 
void loop() 
{
  
  humidity = 1;
//  temperature = dht.readTemperature();

int tempSensorVal = analogRead(A0);
// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = tempSensorVal * (4.30 / 1023.0);
  float temperature = voltage*100;
  // print out the value you read:
//  Serial.println("Voltage : ");
//  Serial.println(voltage);
  Serial.println("Temperature : ");
  Serial.println(temperature);
  delay(500);

  
  
  Serial.println("Sending to gateway");
  uint8_t data[4];
  
  data[0] = humidity;
  data[1] = temperature;
  data[2] = deviceID;
  
  Serial.println("------------- Measurements -------------");
  Serial.print("Humidity: ");
  Serial.print(data[0]);
  
  Serial.print(", Temperature: ");
  Serial.print(data[1]);
 
  Serial.print(", ID: ");
  Serial.print(data[2]);
  Serial.println();
 
  nrf24.send(data, sizeof(data));
  nrf24.waitPacketSent();
  
  // Now wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
 
  if (nrf24.waitAvailableTimeout(1000))
  {
    // Should be a reply message for us now
    if (nrf24.recv(buf, &len))
    {
     
      Serial.print("got reply: ");
      Serial.println((char*)buf);
    }
    else
    {
     
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply.");
    
  }
  delay(5000);
}
