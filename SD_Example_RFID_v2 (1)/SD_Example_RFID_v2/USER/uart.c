/* uart.c
 * contiene las funciones:

 1  UART0_IRQHandler(void)
 2  tx_cadena_UART0(char *ptr)
 3  uart0_set_baudrate(unsigned int baudrate) 
 4  uart0_init(int baudrate) 
  
 */
#include <LPC17xx.h>
#include "uart.h"
#include "modulos.h"
#include <stdio.h>
#include <string.h>


// Variables de la UART

char buffer_uart[30];		// Buffer de recepción de 30 caracteres
char *ptr_rx;			// puntero de recepción
char rx_completa;		// Flag de recepción de cadena que se activa a "1" al recibir la tecla return CR(ASCII=13)
char *ptr_tx;			// puntero de transmisión
char tx_completa;		// Flag de transmisión de cadena que se activa al transmitir el caracter null (fin de cadena)
char fin=0;
int a=0;

char pass_admin_uart[]="1111111\r";
int alarma2;
unsigned int rele;



void delay2(void)
{
	uint32_t i;
	for(i=0;i<125000000;i++);
}	
/*
 * UART0 interrupt handler
 */
void UART0_IRQHandler(void) {
	
    switch(LPC_UART0->IIR&0x0E) {
	
	case 0x04:								 /* RBR, Receiver Buffer Ready */
	*ptr_rx=LPC_UART0->RBR; 	   			 /* lee el dato recibido y lo almacena */
	LPC_UART0->THR=*ptr_tx;     // para el eco
	    if (*ptr_rx++ ==13) 				// Caracter return --> Cadena completa
	    					{
							*ptr_rx=0;		/* Añadimos el caracter null para tratar los datos recibidos como una cadena*/ 
							rx_completa = 1;/* rx completa */
							ptr_rx=buffer_uart;	/* puntero al inicio del buffer para nueva recepción */
	    					}	
		break;
	
    
   case 0x02:								/* THRE, Transmit Holding Register empty */
		if (*ptr_tx!=0) LPC_UART0->THR=*ptr_tx++;	/* carga un nuevo dato para ser transmitido */
		else tx_completa=1;
		break;

    }
}

// Función para enviar una cadena de texto
// El argumento de entrada es la dirección de la cadena, o
// directamente la cadena de texto entre comillas
void tx_cadena_UART0(char *cadena)
{
ptr_tx=cadena;
tx_completa=0;
LPC_UART0->THR=*ptr_tx++;	 // IMPORTANTE: Introducir un carácter al comienzo para iniciar TX o
}							 // activar flag interrupción por registro transmisor vacio


static int uart0_set_baudrate(unsigned int baudrate) {
    int errorStatus = -1; //< Failure

    // UART clock (FCCO / PCLK_UART0)
   // unsigned int uClk = SystemCoreClock / 4;
    unsigned int uClk =SystemCoreClock/4;
    unsigned int calcBaudrate = 0;
    unsigned int temp = 0;

    unsigned int mulFracDiv, dividerAddFracDiv;
    unsigned int divider = 0;
    unsigned int mulFracDivOptimal = 1;
    unsigned int dividerAddOptimal = 0;
    unsigned int dividerOptimal = 0;

    unsigned int relativeError = 0;
    unsigned int relativeOptimalError = 100000;

    uClk = uClk >> 4; /* div by 16 */

    /*
     *  The formula is :
     * BaudRate= uClk * (mulFracDiv/(mulFracDiv+dividerAddFracDiv) / (16 * DLL)
     *
     * The value of mulFracDiv and dividerAddFracDiv should comply to the following expressions:
     * 0 < mulFracDiv <= 15, 0 <= dividerAddFracDiv <= 15
     */
    for (mulFracDiv = 1; mulFracDiv <= 15; mulFracDiv++) {
        for (dividerAddFracDiv = 0; dividerAddFracDiv <= 15; dividerAddFracDiv++) {
            temp = (mulFracDiv * uClk) / (mulFracDiv + dividerAddFracDiv);

            divider = temp / baudrate;
            if ((temp % baudrate) > (baudrate / 2))
                divider++;

            if (divider > 2 && divider < 65536) {
                calcBaudrate = temp / divider;

                if (calcBaudrate <= baudrate) {
                    relativeError = baudrate - calcBaudrate;
                } else {
                    relativeError = calcBaudrate - baudrate;
                }

                if (relativeError < relativeOptimalError) {
                    mulFracDivOptimal = mulFracDiv;
                    dividerAddOptimal = dividerAddFracDiv;
                    dividerOptimal = divider;
                    relativeOptimalError = relativeError;
                    if (relativeError == 0)
                        break;
                }
            }
        }

        if (relativeError == 0)
            break;
    }

    if (relativeOptimalError < ((baudrate * UART_ACCEPTED_BAUDRATE_ERROR) / 100)) {

        LPC_UART0->LCR |= DLAB_ENABLE; 	// importante poner a 1
        LPC_UART0->DLM = (unsigned char) ((dividerOptimal >> 8) & 0xFF);
        LPC_UART0->DLL = (unsigned char) dividerOptimal;
        LPC_UART0->LCR &= ~DLAB_ENABLE;	// importante poner a 0

        LPC_UART0->FDR = ((mulFracDivOptimal << 4) & 0xF0) | (dividerAddOptimal & 0x0F);

        errorStatus = 0; //< Success
    }

    return errorStatus;
}
 					   					  
