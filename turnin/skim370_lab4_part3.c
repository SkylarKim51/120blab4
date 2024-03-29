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

enum States {init, start, pressPound, releasePound, pressY, releaseY, pressLock, releaseLock} state;

unsigned char tempA;
unsigned char count;
unsigned char tempB;

void stateMachine(){
	switch(state) {
		case init:
			state = start;
			break;

		case start:
			if(tempA == 0x04){
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
			if(tempA == 0x00){
				state = releasePound;
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

		case releasePound:
			if(tempA == 0x00){
				state = releasePound;
			}
			else if(tempA == 0x02){
				state = pressY;
			}
			else if(tempA == 0x80){
				state = pressLock;
			}
			else {
				state = start;
			}
			break;

		case pressY:
			if(tempA == 0x00){
				state = releaseY;
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
		
		case releaseY:
			if(tempA == 0x00){
				state = releaseY;
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
			else if(tempA == 0x00){
				state = releaseLock;
			}
			else {
				state = pressLock;
			}
			break;

		case releaseLock:
			state = start;
			break;

		default:
			state = start;
			break;
	}

	switch(state){
		case init:
			break;
		
		case start:
			if(count == 0x02){
				tempB = 0x01;
				count = count;
			}
			else{
				tempB = 0x00;
				count = 0x00;
			}	
			break;	

		case pressPound:
			break;
	
		case releasePound:
			if(count ==  0x02){
				count = count;
			}
			else{
				count = 0x01;
			}
			break;

		case pressY:
			break;
		
		case releaseY:
			if(count == 0x01){
				count = 0x02;
				tempB = 0x01;
			}
			break;
		
		case pressLock:
			count = 0x00;
			tempB = 0x00;
			break;
		
		case releaseLock:
			break;

		default:
			count = 0x00;
			tempB = 0x00;
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
