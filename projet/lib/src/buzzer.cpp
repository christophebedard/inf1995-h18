/**
 * \file buzzer.cpp
 * \brief implementation de la classe Buzzer
 * \author 
 * 
 * Brancher le buzzer entre la broche BROCHE_BUZZER et le GND.
 */

#include "buzzer.h"

const uint8_t Buzzer::NOTE_NULLE = 0;
const uint8_t Buzzer::BROCHE_BUZZER = 7;
const uint8_t Buzzer::NOTE_MIN = 12;
const uint8_t Buzzer::NOTE_MAX = 127;
const NoteMidi Buzzer::DATA_NOTES[] = {
    {Prescaler::PRE_1024, 238}, {Prescaler::PRE_1024, 225}, {Prescaler::PRE_1024, 212}, {Prescaler::PRE_1024, 200}, {Prescaler::PRE_1024, 189},
    {Prescaler::PRE_1024, 178}, {Prescaler::PRE_1024, 168}, {Prescaler::PRE_1024, 159}, {Prescaler::PRE_1024, 150}, {Prescaler::PRE_1024, 142},
    {Prescaler::PRE_1024, 134}, {Prescaler::PRE_1024, 126}, {Prescaler::PRE_1024, 119}, {Prescaler::PRE_1024, 112}, {Prescaler::PRE_1024, 106},
    {Prescaler::PRE_1024, 100}, {Prescaler::PRE_1024, 94}, {Prescaler::PRE_1024, 89}, {Prescaler::PRE_1024, 84}, {Prescaler::PRE_1024, 79},
    {Prescaler::PRE_1024, 75}, {Prescaler::PRE_1024, 71}, {Prescaler::PRE_1024, 67}, {Prescaler::PRE_256, 253}, {Prescaler::PRE_256, 238},
    {Prescaler::PRE_256, 225}, {Prescaler::PRE_256, 212}, {Prescaler::PRE_256, 200}, {Prescaler::PRE_256, 189}, {Prescaler::PRE_256, 178},
    {Prescaler::PRE_256, 168}, {Prescaler::PRE_256, 159}, {Prescaler::PRE_256, 150}, {Prescaler::PRE_256, 142}, {Prescaler::PRE_256, 134},
    {Prescaler::PRE_128, 253}, {Prescaler::PRE_128, 238}, {Prescaler::PRE_128, 225}, {Prescaler::PRE_128, 212}, {Prescaler::PRE_128, 200},
    {Prescaler::PRE_128, 189}, {Prescaler::PRE_128, 178}, {Prescaler::PRE_128, 168}, {Prescaler::PRE_128, 159}, {Prescaler::PRE_128, 150},
    {Prescaler::PRE_128, 142}, {Prescaler::PRE_128, 134}, {Prescaler::PRE_64, 253}, {Prescaler::PRE_64, 238}, {Prescaler::PRE_64, 225},
    {Prescaler::PRE_64, 212}, {Prescaler::PRE_64, 200}, {Prescaler::PRE_64, 189}, {Prescaler::PRE_64, 178}, {Prescaler::PRE_64, 168},
    {Prescaler::PRE_64, 159}, {Prescaler::PRE_64, 150}, {Prescaler::PRE_64, 142}, {Prescaler::PRE_64, 134}, {Prescaler::PRE_32, 253},
    {Prescaler::PRE_32, 238}, {Prescaler::PRE_32, 225}, {Prescaler::PRE_32, 212}, {Prescaler::PRE_32, 200}, {Prescaler::PRE_32, 189},
    {Prescaler::PRE_32, 178}, {Prescaler::PRE_32, 168}, {Prescaler::PRE_32, 159}, {Prescaler::PRE_32, 150}, {Prescaler::PRE_32, 142},
    {Prescaler::PRE_32, 134}, {Prescaler::PRE_32, 126}, {Prescaler::PRE_32, 119}, {Prescaler::PRE_32, 112}, {Prescaler::PRE_32, 106},
    {Prescaler::PRE_32, 100}, {Prescaler::PRE_32, 94}, {Prescaler::PRE_32, 89}, {Prescaler::PRE_32, 84}, {Prescaler::PRE_32, 79},
    {Prescaler::PRE_32, 75}, {Prescaler::PRE_32, 71}, {Prescaler::PRE_32, 67}, {Prescaler::PRE_8, 253}, {Prescaler::PRE_8, 238},
    {Prescaler::PRE_8, 225}, {Prescaler::PRE_8, 212}, {Prescaler::PRE_8, 200}, {Prescaler::PRE_8, 189}, {Prescaler::PRE_8, 178},
    {Prescaler::PRE_8, 168}, {Prescaler::PRE_8, 159}, {Prescaler::PRE_8, 150}, {Prescaler::PRE_8, 142}, {Prescaler::PRE_8, 134},
    {Prescaler::PRE_8, 126}, {Prescaler::PRE_8, 119}, {Prescaler::PRE_8, 112}, {Prescaler::PRE_8, 106}, {Prescaler::PRE_8, 100},
    {Prescaler::PRE_8, 94}, {Prescaler::PRE_8, 89}, {Prescaler::PRE_8, 84}, {Prescaler::PRE_8, 79}, {Prescaler::PRE_8, 75},
    {Prescaler::PRE_8, 71}, {Prescaler::PRE_8, 67}, {Prescaler::PRE_8, 63}, {Prescaler::PRE_8, 59}, {Prescaler::PRE_8, 56},
    {Prescaler::PRE_8, 53}, {Prescaler::PRE_8, 50}, {Prescaler::PRE_8, 47}, {Prescaler::PRE_8, 44}, {Prescaler::PRE_8, 42},
    {Prescaler::PRE_8, 39}};

/**
 * Callback pour la note
 * \todo typedef pour pointeur vers methode de classe
 */
void callbackNote()
{
    // inverse la broche
    PORTC ^= _BV(Buzzer::BROCHE_BUZZER - 1);
}

void Buzzer::init()
{
    // met la broche en sortie
    DDRC |= _BV(Buzzer::BROCHE_BUZZER - 1);

    initTimer2(&callbackNote, nullptr);
}

void Buzzer::play(uint8_t note)
{
    // si la note est non nulle
    if(note != NOTE_NULLE)
    {
        // obtient la note
        NoteMidi note_midi = (NOTE_MIN <= note && note <= NOTE_MAX) ? DATA_NOTES[note - NOTE_MIN] : DATA_NOTES[0];

        // recupere les infos
        Prescaler pre = note_midi.pre;
        uint8_t val_ocrn = note_midi.val_ocrn;

        // execute
        startTimer2();
        setPrescalerTimer2(pre);
        setOCRnATimer2(val_ocrn);
    }
    else
    {
        // si la note est nulle
        stop();
    }
}

void Buzzer::stop()
{
    stopTimer2();
}
