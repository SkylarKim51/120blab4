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

enum states {init, start, pressPound, releasePound, pressY, release Y, pressLock} state;
unsigned char tempA;
unsigned char count;
/*unsigned char A0 = 0x00;
unsigned char A1 = 0x00;*/

void stateMachine(){
	switch(state) {
		case init:
			state = start;
			break;

		case start:
			if(tempA == 0x04){
				state = pressPound;
			}
			else if(tempA & 0x80){
				state = pressLock;
			}
			else{
				state = start;
			}
			break;

		case pressPound:
			if(tempA == 0x00){
				state = releasePound;
			}
			else if(tempA == 0x04){
				state = pressPound;
			}
			else if(tempA & 0x80){
				state = pressLock;
			}
			else{
				state = start;
			}
			break;

		case releasePound:
			if(tempA == 0x00){
				state = releasePound;
			}
			else if(tempA == 0x01){
				state = PressY;
			}
			else if(tempA == 0x80){
				state = pressLock;
			}
			else {
				state = start;
			}
			break;

		case PressY:
			if(tempA == 0x00){
				state = releaseY;
			}		
			else if(tempA == 0x01){
				state = pressY;
			}
			else if(tempA & 0x80){
				state = pressLock;
			}
			else if(tempA == 0x03){
				state = pressReset;
			}
			else{
				state = start;
			}					
			break;
		
		case releaseY:
			if(tempA == 0x00){
				state = releaseY;
			}
			else if(tempA & 0x80){
				state = pressLock;
			}
			else{
				state = start;
			}
			break;
		
		case pressMinus:


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
