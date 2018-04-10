/**
 * \file interruption.cpp
 * \brief implementation de la classe Interruption
 * \author 
 */

#include "interruption.h"


func_t Interruption::int0FuncPtr = nullptr;
func_t Interruption::int1FuncPtr = nullptr;

ISR(INT0_vect)
{
    if (Interruption::int0FuncPtr != nullptr) Interruption::int0FuncPtr();

    // clear flag
    EIFR |= (1 << INTF0);
}

ISR(INT1_vect)
{
    if (Interruption::int1FuncPtr != nullptr) Interruption::int1FuncPtr();

    // clear flag
    EIFR |= (1 << INTF1);
}

void Interruption::initInt0(func_t funcInt0, const TypesTriggerInterrupt typeInt0)
{
    // garde en memoire le pointeur vers la fonction de callback
    int0FuncPtr = funcInt0;

    cli();

    // pin INT0 en entree
    DDRD &= ~(_BV(_BROCHE_TO_PIN(BROCHE_BOUTON)));

    // interruption externe sur INT0
    EIMSK |= (1 << INT0);

    // selon type de trigger specifie
    switch (typeInt0)
    {
        case TypesTriggerInterrupt::RisingEdge:
            EICRA |= (1 << ISC00) | (1 << ISC01);
            break;
        case TypesTriggerInterrupt::FallingEdge:
            EICRA |= (1 << ISC01);
            break;
        default:
        case TypesTriggerInterrupt::RisingOrFallingEdge:
            EICRA |= (1 << ISC00);
            break;
    }

    sei();
}

void Interruption::initInt1(func_t funcInt1, const TypesTriggerInterrupt typeInt1)
{
    // garde en memoire le pointeur vers la fonction de callback
    int1FuncPtr = funcInt1;

    cli();

    // pin INT1 en entree
    DDRD &= ~(_BV(_BROCHE_TO_PIN(BROCHE_BOUTON+1)));

    // interruption externe sur INT1
    EIMSK |= (1 << INT1);

    // selon type de trigger specifie
    switch (typeInt1)
    {
        case TypesTriggerInterrupt::RisingEdge:
            EICRA |= (1 << ISC10) | (1 << ISC11);
            break;
        case TypesTriggerInterrupt::FallingEdge:
            EICRA |= (1 << ISC11);
            break;
        default:
        case TypesTriggerInterrupt::RisingOrFallingEdge:
            EICRA |= (1 << ISC10);
            break;
    }

    sei();
}

