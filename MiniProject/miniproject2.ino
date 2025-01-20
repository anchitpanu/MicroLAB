// Exmaple of using the MQTT library for ESP32 
// Library by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt
// Modified by Arnan Sipitakiat


#include <WiFi.h>
#include <MQTT.h>

const int enablePin = 23;  
const int in1Pin = 22;
const int in2Pin = 19;


const char ssid[] = "ee";
const char pass[] = "aaa12345";

const char mqtt_broker[]="test.mosquitto.org";
const char mqtt_topic[]="group8/command";
const char mqtt_topicesp[]="group8/data";
const char mqtt_client_id[]="arduino_group_8"; // must change this string to a unique value
int MQTT_PORT=1883;

int counter=0;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;


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
    client.subscribe(mqtt_topicesp);
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

    char ch = payload[0];

    if (ch == '+') {
      analogWrite(in1Pin, 0);
      analogWrite(in2Pin, 120);
      client.publish(mqtt_topicesp, "Motor Forward");
    } 
    if (ch == '-') {
      analogWrite(in1Pin, 120);
      analogWrite(in2Pin, 0);
      client.publish(mqtt_topicesp, "Motor Reverse");
    }
    if (ch == 'o') {
      analogWrite(in1Pin, 0);
      analogWrite(in2Pin, 0);
      client.publish(mqtt_topicesp, "Motor Stop");
    }

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling client.loop().
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  digitalWrite(enablePin, HIGH); // Enable the motor


  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  // not that we don't use delay() because we need to keep calling the client.loop()
  // to keep the connection alive
  // if (millis() - lastMillis > 2000) {
  //   lastMillis = millis();
  //   client.publish(mqtt_topic, "Counter = " + String(counter++));
  // }
}