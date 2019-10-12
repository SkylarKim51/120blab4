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

enum states {init, start, pressAdd, releaseAdd, pressMinus, releaseMinus, pressReset, releaseReset} state;
unsigned char tempA = 0x00;
unsigned char count = 0x07;
unsigned char A0 = 0x00;
unsigned char A1 = 0x00;

void stateMachine(){
	switch(state) {
		case init:
			state = start;
			printf("init, ");
			break;

		case start:
			if(A0 && !A1){
				state = pressAdd;
			}
			else if(!A0 && A1){
				state = pressMinus;
			}
			else if(A0 && A1){
				state = pressReset;
			}
			else if(!A0 && !A1){
				state = start;
			}
			printf("start, ");
			break;
		
		case pressAdd:
			if(A0 && !A1){
				state = pressAdd;
			}
			else if(!A0 && !A1){
				state = releaseAdd;
			}
			else if(A0 && A1){
				state = pressReset;
			}
			printf("pressAdd, ");
			break;

		case releaseAdd:
			if(!A0 && !A1){
				state = releaseAdd;
			}		
			else if(!A0 && A1){
				state = pressMinus;
			}
			else if(A0 && !A1){
				state = pressAdd;
			}
			else if(A0 && A1){
				state = pressReset;
			}
			printf("releaseAdd, ");					
			break;

		case pressMinus:
			if(!A0 && A1){
				state = pressMinus;
			}
			else if(!A0 && !A1){
				state = releaseMinus;
			}
			else if(A0 && A1){
				state = pressReset;
			}
			printf("pressMinus, ");		
			break;

		case releaseMinus:
			if(!A0 && !A1){
				state = releaseMinus;
			}
			else if(A0 && !A1){
				state = pressAdd;
			}
			else if(A0 && A1){
				state = pressReset;
			}
			else if(!A0 && A1){
				state = pressMinus;
			}
			printf("releaseMinus, ");
			break;
		
		case pressReset:
			if((A0 && A1) || (!A0 && A1) || (A0 && !A1)){
				state = pressReset;
			}
			else if(!A0 && !A1){
				state = releaseReset;
			}
			printf("pressReset, ");
			break;
		
		case releaseReset:
			if(!A0 && !A1){
				state = releaseReset;
			}
			else if(A0 && !A1){
				state = pressAdd;
			}
			else if(!A0 && A1){
				state = pressMinus;
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
			break;

		case pressAdd:
			if(count >=  9){
				count = count;
			}
			else{
				count = count + 1;
			}
			break;
	
		case releaseAdd:
			break;
		
		case pressMinus:
			if(count <= 0){
				count = count;
			}
			else{
				count = count - 1;
			}
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
	A0 = tempA & 0x01;
	A1 = tempA & 0x02;
	stateMachine();
	PORTC = count;
	count = 0x07;	
    }
	
    return 1;
}
