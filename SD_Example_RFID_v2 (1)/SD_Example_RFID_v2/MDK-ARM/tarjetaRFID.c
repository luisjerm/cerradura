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
//

struct t_screenZone
{
   uint16_t x;         
	 uint16_t y;
	 uint16_t size_x;
	 uint16_t size_y;
	 uint8_t  oldpressed;
};




