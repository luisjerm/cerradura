
/* Includes ------------------------------------------------------------------*/
#include "GLCD.h"
#include "TouchPanel.h"
#include <string.h>
#include "SD_Functions.h"
#include "timer.h"
#include <stdio.h>
#include "rtc.h"
#include "RFID.h"

//
#include "modulos.h"

#include "uart.h"
//


//#define OFF_ALL											25

//

uint8_t screenState;   


unsigned int readed_id_card;
unsigned int sd_load;
unsigned int sd_log;
unsigned int idCard;
//unsigned int timeOut;

char buffer_aux[50];

struct t_screenZone
{
   uint16_t x;         
	 uint16_t y;
	 uint16_t size_x;
	 uint16_t size_y;
	 uint8_t  oldpressed;
};

uint8_t led_1 = 0;
uint8_t led_2 = 0;

struct t_screenZone zone_0 = { 20,  20, 200, 110, 0};		
struct t_screenZone zone_1 = { 20,  20, 200,  50, 0};		// acceso teclado matricial
struct t_screenZone zone_2 = { 20,  80, 200,  50, 0};		// acceso tarjeta RFID
struct t_screenZone zone_3 = { 20, 140, 200,  50, 0};		// acceso wifi
struct t_screenZone zone_sensores = { 20, 200, 200,  50, 0}; // sensores del sistema
struct t_screenZone zone_4 = { 20, 260, 200,  50, 0};
struct t_screenZone zone_5 = {20,   80, 200, 170, 0};
struct t_screenZone zone_6 = { 20, 260, 90,  50, 0};
struct t_screenZone zone_7 = { 120, 260, 90,  50, 0};

struct t_screenZone zone_TARJETA = { 20, 260, 90,  50, 0};

void square(uint16_t x, uint16_t y, uint16_t size_x, uint16_t size_y, uint16_t lineColor)
{
   LCD_DrawLine( x, y, x + size_x, y, lineColor);
   LCD_DrawLine( x, y, x, y + size_y, lineColor);
   LCD_DrawLine( x, y + size_y, x + size_x, y + size_y, lineColor);
   LCD_DrawLine( x + size_x, y, x + size_x, y + size_y, lineColor);
}

void squareButton(uint16_t x, uint16_t y, uint16_t size_x, uint16_t size_y, char * text, uint16_t textColor, uint16_t lineColor)
{
   LCD_DrawLine( x, y, x + size_x, y, lineColor);
   LCD_DrawLine( x, y, x, y + size_y, lineColor);
   LCD_DrawLine( x, y + size_y, x + size_x, y + size_y, lineColor);
   LCD_DrawLine( x + size_x, y, x + size_x, y + size_y, lineColor);
	GUI_Text(x + size_x/2 - (strlen(text)/2)*8, y + size_y/2 - 8, (uint8_t*) text, textColor, Black);
	
}

void fillRect(struct t_screenZone* zone, uint16_t color)
{
	uint16_t i;
	
	for (i = zone->y+1; i < zone->y + zone->size_y-1; i ++) {
		LCD_DrawLine(zone->x + 1, i, zone->x + zone->size_x -1, i, color);
	}
}


void screenMain()
{
   char buffer[40];
	
   sprintf(buffer,"Hora: %02d:%02d:%02d", RTC_GetTime(LPC_RTC, RTC_TIMETYPE_HOUR),
	                                       RTC_GetTime(LPC_RTC, RTC_TIMETYPE_MINUTE),
                                          RTC_GetTime(LPC_RTC, RTC_TIMETYPE_SECOND));
	
	 squareButton(zone_1.x, zone_1.y, zone_1.size_x, zone_1.size_y, "Acc. por teclado", White, Blue);
   squareButton(zone_2.x, zone_2.y, zone_2.size_x, zone_2.size_y, "Acc. por tarjeta ", White, Blue);
   squareButton(zone_3.x, zone_3.y, zone_3.size_x, zone_3.size_y, "Acc. por wifi", White, Blue);
	 squareButton(zone_sensores.x, zone_sensores.y, zone_sensores.size_x, zone_sensores.size_y, "Estado del sistema", White, Blue);
	/*
   squareButton(zone_1.x, zone_1.y, zone_1.size_x, zone_1.size_y, buffer, White, Blue);
   squareButton(zone_2.x, zone_2.y, zone_2.size_x, zone_2.size_y, "Registra Hora", White, Blue);
   squareButton(zone_3.x, zone_3.y, zone_3.size_x, zone_3.size_y, "Visualiza Registro", White, Blue);
	*/
}

