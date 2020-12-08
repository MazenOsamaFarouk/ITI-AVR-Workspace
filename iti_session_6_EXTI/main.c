#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MAN.h"
#include "DIO/DIO_Interface.h"
#include "EXTI/EXTI_Interface.h"
#include "GIE/GIE_Interface.h"

void toggle_led(void)
{
	DIO_VidTogPinValue(PORTC,PIN7);
}

int main(void)
{

DIO_VidSetPinDirection(PORTC,PIN7,OUTPUT);

EXTI_SetCallBack(INT1_EN,toggle_led);
EXTI_init();
EXTI_enable(1);

GIE_enable();

while(1)
{

}





}
