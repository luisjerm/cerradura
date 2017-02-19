#include <LPC17xx.H>
#include "modulos.h"

#define Ftick 10				// SYSTICK desired frecuency interrupt (Hz)

//int timeOut;

void SysTick_Handler(void)	 // Se ejecuta periÛdicamente a Ftick (Hz)
{
	if (timeOut > 0) 
		timeOut--;
//	else if(timeOut == 0)
//		LPC_GPIO0->FIOCLR |=(1<<4);
}

void initTimer(void) 
{
		SysTick_Config(SystemCoreClock/Ftick); // Valor de RELOAD (N? de cuentas  del SYSTICK hasta llegar a cero)	
}

void setTimeOut(unsigned int value)
{
	timeOut = value;
}

unsigned int getTimeOut(void)
{
	return timeOut;
}