void screenTarjeta()
{
   char buffer[40];
	
   sprintf(buffer,"Hora: %02d:%02d:%02d", RTC_GetTime(LPC_RTC, RTC_TIMETYPE_HOUR),
	                                       RTC_GetTime(LPC_RTC, RTC_TIMETYPE_MINUTE),
                                          RTC_GetTime(LPC_RTC, RTC_TIMETYPE_SECOND));
	
   squareButton(zone_1.x, zone_1.y, zone_1.size_x, zone_1.size_y, buffer, White, Blue);
   squareButton(zone_2.x, zone_2.y, zone_2.size_x, zone_2.size_y, "Add usuario", White, Blue);
   squareButton(zone_3.x, zone_3.y, zone_3.size_x, zone_3.size_y, "Visualiza usuario", White, Blue);
	 squareButton(zone_6.x, zone_6.y, zone_6.size_x, zone_6.size_y, "Volver", White, Blue);			

}


void screenMainUpdate()
{
   char buffer[40];
	
   sprintf(buffer,"Hora: %02d:%02d:%02d", RTC_GetTime(LPC_RTC, RTC_TIMETYPE_HOUR),
	                                       RTC_GetTime(LPC_RTC, RTC_TIMETYPE_MINUTE),
                                          RTC_GetTime(LPC_RTC, RTC_TIMETYPE_SECOND));
   squareButton(zone_1.x, zone_1.y, zone_1.size_x, zone_1.size_y, buffer, White, Blue);
}


void screenErrorRegister()
{
  	squareButton(zone_4.x, zone_4.y, zone_4.size_x, zone_4.size_y, "ERROR No se ha podido guardar", White, Red);
}

void screenRegistered()
{
  	squareButton(zone_4.x, zone_4.y, zone_4.size_x, zone_4.size_y, "Dato guardado con exito", White, Green);
}

void screenData()					// Visualiza el contenido de la las tarjetas RFID de la SD
{
   FILE* f_visu;
   int y;
   char text[20];
   
  	squareButton(zone_1.x, zone_1.y, zone_1.size_x, zone_1.size_y, "Datos leidos", White, Blue);
  	squareButton(zone_5.x, zone_5.y, zone_5.size_x, zone_5.size_y, " ", White, Blue);
  	squareButton(zone_6.x, zone_6.y, zone_6.size_x, zone_6.size_y, "Volver", White, Blue);
  	squareButton(zone_7.x, zone_7.y, zone_7.size_x, zone_7.size_y, "Borrar", White, Red);


  f_visu = fopen (fileName,"r");                      /* Open a file from default drive. */
  
  if (f_visu != NULL)  
	{
    for (y=zone_5.y + 2; y < zone_5.y + zone_5.size_y -16; y+=16) {
         if (fscanf(f_visu,"%s\n",text) == EOF)
				 {
            break;
         } 
         GUI_Text(zone_5.x+2, y, (uint8_t*) text, White, Black);         
      }
      fclose (f_visu);
  }
}


int8_t taz_o_NO_taz(void)
{
	 FILE* f_read;
   int y;
   unsigned int card_sd;
	 char text[20];
	
	f_read = fopen (fileName,"r");                      /* Open a file from default drive. */
  
  if (f_read != NULL)  
	{
    while (!feof(f_read)) 
			{
        fscanf(f_read,"%X\n",&card_sd);
				//card_sd=atoi(text);
        if(sd_log==card_sd)
				{
					fclose (f_read);
					return 1;	
				}
                   
      }
      fclose (f_read);
  }
		
 /*
	 if (f = fopen (fileName,"r"))
   {       // ORIGINAL: if (f = fopen (fileName,"r")) // HEMOS PUESTO ==
      while (!feof(f))
			{
       if (fscanf(f,"%X\n",&card_sd) == EOF)
				 {
            if(idCard==card_sd)
						{
							fclose (f);
							return 1;
							
						}
         }  
      }
      fclose (f);
   }*/
	
	return 0;
}


