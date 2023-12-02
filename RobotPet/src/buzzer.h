#include <Arduino.h>
const unsigned int BUZZ = 26; // Check schematic and see pin connection to buzzer
const unsigned int BUZZ_CHANNEL = 4; //Selecting PWM channel 4
const unsigned int octave = 5;

void initBuzzer() {
    ledcAttachPin(BUZZ, BUZZ_CHANNEL);
}

void myChirp(int noteLength) {
    // Glissando inbetween C and C down one octave.
    // Use Short note noteLength
    for(int i = 880; i > 880/2; i--) {
        ledcWriteTone(BUZZ_CHANNEL, i);
        delay(noteLength);
    }
    delay(noteLength);
    ledcWrite(BUZZ_CHANNEL, 0);
}

void jingleRoam(int noteLength) {
    ledcWriteNote(BUZZ_CHANNEL, NOTE_E, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_E, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave);
    delay(noteLength*2);
    ledcWrite(BUZZ_CHANNEL, 0);
}

void jingleMove(int noteLength) {
    // Short beeps
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave);
    delay(noteLength);
    ledcWrite(BUZZ_CHANNEL, 0);
}

void jingleSearch(int noteLength) {
    // Short beeps
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave);
    delay(noteLength);
    ledcWrite(BUZZ_CHANNEL, 0);
}

void jingleFoundHuman(int noteLength) {
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_E, octave+1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave+1);
    delay(noteLength);
    ledcWrite(BUZZ_CHANNEL, 0);
}

void jingleHeardSound(int noteLength) {
    // Short beeps
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave);
    delay(noteLength);
    ledcWrite(BUZZ_CHANNEL, 0);
}

void jingleDance(int noteLength) {
    //C
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_E, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_E, octave);
    delay(noteLength);
    //G
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_B, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_D, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_B, octave);
    delay(noteLength);
    //D
    ledcWriteNote(BUZZ_CHANNEL, NOTE_D, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_Fs, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_A, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_D, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_Fs, octave);
    delay(noteLength);
    //A
    ledcWriteNote(BUZZ_CHANNEL, NOTE_A, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_Cs, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_E, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_A, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_Cs, octave+1);
    delay(noteLength);
    ledcWrite(BUZZ_CHANNEL, 0);
}

void jingleSleep(int noteLength) {
    // C + Bb
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_E, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_Bb, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_G, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_E, octave-1);
    delay(noteLength);
    ledcWriteNote(BUZZ_CHANNEL, NOTE_C, octave-1);
    delay(noteLength*2);
    ledcWrite(BUZZ_CHANNEL, 0);
}

void jingleStop() {
    ledcWrite(BUZZ_CHANNEL, 0);
}