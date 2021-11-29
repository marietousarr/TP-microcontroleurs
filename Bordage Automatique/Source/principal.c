#include "Timer.h"
#include "Driver_GPIO.h"
#include "Driver_Servomoteur.h"

MyTimer_Struct_TypeDef TimerE; // Timer qui sera en encoder mode, le nom de cette variable n'est pas à modifier par l'utilisateur
															// car elle est utilisé par le driver Timer.c
MyTimer_Struct_TypeDef TimerP; //timer permettant d'emettre la pwm pour le servomoteur

MyGPIO_Struct_TypeDef inputEncoderA; // Port de gpio pour le signal A de la girouette
MyGPIO_Struct_TypeDef inputEncoderB; // port gpio pour le signal B de la girouette
MyGPIO_Struct_TypeDef inputEncoderI; // Port gpio pour le signal I de la girouette

MyGPIO_Struct_TypeDef outputPwm; // port de gpio sortant la pwm

int main (){
	
	//enable des gpio, des timers et des afio
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC-> APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	//config des gpio pour le encoder mode
	inputEncoderA.GPIO = GPIOA;
	inputEncoderA.GPIO_Conf = In_Floating;
	inputEncoderA.GPIO_Pin = 0x00;
	MyGPIO_Init(&inputEncoderA);
	
	inputEncoderB.GPIO = GPIOA;
	inputEncoderB.GPIO_Conf = In_Floating;
	inputEncoderB.GPIO_Pin = 0x01;
	MyGPIO_Init(&inputEncoderB);
	
	inputEncoderI.GPIO = GPIOB;
	inputEncoderI.GPIO_Conf = In_Floating;
	inputEncoderI.GPIO_Pin = 0x00;
	MyGPIO_Init(&inputEncoderI);
	
	//config timer pour le encoder mode
	TimerE.timer = TIM2;
	TimerE.ARR = 360*4; // resolution
	TimerE.PSC = 0;
	MyTimer_Base_Init(&TimerE);
	MyTimer_Base_Start(TimerE);
	MyTimer_EncoderMode(&TimerE);
	
	//config des gpio pour la pwm
	outputPwm.GPIO = GPIOA;
	outputPwm.GPIO_Conf = AltOut_Ppull;
	outputPwm.GPIO_Pin = 0x06;
	MyGPIO_Init(&outputPwm);
	
	//config timer pour la pwm
	TimerP.timer = TIM3;
	// periode de 20ms = psc * arr / 72MHz => psc = 20ms * 72 MHz / arr
	TimerP.ARR = 65454; // resolution
	TimerP.PSC = 20 * 72000000 / (65454 * 1000);
	MyTimer_Base_Init(&TimerP);
	MyTimer_Base_Start(TimerP);
	
	//init interrution pour remettre à 0 l'angle après un tour complet
	init_EXIT(); 
	//activation de l'interruption pour changer l'angle des voile en fonction de la direction du vent
	MyTimer_ActiveIT(TimerP.timer ,0, cacul_angle_servo);

	//config pwm
	MyTimer_PWM(TimerP.timer ,1);
	PWMRatio(TimerP.timer, 10.0, 1); //ratio de 10 par défault correspondant à un angle de 0°
	
	while(1){}
	
}

