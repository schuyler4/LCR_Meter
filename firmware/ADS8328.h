#ifndef ADS8328_H
#define ADS8328_H

#define CS_PIN 9

#define CHANNEL0 0x0
#define CHANNEL1 0x1
#define WAKE_UP 0xB
#define READ_CFR 0xC
#define READ_DATA 0xD
#define WRITE_CFR 0xE
#define DEFAULT_MODE 0xF

#define CFG_REG_MASK 0x0FFF

#define COMMAND_OFFSET 4

#define RESET_OFFSET 0
#define TAG_BIT_OFFSET 1
#define DEEP_PWR_DOWN_OFFSET 2
#define NAP_PWR_DOWN_OFFSET 3
#define AUTO_NAP_PWR_DWN_OFFSET 4
#define CHAIN_MODE_OFFSET 5
#define EOC_OFFSET 6
#define EOC_POLARITY_OFFSET 7
#define DONT_CARE_OFFSET 8 
#define TRIGGER_SOURCE_OFFSET 9
#define CLOCK_SOURCE_OFFSET 10
#define CHANNEL_SELECT_MODE_OFFSET 11

void setup_ADS8328(void);
void select_ADS8328_channel(uint16_t channel);
uint16_t sample_ADS8328(void);

#endif 
