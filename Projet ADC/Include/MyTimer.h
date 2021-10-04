#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"

typedef struct
{
TIM_TypeDef * timer ; // TIM1 � TIM4
unsigned short ARR;
unsigned short PSC;
} MyTimer_Struct_TypeDef;

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

#define MyTimer_Base_Start( Timer ) ((Timer).timer ->CR1 = (Timer).timer ->CR1 | ( 1 << 0))

#define MyTimer_Base_Stop( Timer ) (((Timer).timer-> SR & TIM_SR_UIF) ? (1) : (Timer).timer ->CR1 = (Timer).timer ->CR1 & ~( 1 << 0) )

/***************************************************************************************************
* @brief
* @param :-TIM_TypeDef*Timer  :   Timer concerne-char  Prio  :  de 0 a 15
* @Note :   La  fonction   MyTimer_Base_Init  doit  avoir  ete  lancee au prealable
***************************************************************************************************/

void MyTimer_ActiveIT(TIM_TypeDef* Timer ,char Prio, void (* IT_function) (void));

/* **@brief
*@param   . . . .
*@Note    Active  le  channel sp� c i f i � suTimerr  le  timer  sp� c i f i �
*la  gestion  de  la  configuration   I /O n � est  pas  f a i t e  dans  cette  fonction
*ni  le  r � glage de  la p� riode de  la PWM (ARR, PSC)*/
void MyTimer_PWM(TIM_TypeDef* Timer ,char Channel ) ;

void PWMRatio(TIM_TypeDef* Timer ,int ration, char Channel);

#endif
