#include "led_blink.h"

#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRC |= (1 << PC7);
	while (true) {
    	PORTC |= (1 << PC7);
		_delay_ms(1000);
		PORTC &= ~(1 << PC7);
		_delay_ms(1000);
	}

	return 0;
}
