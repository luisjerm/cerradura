#include <stdint.h>
#include "File_Config.h"
#include <stdio.h>
#include <rtl.h>
#include "rtc.h"
#include "SD_Functions.h"

#include "modulos.h"

const char fileName[] = "TarjetasRFID.txt";

uint8_t sdInit(void)
{
	 U32 a;
	 //a=finit(NULL);
   return finit (NULL);			// Función de rtl.h para inicializar El sistema de Archivos 
														// Se tiene que llamar antes de invocar al sistema de archivos
	// El argumento es un puntero que apunta a una unidad espercífica para inicializar													
	// Si tiene como argumento NULL--> Todas las unidades activadas

	// Devuelve 0 NO se ha producido un error
	// !=0 -> Error
}

uint8_t sdRegisterCard(void) //unsigned int readed_id_card)
{
  FILE *f;

  f = fopen (fileName,"a");                      /* Open a file from default drive. */
  
  if (f == NULL)  {
    // ERROR
     return 1;
  }
  else  
	{
		//buffer_aux[0]='h';
		//fwrite (&buffer_aux,sizeof (char), 50, f);
		 fprintf(f,"%X\n", sd_load);
		//fprintf(f,"%d\n", readed_id_card);
    /*fprintf(f,"Hora:_%02d:%02d:%02d\n", RTC_GetTime(LPC_RTC, RTC_TIMETYPE_HOUR),
	                                      RTC_GetTime(LPC_RTC, RTC_TIMETYPE_MINUTE),
                                        RTC_GetTime(LPC_RTC, RTC_TIMETYPE_SECOND));
		*/
    fclose (f);
    return 0; 
  }  
  
}


