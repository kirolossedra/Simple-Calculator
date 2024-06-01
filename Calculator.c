/*
 * Calculator.c
 *
 *  Created on: 7 Nov 2021
 *      Author: kirol
 */


#include "keypad.h"
#include "lcd.h"
#include <avr/delay.h>
#define RAM_SIZE 30
uint8 RAM[RAM_SIZE];


void read(void){
	uint8 key;
	uint8 calc=0;
	uint8 OpIndex;
	uint32 Operand1=0;
	uint32 Operand2=0;

	ready=0;
	LCD_displayStringRowColumn(0,0,"Try Calculating");

			LCD_displayStringRowColumn(1,0,"     ");
			LCD_moveCursor(1,0);


			/*LOOP till filling RAM buffer */

			for(int i=0; i<RAM_SIZE; i++){
						while(!ready){key=KEYPAD_getPressedKey();   }
						if(key<=9){LCD_intgerToString(key);}else{LCD_displayCharacter(key);}
						if(key=='='){break;}
						RAM[i]=key;
						calc++;

							ready=0;
							_delay_ms(290);

					}

//			LCD_intgerToString(calc);

			for(itr i=0; i<calc-1; i++){
				if(RAM[i]>9){OpIndex=i;}
			}
			LCD_moveCursor(2,0);
//			LCD_intgerToString(OpIndex);


			for(itr i=0; i<OpIndex; i++){
//				LCD_intgerToString(CALC[i]);
				uint64 uints=1;
				for(itr j=i; j<OpIndex-1; j++){
					uints*=10;


				}
				Operand1+=uints*RAM[i];


			}


			for(itr i=OpIndex+1; i<calc; i++){
				uint64 uints=1;
							for(itr j=i; j<calc-1; j++){
								uints*=10;


							}
							Operand2+=uints*RAM[i];

			}
			/*Check for the required Operation */
			switch(RAM[OpIndex]){
			case '+':
				LCD_longToString((long)((Operand1)+(Operand2)));
				break;
			case '-':
			LCD_longToString((long)((Operand1)-(Operand2)));
			break;
			case '*':
			LCD_longToString((long)((Operand1)*(Operand2)));
							break;
			case '/':
			LCD_doubleToString((double)(Operand1)/(double)Operand2);
			break;

			}
			ready=0;
			key=0;
			while(key!=127){
				while(!ready){key=KEYPAD_getPressedKey();   }

			}

			/*Clear the LCD
			and the read flag and key */

			ready=0;
			key=0;
			LCD_clearScreen();






}


int main(){

	LCD_init();

	while(1){
		read();

	}

}
