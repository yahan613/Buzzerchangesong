#include "pitches.h"
byte previousState=1, presentState=1, songNumber=10;
const int buttonPin = 6;     // the number of the pushbutton pin
int songLen[2] = {8, 47};
int thisNote = 0;


int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int melody1[] = { 
  NOTE_C6, NOTE_A5, NOTE_F5, 0, NOTE_C6, 0, NOTE_AS5, 0, NOTE_G5,
 0, 0, 0, NOTE_AS5, NOTE_G5, NOTE_E5, 0, NOTE_AS5, 0, NOTE_A5, 0, NOTE_F5, 
 0, 0, 0, 0, NOTE_CS5, NOTE_F5, NOTE_AS5, NOTE_A5, NOTE_C6, NOTE_F5, 
 0, 0, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_G5, 0, 0, 0, 0
};


// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
};
int noteDurations1[] = {
   4, 8, 8, 8, 8, 8, 8, 8, 8, 
  4,4,4,4,8,8,8,8,8,8,8,8, 
  4, 4, 4, 4, 4, 4, 4, 4, 8, 8, 
  4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4
};



void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
   Serial.begin(9600);
}

void loop() {
  checkButton();

   if(songNumber==10){
     for (thisNote = 0; thisNote < songLen[0]; thisNote++) {

      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);
      checkButton();

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(8);
      checkButton();
    }
    checkButton();
   }
  
  if(songNumber==11){
    checkButton();
    for (thisNote = 0; thisNote < songLen[1]; thisNote++) {

      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations1[thisNote];
      tone(8, melody1[thisNote], noteDuration);
      checkButton();
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(8);
      checkButton();
    }
    checkButton();
   }

}

// void playMusic()
// {
//       checkButton();
//     for (int thisNote = 0; thisNote < 14; thisNote++) {

//       // to calculate the note duration, take one second divided by the note type.
//       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//       int noteDuration = 1000 / noteDurations2[thisNote];
//       tone(8, melody2[thisNote], noteDuration);
//       checkButton();
//       // to distinguish the notes, set a minimum time between them.
//       // the note's duration + 30% seems to work well:
//       int pauseBetweenNotes = noteDuration * 1.30;
//       delay(pauseBetweenNotes);
//       // stop the tone playing:
//       noTone(8);
//       checkButton();
//     }
// } 

void checkButton()
{
  for(int i = 0; i < 10; i++)
  {
    presentState = digitalRead(buttonPin);
    delay(2);
  }
  presentState = digitalRead(buttonPin);
  Serial.println(presentState);
  if(presentState==0){
    songNumber=21-songNumber;
    Serial.println(songNumber);
    if(songNumber == 10) {
      thisNote = songLen[1]; 
      Serial.println(thisNote); 
      delay(300);
      }
    else if(songNumber == 11) {
      thisNote = songLen[0]; 
      Serial.println(thisNote); 
      delay(300);
      }

  } else {
    previousState = presentState;
  }
  delay(10);
  previousState = presentState;
}
