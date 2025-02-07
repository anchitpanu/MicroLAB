#define LED 18
hw_timer_t *My_timer = NULL;

// This is the Timer ISR. It is automatically called 
// on a timer alarm event.
void IRAM_ATTR onTimer(){
  digitalWrite(LED, !digitalRead(LED));
}

void setup() {
  pinMode(LED, OUTPUT);
  My_timer = timerBegin(1000000);  // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
  timerAttachInterrupt(My_timer, &onTimer); // point to the ISR
  timerAlarm(My_timer, 892, true, 0);  // set alarm every 1 sec
  // timerAlarmEnable(My_timer);  // enable the alarm
}

void loop() {

}