#define LED     23
#define BUTTON  32

int counter = 0;
bool Bstate = false;
bool lastBstate = false;

void setup() {
  pinMode(BUTTON, INPUT); // set arduino pin to input mode
  pinMode(LED, OUTPUT);  // set arduino pin to output mode
  Serial.begin(9600);

}void loop() {
  Bstate = digitalRead(BUTTON);
  if(digitalRead(BUTTON)==LOW) { 
    digitalWrite(LED, HIGH);
    if(Bstate != lastBstate){
      counter++;
      Serial.println(counter);
      delay(300);
    }
  } else {
    digitalWrite(LED, LOW);
  }
  lastBstate = Bstate;
}