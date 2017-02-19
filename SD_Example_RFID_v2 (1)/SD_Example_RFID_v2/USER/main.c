/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.depeca.uah.es
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            SD Card Example Program
**
**--------------------------------------------------------------------------------------------------------
** Created by:              JP
** Created date:            2016-10-09
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "GLCD.h"
#include "TouchPanel.h"
#include "menu.h"
//#include <RTL.h>                      /* RTL kernel functions & defines      */
#include "File_Config.h"
#include "timer.h"
#include "rtc.h"
#include "MFRC522.h"
#include "SD_Functions.h"

#include "modulos.h"
#include "uart.h"


//VARIABLES
float voltiospoten;
int ciclos;//ciclos PWM ventilador
float voltiostemp;
float voltiosdist;
float temperatura;
int i, j,st, x=1, b=1;					// indices para moverte por la matriz
char teclado[FILAS][COLUMNAS];/*={{"1", "2", "3","A"},						// matriz de con las teclas de l teclado
																	{"4", "5", "6","B"},
																	{"7", "8", "9", "C"},
																	{"#", "0", "*", "D"}};*/
int y=1;	 //	   y=0 si se a producido la EINT2 
					//     y=1 si NO se a producido la EINT2
int estado; // var que nos dice en que estado estamos
char tecla; // variable con la resolución de la tecla pulsada
char valores [30];
char pass[7];
char pass_admin[7]="1111111";
int cont=0;
uint8_t sd_init;
int timeOut;


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{ 
	LCD_Initializtion();	
	
	TP_Init(); 
	TouchPanel_Calibrate();

  initTimer(); 		//Systick
	init_RTC();
  MFRC522_init ();
	sd_init = sdInit();
	
	config_pwm2();
  LPC_GPIO0->FIODIR|=(1<<4); // PIN 0.4 PARA EL RELE DECLARADO COMO SALIDA
  LPC_GPIO0->FIOCLR|=(1<<4); // INICIALMENTE CERRADO
	
	initScreenStateMachine();
	
	while (1)	
	{
		screenStateMachine();

	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
