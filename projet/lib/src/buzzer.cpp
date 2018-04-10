/**
 * \file buzzer.cpp
 * \brief implementation de la classe Buzzer
 * \author 
 * 
 * Brancher le buzzer entre la broche BROCHE_BUZZER et le GND.
 */

#include "buzzer.h"


const NoteMidi Buzzer::DATA_NOTES[] = {
    {Prescaler::Div_1024, 238}, {Prescaler::Div_1024, 225}, {Prescaler::Div_1024, 212}, {Prescaler::Div_1024, 200}, {Prescaler::Div_1024, 189},
    {Prescaler::Div_1024, 178}, {Prescaler::Div_1024, 168}, {Prescaler::Div_1024, 159}, {Prescaler::Div_1024, 150}, {Prescaler::Div_1024, 142},
    {Prescaler::Div_1024, 134}, {Prescaler::Div_1024, 126}, {Prescaler::Div_1024, 119}, {Prescaler::Div_1024, 112}, {Prescaler::Div_1024, 106},
    {Prescaler::Div_1024, 100}, {Prescaler::Div_1024, 94}, {Prescaler::Div_1024, 89}, {Prescaler::Div_1024, 84}, {Prescaler::Div_1024, 79},
    {Prescaler::Div_1024, 75}, {Prescaler::Div_1024, 71}, {Prescaler::Div_1024, 67}, {Prescaler::Div_256, 253}, {Prescaler::Div_256, 238},
    {Prescaler::Div_256, 225}, {Prescaler::Div_256, 212}, {Prescaler::Div_256, 200}, {Prescaler::Div_256, 189}, {Prescaler::Div_256, 178},
    {Prescaler::Div_256, 168}, {Prescaler::Div_256, 159}, {Prescaler::Div_256, 150}, {Prescaler::Div_256, 142}, {Prescaler::Div_256, 134},
    {Prescaler::Div_128, 253}, {Prescaler::Div_128, 238}, {Prescaler::Div_128, 225}, {Prescaler::Div_128, 212}, {Prescaler::Div_128, 200},
    {Prescaler::Div_128, 189}, {Prescaler::Div_128, 178}, {Prescaler::Div_128, 168}, {Prescaler::Div_128, 159}, {Prescaler::Div_128, 150},
    {Prescaler::Div_128, 142}, {Prescaler::Div_128, 134}, {Prescaler::Div_64, 253}, {Prescaler::Div_64, 238}, {Prescaler::Div_64, 225},
    {Prescaler::Div_64, 212}, {Prescaler::Div_64, 200}, {Prescaler::Div_64, 189}, {Prescaler::Div_64, 178}, {Prescaler::Div_64, 168},
    {Prescaler::Div_64, 159}, {Prescaler::Div_64, 150}, {Prescaler::Div_64, 142}, {Prescaler::Div_64, 134}, {Prescaler::Div_32, 253},
    {Prescaler::Div_32, 238}, {Prescaler::Div_32, 225}, {Prescaler::Div_32, 212}, {Prescaler::Div_32, 200}, {Prescaler::Div_32, 189},
    {Prescaler::Div_32, 178}, {Prescaler::Div_32, 168}, {Prescaler::Div_32, 159}, {Prescaler::Div_32, 150}, {Prescaler::Div_32, 142},
    {Prescaler::Div_32, 134}, {Prescaler::Div_32, 126}, {Prescaler::Div_32, 119}, {Prescaler::Div_32, 112}, {Prescaler::Div_32, 106},
    {Prescaler::Div_32, 100}, {Prescaler::Div_32, 94}, {Prescaler::Div_32, 89}, {Prescaler::Div_32, 84}, {Prescaler::Div_32, 79},
    {Prescaler::Div_32, 75}, {Prescaler::Div_32, 71}, {Prescaler::Div_32, 67}, {Prescaler::Div_8, 253}, {Prescaler::Div_8, 238},
    {Prescaler::Div_8, 225}, {Prescaler::Div_8, 212}, {Prescaler::Div_8, 200}, {Prescaler::Div_8, 189}, {Prescaler::Div_8, 178},
    {Prescaler::Div_8, 168}, {Prescaler::Div_8, 159}, {Prescaler::Div_8, 150}, {Prescaler::Div_8, 142}, {Prescaler::Div_8, 134},
    {Prescaler::Div_8, 126}, {Prescaler::Div_8, 119}, {Prescaler::Div_8, 112}, {Prescaler::Div_8, 106}, {Prescaler::Div_8, 100},
    {Prescaler::Div_8, 94}, {Prescaler::Div_8, 89}, {Prescaler::Div_8, 84}, {Prescaler::Div_8, 79}, {Prescaler::Div_8, 75},
    {Prescaler::Div_8, 71}, {Prescaler::Div_8, 67}, {Prescaler::Div_8, 63}, {Prescaler::Div_8, 59}, {Prescaler::Div_8, 56},
    {Prescaler::Div_8, 53}, {Prescaler::Div_8, 50}, {Prescaler::Div_8, 47}, {Prescaler::Div_8, 44}, {Prescaler::Div_8, 42},
    {Prescaler::Div_8, 39}};

void callbackNote()
{
    // inverse la broche
    PORTC ^= _BV(_BROCHE_TO_PIN(BROCHE_BUZZER));
}

void Buzzer::init()
{
    // met la broche en sortie
    DDRC |= _BV(_BROCHE_TO_PIN(BROCHE_BUZZER));

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
        cli();
        Timer2::resetTCNTn();
        Timer2::setWaveformGenerationMode(WGM::Mode_2);
        Timer2::setCompareOutputMode(COM::Set, COM::Normal);
        Timer2::setInterruptEnable(true, false, false);
        Timer2::setPrescaler(pre);
        Timer2::setOCRnA(val_ocrn);
        sei();
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
