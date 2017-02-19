#include "modulos.h"
#define SCREEN_ALARMA								15


void ADC_IRQHandler(void)
{
		
	if(((LPC_ADC->ADSTAT>>2) & 0x01)==1)//canal2	
	{
		voltiostemp= (((LPC_ADC->ADDR2 >>4)&0xFFF)*V_refp/4095)*1000;
		temperatura=voltiostemp/10;
		pantalla_sensores();
		if(temperatura > 16)
		{
			config_pwm2();
			velocidad_ventilador();
			pantalla_ventilador();
		}
		else
		{
			//LPC_SC->PCONP&=~(1<<6);//power off PWM
			pantalla_sensores();
			pantalla_distancia_2();
			
		}
	}
	
	if(((LPC_ADC->ADSTAT>>0) & 0x01)==1)//canal0
	{
		voltiospoten= ((LPC_ADC->ADDR0 >>4)&0xFFF)*3.3/4095;
		ciclos=(voltiospoten*100)/3.3;	
	}

	if(((LPC_ADC->ADSTAT>>1) & 0x01)==1)//canal1
	{
		voltiosdist= ((LPC_ADC->ADDR1 >>4)&0xFFF)*V_refp/4095;
		if(voltiosdist>2)
		{
			pantalla_distancia_1();
			//screenState = SCREEN_ALARMA;
			//alarma();
		}
		else
		{
			GUI_Text(30,150,"                 ",White,Black);
			pantalla_sensores();
			pantalla_distancia_2();
			
		}		
	}

}


void init_ADC(void)
{	
	LPC_SC->PCONP|= (1<<12);					// POwer ON
	LPC_PINCON->PINSEL1|= (1<<14)|(1<<18);  	// ADC input= P0.23 (AD0.0) p0.25 (ad0.2)
	LPC_PINCON->PINSEL1|= (1<<16);						// ADC input= P1.30 (AD0.4)
	LPC_PINCON->PINMODE1|= (2<<14)|(2<<18); 	// Deshabilita pullup/pulldown
	LPC_PINCON->PINMODE1|= (2<<16);						// Deshabilita pullup/pulldown
	LPC_SC->PCLKSEL0|= (0x00<<8); 		// CCLK/4 (Fpclk después del reset) (100 Mhz/4 = 25Mhz)
	LPC_ADC->ADCR =(0x01<<0)|				// canal 0
								 (0x01<<2)|	  	  // Canal 2
								 (0x01<<1)|	  	  // Canal 4
								 (0x01<<8)|					// CLKDIV=1   (Fclk_ADC=25Mhz /(1+1)= 12.5Mhz)
								 (0x01<<21)|			 	// PDN=1
								 (4<<24);				    // Inicio de conversión con el Match 1 del Timer 0
	
	LPC_ADC->ADINTEN= (1<<0)|(1<<2)|(1<<1)|(1<<8);	// Hab. interrupción fin de conversión canal 0 (DONE canal 0 + DONE global)
	NVIC_EnableIRQ(ADC_IRQn);					//  
	NVIC_SetPriority(ADC_IRQn,2);			//         
}	

						
void init_TIMER0(void)
{
	  LPC_SC->PCONP|=(1<<1);						// 
	  //LPC_PINCON->PINSEL3|= 0x0C000000; // P1.29 en modo MATCH   
    LPC_TIM0->MCR = 0x10;   					//   
    LPC_TIM0->MR1 = (F_pclk/F_muestreo/2)-1; // Se han de producir DOS Match para iniciar la conversión!!!!   
    LPC_TIM0->EMR = 0x00C2;   				// activamos modo toggle
    LPC_TIM0->TCR = 0x01;     				//  
}	