void screenDataError()
{
  	squareButton(zone_4.x, zone_4.y, zone_4.size_x, zone_4.size_y, "Dato guardado con exito", White, Green);
}

void screenErrorNoSD()
{
   squareButton(zone_4.x, zone_4.y, zone_4.size_x, zone_4.size_y, "ERROR No SD", White, Red);
}

int8_t zonePressed(struct t_screenZone* zone)
{
   Coordinate* coord;
	
	coord = Read_Ads7846();
	
	if (coord > 0) {
		getDisplayPoint(&display, coord, &matrix );

		if ((display.x > zone->x) && (display.x < zone->x + zone->size_x) && 
			  (display.y > zone->y) && (display.y < zone->y + zone->size_y))
      return 1;
	}
	
	return 0;
}




void screen_Add_RFID(void)
{
		squareButton(zone_TARJETA.x, zone_TARJETA.y, zone_TARJETA.size_x, zone_TARJETA.size_y, "Volver", White, Blue);
		squareButton(zone_2.x, zone_2.y, zone_2.size_x, zone_2.size_y, "Registrar", White, Blue);
}

/*void WDT_Feed(void)
{
	LPC_WDT->WDFEED=0xAA;
LPC_WDT->WDFEED=0x55;

}*/
void init_WDT(void)
{
	LPC_WDT->WDTC=F_wdclk*0.5; // Timeout=2seg.
	LPC_WDT->WDCLKSEL=0x01;  // Clock=PCLK
	LPC_WDT->WDMOD=0x03;		// Enable y Reset	if Timeout
  LPC_WDT->WDFEED=0xAA;
  LPC_WDT->WDFEED=0x55;
}

