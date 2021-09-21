#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"

typedef struct{
TIM_TypeDef * timer ; // TIM1 � TIM4
unsigned short ARR;
unsigned short PSC;
} MyTimer_Struct_TypeDef ;
/*
*****************************************************************************************
* @brief
* @param -> Param�tre sous forme d � une structure ( son adresse ) contenant l e s
informations de base
* @Note -> Fonction � lancer syst �matiquement avant d � a l l e r plus en d� t a i l dans l e s
conf plus f i n e s (PWM, codeur inc . . . )
*************************************************************************************************
*/
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer );
#define MyTimer_Base_Start ( Timer ) ((Timer)->timer ->CR1 = (Timer).timer->CR1 | ( 1 << 0))
#define MyTimer_Base_Stop ( Timer ) (((Timer)->timer->SR & TIM_SR_UIF) ? (!0) : ((Timer)->timer->SR = ((Timer)->timer->SR & ~TIM_SR_UIF )
#endif
