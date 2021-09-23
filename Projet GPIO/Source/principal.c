//#include "stm32f10x.h"
#include "Driver_GPIO.h"

//�l�ments internes
#define BROCHE_BP GPIOC
#define PORT_BP 13
#define BROCHE_LD GPIOA
#define PORT_LD 5

// �l�ments externes
#define BROCHE_LD_E GPIOC
#define PORT_LD_E 10

// d�claration led et bouton poussoir 
MyGPIO_Struct_TypeDef broche_led;
MyGPIO_Struct_TypeDef broche_bp;

int main( void )
{
	
RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ; //on a �crit 1 au 2e, 3e et 4e bit de APB2ENR

	//Test sans fonctions 
/*	
//config de la led en push pull
BROCHE_LD -> CRL &= ~(0x1 << (PORT_LD*4+2)); // on mets d'abord 0 sur le bit 3 de la broche
BROCHE_LD -> CRL |= (0x1 << (PORT_LD*4+1)); //on �crit 2 sur le bit 2 de la broche


//config de la led en opendrain
//BROCHE_LD_E -> CRL |= (0x1 << (PORT_LD_E*4+1)); // il sufft d'avoir 0110 sur le 5e port on ajoute juste 1 au bit 2


//config du bouton poussoir en floating input
BROCHE_BP -> CRH &= ~(0x1 << ((15- PORT_BP)*4)); // on �crit 4 sur le crh du bouton


do
{
	if ((BROCHE_BP -> IDR & (0x1 << PORT_BP))) // verifie si idr a re�u est modifi� (bouton appuy�)
	{
		BROCHE_LD -> ODR &= ~(0x1<< PORT_LD); // vient cocher sur le 5e bit allume la led
	} else {
		BROCHE_LD -> ODR |= (0x1<< PORT_LD); // vient d�cocher eteint la led
	}

} while(1);
*/
	//Test avec fonctions
	
	// Param�tres led
broche_led.GPIO = GPIOA;
broche_led.GPIO_Pin = 0x05;

//config de la led en push pull
broche_led.GPIO_Conf = Out_Ppull;


//config de la led en opendrain
//broche_led.GPIO_Conf = Out_OD;

MyGPIO_Init(&broche_led);


//config du bouton poussoir en floating input
broche_bp.GPIO = GPIOC;
broche_bp.GPIO_Pin = 0x0D;
broche_bp.GPIO_Conf = In_Floating;

MyGPIO_Init(&broche_bp);

do
{
	if ((MyGPIO_Read(broche_bp.GPIO, 0x0D)==1)) // verifie si idr a re�u est modifi� (bouton appuy�)
	{
		MyGPIO_Set(broche_led.GPIO, 0x05); // vient cocher sur le 5e bit allume la led
	} else {
		MyGPIO_Reset(broche_led.GPIO, 0x05); // vient d�cocher eteint la led
	}

} while(1);

}



