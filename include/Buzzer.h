#define NUM_NOTES 14 // number of notes stored

class CBuzzer{
    private:
        int buzzPin;
        const int tempo = 130;
        const int numNotes = NUM_NOTES;
        char names[NUM_NOTES] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B', 'c', 'd', 'e', 'f', 'g', 'a', 'b'};
        int frequencies[NUM_NOTES] = {130, 146, 164, 174, 196, 220, 246, 261, 294, 330, 349, 392, 440, 493};
        char *songNotes;
        int *songBeats;
        bool isPlaying = false;
        long waiting = 0;
        int currentNote;
        long prevTime;

        int frequency(char note);

    public:
        CBuzzer(int pin);
        void play(char * notes, int * beats);
        void loop();
};