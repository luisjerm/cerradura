#include "modulos.h"


void config_pwm2(void)
  {
		LPC_SC->PCONP|=(1<<6);//power on PWM
		LPC_PINCON->PINSEL7|=(3<<18); // P3.25  salida PWM (PWM1.2)
		LPC_PWM1->MR0=F_pclk*Tpwm-1;// valor MR0 para que salte en 15 ms ( el periodode la señal PWM)
		LPC_PWM1->PCR|=(1<<10); //configurado el ENA2 (PWM1.2)
		LPC_PWM1->MCR|=(1<<1);// resetea el PWMTC cuando el PWMMR0 sea alcanzado por este
		LPC_PWM1->TCR|=(1<<0)|(1<<3);// un bit en cero te permite habilitar TC y el bit en 3 habilita el modulo PWM
	}
	
void velocidad_ventilador(void)
	{
    LPC_PWM1->MR2=(F_pclk*1e-3 + F_pclk*9e-3*ciclos/100); // Tiempo en alta(TH)
		LPC_PWM1->LER|=(1<<2)|(1<<0); //esto permite que el valor de MR2 sea efectivo antes de que se produzca el reset
  }
