int ledPin = 13;
int outpins[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int midinotes[10] = {24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
#include <MIDI.h>


void OnNoteOn(byte channel, byte note, byte velocity)
{

  for (int i = 0; i < 10; i++) {

    if (note == midinotes[i]) {
      digitalWrite(outpins[i], 1);
      digitalWrite(ledPin, 1);
    }

  }
  Serial.print(note);

  Serial.println ( " on");
}

void OnNoteOff(byte channel, byte note, byte velocity)
{

  for (int i = 0; i < 10; i++) {

    if (note == midinotes[i]) {
      digitalWrite(outpins[i], 0);
      digitalWrite(ledPin, 0);
    }
    Serial.print(note);

    Serial.println( " off");
  }
}
void setup()
{
  pinMode(ledPin, OUTPUT);

  for (int i = 0; i < 10; i++) {
    pinMode(outpins[i], OUTPUT);
  }
  MIDI.begin(MIDI_CHANNEL_OMNI);

  //usbMIDI.setHandleNoteOff(OnNoteOff);
  //usbMIDI.setHandleNoteOn(OnNoteOn) ;
  MIDI.setHandleNoteOff(OnNoteOff);
  MIDI.setHandleNoteOn(OnNoteOn) ;

}

void loop()
{
  //usbMIDI.read();
  MIDI.read();

}
