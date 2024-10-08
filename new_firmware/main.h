#ifndef MAIN_H
#define MAIN_H

#define ADC_SAMPLE_COUNT 100

#define CURRENT_ADC_PIN 26
#define VOLTAGE_ADC_PIN 27

#define MUX_BIT0 0
#define MUX_BIT_COUNT 3

void setup_GPIO(void);
void select_range(void);
bool sample_timer_callback(repeating_timer_t *rt);

#endif