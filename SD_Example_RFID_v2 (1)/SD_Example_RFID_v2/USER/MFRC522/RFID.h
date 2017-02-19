/*
* MFRC522.cpp - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
* _Please_ see the comments in MFRC522.h - they give useful hints and background.
* Released into the public domain.
*/
 
#include "MFRC522.h"
#include <string.h>
#include <LPC17xx.H>                 /* LPC17xx Definitions                  */
#include <SPI_LPC17xx.h>

 
#define pin_RESET  0
#define pin_CS  1

#define  m_RESET(n) (n ? (LPC_GPIO0->FIOSET |= (1<<pin_RESET)) : (LPC_GPIO0->FIOCLR |= (1<<pin_RESET)))           
#define  m_CS(n) (n ? (LPC_GPIO0->FIOSET |= (1<<pin_CS)) : (LPC_GPIO0->FIOCLR |= (1<<pin_CS)))           


void 	m_SPI_init (void);
void m_SPI_frequency(int kbaud);
uint8_t m_SPI_write (uint8_t outb);
void wait_ms(unsigned int ms);
unsigned int readRFID(void);
