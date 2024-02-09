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

static void chip_select_low(void)
{
    gpio_put(CS_PIN, 0);
}

static void chip_select_high(void)
{
    gpio_put(CS_PIN, 1);
}

uint16_t ADS8328_read_config_register(void)
{
    uint16_t address = READ_CFR << COMMAND_OFFSET;    
    uint8_t result1;
    uint8_t result2;

    uint8_t address1 = (uint8_t)(address >> 8);
    uint8_t address2 = (uint8_t)(address & 0xFF);

    chip_select_low();
    spi_write_read_blocking(spi0, &address1, &result1, 1);
    spi_write_read_blocking(spi0, &address2, &result2, 1);
    chip_select_high();

    return (result1 << 8) | result2;
}

void setup_ADS8328(void)
{
    uint8_t write_command = DEFAULT_MODE << COMMAND_OFFSET;
    //uint16_t write_command = DEFAULT_MODE;
    toggle_chip_select();
    //spi_write16_blocking(spi_default, &write_command, 1); 
    spi_write_blocking(spi0, &write_command, 1);
    toggle_chip_select(); 
    /*uint16_t config_reg_value = ADS8328_read_config_register();
    config_reg_value &= ~(1 << CHANNEL_SELECT_MODE_OFFSET);
    
    uint16_t write_cfg_req_address = WRITE_CFR;
    uint16_t read_tx_data = 0;
    uint16_t ack;

    toggle_chip_select();
    spi_write16_blocking(spi_default, &write_cfg_req_address, 1);
    spi_write16_blocking(spi_default, &config_reg_value, 1);  
    spi_read16_blocking(spi_default, read_tx_data, &ack, 1);
    toggle_chip_select();*/    
}

void select_ADS8328_channel(uint8_t channel)
{
    if(channel == 0 || channel == 1)
    {
        uint16_t nothing = 0;
        uint8_t channel_address = channel << COMMAND_OFFSET;
        toggle_chip_select();
        spi_write_blocking(spi0, &channel_address, 1);
        //spi_read16_blocking(spi_default, nothing, &nothing, 1);   
        toggle_chip_select();
    }
}

uint16_t sample_ADS8328(void)
{
    //gpio_put(CONVST_PIN, 0);
    //trigger_delay();   
    //gpio_put(CONVST_PIN, 1); 
    uint16_t zero = 0;
    uint16_t result = 0;    
    uint8_t read_command = READ_DATA << COMMAND_OFFSET;
    toggle_chip_select();
    spi_write_blocking(spi0, &read_command, 1);
    spi_read16_blocking(spi0, zero, &result, 1);
    toggle_chip_select();

    return result; 
}

