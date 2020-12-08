/*
 * GIF_Interface.c
 *
 *  Created on: Jun 19, 2020
 *      Author: mazen
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_CALC.h"
#include "GIE_Register.h"
#include "GIE_Interface.h"




void GIE_enable(void)
{
	SET_BIT(SREG,7);
}
void GIE_disable(void)
{
	CLR_BIT(SREG,7);

}
