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

enum states {init, start, oneAdd, pressAdd, releaseAdd, oneMinus, pressMinus, releaseMinus, pressReset, releaseReset} state;
unsigned char tempA;
unsigned char count;
/*unsigned char A0 = 0x00;
unsigned char A1 = 0x00;*/

void stateMachine(){
	switch(state) {
		case init:
			state = start;
			printf("init, ");
			break;

		case start:
			if(tempA == 0x01){
				state = oneAdd;
			}
			if(tempA == 0x02){
				state = oneMinus;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			if(tempA == 0x00){
				state = start;
			}
			printf("start, ");
			break;

		case oneAdd:
			state = pressAdd;
			break;

		case pressAdd:
			if(tempA == 0x01){
				state = pressAdd;
			}
			if(tempA == 0x00){
				state = releaseAdd;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			printf("pressAdd, ");
			break;

		case releaseAdd:
			if(tempA == 0x00){
				state = releaseAdd;
			}		
			if(tempA == 0x02){
				state = oneMinus;
			}
			if(tempA == 0x01){
				state = oneAdd;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			printf("releaseAdd, ");					
			break;
		
		case oneMinus:
			state = pressMinus;
			break;
		
		case pressMinus:
			if(tempA == 0x02){
				state = pressMinus;
			}
			if(tempA == 0x00){
				state = releaseMinus;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			printf("pressMinus, ");		
			break;

		case releaseMinus:
			if(tempA == 0x00){
				state = releaseMinus;
			}
			if(tempA == 0x01){
				state = oneAdd;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			if(tempA == 0x02){
				state = oneMinus;
			}
			printf("releaseMinus, ");
			break;
		
		case pressReset:
			if(tempA == 0x03 || tempA == 0x01 || tempA == 0x02){
				state = pressReset;
			}
			if(tempA == 0x00){
				state = releaseReset;
			}
			printf("pressReset, ");
			break;
		
		case releaseReset:
			if(tempA == 0x00){
				state = releaseReset;
			}
			if(tempA == 0x01){
				state = oneAdd;
			}
			if(tempA == 0x02){
				state = oneMinus;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			break;
		default:
			state = start;
			break;
	}

	switch(state){
		case init:
			break;
		
		case start:
			count = 0x07;
			break;	

		case oneAdd:
			if(count >=  9){
				count = count;
			}
			else{
				count = count + 1;
			}
			break;
	
		case pressAdd:
			break;

		case releaseAdd:
			break;
		
		case oneMinus:
			if(count <= 0){
				count = count;
			}
			else{
				count = count - 1;
			}
			break;
		
		case pressMinus:
			break;

		case releaseMinus:
			break;

		case pressReset:
			count = 0;
			break;

		case releaseReset:
			break;

		default:
			count = 0x07;
			break;
	}
}		

int main() { 
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;

	state = init;
    while (1) {
	tempA = PINA;
/*	A0 = tempA & 0x01;
	A1 = tempA & 0x02;*/
	stateMachine();
	PORTC = count;	
    }
	
    return 1;
}
