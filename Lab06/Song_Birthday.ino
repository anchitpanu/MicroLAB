#include <Arduino.h>

#define BUZZER_PIN 18
#define BUTTON_PIN 32

hw_timer_t *My_timer = NULL;

volatile int noteIndex = 0;      // To keep track of the note index
volatile unsigned long lastNoteTime = 0; // Time when the last note was played
int duration = 0; // Duration of each note in ms (tweak this for the song)

int tempoLevels[5] = {1100000, 850000, 600000, 350000, 100000};  // speed of the song (slowest, slow, normal, fast, fastest)
int currentTempo = 3;  // Default speed level
const int noteDuration = 400;  // Duration of each note in ms (tweak this for the song)

// Happy Birthday Melody (in Hz)
const int notes[] = {
  262, 262, 294, 262, 349, 330, 0,  // Happy Birthday to You
  262, 262, 294, 262, 392, 349, 0,  // Happy Birthday to You
  262, 262, 523, 440, 349, 330, 294, 0, // Happy Birthday Dear (Name)
  466, 466, 440, 349, 392, 349, 0   // Happy Birthday to You
};

// Note durations
// int noteDurations[] = {
//   400, 400, 200, 200, 200, 200, 400,  
//   400, 400, 200, 200, 200, 200, 400,  
//   400, 400, 200, 200, 200, 200, 200, 400,  
//   400, 400, 200, 200, 200, 200, 400  
// };

const int numNotes = sizeof(notes) / sizeof(notes[0]);

void IRAM_ATTR onTimer() {
  // noTone(BUZZER_PIN);  // Stop before play the next note
  tone(BUZZER_PIN, notes[noteIndex]);  // Play current note
  lastNoteTime = millis();  // Update the time of the last note played
  duration = noteDuration; /*[noteIndex];*/  // Set the length of the note as specified.
  noteIndex = (noteIndex + 1) % numNotes;  // Loop the song
}

void IRAM_ATTR onButtonPress() {
  currentTempo = (currentTempo + 1) % 5;  // Update the speed of the song (5 level)
  Serial.print("Current Tempo: " + currentTempo);
  // Serial.println(currentTempo);  // Debug: print currentTempo value
  timerAlarm(My_timer, tempoLevels[currentTempo], true, 0);  // Adjust the speed of the song
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Pull Up button
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);  // ตั้ง interrupt สำหรับปุ่มกด
  Serial.begin(115200);  
  // Set up the timer for LED toggling and note playback
  My_timer = timerBegin(1000000);  // Timer 0 with prescale 80 (1 tick = 1 µs)
  timerAttachInterrupt(My_timer, &onTimer);  // Attach interrupt for the timer
  timerAlarm(My_timer, tempoLevels[currentTempo], true, 0);  // Set the song that start with default speed level (level 1)
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Check if it's time to play the next note
  if (currentMillis - lastNoteTime >= duration) {
    // noTone(BUZZER_PIN);  // Stop before play the next note
    lastNoteTime = currentMillis; // Update the time of the last note played
    noTone(BUZZER_PIN);  // Stop the buzzer if the note is 0
    tone(BUZZER_PIN, notes[noteIndex]);  // Move to the next note
    duration = noteDuration; /*[noteIndex];*/  // Set the lenght of the next note
  }
}