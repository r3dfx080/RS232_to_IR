/*
 * uart lib for atmega324/328
 *
 * stolen from the internet and expanded by _redfox
 * 
 */ 

#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000UL // 16MHz clock
#define BAUDRATE 9600 // 9600 baud by default

void UART_init();

// receive character over UART
unsigned char UART_RxChar();

// send character over UART
void UART_TxChar(char chr);

// ChatGPT made one, sends formatted float as XX.XX
void UART_SendFloat(float number);

// send string of chars over UART
void UART_SendString(char *str);

#endif /* UART_H_ */