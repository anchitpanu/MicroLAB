#define LDR  35    // use gpio36 or Analog 1 pin for input

int LDR_Value = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  LDR_Value = analogRead(LDR);  // or use analogRead(A1)
  Serial.println(LDR_Value);
  delay(100);
}