#include "modulos.h"

/*-------------------------Sistema de Seguridada Variables globales------------------------------------------*/
int detectado=0;
void init_TIMER1(void)
{
	  LPC_SC->PCONP|=(1<<2);						// power on TIMER1
    LPC_TIM1->MCR = 0x03;							// Reset TC on Match, and Interrupt!  
    LPC_TIM1->MR0 = F_pclk/5-1;  			// queremos que interrumpa en 500ms(2HZ)
    LPC_TIM1->TCR = 0x01;							// habilitamos contador
    NVIC_EnableIRQ(TIMER1_IRQn);			// habilitamos función de interrupción TIMER1
	 // NVIC_SetPriority(TIMER1_IRQn,2);    
}

void Config(void)
{
	teclado[0][0]='D';//D 1.25-2.10-2.11-2.12-1.31-4.28-4.29-0.28 (cableado de D al *)
	teclado[0][1]='C';//C
	teclado[0][2]='B';//B
	teclado[0][3]='A';//A
	teclado[1][0]='#';//#
	teclado[1][1]='9';//9
	teclado[1][2]='6';//6
	teclado[1][3]='3';//3
	teclado[2][0]='0';//0
	teclado[2][1]='8';//8
	teclado[2][2]='5';//5
	teclado[2][3]='2';//2
	teclado[3][0]='*';//*
	teclado[3][1]='7';//7
	teclado[3][2]='4';//4
	teclado[3][3]='1';//1
	
}

void TIMER1_IRQHandler(void)
{
	LPC_TIM1->IR|= (1<<0); 						// borramos flag MR0

	// Comprobamos si se producido un 0 en alguna de los otros 4 pines de las columnas

	LPC_GPIO0->FIOCLR = (1<<5);	 // pone un 0 en fila 1
	LPC_GPIO2->FIOSET = (1<<10);	 // pone un 1 en fila 2
	LPC_GPIO2->FIOSET = (1<<11);	 // pone un 1 en fila 3
	LPC_GPIO2->FIOSET = (1<<12);	 // pone un 1 en fila 4
	i=1;
	
	if((LPC_GPIO1->FIOPIN & (1<<31))==0)	// si se ha producido un 0 en la columna 1?
	{
		j=1;		// indice de las columnas a 1
		detectado=1;
	}
	if((LPC_GPIO4->FIOPIN & (1<<28))==0)	// si se ha producido un 0 en la columna 2?
	{
		j=2;		// indice de las columnas a 2
	  detectado=1;
}
	if((LPC_GPIO4->FIOPIN & (1<<29))==0)	// si se ha producido un 0 en la columna 3?
	{
		j=3;		// indice de las columnas a 3
		detectado=1;
	}
	if((LPC_GPIO0->FIOPIN & (1<<28))==0)	// si se ha producido un 0 en la columna 4?
	{
		j=4;		// indice de las columnas a 4
	  detectado=1;
 }
	
	if(detectado==0){
		LPC_GPIO0->FIOSET = (1<<5);	 // pone un 0 en fila 1
		LPC_GPIO2->FIOCLR = (1<<10);	 // pone un 1 en fila 2
		LPC_GPIO2->FIOSET = (1<<11);	 // pone un 1 en fila 3
		LPC_GPIO2->FIOSET = (1<<12);	 // pone un 1 en fila 4
		i=2;
	
	if((LPC_GPIO1->FIOPIN & (1<<31))==0)	// si se ha producido un 0 en la columna 1?
	{
		j=1;		// indice de las columnas a 1
		detectado=1;
	}
	if((LPC_GPIO4->FIOPIN & (1<<28))==0)	// si se ha producido un 0 en la columna 2?
	{
		j=2;		// indice de las columnas a 2
	  detectado=1;
}
	if((LPC_GPIO4->FIOPIN & (1<<29))==0)	// si se ha producido un 0 en la columna 3?
	{
		j=3;		// indice de las columnas a 3
		detectado=1;
	}
	if((LPC_GPIO0->FIOPIN & (1<<28))==0)	// si se ha producido un 0 en la columna 4?
	{
		j=4;		// indice de las columnas a 4
	  detectado=1;
 }
 }
	if(detectado==0){
		LPC_GPIO0->FIOSET = (1<<5);	 // pone un 0 en fila 1
		LPC_GPIO2->FIOSET = (1<<10);	 // pone un 1 en fila 2
		LPC_GPIO2->FIOCLR = (1<<11);	 // pone un 1 en fila 3
	  LPC_GPIO2->FIOSET = (1<<12);	 // pone un 1 en fila 4
		i=3;
	
	
	if((LPC_GPIO1->FIOPIN & (1<<31))==0)	// si se ha producido un 0 en la columna 1?
	{
		j=1;		// indice de las columnas a 1
		detectado=1;
	}
	if((LPC_GPIO4->FIOPIN & (1<<28))==0)	// si se ha producido un 0 en la columna 2?
	{
		j=2;		// indice de las columnas a 2
	  detectado=1;
}
	if((LPC_GPIO4->FIOPIN & (1<<29))==0)	// si se ha producido un 0 en la columna 3?
	{
		j=3;		// indice de las columnas a 3
		detectado=1;
	}
	if((LPC_GPIO0->FIOPIN & (1<<28))==0)	// si se ha producido un 0 en la columna 4?
	{
		j=4;		// indice de las columnas a 4
	  detectado=1;
 }
	}
 if(detectado==0){
		LPC_GPIO0->FIOSET = (1<<5);	 // pone un 1 en fila 1
		LPC_GPIO2->FIOSET = (1<<10);	 // pone un 1 en fila 2
		LPC_GPIO2->FIOSET = (1<<11);	 // pone un 1 en fila 3
		LPC_GPIO2->FIOCLR = (1<<12);	 // pone un 0 en fila 4
		i=4;
 
	
	if((LPC_GPIO1->FIOPIN & (1<<31))==0)	// si se ha producido un 0 en la columna 1?
	{
		j=1;		// indice de las columnas a 1
		detectado=1;
	}
	if((LPC_GPIO4->FIOPIN & (1<<28))==0)	// si se ha producido un 0 en la columna 2?
	{
		j=2;		// indice de las columnas a 2
	  detectado=1;
}
	if((LPC_GPIO4->FIOPIN & (1<<29))==0)	// si se ha producido un 0 en la columna 3?
	{
		j=3;		// indice de las columnas a 3
		detectado=1;
	}
	if((LPC_GPIO0->FIOPIN & (1<<28))==0)	// si se ha producido un 0 en la columna 4?
	{
		j=4;		// indice de las columnas a 4
	  detectado=1;
 }
	}
	//j=3;
	detectado=0;
	y=0; // para indicar k se  a producido la EINT2
	estado++;// cambiamos de estado                          
	LPC_TIM1->TC  = 0x00;
	LPC_TIM1->TCR = 0x01;							// habilitamos contador
	
}	

