/*	Author: skim370
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
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
enum states {init, start, pressPound, pressY, pressLock} state;
unsigned char tempA;
unsigned char count;
unsigned char tempB;

void stateMachine(){
	switch(state) {
		case init:
			state = start;
			break;

		case start:
			if(tempA == 0x00){
				state = start;
			}
			else if(tempA == 0x04){
				state = pressPound;
			}
			else if(tempA == 0x80){
				state = pressLock;
			}
			else{
				state = start;
			}
			break;

		case pressPound:
			if((tempA == 0x04) || (tempA == 0x00)){
				state = pressPound;
			}
			else if(tempA == 0x02){
				state = pressY;
			}
			else if(tempA == 0x80){
				state = pressLock;
			}
			else{
				state = start;
			}
			break;
			
		case pressY:
			if((tempA == 0x00) || (tempA == 0x02)){
				state = pressY;
			}
			else if(tempA == 0x04){
				state = pressPound;
			}
			else if(tempA == 0x80){
				state = pressLock;
			}
			else{
				state = start;
			}
			break;
		
		case pressLock:
			if(tempA == 0x80){
				state = pressLock;
			}
			else if(tempA == 0x04){
				state = pressPound;
			}
			else{
				state = start;
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
		
		case pressPound:
			break;
		
		case pressY:
			break;
	
		case pressLock:
			break;

		default:
			count = count;
			tempB = tempB;
			break;
	}
}		

int main() { 
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;

	state = init;
    while (1) {
	tempA = PINA;
	reloadA = tempA;
	stateMachine();
	PORTB = count;
	tempB = 0x00;
	count = 0x00;
	
    }
	
    return 1;
}
