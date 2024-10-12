#ifndef MAIN_H
#define MAIN_H

#define ADC_SAMPLE_COUNT 255

#define CURRENT_ADC_PIN 26
#define VOLTAGE_ADC_PIN 27
#define CURRENT_ADC_CHANNEL 0
#define VOLTAGE_ADC_CHANNEL 1

#define MUX_BIT0 0
#define MUX_BIT_COUNT 3

#define VOLTAGE_HIGH_THRESHOLD 2.9
#define VOLTAGE_LOW_THRESHOLD 2.6

float RANGE_RESISTORS[] = {499, 4990, 49900, 499000, 4990000};

void setup_GPIO(void);
void select_range(uint8_t range);
bool sample_timer_callback(repeating_timer_t *rt);
float take_reading(void);

#endif