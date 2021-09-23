#ifndef MYTIMER_H
#define MYTIMER_H

#include <stdio.h>
#include "stm32f10x.h"

typedef struct
{
TIM_TypeDef * timer ; // TIM1 à TIM4
unsigned short ARR;
unsigned short PSC;
} MyTimer_Struct_TypeDef ;
/*
*****************************************************************************************
* @brief
* @param -> Paramètre sous forme d ’ une structure ( son adresse ) contenant l e s
informations de base
* @Note -> Fonction à lancer syst ématiquement avant d ’ a l l e r plus en dé t a i l dans l e s
conf plus f i n e s (PWM, codeur inc . . . )
*************************************************************************************************
*/
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer );
#define MyTimer_Base_Start ( Timer ) ((Timer) -> timer ->CR1 = (Timer)->CR1 | ( 1 << 0))
#define MyTimer_Base_Stop ( Timer ) (((Timer) -> timer->SR & TIM_SR_UIF) ? (!0) : TIM2->SR = TIM2->SR & ~TIM_SR_UIF )
#endif
