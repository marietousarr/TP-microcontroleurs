#include "Timer.h"
#include "Driver_GPIO.h"


MyTimer_Struct_TypeDef Timer;
MyTimer_Struct_TypeDef TimerS;

MyGPIO_Struct_TypeDef inputEncoder;
MyGPIO_Struct_TypeDef inputEncoder1;

MyGPIO_Struct_TypeDef outputPwm;

int k=0; // valeur pour calculer 'a
int alpha=0;
int teta = 0;
int rationPwm = 0;

int main (){
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ; 
	
	inputEncoder.GPIO = GPIOA;
	inputEncoder.GPIO_Conf = In_Floating;
	inputEncoder.GPIO_Pin = 0;
	MyGPIO_Init(&inputEncoder);
	
	inputEncoder1.GPIO = GPIOA;
	inputEncoder1.GPIO_Conf = In_Floating;
	inputEncoder1.GPIO_Pin = 1;
	MyGPIO_Init(&inputEncoder1);
	
	outputPwm.GPIO = GPIOA;
	outputPwm.GPIO_Conf = AltOut_Ppull;
	outputPwm.GPIO_Pin = 6;
	MyGPIO_Init(&outputPwm);
	
	Timer.timer = TIM2;
	Timer.ARR = 360*4; // resolution
	Timer.PSC = 1;
	MyTimer_Base_Init(&Timer);
	MyTimer_Base_Start(Timer);
	MyTimer_EncoderMode(&Timer);
	
	// communication de alpha au servomoteur 
	TimerS.timer = TIM3;
	// periode de 0.020s = psc * arr / 72MHz
	TimerS.ARR = 65454; // resolution
	TimerS.PSC = 0.02 * 72000000 / 65454;
	MyTimer_Base_Init(&TimerS);
	MyTimer_Base_Start(TimerS);
	
	

	while(1){
		
		k = Timer.timer -> CNT; //valeur à recuperer pour le encoder mode
		// calculer 'a à partir de k sacahnt que la resolution c'est arr
		alpha = k/4;
		
		if (alpha <= 180 && alpha >= 45)
			teta = alpha +45;
		
		rationPwm =(2-teta/90)*50;
		PWMRatio( TimerS.timer, rationPwm, 1);
		//config pwm
		MyTimer_PWM(TimerS.timer ,1);
	}
	
}

