
#include <EEPROM.h>
int deviceID = 0, curDeviceID;
void setup() {
  Serial.begin(9600);
  EEPROM.write(0, deviceID);
  curDeviceID = EEPROM.read(0);
  if (curDeviceID == deviceID) {
    Serial.print("Arduino ID successfully changed to: ");
    Serial.println(curDeviceID);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
}
