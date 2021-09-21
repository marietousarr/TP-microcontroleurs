#include "MyTimer.h"

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ){
	Timer -> Timer -> ARR = Timer ->ARR;
	Timer -> Timer -> PSC = Timer ->PSC;
}
