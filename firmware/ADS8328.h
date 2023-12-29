#ifndef ADS8328_H
#define ADS8328_H

#define SELECT_CHANNEL0 0x0
#define SELECT_CHANNEL1 0x1
#define WAKE_UP 0xB
#define READ_CFR 0xC
#define READ_DATA 0xD
#define WRITE_CFR 0xE
#define DEFAULT_MODE 0xF

#define CFG_REG_MASK 0x0FFF

typedef enum config_reg 
{
    RESET = 0,
    TAG_BIT = 1,
    DEEP_PWR_DOWN = 2,
    NAP_PWR_DOWN = 3,
    AUTO_NAP_PWR_DWN = 4,
    CHAIN_MODE = 5,
    EOC = 6,
    EOC_POLARITY = 7,
    DONT_CARE = 8,
    TRIGGER_SOURCE = 9,
    CLOCK_SOURCE = 10,
    CHANNEL_SELECT_MODE = 11,
} ConfigReg;

void setup_ADS8328(void);
void read_ADS8328(void);

#endif 
