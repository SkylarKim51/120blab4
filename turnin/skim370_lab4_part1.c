/*	Author: skim370
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <stdio.h>
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"

#endif

enum states {init, onB0, pressB1, onB1, pressB0} state;
unsigned char tempA = 0x00;
unsigned char tempB = 0x00;

void stateMachine(){
	switch(state) {
		case init:
			state = onB0;
			printf("init, ");
			break;

		case onB0:
			if(tempA & 0x01){
				state = pressB1;
			}
			else if(!(tempA & 0x01)){
				state = onB0;
			}
			printf("onB0, ");
			break;

		case pressB1:
			if(!(tempA & 0x01)){
				state = onB1;
			}		
			else if(tempA & 0x01){
				state = pressB1;
			}
			printf("pressB1, ");					
			break;

		case onB1:
			if(tempA & 0x01){
				state = pressB0;
			}
			else if(!(tempA & 0x01)){
				state = onB1;
			}
			printf("onB1, ");		
			break;

		case pressB0:
			if(!(tempA & 0x01)){
				state = onB0;
			}
			else if(tempA & 0x01){
				state = pressB0;
			}
			printf("pressB0, ");
			break;
		
		default:
			state = onB0;
			break;
	}

	switch(state){
		case init:
			tempB = 0x01;
			break;
		
		case onB0:
			tempB = 0x01;
			break;

		case pressB1:
			tempB = 0x02;
			break;
	
		case onB1:
			tempB = 0x02;
			break;
		
		case pressB0:
			tempB = 0x01;
			break;
		default:
			tempB = 0x01;
			break;
	}
}		

int main() { 
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;

	state = init;
    while (1) {
	tempA = PINA;
	stateMachine();
	PORTB = tempB;	
    }
	
    return 1;
}
