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
    {Prescaler::Pres_1024, 238}, {Prescaler::Pres_1024, 225}, {Prescaler::Pres_1024, 212}, {Prescaler::Pres_1024, 200}, {Prescaler::Pres_1024, 189},
    {Prescaler::Pres_1024, 178}, {Prescaler::Pres_1024, 168}, {Prescaler::Pres_1024, 159}, {Prescaler::Pres_1024, 150}, {Prescaler::Pres_1024, 142},
    {Prescaler::Pres_1024, 134}, {Prescaler::Pres_1024, 126}, {Prescaler::Pres_1024, 119}, {Prescaler::Pres_1024, 112}, {Prescaler::Pres_1024, 106},
    {Prescaler::Pres_1024, 100}, {Prescaler::Pres_1024, 94}, {Prescaler::Pres_1024, 89}, {Prescaler::Pres_1024, 84}, {Prescaler::Pres_1024, 79},
    {Prescaler::Pres_1024, 75}, {Prescaler::Pres_1024, 71}, {Prescaler::Pres_1024, 67}, {Prescaler::Pres_256, 253}, {Prescaler::Pres_256, 238},
    {Prescaler::Pres_256, 225}, {Prescaler::Pres_256, 212}, {Prescaler::Pres_256, 200}, {Prescaler::Pres_256, 189}, {Prescaler::Pres_256, 178},
    {Prescaler::Pres_256, 168}, {Prescaler::Pres_256, 159}, {Prescaler::Pres_256, 150}, {Prescaler::Pres_256, 142}, {Prescaler::Pres_256, 134},
    {Prescaler::Pres_128, 253}, {Prescaler::Pres_128, 238}, {Prescaler::Pres_128, 225}, {Prescaler::Pres_128, 212}, {Prescaler::Pres_128, 200},
    {Prescaler::Pres_128, 189}, {Prescaler::Pres_128, 178}, {Prescaler::Pres_128, 168}, {Prescaler::Pres_128, 159}, {Prescaler::Pres_128, 150},
    {Prescaler::Pres_128, 142}, {Prescaler::Pres_128, 134}, {Prescaler::Pres_64, 253}, {Prescaler::Pres_64, 238}, {Prescaler::Pres_64, 225},
    {Prescaler::Pres_64, 212}, {Prescaler::Pres_64, 200}, {Prescaler::Pres_64, 189}, {Prescaler::Pres_64, 178}, {Prescaler::Pres_64, 168},
    {Prescaler::Pres_64, 159}, {Prescaler::Pres_64, 150}, {Prescaler::Pres_64, 142}, {Prescaler::Pres_64, 134}, {Prescaler::Pres_32, 253},
    {Prescaler::Pres_32, 238}, {Prescaler::Pres_32, 225}, {Prescaler::Pres_32, 212}, {Prescaler::Pres_32, 200}, {Prescaler::Pres_32, 189},
    {Prescaler::Pres_32, 178}, {Prescaler::Pres_32, 168}, {Prescaler::Pres_32, 159}, {Prescaler::Pres_32, 150}, {Prescaler::Pres_32, 142},
    {Prescaler::Pres_32, 134}, {Prescaler::Pres_32, 126}, {Prescaler::Pres_32, 119}, {Prescaler::Pres_32, 112}, {Prescaler::Pres_32, 106},
    {Prescaler::Pres_32, 100}, {Prescaler::Pres_32, 94}, {Prescaler::Pres_32, 89}, {Prescaler::Pres_32, 84}, {Prescaler::Pres_32, 79},
    {Prescaler::Pres_32, 75}, {Prescaler::Pres_32, 71}, {Prescaler::Pres_32, 67}, {Prescaler::Pres_8, 253}, {Prescaler::Pres_8, 238},
    {Prescaler::Pres_8, 225}, {Prescaler::Pres_8, 212}, {Prescaler::Pres_8, 200}, {Prescaler::Pres_8, 189}, {Prescaler::Pres_8, 178},
    {Prescaler::Pres_8, 168}, {Prescaler::Pres_8, 159}, {Prescaler::Pres_8, 150}, {Prescaler::Pres_8, 142}, {Prescaler::Pres_8, 134},
    {Prescaler::Pres_8, 126}, {Prescaler::Pres_8, 119}, {Prescaler::Pres_8, 112}, {Prescaler::Pres_8, 106}, {Prescaler::Pres_8, 100},
    {Prescaler::Pres_8, 94}, {Prescaler::Pres_8, 89}, {Prescaler::Pres_8, 84}, {Prescaler::Pres_8, 79}, {Prescaler::Pres_8, 75},
    {Prescaler::Pres_8, 71}, {Prescaler::Pres_8, 67}, {Prescaler::Pres_8, 63}, {Prescaler::Pres_8, 59}, {Prescaler::Pres_8, 56},
    {Prescaler::Pres_8, 53}, {Prescaler::Pres_8, 50}, {Prescaler::Pres_8, 47}, {Prescaler::Pres_8, 44}, {Prescaler::Pres_8, 42},
    {Prescaler::Pres_8, 39}};

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

    Timer2::setCompACallback(&callbackNote);
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
        Timer2::start();
        Timer2::setPrescaler(pre);
        Timer2::setOCRnA(val_ocrn);
    }
    else
    {
        // si la note est nulle : silence
        stop();
    }
}

void Buzzer::stop()
{
    Timer2::stop();
}
