#include <Adafruit_I2CDevice.h>

#define PCF8574_Address 0x20

Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(PCF8574_Address);

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("I2C address detection test");
  if (!i2c_dev.begin()) {
    Serial.print("Did not find device at 0x");
    Serial.println(i2c_dev.address(), HEX);
    while (1);
  }
  Serial.print("Device found on address 0x");
  Serial.println(i2c_dev.address(), HEX);
}
void loop() {
  
} 