void 	initScreenStateMachine(void)
{
	screenState = SCREEN_MAIN;
}
/*
void pantalla_ini (void)
{
	LCD_DrawLine( 20, 20, 220, 20, 0x001F);	// recta de arriba, se hace uniendo dos puntos (x0,y0) y (x1, y1)
	LCD_DrawLine( 220, 20, 220, 60, 0x001F);// recta de la derecha
	LCD_DrawLine( 20, 60, 220, 60, 0x001F);// recta de abajo
	LCD_DrawLine( 20, 20, 20, 60, 0x001F);	// recta de la izquierda
	GUI_Text(30, 30,"TECLADO MATRICIAl" ,0xFFFF, 0x001F); // el texto esta en la posicion (x, y)=(30,30)
	
	LCD_DrawLine( 20, 100, 220, 100, 0x001F);
	LCD_DrawLine( 220, 100, 220, 140, 0x001F);
	LCD_DrawLine( 20, 140, 220, 140, 0x001F);
	LCD_DrawLine( 20, 100, 20, 140, 0x001F);
	GUI_Text(30, 110,"MODULO RFID",0xFFFF, 0x001F);
	//GUI_Text(80, 110,"MODULO RFID",0xFFFF, 0x001F);
	
	LCD_DrawLine( 20, 180, 220, 180, 0x001F);
	LCD_DrawLine( 220, 180, 220, 220, 0x001F);
	LCD_DrawLine( 20, 220, 220, 220, 0x001F);
	LCD_DrawLine( 20, 180, 20, 220, 0x001F);
	GUI_Text(60, 190,"WIFI",0xFFFF, 0x001F);
	
	LCD_DrawLine( 20, 260, 220, 260, 0x001F);
	LCD_DrawLine( 220, 260, 220, 300, 0x001F);
	LCD_DrawLine( 20, 300, 220, 300, 0x001F);
	LCD_DrawLine( 20, 260, 20, 300, 0x001F);
	GUI_Text(80, 270,"SENSORES",0xFFFF, 0x001F);
	
}

void teclado_matricial (void)
{
	LCD_DrawLine( 20, 20, 220, 20, 0x001F);
	LCD_DrawLine( 220, 20, 220, 60, 0x001F);
	LCD_DrawLine( 20, 60, 220, 60, 0x001F);
	LCD_DrawLine( 20, 20, 20, 60, 0x001F);
	GUI_Text(80, 30,(uint8_t*)"TECLADO MATRICIAL" ,0xFFFF, 0x001F);
}

void RFID (void)
{
	LCD_DrawLine( 20, 100, 220, 100, 0x001F);
	LCD_DrawLine( 220, 100, 220, 140, 0x001F);
	LCD_DrawLine( 20, 140, 220, 140, 0x001F);
	LCD_DrawLine( 20, 100, 20, 140, 0x001F);
	GUI_Text(80, 110,(uint8_t*)"RFID",0xFFFF, 0x001F);
}

void WIFI (void)
{
	LCD_DrawLine( 20, 180, 220, 180, 0x001F);
	LCD_DrawLine( 220, 180, 220, 220, 0x001F);
	LCD_DrawLine( 20, 220, 220, 220, 0x001F);
	LCD_DrawLine( 20, 180, 20, 220, 0x001F);
	GUI_Text(60, 190,(uint8_t*)"WIFI",0xFFFF, 0x001F);
}

void pantalla_password(void)
{
	
	GUI_Text(40,60,"Password:",0x0000,White);
	if (zonePressed(&zone_6))
	{			
            screenState = SCREEN_MAIN;		// acceso teclado
  }
	tecla=tecladoM();
	pass[0]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(40,90,(uint8_t*)valores,0x0000,White);
	if (zonePressed(&zone_6))
	{			
            screenState = SCREEN_MAIN;		// acceso teclado
  }
	tecla=tecladoM();
	pass[1]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(50,90,(uint8_t*)valores,0x0000,White);
	if (zonePressed(&zone_6))
	{			
            screenState = SCREEN_MAIN;		// acceso teclado
  }
	tecla=tecladoM();
	pass[2]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(60,90,(uint8_t*)valores,0x0000,White);
	if (zonePressed(&zone_6))
	{			
            screenState = SCREEN_MAIN;		// acceso teclado
  }
	tecla=tecladoM();
	pass[3]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(70,90,(uint8_t*)valores,0x0000,White);
	if (zonePressed(&zone_6))
	{			
            screenState = SCREEN_MAIN;		// acceso teclado
  }
	tecla=tecladoM();
	pass[4]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(80,90,(uint8_t*)valores,0x0000,White);
	if (zonePressed(&zone_6))
	{			
            screenState = SCREEN_MAIN;		// acceso teclado
  }
	tecla=tecladoM();
	pass[5]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(90,90,(uint8_t*)valores,0x0000,White);
	if (zonePressed(&zone_6))
	{			
            screenState = SCREEN_MAIN;		// acceso teclado
  }
	tecla=tecladoM();
	pass[6]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(100,90,(uint8_t*)valores,0x0000,White);
	
}


void pantalla_password_wifi(void)
{
	GUI_Text(60,160,(uint8_t*)"Accediendo mediante interfaz web" ,0xffff,Blue);
	//DrawRectangulo(165,265, 65, 35, Black);
	GUI_Text(190,275,(uint8_t*)"OK",0xffff,Black);
}


void pantalla_tempe(void)
{
		sprintf(valores,"%c",tecla);
		GUI_Text(60,160,(uint8_t*)"Por favor accecar la llave RFID" ,0xffff,Blue); 
}
void pantalla_RFID(void)
{
	GUI_Text(60,160,(uint8_t*)"Por favor accecar la llave RFID" ,0xffff,Blue); 
	
	// Llamar a la funcion de RFID
	
	
}
void boton_atras (void)
{

	LCD_DrawLine( 20, 260, 220, 260, Blue);
	LCD_DrawLine( 220, 260, 220, 300, Blue);
	LCD_DrawLine( 20, 300, 220, 300, Blue);
	LCD_DrawLine( 20, 260, 20, 300, Blue);
	GUI_Text(80, 270,(uint8_t*)"ATRAS",White, Black);
}


void pantalla_pss_ok(void)
{
	GUI_Text(80,120,"OK! abriendo!",White,Black);
}

void pantalla_pss_bad_1(void)
{
	GUI_Text(80,120,"Intentos fallidos: 1/3",White,Black);
}

void pantalla_pss_bad_2(void)
{
	GUI_Text(80,140,"Intentos fallidos: 2/3",White,Black);
}

void pantalla_pss_bad_3(void)
{
	GUI_Text(80,160,"Intentos fallidos: 3/3",White,Black);
}

void pantalla_alarma(void)
{
	GUI_Text(80,180,"Alarma! Intruso!",White,Black);
}

void pantalla_sensores(void)
{
	GUI_Text(30,30,"Tempt(ºC):",White,Black);
	
	sprintf(valores,"%lf",temperatura);
	GUI_Text(130,30,(uint8_t*)valores,White,Black);
}
void pantalla_ventilador(void)
{
	GUI_Text(30,90,"Ciclos:",White,White);
	
	sprintf(valores,"%d",ciclos);
	GUI_Text(130,90,(uint8_t*)valores,White,Black);
}

void pantalla_distancia_1(void)
{
	GUI_Text(30,120,"Dist(V):",White,Black);
	sprintf(valores,"%lf",voltiosdist);
	GUI_Text(130,120,(uint8_t*)valores,White,Black);
	
	GUI_Text(30,150,"FUS FUS!!",White,Black);
}

void pantalla_distancia_2(void)
{
	GUI_Text(30,120,"Dist(V):",White,Black);
	sprintf(valores,"%lf",voltiosdist);
	GUI_Text(130,120,(uint8_t*)valores,White,Black);
	
}
*/


