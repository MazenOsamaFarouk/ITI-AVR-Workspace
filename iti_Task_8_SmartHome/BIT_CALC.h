#ifndef BIT_CALC_H
#define BIT_CALC_H 

#define SET_BIT(var, bit_no)      ((var) |=  (1 << (bit_no)))

#define CLR_BIT(var, bit_no)      ((var) &= ~(1 << (bit_no)))

#define TOG_BIT(var, bit_no)      ((var) ^=  (1 << (bit_no)))

#define GET_BIT(var, bit_no)     ((((var) >> (bit_no)) & 0x01))
	
#endif			

