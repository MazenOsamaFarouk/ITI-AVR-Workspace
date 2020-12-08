/* Filename: BIT_MAN.h -> BIT MANIipulation 
*  Author: Mazen Osama Farouk
*  Version: 2.0
*  Description:
 this file contains function macros for most commonly used 
 bit manipulation operations.

*/

#ifndef _BIT_MAN_H
#define _BIT_MAN_H

// 1. BIT selection
// this macro is used in all other macros
#define BIT(n)   (1<<(n))

// FOR ALL  other macros:
//use BIT(n) macro to provid a single bit for a bit_mask
// or use OR like this: (BIT(0)|BIT(1)|BIT(2)|...) to
// provide a multi-bit bit_mask

// 2. SET a bit (or more)
#define SET_BIT(var, bit_mask)		((var) |= (bit_mask))
// 3. CLEAR a bit (or more)
#define CLR_BIT(var, bit_mask)		((var) &=~ (bit_mask))
// 4. TOGGLE a bit (or more)
#define TOG_BIT(var, bit_mask)		((var) ^= (bit_mask))

// 5. ROTate or Circular Shift (Right)
#define ROT_R(var, amt)           (var = (var >> amt) | (var << (sizeof(var)*8 - amt)))
// 6. ROTate or Circular SHIFT (Left)
#define ROT_L(var, amt)	        (var = (var << amt) | (var >> (sizeof(var)*8 - amt)))
// 7. GET a bit value
#define GET_BIT(var, bit_n)			(((var)>>(bit_n)) & 1)
// 8. isEven or isOdd
#define IS_ODD(var)					(((var)>>0) & 1)


// 9. insert a value 
// 9.a shield: used for insert only
#define shield(no_bits,offset)  (((1<<no_bits)-1)<<offset)
// 9.b prep: used for insert only
#define prep(value,offset)		(value<<offset)
//USAGE:  
// a) INPUTS: 
//		-var: the variable to insert the value into
//			  this variable must be an lvalue
//      -value: the value you want to insert into the var
//				its assumed that your value occupies the LSBs
//		-no_bits: the value is represneted in how many bits?
//				 its used to generate the shield
//		-offset: where to insert the value in var
//	for example:
//							7 6 5 4 3 2 1 0
// if var = 				0 0 0 0 0 0 0 0
// and value=0b110 , no_bits=3 , offset=2
// then result will be:  	0 0 0[1 1 0]0 0 
#define INSERT_BITS(var,value,no_bits,offset)	(var)=((var)&(~shield(no_bits,offset)))|   \
												(prep(value,offset)&shield(no_bits,offset))


#endif