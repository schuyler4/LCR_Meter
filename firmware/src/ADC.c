// Configure the ADC registers to setup an interupt ADC sample.
void setup_ADC(void)
{
    // set the ADC reference to the supply voltage (5V)
    ADMUX &= ~(1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    // The 0th ADC channel is used initially, so the channel does not need 
    // to be configured.

    // enable the ADC
    // enable the ADC interupt
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 < ADPS1) | (1 << ADPS0);

    // disable digital logic on ADC pins
    DIDR0 |= (1 << ADC1D) | (1 << ADC0D); 
}

void start_ADC_conversion(void)
{
    ADCSRA |= (1 << ADSC); 
}