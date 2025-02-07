#define Button_Pin   19
#define LED1_Pin     17
 
void IRAM_ATTR IO_INT_ISR()
{
  // Toggle The LED
  digitalWrite(LED1_Pin, !digitalRead(LED1_Pin));
}
 
void setup()
{
  pinMode(LED1_Pin, OUTPUT);
  pinMode(Button_Pin, INPUT);
  attachInterrupt(Button_Pin, IO_INT_ISR, RISING); // interrupt on rising edge
}
 
void loop()
{
  // Do Nothing...
}