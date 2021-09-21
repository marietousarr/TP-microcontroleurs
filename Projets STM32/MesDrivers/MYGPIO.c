#include <stdio.h>
#include <stdlib.h>


void MyGPIO_Init( MyGPIO_Struct_TypeDef * GPIOStructPtr){
	
	GPIOStructPtr -> GPIO -> CRL &= ~(0xF << (GPIO_Pin*4));
	
	GPIOStructPtr -> GPIO -> CRL |= (GPIO_Conf<< GPIO_Pin*4);
}

int MyGPIO_Read( MyGPIO_TypeDef * GPIO, char GPIO_Pin){
	if (GPIO -> IDR & (0x1 << GPIO_Pin)) return 1;
	else return 0;
}

void MyGPIO_Set( MyGPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO -> ODR |= (0x01 << GPIO_Pin);
}

void MyGPIO_Reset( MyGPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO -> ODR &= ~(0x01 << GPIO_Pin);
}

void MyGPIO_Toggle( MyGPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO -> ODR ^= (0x01 << GPIO_Pin);
}