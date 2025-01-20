#include <Adafruit_PCF8574.h>
/* Example for 1 output LED that is connected from power to the GPIO expander pin #7
 * Note the LEDs must be connected with the CATHODES to the expander, to SINK current!
 * The PCF8574 cannot SOURCE current!
 */

#define PCF8574_Address 0x20

Adafruit_PCF8574 pcf;
void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("Adafruit PCF8574 LED blink test");
  if (!pcf.begin(PCF8574_Address, &Wire)) {
    Serial.println("Couldn't find PCF8574");
  }
  pcf.pinMode(0, INPUT);
  pcf.pinMode(7, OUTPUT);
}
void loop() {
  if (pcf.digitalRead(0) == 0) {
    pcf.digitalWrite(7, LOW);  // turn LED on by sinking current to ground
  } else {
    pcf.digitalWrite(7, HIGH); // turn LED off by turning off sinking transistor
  }
}
