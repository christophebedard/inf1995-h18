#include "delai.h"
#include "buzzer.h"


int main()
{
    Buzzer buzz;

    buzz.playNote(45);
    waitForMs(1000);
    buzz.playNote(60);
    waitForMs(1000);
    buzz.playNote(70);
    waitForMs(1000);
    buzz.playNote(80);
    waitForMs(1000);
    buzz.stopNote();

    while(true);

    return 0;
}