void uart0_init(int baudrate) {
    
    LPC_PINCON->PINSEL0 = (1 << 4) | (1 << 6);// Change P0.2 and P0.3 mode to TXD0 and RXD0
   
    LPC_UART0->LCR &= ~STOP_1_BIT & ~PARITY_NONE; // Set 8N1 mode (8 bits/dato, sin pariad, y 1 bit de stop)
    LPC_UART0->LCR |= CHAR_8_BIT;

    uart0_set_baudrate(baudrate);// Set the baud rate
    
     
    LPC_UART0->IER = THRE_IRQ_ENABLE|RBR_IRQ_ENABLE;// Enable UART TX and RX interrupt (for LPC17xx UART)   
    NVIC_EnableIRQ(UART0_IRQn);// Enable the UART interrupt (for Cortex-CM3 NVIC)

    
}

void uart_main(void)
{
//LPC_GPIO1->FIODIR |= (1<<18);	 // P1.18 definido como salida  
	//LPC_GPIO1->FIOCLR |= (1<<18);	 // P1.18 apagado 
	
	LPC_GPIO0->FIODIR |=(1<<4); // el relé def. salida
	LPC_GPIO0->FIOCLR |= (1<<4);	 // P0.4 apagado
	ptr_rx=buffer_uart;	                 // inicializa el puntero de recepción al comienzo del buffer
	uart0_init(115200);					 // configura la UART0 a 9600 baudios, 8 bits, 1 bit stop
						

	tx_cadena_UART0("Bienvenido al sistema de Acceso.Para salir introducir el comando: 'salir'.\n\r"
									"Introduce el password(Intento: 1/3):\n\r");
	while(rx_completa==0); // Espera introducir una cadena de caracteres terminada con CR (0x0D)
		//rx_completa=0;				// Borrar flag  
	
	do{
	if(rx_completa)
		{					 	// Comprabamos la llegada de una cadena por RXD
				rx_completa=0; 				// Borrar flag para otra recepción
			
			
			/*	tx_cadena_UART0(buffer);//
			  delay();								//
			  tx_cadena_UART0("\n");	*/
			
			
				if (strcmp (buffer_uart, pass_admin_uart) == 0)
				{				
					tx_cadena_UART0("Password Correcta\n\r");
					LPC_GPIO0->FIOSET |=(1<<4); // pone un 1 en el relé (abrimos el relé)		
					setTimeOut(TIMEOUT_OK);
					//initTimer();
					while(timeOut!=0);
					//delay2();
					tx_cadena_UART0("Cerrando\n\r");
					LPC_GPIO0->FIOCLR |=(1<<4); // pone un 1 en el FIOCLR del relé (cerramos el relé)	7
					memset (buffer_uart, '\0', sizeof(buffer_uart));
					fin=1;
				}
				else if (strcmp (buffer_uart, "exit\r") == 0)
				{
					tx_cadena_UART0("Hasta pronto!\n\r");
					memset (buffer_uart, '\0', sizeof(buffer_uart));
					fin=1;
				}
				else
			 {
					tx_cadena_UART0("password incorrecta\n\r");
				  memset (buffer_uart, '\0', sizeof(buffer_uart));
					alarma2++;
					if (alarma2==3)
					{
						tx_cadena_UART0("Alarma Intruso! \n\r");
						alarma();
						memset (buffer_uart, '\0', sizeof(buffer_uart));
						fin=1;
					}
				}
		}
	}while(fin==0);	
		
	//screenState = SCREEN_MAIN;

}