#include "modulos.h"


uint16_t muestras[N_muestras];			// Array para guardar las muestras de un ciclo de un seno
float voltios;

void genera_muestras(uint8_t muestras_ciclo) //  muestras_ciclo=N_muestras =32
{
	//uint8_t i;
	muestras[0]=0x1FF;
	muestras[1]=0x2C7;
	muestras[2]=0x386;
	muestras[3]=0x437;
	muestras[4]=0x4D2;
	muestras[5]=0x552;
	muestras[6]=0x5B0;
	muestras[7]=0x5EA;
	muestras[8]=0x5FE;
	muestras[9]=0x5EA;
	
	muestras[10]=0x5B0;
	muestras[11]=0x552;
	muestras[12]=0x4D2;
	muestras[13]=0x437;
	muestras[14]=0x386;
	muestras[15]=0x2C7;
	muestras[16]=0x1FF;
	muestras[17]=0x137;
	muestras[18]=0x078;
	muestras[19]=0x000;
	
	muestras[20]=0x000;
	muestras[21]=0x000;
	muestras[22]=0x000;
	muestras[23]=0x000;
	muestras[24]=0x000;
	muestras[25]=0x000;
	muestras[26]=0x000;
	muestras[27]=0x000;
	muestras[28]=0x000;
	muestras[29]=0x000;
	
	muestras[30]=0x078;
	muestras[31]=0x137;
	
	
	
	/*for(i=0;i<muestras_ciclo;i++)
		muestras[i]=1023*(0.5 + 1*sin(2*pi*i/muestras_ciclo)); // Ojo! el DAC es de 10bits => 2^10= 1024 ->(0...1023)*/
	
}

// Timer 2 interrumpe periódicamente a F = F_out x N_muestras !!!!
// La muestra correpondiente del array,  se saca al DAC en cada interrupción
void TIMER2_IRQHandler(void)
{
	static uint8_t indice_muestra;
	LPC_TIM2->IR|= (1<<0); 
	cont++;
	if(cont<=170000)
	{
		LPC_DAC->DACR= muestras[indice_muestra++] << 6; // ? 
		/* Este registro almacena el valor digital a convertir a analogico*/
		if(	indice_muestra==N_muestras)
			indice_muestra=0; 
	}
	else
		LPC_DAC->DACR=0<<6;
}	

void init_DAC(void)
{
	LPC_PINCON->PINSEL1|= (2<<20); 	 	// DAC output = P0.26 (AOUT)
	LPC_PINCON->PINMODE1|= (2<<20); 	// Deshabilita pullup/pulldown
	LPC_SC->PCLKSEL0|= (0x00<<22); 	 	// CCLK/4 (Fpclk después del reset) (100 Mhz/4 = 25Mhz)	
	LPC_DAC->DACCTRL=0;								//  
}

void init_TIMER2(void)
{
	  LPC_SC->PCONP|=(1<<22);						// 	habilita el timer 1
		//LPC_PINCON->PINSEL3|= (3<<12);
    LPC_TIM2->PR = 0x00;     	 				//  desahabilita el prescaler
    LPC_TIM2->MCR = 0x03;							// "11"->Reset TC on Match, and Interrupt!  
    LPC_TIM2->MR0 = (F_pclk/F_out/N_muestras)-1;  //  MR0=0x30C= 780 
    LPC_TIM2->EMR = 0xC1;   					// ¿Debería ser un 0x1 -> para EM0?, pero 0x0 no hacer nada
    LPC_TIM2->TCR = 0x01;							// habilita timer, contador
    NVIC_EnableIRQ(TIMER2_IRQn);			// habilita  IRQ
	  NVIC_SetPriority(TIMER2_IRQn,0);  // Asigna grupo de prioridad a la nt
}

void alarma(void)
{
	//NVIC_SetPriorityGrouping(2);
	genera_muestras(N_muestras);  // N_muestras=32
	cont=0;
	init_DAC();
	init_TIMER2();
	while(cont<=170000);
	
}




