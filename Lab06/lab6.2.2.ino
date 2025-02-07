#define LED 25
hw_timer_t *My_timer = NULL;

// This is the Timer ISR. It is automatically called 
// on a timer alarm event.
void IRAM_ATTR onTimer(){
  digitalWrite(LED, !digitalRead(LED));
}

void setup() {
  pinMode(LED, OUTPUT);
  My_timer = timerBegin(0, 80, true);  // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
  timerAttachInterrupt(My_timer, &onTimer, true); // point to the ISR
  timerAlarmWrite(My_timer, 1000000, true);  // set alarm every 1 sec
  timerAlarmEnable(My_timer);  // enable the alarm
}

void loop() {

}
