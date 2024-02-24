
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : SSD_PRV.h        *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef SSD_PRV_H_
#define SSD_PRV_H_

						  /*  GFEDCBA*/
#define SSD_ZERO			0b0111111
#define SSD_ONE				0b0000110
#define SSD_TWO				0b1011011
#define SSD_THEE			0b1001111
#define SSD_FOUR			0b1100110
#define SSD_FIVE			0b1101101
#define SSD_SIX				0b1111101
#define SSD_SEVEN			0b0000111
#define SSD_EIGHT			0b1111111
#define SSD_NINE			0b1101111
#define SSD_DOT				0b0000000

typedef enum {
	SSD_OK = 0u,
	SSD_NOK,
	SSD_PTR_ERROR,
	SSD_WRONG_CONFIGURATION
}SSD_ErrorStates_t;

#endif
