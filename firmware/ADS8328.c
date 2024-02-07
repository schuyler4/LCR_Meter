//
// FILENAME: ADS8328.c
//
// DESCRIPTION: ADS8328 16 bit 500kS/s ADC Driver.
//
// WRITTEN BY: Marek Newton
//

#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "main.h"
#include "ADS8328.h"

static void trigger_delay(void)
{
    __asm volatile("nop\n nop \n nop \n nop \n nop \n nop \n nop \n nop \n");   
}

static void toggle_chip_select(void)
{
    gpio_put(CS_PIN, !gpio_get(CS_PIN));    
}

static uint16_t ADS8328_read_config_register(void)
{
    uint16_t address = READ_CFR;    
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
    config_reg_value &= ~(1 << CHANNEL_SELECT_MODE_OFFSET);
    
    uint16_t write_cfg_req_address = WRITE_CFR;
    uint16_t read_tx_data = 0;
    uint16_t ack;

    toggle_chip_select();
    spi_write16_blocking(spi_default, &write_cfg_req_address, 1);
    spi_write16_blocking(spi_default, &config_reg_value, 1);  
    spi_read16_blocking(spi_default, read_tx_data, &ack, 1);
    toggle_chip_select();    
}

void select_ADS8328_channel(uint16_t channel)
{
    if(channel == 0 || channel == 1)
    {
        uint16_t nothing = 0;
        uint16_t channel_address = channel;
        toggle_chip_select();
        spi_write16_blocking(spi_default, &channel_address, 1);
        spi_read16_blocking(spi_default, nothing, &nothing, 1);   
        toggle_chip_select();
    }
}

uint16_t sample_ADS8328(void)
{
    gpio_put(CONVST_PIN, 0);
    trigger_delay();   
    gpio_put(CONVST_PIN, 1); 

    uint16_t result = 0;    
    uint16_t read_command = READ_DATA;
    toggle_chip_select();
    spi_write16_blocking(spi_default, &read_command, 1);
    spi_read16_blocking(spi_default, result, &result, 1);
    toggle_chip_select();

    return result; 
}

