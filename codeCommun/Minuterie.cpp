void Minuterie(const uint16_t duree)
{
    TCNT1 =  0;
    
    OCR1A = duree; 
}

void SetUpMinuterie()
{
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) ;  

    TCCR1B |= (1 << WGM12)  | (1 << CS12) | (1 << CS10) ;

    TIMSK1 |=  (1 << OCIE1A);
}
