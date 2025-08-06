/*
 * uart lib for atmega324/328
 *
 * stolen from the internet and expanded by _redfox
 * 
 */ 
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

void UART_init() {
	UBRR0 = F_CPU / 16 / BAUDRATE - 1;
	
	UCSR0C = (0 << USBS0) | (3 << UCSZ00);
	UCSR0B = (1<<TXEN0) | (1<<RXEN0)| (1 << RXCIE0);
	
}

// send character over UART
void UART_TxChar(char chr) {
	while (!(UCSR0A & (1 << UDRE0)));  /* Wait for empty transmit buffer */
	UDR0 = chr;
}

// receive character over UART
unsigned char UART_RxChar() {
	while (!(UCSR0A & (1 << RXC0)));  // Wait until data is received
	return UDR0;  // Return received character
}

// send string of chars over UART
// uses UART_TxChar
void UART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)
	{
		UART_TxChar(str[j]);
		j++;
	}
}


void UART_SendFloat(float number) {
	char buffer[20];          // Buffer to store the formatted string
	uint16_t integer_part = (uint16_t)number;               // Extract integer part
	uint16_t decimal_part = (uint16_t)((number - integer_part) * 100); // Extract two decimal places

	// Format the float manually as "integer.decimal"
	sprintf(buffer, "%u.%02u ", integer_part, decimal_part);
	UART_SendString(buffer);
}