char tecladoM(void)
{
	init_TIMER1();
	i=0;
	j=0;
	LPC_GPIO0->FIODIR|=(1<<5); // pone un 1 en fila 1 -> lo cambiamos pr el 0.05 antes estaba el 1.25(utilizado por la sd)
	LPC_GPIO2->FIODIR|=(1<<10); // pone un 1 en fila 2
	LPC_GPIO2->FIODIR|=(1<<11); // pone un 1 en fila 3
	LPC_GPIO2->FIODIR|=(1<<12); // pone un 1 en fila 4
	// Ponemos los 1's en los 4 pines de las filas:
	LPC_GPIO1->FIOPIN|=(1<<31); // pone un 1 en fila 1
	LPC_GPIO4->FIOPIN|=(1<<28); // pone un 1 en fila 2
	LPC_GPIO4->FIOPIN|=(1<<29); // pone un 1 en fila 3
	LPC_GPIO0->FIOPIN|=(1<<28); // pone un 1 en fila 4
	
	NVIC_SetPriority(TIMER1_IRQn,4);
	//NVIC_SetPriority(TIMER1_IRQn,1);   //      
  NVIC_EnableIRQ(TIMER1_IRQn);       //     
  //NVIC_SetPriorityGrouping(2);				//
	NVIC_SetPriorityGrouping(4);
	
	/*
			Configuración del timer utlizado, y de los pines...
			se podría hacer llamando a una funcion Conf();
	*/

	Config();
	estado=1;
	y=1;
	while(1)
	{
		
	if (zonePressed(&zone_6))//<-----------
	{			
            screenState = SCREEN_MAIN;		// acceso teclado
						LPC_SC->PCONP|=(0<<2);
		break;
  }
	
		if((y==0) &&(i!=0)&&(j!=0))
		{
				tecla=teclado[i-1][j-1];  // La tecla pulsada es.... 
				// restauramos los indices a 0, e y a 1 (no se ha producido la interrupción)
				y=1;
				//i=0;
				//j=0;
			return tecla;
		}
	}// fin del while

}
