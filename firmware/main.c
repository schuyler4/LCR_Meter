#include <stdio.h>
#include "pico/stdlib.h"

int main(void)
{
	stdio_init_all();
	const uint LED_PIN = PICO_DEFAULT_LED_PIN;

	gpio_init(LED_PIN);

	gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_put(LED_PIN, 1);
	printf("Hello UART\n");

	while(1)
	{
		gpio_put(LED_PIN, 0);
		printf("GOD\n");
		sleep_ms(1000);


		gpio_put(LED_PIN, 1);
		printf("LED OFF\n");
		sleep_ms(1000);
	}

	return 1;
}
