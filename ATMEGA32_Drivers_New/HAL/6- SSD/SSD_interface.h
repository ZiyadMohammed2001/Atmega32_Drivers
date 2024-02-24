
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : SSD_Interface.h  *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#include "SSD_prv.h"

typedef enum
{
    SSD_Cathod,
    SSD_Anode,
    SSD_FtKat
} SSD_Type_t;

typedef struct
{
    SSD_Type_t SSD_Type;			/*To configure Common Anode or Common Cathode */
    uint8 u8Port;					/*To configure The used Port.*/
    uint8 u8FirstLedPin;			/*To configure the first pin of the output.*/
    uint8 u8EnablePort;				/*To Configure The Enable Port.*/
    uint8 u8EnablePin;				/*To Configure The Enable Pin.*/
} SSD_t;

typedef struct
{
    SSD_Type_t SSD_Type;			/*To configure Common Anode or Common Cathode */
    uint8 u8Port;					/*To configure The used Port.*/
    uint8 u8Pin;					/*To configure the Dot pin.*/
} SSDDotLED_t;

SSD_ErrorStates_t SSD_u8SetNumber(SSD_t const *Copy_stSSD, uint8 Copy_u8Number);

SSD_ErrorStates_t SSD_EnableDotLED(SSDDotLED_t const * Copy_SSDDotLED);

SSD_ErrorStates_t SSD_DisableDotLED(SSDDotLED_t const * Copy_SSDDotLED);


#endif
