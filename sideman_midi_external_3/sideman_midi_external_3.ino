int ledPin = 13;
int inpins[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int midinotes[9][10] =
{
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
  {12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
  {24, 25, 26, 27, 28, 29, 30, 31, 32, 33},
  {36, 37, 38, 39, 40, 41, 42, 43, 44, 45},
  {48, 49, 50, 51, 52, 53, 54, 55, 56, 57},
  { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69},
  { 72, 73, 74, 75, 76, 77, 78, 79, 80, 81},
  { 84, 85, 86, 87, 88, 89, 90, 91, 92, 93},
  { 96, 97, 98, 99 , 100, 101, 102, 103, 104, 105}
};

// these are in differnt orders due to the way the jacks and reed swithches got wired

int trigsendnotes[10] =
//{24, 29, 30, 25, 31, 26, 27, 32, 33, 28};
{33, 28, 27, 32, 31, 26, 30, 25, 24, 29};

int midisendnotes[10] =
{24, 29, 25, 30, 26, 31, 27, 32, 28, 33};

//  {24, 25, 26, 27, 28, 29, 30, 31, 32, 33};

int notestate[10];
int d15, d16, channel;

#include <MIDI.h>


void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(13, 1);

  for (int i = 0; i < 10; i++) {
    pinMode(inpins[i], INPUT);
  }
  pinMode(15, INPUT);
  pinMode(16, INPUT);

  delay(200);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  usbMIDI.begin();

  MIDI.turnThruOff();

  //usbMIDI.setHandleNoteOff(OnNoteOff);
  //usbMIDI.setHandleNoteOn(OnNoteOn) ;


  for (int i = 0; i < 10; i++) {

    MIDI.sendNoteOff(midisendnotes[i], 100, 1);
    usbMIDI.sendNoteOff(midisendnotes[i], 100, 1);

  }


}

void loop()
{


  int d15 = digitalRead(15);
  int d16 = digitalRead(16);


  if (d15 == 0 && d16 == 0) {
    channel = 0;
  }

  if (d15 == 1 && d16 == 0) {
    channel = 1;


  }

  if (d15 == 0 && d16 == 1) {
    channel = 2;


  }

  if (d15 == 1 && d16 == 1) {
    channel = 3;


  }

  for (int i = 0; i < 10; i++) {
    byte intemp = digitalRead(inpins[i]);
    if (intemp == 1 && notestate[i] == 0) {
      MIDI.sendNoteOn(trigsendnotes[i], 100, 1);
      notestate[i] = 1;
      digitalWrite(ledPin, 1);
      Serial.print ("trig ");
      Serial.print(inpins[i]);          Serial.println(" on ");

    }



    if (intemp == 0 && notestate[i] == 1) {
      MIDI.sendNoteOff(trigsendnotes[i], 100, 1);
      notestate[i] = 0;
      digitalWrite(ledPin, 0);
      Serial.print ("trig ");

      Serial.print(inpins[i]);          Serial.println(" off ");

    }
  }


  if (usbMIDI.read()) {                    // Is there a MIDI message incoming ?
    byte type = usbMIDI.getType();
    byte note = usbMIDI.getData1();
    byte ch = usbMIDI.getChannel();

    Serial.print(type);
    Serial.print(" ");

    Serial.println(note);
    switch (type) {
      case 0:

        for (int j = 0; j < 10; j++) {

          for (int i = 0; i < 10; i++) {
            if (ch == channel || channel == 0) {

              if (note == midinotes[j][i]  ) {
                //digitalWrite(outpins[i], 0);
                digitalWrite(ledPin, 0);
                MIDI.sendNoteOff(midisendnotes[i], 100, 1);
              }
            }
          }

        }
        break;



      case 1:
        for (int j = 0; j < 10; j++) {

          for (int i = 0; i < 10; i++) {
            if (ch == channel || channel == 0) {

              if (note == midinotes[j][i]) {
                // digitalWrite(outpins[i], 1);
                digitalWrite(ledPin, 1);
                MIDI.sendNoteOn(midisendnotes[i], 100, 1);
              }
            }
          }
        }
        break;


    }
  }


  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
    byte type = MIDI.getType();
    byte note = MIDI.getData1();
    byte ch = MIDI.getChannel();

    if (type != 248) {
      Serial.println("DIN ");


    }
    switch (type) {
      case 128:
        for (int j = 0; j < 10; j++) {

          for (int i = 0; i < 10; i++) {
            if (ch == channel || channel == 0) {

              if (note == midinotes[j][i]) {
                //digitalWrite(outpins[i], 0);
                digitalWrite(ledPin, 0);
                MIDI.sendNoteOff(midisendnotes[i], 100, 1);
                Serial.print(" off ");          Serial.println(note);
              }
            }
          }
        }
        break;

      case 144:
        for (int j = 0; j < 10; j++) {

          for (int i = 0; i < 10; i++) {
            if (ch == channel || channel == 0) {

              if (note == midinotes[j][i]) {
                // digitalWrite(outpins[i], 1);
                digitalWrite(ledPin, 1);
                MIDI.sendNoteOn(midisendnotes[i], 100, 1);
                Serial.print(" on ");          Serial.println(note);
              }
            }
          }
        }
        break;


    }
  }


  //MIDI.read();

}
