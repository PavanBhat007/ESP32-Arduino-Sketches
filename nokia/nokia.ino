#include "pitches.h"

// Nokia Tune notes
int nokiaMelody[] = {
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_D5, NOTE_FS4, NOTE_D5, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_A4, NOTE_FS4, NOTE_B4,
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_D5, NOTE_FS4, NOTE_D5, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_A4, NOTE_FS4, NOTE_B4,
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_D5, NOTE_FS4, NOTE_D5, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_A4, NOTE_FS4, NOTE_B4,
  NOTE_E5, NOTE_D5, NOTE_FS4, NOTE_D5, NOTE_FS4, NOTE_D5, NOTE_FS4, NOTE_GS4, NOTE_B4, NOTE_A4, NOTE_FS4, NOTE_B4
};

// Note durations: 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8,
  4, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8,
  4, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8,
  4, 8, 8, 4, 4, 4, 4, 8, 8, 8, 8, 8
};

void setup() {
  // // Iterate over the notes of the melody
  for (int thisNote = 0; thisNote < 48; thisNote++) {
    // Calculate the note duration
    int noteDuration = 1000 / noteDurations[thisNote];
    // Play the note
    tone(6, nokiaMelody[thisNote], noteDuration);
    // Set a pause between notes
    delay(noteDuration * 1.30);
    // Stop the tone playing
    noTone(6);
  }
}

void loop() {
  setup();
}
