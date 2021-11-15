#ifndef DRIVER_SERVOMOTEUR_H
#define DRIVER_SERVOMOTEUR_H
#include "stm32f10x.h"
#include "Timer.h"

/* **@brief
*@param -> addresse du timer associ� � la pwm et l'angle des voiles � communiquer au servomoteur
*@Note -> Communique au servomoteur l'angle des voiles en �mettant une pwm avec le ratio correspondant*/
void update_angle_servomoteur(TIM_TypeDef * timer, int teta);

#endif
