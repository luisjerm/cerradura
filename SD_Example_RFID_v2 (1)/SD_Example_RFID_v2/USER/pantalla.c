#include "modulos.h"

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
  
	tecla=tecladoM();
	if (screenState != SCREEN_MAIN)
	{
	pass[0]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(40,90,(uint8_t*)valores,0x0000,White);
	
	tecla=tecladoM();
	if (screenState != SCREEN_MAIN)
	{	
	pass[1]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(50,90,(uint8_t*)valores,0x0000,White);
	
	tecla=tecladoM();
	if (screenState != SCREEN_MAIN)
	{	
	pass[2]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(60,90,(uint8_t*)valores,0x0000,White);
	
	tecla=tecladoM();
	if (screenState != SCREEN_MAIN)
	{	
	pass[3]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(70,90,(uint8_t*)valores,0x0000,White);
	
	tecla=tecladoM();
	if (screenState != SCREEN_MAIN)
	{	
	pass[4]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(80,90,(uint8_t*)valores,0x0000,White);
	
	tecla=tecladoM();
	if (screenState != SCREEN_MAIN)
	{	
	pass[5]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(90,90,(uint8_t*)valores,0x0000,White);
	
	tecla=tecladoM();
	if (screenState != SCREEN_MAIN)
	{	
	pass[6]=tecla;
	sprintf(valores,"%c",tecla);
							
	GUI_Text(100,90,(uint8_t*)valores,0x0000,White);
							}
						}
					}
				}
			}
		}
  }
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
	GUI_Text(60,120,"Intentos fallidos: 1/3",White,Black);
}

void pantalla_pss_bad_2(void)
{
	GUI_Text(60,120,"Intentos fallidos: 2/3",White,Black);
}

void pantalla_pss_bad_3(void)
{
	GUI_Text(60,120,"Intentos fallidos: 3/3",White,Black);
}

void pantalla_alarma(void)
{
	GUI_Text(80,180,"Alarma! Intruso!",White,Black);
}

void pantalla_sensores(void)
{
	//GUI_Text(30,30,"Tempt(grados):",White,Black);
	
	sprintf(valores,"%lf",temperatura);
	GUI_Text(130,30,(uint8_t*)valores,White,Black);
}
void pantalla_ventilador(void)
{
	//GUI_Text(30,90,"Ciclos:",White,Black);
	
	sprintf(valores,"%d",ciclos);
	GUI_Text(130,90,(uint8_t*)valores,White,Black);
}

void pantalla_distancia_1(void)
{
	//GUI_Text(30,120,"Dist(V):",White,Black);
	sprintf(valores,"%lf",voltiosdist);
	GUI_Text(130,120,(uint8_t*)valores,White,Black);
	
	GUI_Text(30,150,"Alarma! Intruso!",White,Black);
}

void pantalla_distancia_2(void)
{
	//GUI_Text(30,120,"Dist(V):",White,Black);
	sprintf(valores,"%lf",voltiosdist);
	GUI_Text(130,120,(uint8_t*)valores,White,Black);
}


