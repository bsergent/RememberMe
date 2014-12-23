/* RememberMe
 * Created by ha1fBit
 * For Kelsea's Christmas Present
 * 12-18-14R
 * 2014© Ben Sergent V
 */

// PINS =====
const int speakerPinA = 5;
const int speakerPinB = 6;
const int lightPinA = 7;
const int buttonPinA = 8;
const int lightPinB = 9;
const int buttonPinB = 10;
const int lightPinC = 11;
const int buttonPinC = 12;
const int lightPinD = 18;
const int buttonPinD = 19;

// TONES =====
const int _B5 = 988;//
const int _A5 = 880;
const int _E5 = 659;
const int _C5 = 523;

const int _B4 = 494;//
const int _A4 = 440;
const int _G4 = 392;
const int _F4 = 349;
const int _E4 = 329;//
const int _D4 = 293;
const int _C4 = 261;

const int _B3 = 246;
const int _A3 = 220;//
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

const int loseNotesA[] = { _G3 , _F3 , _D3 };
const int loseNotesB[] = {  0  ,  0  ,  0  };
const int loseBeats[] = {   2  ,  2  ,  4 };
const int loseLength = 3;

// OTHER CONSTANTS
const int tempo = 250;
const int maxPatternLength = 100;

// VARIABLES
int pattern[100];
int currentProgression = 1;
int playerInputProgression = 1;
int gameState = 0;
boolean wasButtonPushed = false;

// METHODS =====
void setup() {
  pinMode(speakerPinA, OUTPUT);
  pinMode(speakerPinB, OUTPUT);
  pinMode(lightPinA, OUTPUT);
  pinMode(lightPinB, OUTPUT);
  pinMode(lightPinC, OUTPUT);
  pinMode(lightPinD, OUTPUT);
  pinMode(buttonPinA, INPUT);
  pinMode(buttonPinB, INPUT);
  pinMode(buttonPinC, INPUT);
  pinMode(buttonPinD, INPUT);
  
  // Randomize pattern
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  switch (gameState) {
    case 0: // Game startup
      Serial.println("Pattern:");
      for (int i = 0; i < maxPatternLength; i++) {
        pattern[i] = random(4);
        Serial.print(pattern[i]);
      }
      currentProgression = 1;
      gameState = 1;
      //playMelody(startupNotesA, startupNotesB, startupBeats, startupLength, false, true);
      playOldMelody();
      break;
    case 1: // Showing pattern
      delay(500);
      showPattern();
      gameState = 2;
      break;
    case 2: // Receiving player pattern
      playerInputProgression = 1;
      Serial.println("Receiving input");
      while (playerInputProgression <= currentProgression) {
        int buttonPushed = -1;
        if (digitalRead(buttonPinA) == HIGH){
          digitalWrite(lightPinA, HIGH);
          buttonPushed = 0;
        } else {
          digitalWrite(lightPinA, LOW);
        }
        if (digitalRead(buttonPinB) == HIGH) {
          digitalWrite(lightPinB, HIGH);
          buttonPushed = 1;
        } else {
          digitalWrite(lightPinB, LOW);
        }
        if (digitalRead(buttonPinC) == HIGH) {
          digitalWrite(lightPinC, HIGH);
          buttonPushed = 2;
        } else {
          digitalWrite(lightPinC, LOW);
        }
        if (digitalRead(buttonPinD) == HIGH) {
          digitalWrite(lightPinD, HIGH);
          buttonPushed = 3;
        } else {
          digitalWrite(lightPinD, LOW);
        }
        
        if (buttonPushed >= 0 && !wasButtonPushed) {
          Serial.println("Pushed button");
          Serial.println(buttonPushed);
          if (buttonPushed != pattern[playerInputProgression]) {
            gameState = 3;
            break;
          }
          playerInputProgression++;
        }
        
        if (buttonPushed < 0) {
          wasButtonPushed = false;
        } else {
          wasButtonPushed = true;
        }
        
        delay(10);
      }
      Serial.println("Finished receiving input");
      //currentProgression++;
      //gameState = 1;
      break;
    case 3: // Player lost
      playMelody(loseNotesA, loseNotesB, loseBeats, loseLength, false, true);
      gameState = 0;
      break;
    case 4: // Player won
      playMelody(winNotesA, winNotesB, winBeats, winLength, false, true);
      gameState = 0;
      break;
    default:
      gameState = 0;
      break;
  }
}

void showPattern() {
  digitalWrite(lightPinA,HIGH);
  playSound(_A3, 0, 400, false);
  setRowLightState(false);
  delay(400);
  
  digitalWrite(lightPinB,HIGH);
  playSound(_A3, 0, 400, false);
  setRowLightState(false);
  delay(400);
  
  digitalWrite(lightPinC,HIGH);
  playSound(_A3, 0, 400, false);
  setRowLightState(false);
  delay(400);
  
  setRowLightState(true);
  playSound(_B5, 0, 500, false);
  setRowLightState(false);
  delay(1000);
  
  for (int i = 0; i < currentProgression; i++) {
    setRowLightState(false);
    int showDelay = 500;
    if (currentProgression > 5) showDelay = 250;
    if (currentProgression > 10) showDelay = 150; 
    switch(pattern[i]) {
      case 0:
        digitalWrite(lightPinA,HIGH);
        playSound(_A3, 0, showDelay, false);
        break;
      case 1:
        digitalWrite(lightPinB,HIGH);
        playSound(_E4, 0, showDelay, false);
        break;
      case 2:
        digitalWrite(lightPinC,HIGH);
        playSound(_B4, 0, showDelay, false);
        break;
      case 3:
        digitalWrite(lightPinD,HIGH);
        playSound(_B5, 0, showDelay, false);
        break;
      default:
        gameState = 0;
        break;
    }
    setRowLightState(false);
    delay(100);
  }
}

void setRowLightState(boolean newState) {
  if (newState) {
    digitalWrite(lightPinA,HIGH);
    digitalWrite(lightPinB,HIGH);
    digitalWrite(lightPinC,HIGH);
    digitalWrite(lightPinD,HIGH);
  } else {
    digitalWrite(lightPinA,LOW);
    digitalWrite(lightPinB,LOW);
    digitalWrite(lightPinC,LOW);
    digitalWrite(lightPinD,LOW);
  }
}

void playMelody(const int notesA[], const int notesB[], const int beats[], const int length, boolean repeatMelody, boolean warble) {
  do {
    for (int i = 0; i < length; i++) {
      setRowLightState(false);
      if (notesA[i] <= 220 || notesB[i] <= 220) {
        digitalWrite(lightPinA,HIGH);
      } else if (notesA[i] <= 329 || notesB[i] <= 329) {
        digitalWrite(lightPinB,HIGH);
      } else if (notesA[i] <= 494 || notesB[i] <= 494) {
        digitalWrite(lightPinC,HIGH);
      } else if (notesA[i] <= 988 || notesB[i] <= 988) {
        digitalWrite(lightPinD,HIGH);
      }
      playSound(notesA[i], notesB[i], (beats[i]*tempo)-25, warble);
      setRowLightState(false);
      delay(25);
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








