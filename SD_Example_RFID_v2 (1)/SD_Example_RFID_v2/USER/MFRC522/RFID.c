/*
* RFID.c - SPI configuration and high level functions to use the MFRC552 library for LPC1768
*/

// MFRC552_RST:    P0.0
// MFRC552_MISO:   P1.23
// MFRC552_MOSI:   P1.24
// MFRC552_SCK:    P1.20
// MFRC552_SS/SDA: P0.1


#include "MFRC522.h"
#include <LPC17xx.H>                 /* LPC17xx Definitions                  */


#define  RFID_SPI_FREC 10000 // SPI speed in kbaud
#define ___PCLK    100000000

// Functions use SSP0 module 
#define pin_RESET  0   // RESET pin of MFRC552: P0.0
#define pin_CS     1   // CS pin of MFRC552:    P0.1

#define  m_RESET(n) (n ? (LPC_GPIO0->FIOSET |= (1<<pin_RESET)) : (LPC_GPIO0->FIOCLR |= (1<<pin_RESET)))           
#define  m_CS(n) (n ? (LPC_GPIO0->FIOSET |= (1<<pin_CS)) : (LPC_GPIO0->FIOCLR |= (1<<pin_CS)))           


/* SSPxSR - bit definitions. */
#define TFE     0x01
#define TNF     0x02
#define RNE     0x04
#define RFF     0x08
#define BSY     0x10

void m_SPI_frequency(int kbaud) {
  /* Set an SPI clock to required baud rate. */
  unsigned int div;

  div = (___PCLK/1000 + kbaud - 1) / kbaud;
  if (div == 0)   div = 0x02;
  if (div & 1)    div++;
  if (div > 0xFE) div = 0xFE;
  LPC_SSP0->CPSR = div;   
}


// This 
void 	m_SPI_init (int bits, int mode){
    LPC_GPIO0->FIODIR |= (1<<pin_RESET); 
    LPC_GPIO0->FIODIR |= (1<<pin_CS); 
    LPC_GPIO0->FIOSET |= (1<<pin_CS); 
    LPC_GPIO0->FIOSET |= (1<<pin_RESET);
   
  /* Initialize and enable the SSP Interface module. */

  LPC_SC->PCONP       |= (1 << 21);           /* Enable power to SSPI0 block */

  /* SCK, MISO, MOSI are SSP pins. */

  LPC_PINCON->PINSEL3 &= ~(3UL<<8);             /* P1.20 cleared               */
  LPC_PINCON->PINSEL3 |=  (3UL<<8);             /* P1.20 SCK0                  */
  LPC_PINCON->PINSEL3 &= ~((3<<14) | (3<<16));  /* P1.23, P1.24 cleared        */
  LPC_PINCON->PINSEL3 |=  ((3<<14) | (3<<16));  /* P1.23 MISO0, P1.24 MOSI0    */

  LPC_SC->PCLKSEL1    &= ~(3<<10);              /* PCLKSP0 = CCLK/4 ( 25MHz)   */
  LPC_SC->PCLKSEL1    |=  (1<<10);              /* PCLKSP0 = CCLK   (100MHz)   */

  LPC_SSP0->CPSR       = 250;                   /* 100MHz / 250 = 400kBit      */

  LPC_SSP0->CR0        = 0x0007;              /* 8Bit, CPOL=0, CPHA=0        */
  LPC_SSP0->CR1        = 0x0002;              /* SSP0 enable, master         */

  m_SPI_frequency(RFID_SPI_FREC);

   
}


uint8_t m_SPI_write (uint8_t outb) {
   m_SPI_frequency(RFID_SPI_FREC);

   /* Write and Read a byte on SPI interface. */
   LPC_SSP0->DR = outb;
   while (LPC_SSP0->SR & BSY);                 /* Wait for transfer to finish */
   return (LPC_SSP0->DR);                      /* Return received value       */
}


void wait_ms(unsigned int ms) {
   int i,j;
   
   for (i = 0; i < ms; i++)
      for (j = 0; j<17500;j++);   
}

// This function return RFIF serial number if card is present. If not returns 0
unsigned int readRFID(void) {
   unsigned int id = 0;
   int i;
   
   // Check if a new card is present
   if (PICC_IsNewCardPresent())
   {
      // Read serial number
      if (PICC_ReadCardSerial()) 
      {
         // Enviamos serialemente su UID
         for (i = 0; i < uid.size; i++) {
            id = (id << 8) + uid.uidByte[i];
         } 
         // Terminamos la lectura de la tarjeta  actual
         PICC_HaltA();         
      }       
   }
   
   return id;
}


