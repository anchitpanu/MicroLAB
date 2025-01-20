#define RELAY   23

void setup() {
  pinMode(RELAY, OUTPUT);  // set arduino pin to output mode
}void loop() {
    digitalWrite(RELAY, HIGH);
    delay(1000);
    digitalWrite(RELAY, LOW);
    delay(1000);
  }
