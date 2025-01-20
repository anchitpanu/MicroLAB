#include <WiFi.h>
#include <MQTT.h>
#include <LCD_I2C.h>

const int enablePin = 23;  
const int in1Pin = 18;
const int in2Pin = 19;

const char ssid[] = "ee";
const char pass[] = "aaa12345";

const char mqtt_broker[] = "test.mosquitto.org";
const char mqtt_topic[] = "group8/command";
const char mqtt_topicesp[] = "group8/data";
const char mqtt_client_id[] = "arduino_group_8";
int MQTT_PORT = 1883;

WiFiClient net;
MQTTClient client;

LCD_I2C lcd(0x27, 16, 2);

String motorState = "";  // Store current motor state

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(mqtt_client_id)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe(mqtt_topic);
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  char ch = payload[0];

  if (ch == '+') {
    analogWrite(in1Pin, 0);
    analogWrite(in2Pin, 120);
    motorState = "Clockwise";
    client.publish(mqtt_topicesp, "Motor Forward");
  } 
  else if (ch == '-') {
    analogWrite(in1Pin, 120);
    analogWrite(in2Pin, 0);
    motorState = "CounterClockwise";
    client.publish(mqtt_topicesp, "Motor Reverse");
  } 
  else if (ch == 'o') {
    analogWrite(in1Pin, 0);
    analogWrite(in2Pin, 0);
    motorState = "Motor Stop";
    client.publish(mqtt_topicesp, "Motor Stop");
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  lcd.begin();
  lcd.backlight();

  digitalWrite(enablePin, HIGH); // Enable the motor

  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    connect();
  }

  // Continuously update LCD with the motor state
  static String lastState = "";  // Store the last displayed state
  if (motorState != lastState) { // Update only when state changes
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(motorState);
    lastState = motorState;
  }
}
