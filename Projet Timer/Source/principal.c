//#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"


MyTimer_Struct_TypeDef Timer;
MyGPIO_Struct_TypeDef broche_led;


void Callback(){
	MyGPIO_Toggle(GPIOA, 5);
}

int main(void)
{
	
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ; //on a écrit 1 au 2e, 3e et 4e bit de APB2ENR
	
// Paramètres led
broche_led.GPIO = GPIOA;
broche_led.GPIO_Pin = 0x05;

//config de la led en push pull
broche_led.GPIO_Conf = Out_Ppull;

MyGPIO_Init(&broche_led);
	
	// Test avec fonctions
Timer.timer = TIM2;
Timer.ARR = 65454;
Timer.PSC = 550;
MyTimer_Base_Init (&Timer);
	
//MyTimer_ActiveIT(Timer.timer ,0, Callback);
	
MyTimer_Base_Start(Timer);

PWMRatio(Timer.timer ,20);
MyTimer_PWM(Timer.timer,1);

while(1) {
	//MyTimer_Base_Stop(Timer);
	
	}

	
//Test sans fonctions
/*
TIM2->ARR = 65454;
TIM2->PSC = 550;
TIM2->CR1 = TIM2->CR1 | ( 1 << 0);
	
	while(1) {
		if (TIM2->SR & TIM_SR_UIF) { // Scrutation de UIF
    TIM2->SR = TIM2->SR & ~TIM_SR_UIF; // Remise à zéro de UIF
		}
	}
*/

	
}

