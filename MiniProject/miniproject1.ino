const int enablePin = 23;  
const int in1Pin = 18;
const int in2Pin = 19; 
const int buttonpin = 32;
const int ledpin = 27;

void setup() {
  Serial.begin(9600);
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(buttonpin, INPUT);

  digitalWrite(enablePin, HIGH); // Enable the motor
}

void loop() {
  if (Serial.available() > 0) {
    char ch = Serial.read();

    if (ch == '+') {
      analogWrite(in1Pin, 0);
      analogWrite(in2Pin, 120);
      Serial.println("Motor Forward");
    } 
    else if (ch == '-') {
      analogWrite(in1Pin, 120);
      analogWrite(in2Pin, 0);
      Serial.println("Motor Reverse");
    } else {
      Serial.println(" ");
    }
  }
}