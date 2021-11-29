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
* @param -> Param�tre sous forme d � une structure ( son adresse ) contenant les
informations de base
* @Note -> Fonction � lancer syst �matiquement avant d�aller plus en d�tail dans les
configurations plus fines (PWM, codeur inc . . . )
*************************************************************************************************
*/

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer );

#define MyTimer_Base_Start( Timer ) ((Timer).timer ->CR1 = (Timer).timer ->CR1 | ( 1 << 0))

#define MyTimer_Base_Stop( Timer ) (((Timer).timer-> SR & TIM_SR_UIF) ? (1) : (Timer).timer ->CR1 = (Timer).timer ->CR1 & ~( 1 << 0) )


/* ** @brief
* @param :-TIM_TypeDef*Timer  :   Timer concerne-char  Prio  :  de 0 a 15
*@Note   Cette fonction active une interruption au d�bordement de Timer et ex�cute la fonction IT_fonction. 
* La  fonction   MyTimer_Base_Init  doit  avoir  ete  lancee au prealable
***************************************************************************************************/
void MyTimer_ActiveIT(TIM_TypeDef* Timer ,char Prio, void (* IT_function) (void));

/* **@brief
*@param-> Param�tre sous forme d�une structure ( son adresse ) contenant les
informations de base sur le timer
*@Note    Active  le mode Encoder sur le timer sp�cifi� par la structure
*la  gestion  de  la  configuration I/O n�est pas  faite dans cette fonction*/
void MyTimer_EncoderMode( MyTimer_Struct_TypeDef * Timer );

/* **@brief
*@param -> une structure contenant les informations de base sur le timer associ� � la pwm et
*le channel sur laquelle la pwm sera �mise 
*@Note    Active  le mode pwm sur le timer sp�cifi� et acitve le  channel sp�cifi� sur ce dernier
*la  gestion  de  la  configuration I/O n�est pas  faite dans cette fonction
*ni  le  r�glage de la p�riode de la PWM (ARR, PSC)*/
void MyTimer_PWM(TIM_TypeDef* Timer ,char Channel );

/* **@brief
*@param  -> une structure contenant les informations sur le timer associ�, 
* le ration de la pwm � mettre en oeuvre et le channel sur lequel la pwm sera �mise
*@Note   Communique au timer le ration de la pwm � �metrre*/
void PWMRatio(TIM_TypeDef* Timer ,float ration, char Channel);

/* **@brief
*@Note   Cette fonction initialise une external interupt servant � remettre � 0 le compteur du Timer 
*en Encoder mode*/
void init_EXIT(void);

#endif
