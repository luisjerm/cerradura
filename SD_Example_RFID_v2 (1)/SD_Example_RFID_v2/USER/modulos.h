#ifndef __MODULOS_H__
#define __MODULOS_H__

#define TIMEOUT_ERROR       20
#define TIMEOUT_OK          50

#define SCREEN_INIT_SD              0
#define SCREEN_MAIN                 1
#define SCREEN_MAIN_WAIT            2
#define SCREEN_ERROR_REGISTER       3
#define SCREEN_ERROR_REGISTER_WAIT  4
#define SCREEN_REGISTERED           5
#define SCREEN_REGISTERED_WAIT      6
#define SCREEN_DATA                 7
#define SCREEN_DATA_WAIT            8
#define SCREEN_ERROR_NO_SD          9

// nuevos estados:
#define SCREEN_TECLADOM							10
#define SCREEN_WIFI									11
#define SCREEN_TARJETA							12
#define SCREEN_TARJETA_WAIT					13
#define ADD_USER										22
#define SCREEN_ABRIR_OK						  14
#define SCREEN_ALARMA								15
#define SCREEN_TECLADOM_FAIL_1			16
#define SCREEN_TECLADOM_FAIL_2			17
#define ADD_TO_SD										18
#define SCREEN_SENSORES							19
#define COMP_IDCARD_SD							20
#define DESC_TECLADO								21
#define ADD_USER_WAIT								23
#define SCREEN_SENSORES_WAIT				24

extern struct t_screenZone zone_0;		
extern struct t_screenZone zone_1;		// acceso teclado matricial
extern struct t_screenZone zone_2;		// acceso tarjeta RFID
extern struct t_screenZone zone_3;		// acceso wifi
extern struct t_screenZone zone_sensores; // sensores del sistema
extern struct t_screenZone zone_4;
extern struct t_screenZone zone_5;
extern struct t_screenZone zone_6;
extern struct t_screenZone zone_7;

#include <LPC17xx.H>
#include <Math.h>
//
//#include <Net_Config.h>
#include <stdio.h>
#include <string.h>
//
#include "GLCD.h"

#include "TouchPanel.h" 
#include "AsciiLib.h"

#define F_cpu 100e6		// Defecto Keil (xtal=12Mhz)
#define F_pclk F_cpu/4 // Defecto despues del reset
#define pi 3.14159
#define F_out 1000			// Frecuencia de salida del DAC 
#define N_muestras 32
#define F_muestreo 1 // Fs=1Hz (Cada 1 s se toma una muestra del canal 0)
#define V_refp 3.3
#define FILAS 4
#define COLUMNAS 4
#define Tpwm 15e-3	// Perido de la señal PWM (15ms)
// WDT
#define F_wdclk F_pclk/4 		// WDT clk

extern uint8_t screenState; 
extern unsigned int readed_id_card;
extern unsigned int sd_load;
extern unsigned int sd_log;
extern char buffer_aux[50];


//VARIABLES
extern float voltiospoten;
extern int ciclos;//ciclos PWM ventilador
extern float voltiostemp;
extern float voltiosdist;
extern float temperatura;


//TECLADO MATRICIAL
extern int i, j, st, x, b;					// indices para moverte por la matriz
extern char teclado[FILAS][COLUMNAS];/*={{"1", "2", "3","A"},						// matriz de con las teclas de l teclado
																	{"4", "5", "6","B"},
																	{"7", "8", "9", "C"},
																	{"#", "0", "*", "D"}};*/
extern int y;	 //	   y=0 si se a producido la EINT2 
					//     y=1 si NO se a producido la EINT2
									
extern int estado; // var que nos dice en que estado estamos

extern char tecla; // variable con la resolución de la tecla pulsada
extern char valores [30];
extern char pass[7];

extern char pass_admin[7];
extern int tries;

extern int cont_alarmar;
//FUNCIONES 
//FUNCIONES ALARMA
//void init_DAC(void);
//void init_TIMER2(void);
void alarma(void);
//int ventilador(int ciclos_temp);	// como argumento: ciclos_temp= al ciclo de trabajo en alta de la PWM,
																	//	desde la función de la funcion que gestiona la temperatura.
																	// no devuelve nada, int se cambiara por void
void config_pwm2(void);
void velocidad_ventilador(void);
void pantalla_ventilador(void);																
char tecladoM (void);							// como argumento: void 
																	// devuelve: la tecla pulsada

//FUNCIONES POTENCIOMETRO configura canal0 en P0.23
void init_ADC(void);
void init_TIMER0(void);
extern int z;

//FUNCIONES TECLADO
void init_TIMER1(void);
void Config(void);

//PANTALLA
void teclado_matricial (void);
void RFID (void);
void WIFI (void);
void pantalla_password(void);
void pantalla_password_wifi(void);
void pantalla_RFID(void);
void boton_atras (void);
void pantalla_ini (void);

void pantalla_pss_ok(void);
void pantalla_pss_bad_1(void);
void pantalla_pss_bad_2(void);
void pantalla_pss_bad_3(void);
void pantalla_alarma(void);
void pantalla_sensores(void);


//FUNCIONES PIR
void pantalla_distancia_1(void);
void pantalla_distancia_2(void);



// ALARMA
extern int cont;
void genera_muestras(uint8_t muestras_ciclo);
void init_DAC(void);
void init_TIMER2(void);

// Tarjeta RFID

void Add_RFID(void);

//main
  void screenStateMachine(void);

extern int timeOut;
#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

