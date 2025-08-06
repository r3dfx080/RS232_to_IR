/*
 * RS232_to_IR.c
 *
 * Author : _redfox
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#include "uart.h"
#include "ir_send.h"

volatile bool ir_trigger = false;

ISR(USART_RX_vect) {
	switch(UDR0){
		default:	
		ir_trigger = true;
		break;
	}
	
	//ir_trigger = true;

}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0xFF;
	
	DDRD &= ~(1 << PD0);
	
	UART_init();
	
	sei();
	
    while (1) 
    {
		if (ir_trigger)
		{
			ir_trigger = false;

			sendPanasonic(0x4004, 0x09005059);
			_delay_ms(100);

	    }
	}
}

