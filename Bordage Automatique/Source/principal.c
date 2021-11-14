#include "Timer.h"
#include "Driver_GPIO.h"


MyTimer_Struct_TypeDef Timer; // encoder
MyTimer_Struct_TypeDef TimerS; //timer de la pwm du servomoteur

MyGPIO_Struct_TypeDef inputEncoder;
MyGPIO_Struct_TypeDef inputEncoder1;
MyGPIO_Struct_TypeDef inputEncoderI;


MyGPIO_Struct_TypeDef outputPwm;

int k=0; // valeur pour calculer 'a
int alpha=0;
int teta = 0;
int rationPwm = 0;

int main (){
	
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ; 
	
	//enable des gpio et des timers
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC-> APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	//config des gpio pour le encoder
	inputEncoder.GPIO = GPIOA;
	inputEncoder.GPIO_Conf = In_Floating;
	inputEncoder.GPIO_Pin = 0x00;
	MyGPIO_Init(&inputEncoder);
	
	inputEncoder1.GPIO = GPIOA;
	inputEncoder1.GPIO_Conf = In_Floating;
	inputEncoder1.GPIO_Pin = 0x01;
	MyGPIO_Init(&inputEncoder1);
	
	inputEncoderI.GPIO = GPIOB;
	inputEncoderI.GPIO_Conf = In_Floating;
	inputEncoderI.GPIO_Pin = 0x00;
	MyGPIO_Init(&inputEncoderI);
	
	//config timer pour le encoder mode
	Timer.timer = TIM2;
	Timer.ARR = 360*4; // resolution
	Timer.PSC = 0;
	MyTimer_Base_Init(&Timer);
	MyTimer_Base_Start(Timer);
	MyTimer_EncoderMode(&Timer);
	
	//config des gpio pour la pwm
	outputPwm.GPIO = GPIOA;
	outputPwm.GPIO_Conf = AltOut_Ppull;
	outputPwm.GPIO_Pin = 0x06;
	MyGPIO_Init(&outputPwm);
	
	//config timer pour la pwm
	// communication de alpha au servomoteur 
	TimerS.timer = TIM3;
	// periode de 20ms = psc * arr / 72MHz
	TimerS.ARR = 65454; // resolution
	TimerS.PSC = 20 * 72000000 / (65454 * 1000);
	MyTimer_Base_Init(&TimerS);
	MyTimer_Base_Start(TimerS);
	
	
	//config pwm
	MyTimer_PWM(TimerS.timer ,1);
	PWMRatio( TimerS.timer, 10, 1);
	
	//init interrution pour remettre à 0 l'angle à un tour complet
	init_EXIT(); 

	while(1){
		
		k = Timer.timer -> CNT; //valeur à recuperer pour le encoder mode
		
		// calculer 'a à partir de k sacahnt que la resolution c'est arr
		alpha = k/4;
		
		//calcul du teta correspondant
		if (alpha >= 45 && alpha <= 180 )
			teta = (90*alpha  -30*135)/135;
		else if (alpha >180 && alpha<=315)
			teta = (-90*alpha  +210*135)/135;
		
		//mise à jour du ratio de la pwm
		rationPwm =(2-teta/90)*100/20;
		PWMRatio( TimerS.timer, rationPwm, 1);
	}
	
}

