/*************************************************
* AUTHOR : Amira Moustafa
* Date   : 29/11/2020
* VERION : V0.0 
* DISCRIPTION: DIO_Interface.h
**************************************************/

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "STD_Type.h"

/*function prototype*/
void DIO_voidSetPinDirection(u8 copy_u8port, u8 copy_u8pin, u8 copy_u8state);
void DIO_voidSetPinValue    (u8 copy_u8port, u8 copy_u8pin, u8 copy_u8value);
u8   DIO_voidGetPinValue    (u8 copy_u8port, u8 copy_u8pin);
void DIO_SetPortDirection	(u8 copy_u8port, u8 copy_u8state);
void DIO_SetPortValue		(u8 copy_u8port, u8 copy_u8value);
void DIO_voidTogglePin		(u8 copy_u8port, u8 copy_u8pin);
void DIO_voidSetSomePinsDir (u8 copy_u8port, u8 copy_u8num_pins, u8 copy_u8state);
void DIO_voidSetSomePinsval (u8 copy_u8port, u8 copy_u8num_pins, u8 copy_u8val);

#endif