void screenStateMachine(void)
{ 
  uint8_t error;
	
	uint8_t sd=1;
	uint16_t intentos=0;
	
  int key1= 0x360EF245;		// tarjeta
	//LPC_GPIO0->FIODIR|=(1<<4); // pone un 1 en fila 1
	//LPC_GPIO0->FIOCLR |=(1<<4); // pone un 1 en el relé (abrimos el relé)
		
   switch (screenState)
	{
      case SCREEN_INIT_SD:
         LCD_Clear(Black);
			   //MFRC522_init ();
//				if(sd_init==0){
//					while(sd==1){
						sd = sdInit();
//						intentos++;
//					}
					 if (sd!= 0) {
							screenState = SCREEN_ERROR_NO_SD;
							//sd_init=1;
					 } 
					 else {  
								screenState = SCREEN_TARJETA;               
							//sd_init=1;
					 }           
//				 }	
//					else
//						screenState = SCREEN_TARJETA;
			break;

      case SCREEN_ERROR_NO_SD:
         screenErrorNoSD();
         if (zonePressed(&zone_4)) {
            screenState = SCREEN_MAIN;               
         }               

       
       break;
            
      case SCREEN_MAIN:
         LCD_Clear(Black);
         screenMain();
         screenState = SCREEN_MAIN_WAIT;
         break;
			 
      case SCREEN_MAIN_WAIT:
				
				if (zonePressed(&zone_1))
				 {			
            screenState = SCREEN_TECLADOM;		// acceso teclado
         }	 
				 if (zonePressed(&zone_2))
				 {			
					 screenState = SCREEN_INIT_SD;			// acceso tarjeta
         }
	
				 if (zonePressed(&zone_3))
				 {
            screenState = SCREEN_WIFI;				// acceso wifi
         }
				 if (zonePressed(&zone_sensores))
				 {
            screenState = SCREEN_SENSORES;		// Estado del sistema
         }
		
				 break;
				 
      case SCREEN_TECLADOM:										// Primer intento
					
					LCD_Clear(Black);
					squareButton(zone_6.x, zone_6.y, zone_6.size_x, zone_6.size_y, "Volver", White, Blue);
					pantalla_password();
			if (screenState != SCREEN_MAIN)
			{
					if(strcmp(pass_admin ,pass) == 0)
					{
						pantalla_pss_ok();
						LPC_GPIO0->FIOPIN |=(1<<4); // pone un 1 en el relé (abrimos el relé)
						setTimeOut(TIMEOUT_OK);
						screenState = SCREEN_ABRIR_OK;
						
					}
					else
					{
						screenState = SCREEN_TECLADOM_FAIL_1;
					}
			}
        break;
			case SCREEN_TECLADOM_FAIL_1:				// Segundo intento
			{
					LCD_Clear(Black);
				  squareButton(zone_6.x, zone_6.y, zone_6.size_x, zone_6.size_y, "Volver", White, Blue);
					pantalla_pss_bad_1();
					pantalla_password();
				if (screenState != SCREEN_MAIN)
			 {
				  if(strcmp(pass_admin ,pass) == 0)
					{
						pantalla_pss_ok();
						LPC_GPIO0->FIOPIN |=(1<<4); // pone un 1 en el relé (abrimos el relé)
						setTimeOut(TIMEOUT_OK);
						screenState = SCREEN_ABRIR_OK;
					}
					else
					{
						screenState = SCREEN_TECLADOM_FAIL_2;
					}
				}
				break;
			}
			case SCREEN_TECLADOM_FAIL_2:			// Tercer intento
			{
					LCD_Clear(Black);
				  squareButton(zone_6.x, zone_6.y, zone_6.size_x, zone_6.size_y, "Volver", White, Blue);
					pantalla_pss_bad_2();
					pantalla_password();
				
				if (screenState != SCREEN_MAIN)
			  {
				
					if(strcmp(pass_admin ,pass) == 0)
					{
						pantalla_pss_ok();
						LPC_GPIO0->FIOPIN |=(1<<4); // pone un 1 en el relé (abrimos el relé)
						setTimeOut(TIMEOUT_OK);
						//initTimer();
						screenState = SCREEN_ABRIR_OK;
					}
					else	
					{
						screenState = SCREEN_ALARMA;
					}
				}
					break;

			}

			case SCREEN_ABRIR_OK:
			{
				//while(getTimeOut()!=0);
				if (timeOut == 0)
				{
					//setTimeOut(TIMEOUT_OK);			// tiempo que se quedará abierto el relé
					
					LPC_GPIO0->FIOCLR |=(1<<4);		// cerrar el relé11
					screenState = SCREEN_MAIN;		// vuelve al menú principal
					//TP_Init();
					
					//init_WDT();
					//WDT_Feed();
				}
				break;
			}
			
		
			case SCREEN_ALARMA:
			{		
					cont=0;
					pantalla_alarma();
					alarma();											// suena la alarma
					screenState = SCREEN_MAIN;		// vuelve al menú principal
					//init_WDT();
					//WDT_Feed();
			
				break;
			}
			case SCREEN_WIFI:									// UART
			{	
				LCD_Clear(Black);
				GUI_Text(30,30,"192.168.4.1",White,Black);
				uart_main();
				
				screenState = SCREEN_MAIN;
				//LCD_Initializtion();	
				TP_Init(); 
		//TouchPanel_Calibrate();
        break;
			}
			case SCREEN_SENSORES:							// SENSORES
			{	
				
				screenState = SCREEN_SENSORES_WAIT;	
				
			
        break;
			
			}
			case SCREEN_SENSORES_WAIT:
			{
				LCD_Clear(Black);
				squareButton(zone_6.x, zone_6.y, zone_6.size_x, zone_6.size_y, "Volver", White, Blue);
				GUI_Text(30,30,"Tempt(grados):",White,Black);
				GUI_Text(30,90,"Ciclos:",White,Black);
				GUI_Text(30,120,"Dist(V):",White,Black);
				init_ADC();
				init_TIMER0();
			 break;
			}
			case SCREEN_TARJETA:
			{
         LCD_Clear(Black);
         screenTarjeta();
         screenState = SCREEN_TARJETA_WAIT;
         break;
			}
			case SCREEN_TARJETA_WAIT:
				
				 if (zonePressed(&zone_2))	
				 {		
						 screenState = ADD_USER;
         }						 
         if (zonePressed(&zone_3))						// Visualizar el contennido de la SD
				 {
            screenState = SCREEN_DATA;
         }
				 if (zonePressed(&zone_6))
				 {			
            screenState = SCREEN_MAIN;		// acceso teclado
         }
         if (RTC_Changed)											// Actualiza la hora
				 {
            RTC_Changed = 0;
            screenMainUpdate();
         }					
         if (sdInit())												// Llama a finit(NULL) para activar todos los disp. de almacenamiento
				 {		
            screenState = SCREEN_ERROR_NO_SD;		// error en SD
         } 
         
         if ((idCard = readRFID()) > 0)
				 {
					 //screenState = COMP_IDCARD_SD;
					 
	         GUI_Text(0, 200, "Tarjeta Detectada", Yellow, Black);
					 sd_log=idCard;
           sprintf(buffer_aux,"ID: %X",idCard);
	         GUI_Text(0, 220, (uint8_t*)buffer_aux, Yellow, Black);
					 
					 if(sd_log==key1)
					 {	
							setTimeOut(TIMEOUT_OK);
						  LPC_GPIO0->FIOPIN |=(1<<4); // pone un 1 en el relé (abrimos el relé)
						 	screenState = SCREEN_ABRIR_OK; 
						}
						else
						{
							screenState = COMP_IDCARD_SD;
							GUI_Text(0, 250, "Abrir rele",Black, Black);
							//GUI_Text(0, 250, "Intruso", Yellow, Black);
							//LPC_GPIO0->FIOCLR|=(1<<4); // pone un 1 en fila 1
							//screenState = SCREEN_ALARMA;
						}
						/**/
						
         }
        break;
			case ADD_USER:
			{
				LCD_Clear(Black);
				screen_Add_RFID();
				screenState = ADD_USER_WAIT;
				break;
			}
			case ADD_USER_WAIT:
			{
				readed_id_card = readRFID();
				if ( readed_id_card > 0)
				{
	         GUI_Text(0, 20, "Tarjeta Detectada!", Yellow, Black);
					 sd_load=readed_id_card;
           sprintf(buffer_aux,"ID: %X",readed_id_card);           
	         GUI_Text(0, 40, (uint8_t*)buffer_aux, Yellow, Black);
				}
				if (zonePressed(&zone_2))								// boton registrar tarjeta
				{
							screenState = ADD_TO_SD;				// ADD_TO_SD: estado para guardar la nueva ID
				}
				if (zonePressed(&zone_TARJETA))
				{
						screenState = SCREEN_TARJETA;		// Volver al estado SCREEN_TARJETA
				}
				break;
			}
			case COMP_IDCARD_SD:
			{
				if(taz_o_NO_taz())
				{
					pantalla_pss_ok();
					LPC_GPIO0->FIOPIN |=(1<<4); // pone un 1 en el relé (abrimos el relé)
					setTimeOut(TIMEOUT_OK);
					screenState = SCREEN_ABRIR_OK;	
				}
				else
				{
					screenState = SCREEN_ALARMA;
				}
				break;
			}
			case ADD_TO_SD:
			{
				 error = sdRegisterCard();				// función para añadir nuevo usuario, si devuelve 1 error, si devuelve 0 correcto
				
				 if (error)
						{
               setTimeOut(TIMEOUT_ERROR);
               screenState = SCREEN_ERROR_REGISTER;
            } 
            else
						{
               setTimeOut(TIMEOUT_OK);
               screenState = SCREEN_REGISTERED;
            }
			  break;
			}
      case SCREEN_ERROR_REGISTER:
         screenErrorRegister();
         screenState = SCREEN_ERROR_REGISTER_WAIT;
         break;
			 
      case SCREEN_ERROR_REGISTER_WAIT:
         if (getTimeOut() == 0){
            screenState = SCREEN_MAIN;
         }	
         break;

      case SCREEN_REGISTERED:
         screenRegistered();
         screenState = SCREEN_REGISTERED_WAIT;
         break;
			 
      case SCREEN_REGISTERED_WAIT:
         if (getTimeOut() == 0){
            screenState = SCREEN_TARJETA;
         }	
         break;

      case SCREEN_DATA:
         LCD_Clear(Black);
         screenData();
         setTimeOut(TIMEOUT_OK);
         screenState = SCREEN_DATA_WAIT;
         break;
			 
      case SCREEN_DATA_WAIT:
         if (zonePressed(&zone_6)) {
            screenState = SCREEN_TARJETA;
         }	
         if (zonePressed(&zone_7)) {
            fdelete (fileName); 					// borra el archivo de la SD de las tarjetas
            screenState = SCREEN_DATA;
         }	
         break;

      default:
         break;
   }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
