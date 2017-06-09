# MIDI-Wurlitzer-Sideman
Adding USB and DIN MIDI as well as CV trigger inputs to a 1959 drum machine<br>
<br>
The external trigger unit must be connected to the Sideman with a stereo 1/8" cable. This provides power and communication.<br>

A motor switch has been added. This turn off the motor, reguardless of wether the swithc is on or off. 
So as not to have the triggers MIDI or buttons trigger multiple sounds, always turn both switches off when not using the internal sequencer. 
<br>
CV triggers v
Any CV signal will trigger the indicated sound. Sound is held on when trigger is high. Some sound have sustain while other's don't.<br>
<br>
MIDI<br>
DIN and USB MIDI act just the same. <br>
Channel controll is located inide the trigger box<br>
ON ON = Omni, ON OFF= channel 1,  OFF ON = 2, OFF OFF =3<br>
<br>
The device will trigger with notes from any octave. C0 and C2 for example will both trigger the kick. <br>
C Bass drum<br>
Db Tom 1 <br>
D Tom 2 <br>
Eb Temple block 1 <br>
E Temple block 2 <br>
F Wood block <br>
Gb Clave<br>
G Maraca<br>
Ab Brush<br>
A Cymbal<br>
<br>
<br>
Hardwarev
There is a separate Teensy LC in the control box and Sideman. <br>
The external one reads the MIDI and triggers and sends another midi signal to the internal Teensy. <br>
That one then turns on and off reed switches attached to the trigger buttons.<br>
The internal Teensy is powered by a 5v AC DC wallwart inside the Sideman.<br>
The stereo cable is +3v3 tip, MIDI (from ext to internal) ring, Ground sleeve<br>
