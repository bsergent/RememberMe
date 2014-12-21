/* RememberMe
 * Created by ha1fBit
 * For Kelsea's Christmas Present
 * 12-18-14R
 * 2014© Ben Sergent V
 */

// PINS =====
const int speakerPinA = 8;
const int speakerPinB = 9;
const int buttonAPin = 10;
const int lightAPin = 11;
const int buttonBPin = 12;
const int lightBPin = 13;
const int buttonCPin = 14;
const int lightCPin = 15;
const int buttonDPin = 16;
const int lightDPin = 17;

// TONES =====
const int _B5 = 988;
const int _A5 = 880;
const int _E5 = 659;
const int _C5 = 523;

const int _B4 = 494;
const int _A4 = 440;
const int _G4 = 392;
const int _F4 = 349;
const int _E4 = 329;
const int _D4 = 293;
const int _C4 = 261;

const int _B3 = 246;
const int _A3 = 220;
const int _G3 = 196;
const int _F3 = 174;
const int _E3 = 165;
const int _D3 = 147;

// MELODIES =====
const int startupNotesA[] = { _C4, _B4, _C4, _C5 };
const int startupNotesB[] = { _F3, _G3, _E4, _G4 };
const int startupBeats[] = {   1 ,  1 ,  1 ,  3 };
const int startupLength = 4;

const int winNotesA[] = { _B5, _B5, _A5, _A5, _G4, _G3, _G4, _G3 };
const int winNotesB[] = { _G4, _G4, _F4, _F4, _D4, _D3, _D4, _D3 };
const int winBeats[] = {   1 ,  2 ,  1 ,  2 ,  1 ,  1 ,  1 ,  3  };
const int winLength = 8;

const int loseNotesA[] = { _G3 };
const int loseNotesB[] = { 0 };
const int loseBeats[] = { 4 };
const int loseLength = 1;

const int tempo = 250;

// METHODS =====
void setup() {
  pinMode(speakerPinA, OUTPUT);
  pinMode(speakerPinB, OUTPUT);
}

void loop() {
  playMelody(startupNotesA, startupNotesB, startupBeats, startupLength, false, false);
  delay(1000);
  playMelody(winNotesA, winNotesB, winBeats, winLength, false, true);
  delay(1000);
  playOldMelody();
  delay(1000);
  playSound(_A5, _F4, 1000, true);
  delay(1000);
  playSound(_A5, _F4, 1000, false);
  delay(1000);
}

void playMelody(const int notesA[], const int notesB[], const int beats[], const int length, boolean repeatMelody, boolean warble) {
  do {
    for (int i = 0; i < length; i++) {
      playSound(notesA[i], notesB[i], beats[i]*tempo, warble);
    }
  } while (repeatMelody);
}

void playOldMelody() {
  playSound(_B5, _G4, 250, true);
  delay(25);
  playSound(_B5, _G4, 500, true);
  delay(25);
  playSound(_A5, _F4, 250, true);
  delay(25);
  playSound(_A5, _F4, 500, true);
  delay(25);
  playSound(_G4, _D4, 250, true);
  delay(25);
  playSound(_G3, _D3, 250, true);
  delay(25);
  playSound(_G4, _D4, 250, true);
  delay(25);
  playSound(_G3, _D3, 750, true);
  delay(25);
}

void playSound(int noteA, int noteB, unsigned long totalPlayTime, boolean warble) // freqA, freqB, totalTimeInMilliseconds
{	 
  totalPlayTime = totalPlayTime * 1000; // Convert to microseconds
  unsigned long startTime = micros();
  long periodA = (long) (1000000/noteA)/2; // 1000000/frequencyInHertz
  long periodB = (long) (1000000/noteB)/2;
  long timeTilNextA = periodA;
  long timeTilNextB = periodB;
  while (micros() < (startTime+totalPlayTime)) {
    if (noteB != 0) { // Attempt to mix the notes
        
      if (timeTilNextA < timeTilNextB) {
        if (timeTilNextA>0 || warble) delayMicroseconds(timeTilNextA);
        timeTilNextB -= timeTilNextA;
        digitalWrite(speakerPinA, !digitalRead(speakerPinA));
        timeTilNextA = periodA;
      } else {
        if (timeTilNextB>0 || warble) delayMicroseconds(timeTilNextB);
        timeTilNextA -= timeTilNextB;
        digitalWrite(speakerPinB, !digitalRead(speakerPinB));
        timeTilNextB = periodB;
      }
      
    } else {
      digitalWrite(speakerPinA,HIGH);
      delayMicroseconds(periodA);
      digitalWrite(speakerPinA,LOW);
      delayMicroseconds(periodA);
    }
  }
  digitalWrite(speakerPinA,LOW);
  digitalWrite(speakerPinB,LOW);
}








