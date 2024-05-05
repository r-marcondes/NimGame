#include "Buzzer.h"
#include <Arduino.h>
#include <stdlib.h>

CBuzzer::CBuzzer(int pin)
{
    buzzPin = pin;
    pinMode(buzzPin, OUTPUT);
}

int CBuzzer::frequency(char note)
{
  int i;

  for (i = 0; i < NUM_NOTES; i++)
  {
    if (names[i] == note)
    {
      return(frequencies[i]);
    }
  }
  return(0);  // looked through everything and didn't find it, return 0
}

void CBuzzer::play(char * notes, int * beats)
{
    prevTime = millis();

    songNotes = notes;
    songBeats = beats;
    currentNote = 0;
    waiting = 0;
    isPlaying = true;
}

void CBuzzer::loop()
{
    int duration;
    if(isPlaying)
    {
        if(songNotes[currentNote] != 0)
        {
            if((millis() - prevTime) > waiting)
            {
                duration = songBeats[currentNote] * tempo;
                if(songNotes[currentNote] != ' ')
                {
                    tone(buzzPin, frequency(songNotes[currentNote]), duration);
                }
                waiting = duration;
                currentNote++;
                prevTime = millis();                
            }
        }
        else
        {
            isPlaying = false;
        }
    }
}