#include <stdint.h>
#include "ADS8328.h"

static void toggle_chip_select(void)
{
    gpio_put(CS_PIN, !gpio_get(CS_PIN));    
}

static uint16_t ADS8328_read_config_register(void)
{
    uint16_t address = READ_CFG;    
    uint16_t nothing = 0; 
    uint16_t result;

    toggle_chip_select();
    spi_write16_blocking(spi_default, &address, 1);
    spi_read16_blocking(spi_default, 0x00,  &nothing, 1); 
    spi_read16_blocking(spi_default, 0x00, &result, 1); 
    toggle_chip_select();

    return result | CFG_REG_MASK;
}

void setup_ADS8328(void)
{
    uint16_t config_reg_value = ADS8328_read_config_register();
    config_reg_value &= ~(1 << ConfigReg.CHANNEL_SELECT_MODE);
    
    uint16_t write_cfg_req_address = WRITE_CFR;
    uint16_t ack;

    toggle_chip_select();
    spi_write16_blocking(spi_default, &write_cfg_reg_addresss, 1);
    spi_write16_blocking(spi_default, &config_reg_value, 1);  
    spi_read16_blocking(spi_default, &ack, 1);
    toggle_chip_select();    
}

void read_ADS8328(uint8_t channel)
{
}

