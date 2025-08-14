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

// Panasonic remote address
#define ADDRESS		0x4004

// RS-232 commands
#define PLAY_COMMAND			0x3A
#define STOP_COMMAND			0x3F
#define FF_COMMAND				0xAB
#define REW_COMMAND				0xAC

#define PAUSE_COMMAND			0x3B
#define EJECT_COMMAND			0x2A
#define REC_COMMAND				0x3C
#define SLOW_COMMAND			0xB1

#define MENU_COMMAND			0xE0
#define OSD_COMMAND				0xE1

#define TRACKING_MINUS_COMMAND	0xD1
#define TRACKING_PLUS_COMMAND	0xD2

#define KEY_DOWN_COMMAND		0xC1
#define KEY_STORE_COMMAND		0xC2

// IR codes for VEQ1656
#define PLAY_CODE		0x09005059
#define STOP_CODE		0x09000009	// eject is possible by holding down STOP button on a remote
#define FF_CODE			0x0900C0C9
#define REW_CODE		0x09004049

#define PAUSE_CODE		0x09006069
#define SLOW_CODE		0x0900F0F9	// slow mode
#define REC_CODE		0x09001019

#define MENU_CODE		0x09806AE3
#define OSD_CODE		0x0900EAE3

#define TRACKING_MINUS	0x098040C9 // tracking - | key UP
#define TRACKING_PLUS	0x098066EF // tracking +

#define KEY_DOWN		0x0980C049
#define KEY_STORE		0x09801A93 // store/OK | reset

typedef struct {
	uint8_t command;
	uint32_t irCode;
} CommandMap;

const CommandMap commandMap[] = {
	{ PLAY_COMMAND,            PLAY_CODE },
	{ STOP_COMMAND,            STOP_CODE },
	{ FF_COMMAND,              FF_CODE },
	{ REW_COMMAND,             REW_CODE },
	{ PAUSE_COMMAND,           PAUSE_CODE },
	{ EJECT_COMMAND,           STOP_CODE },  // same IR as STOP
	{ REC_COMMAND,             REC_CODE },
	{ SLOW_COMMAND,            SLOW_CODE },
	{ MENU_COMMAND,            MENU_CODE },
	{ OSD_COMMAND,             OSD_CODE },
	{ TRACKING_MINUS_COMMAND,  TRACKING_MINUS },
	{ TRACKING_PLUS_COMMAND,   TRACKING_PLUS },
	{ KEY_DOWN_COMMAND,        KEY_DOWN },
	{ KEY_STORE_COMMAND,       KEY_STORE }
};

uint8_t cmd;

ISR(USART_RX_vect) {
	cmd = UDR0;
	for (uint8_t i = 0; i < sizeof(commandMap) / sizeof(commandMap[0]); i++) {
		if (commandMap[i].command == cmd) {
			if (cmd == EJECT_COMMAND){
				// activating eject by "holding down" STOP button for ~3s
				for (uint8_t j = 0; j < 20; j++){
					sendPanasonic(ADDRESS, STOP_CODE);
					_delay_ms(100);
				}
			}
			else
			{
				sendPanasonic(ADDRESS, commandMap[i].irCode);
			}
			break;
		}
	}
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

	}
}

