/*************************************************
* AUTHOR : Amira Moustafa
* Date   : 29/11/2020
* VERION : V0.0 
* DISCRIPTION: DIO_Interface.h
**************************************************/
#include "BIT_MATH.h"
#include "STD_Type.h"
#include "DIO_Private.h"

/*function definition*/
void DIO_voidSetPinDirection(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8state){
	if(1 ==  copy_u8state){
		switch(copy_u8port){
			case 0: set_bit(DDRA, copy_u8pin); break;
			case 1: set_bit(DDRB, copy_u8pin); break;
			case 2: set_bit(DDRC, copy_u8pin); break;
			case 3: set_bit(DDRD, copy_u8pin); break;
		}
	}
	else if(0 == copy_u8state){
		switch(copy_u8port){
			case 0: clear_bit(DDRA, copy_u8pin); break;
			case 1: clear_bit(DDRB, copy_u8pin); break;
			case 2: clear_bit(DDRC, copy_u8pin); break;
			case 3: clear_bit(DDRD, copy_u8pin); break;
		}
	}
	else {
		
		
	}		
}
void DIO_voidSetPinValue(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8value){
	if(1 == copy_u8value){
		
		switch(copy_u8port){
			case 0: set_bit(PORTA, copy_u8pin); break;
			case 1: set_bit(PORTB, copy_u8pin); break;
			case 2: set_bit(PORTC, copy_u8pin); break;
			case 3: set_bit(PORTD, copy_u8pin); break;
		}
	}
	else if(0 == copy_u8value){
		switch(copy_u8port){
			case 0: clear_bit(PORTA, copy_u8pin); break;
			case 1: clear_bit(PORTB, copy_u8pin); break;
			case 2: clear_bit(PORTC, copy_u8pin); break;
			case 3: clear_bit(PORTD, copy_u8pin); break;
		}
	}
	else {
		
		
	}
	
	
}
u8   DIO_voidGetPinValue(u8 copy_u8port, u8 copy_u8pin){	

    int result = 0;
	switch(copy_u8port){
		
		case 0: result =  IS_bit_set(PINA, copy_u8pin); break;
		case 1: result =  IS_bit_set(PINB, copy_u8pin); break;
		case 2: result =  IS_bit_set(PINC, copy_u8pin); break;
		case 3: result =  IS_bit_set(PIND, copy_u8pin); break;

	}	
	return result;
}
void DIO_SetPortDirection(u8 copy_u8port, u8 copy_u8state){
	switch(copy_u8port)
	  {
	  case 0: DDRA=copy_u8state; break;
	  case 1: DDRB=copy_u8state; break;
	  case 2: DDRC=copy_u8state; break;
	  case 3: DDRD=copy_u8state; break;
	  }
}
void DIO_SetPortValue(u8 copy_u8port, u8 copy_u8value){
  switch(copy_u8port)
  {
  case 0: PORTA=copy_u8value; break;
  case 1: PORTB=copy_u8value; break;
  case 2: PORTC=copy_u8value; break;
  case 3: PORTD=copy_u8value; break;
  }
	
}
void DIO_voidTogglePin(u8 copy_u8port, u8 copy_u8pin){
	switch(copy_u8port){
		case 0: toggle_bit(PORTA, copy_u8pin); break;
		case 1: toggle_bit(PORTB, copy_u8pin); break;
		case 2: toggle_bit(PORTC, copy_u8pin); break;
		case 3: toggle_bit(PORTD, copy_u8pin); break;
	}
	
}
void DIO_voidSetSomePinsDir (u8 copy_u8port, u8 copy_u8num_pins, u8 copy_u8state){
	for(int i = 0; i < copy_u8num_pins; i++){
		DIO_voidSetPinDirection(copy_u8port, i,  copy_u8state);
	}

}
void DIO_voidSetSomePinsval (u8 copy_u8port, u8 copy_u8num_pins, u8 copy_u8val){
	for(int i = 0; i < copy_u8num_pins; i++){
		DIO_voidSetPinValue(copy_u8port, i,  copy_u8val);
	}

}
