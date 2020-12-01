/*************************************************
* AUTHOR : Amira Moustafa
* Date   : 29/11/2020
* VERION : V0.0 
* DISCRIPTION: BIT_MATH.h
**************************************************/
#ifndef  BIT_MATH_H
#define  BIT_MATH_H

#define set_bit(REG,BIT_NUM) (REG |= (1<< BIT_NUM))
#define clear_bit(REG,BIT_NUM) (REG  &= ~(1<< BIT_NUM))
#define toggle_bit(REG,BIT_NUM) (REG  ^= (1<< BIT_NUM))
#define IS_bit_set(REG,BIT_NUM) ( REG & (1 << BIT_NUM) )
#define IS_bit_clear(REG,BIT_NUM) (!(REG &(1<< BIT_NUM)))

#endif
