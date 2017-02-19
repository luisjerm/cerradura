
#include <LPC17xx.H>
//#include "lpc17xx_rtc.h"

#define PCRTC 9							// Power RTC
#define CLKEN 0							// Hab. time counters
#define RTCIF 0							// Flag interrupción
#define IMSEC 0							// Interrup. incremento segundos
#define CCALEN 4						// Calibr. enable


uint8_t RTC_Changed = 0;

// Fijamos la fecha y hora actual
void set_time(void)
{
	LPC_RTC->YEAR=2014;
	LPC_RTC->MONTH=9;
	LPC_RTC->DOM=29;
	LPC_RTC->DOW=1;
	LPC_RTC->HOUR=15;
	LPC_RTC->MIN=53;
	LPC_RTC->SEC=0;
}	


void init_RTC(void)
{	
	LPC_SC->PCONP|= (1<<PCRTC);						// POwer ON
	LPC_RTC->CCR|=(1<<CLKEN)|(1<<CCALEN);	// Calib. OFF
	LPC_RTC->CIIR|=(1<<IMSEC);						// Interrup incremento segundos
	
	set_time();
	NVIC_EnableIRQ(RTC_IRQn);

}


void RTC_IRQHandler(void)
{
	RTC_Changed = 1;
	LPC_RTC->ILR|=(1<<RTCIF);
}	

