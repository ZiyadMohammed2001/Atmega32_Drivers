
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : SPI_Program.c    *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "SPI_interface.h"
#include "SPI_prv.h"
#include "SPI_cfg.h"
#include "SPI_reg.h"

static void (*SPI_pvCallBAckFuncArr[1])(void) = {NULL};

void SPI_voidInit(void)
{
	/* SPI Configuration based on SPI_cfg.h. */
#if SPI_MODE == SPI_MASTER_MODE_NODE
	SPCR = (SPI_ENABLE) | (SPI_CLOCK_RATE_DIV) | (SPI_DATA_ORDER) | (SPI_CLOCK_POLARITY) | (SPI_CLOCK_PHASE) | (SPI_MASTER_MODE) | (SPI_INTERRUPT_STATE);
#elif SPI_MODE == SPI_SLAVE_MODE_NODE
	SPCR = (SPI_ENABLE) | (SPI_SLAVE_MODE) | (SPI_DATA_ORDER) | (SPI_CLOCK_POLARITY) | (SPI_CLOCK_PHASE) | (SPI_INTERRUPT_STATE);
#else
#error Wrong SPI_MODE Configuration.
#endif

	/* Double SPI speed if required. */
#if SPI_SPEED_X == SPI_1X_SPEED
	SPSR |= SPI_1X_SPEED;
#elif SPI_SPEED_X == SPI_2X_SPEED
	SPSR |= SPI_2X_SPEED;
#elif
#error Wrong SPI_SPEED_X Configuration.
#endif
}

/* Modified function with timeout. */
SPI_Errors_t SPI_u8SendReceiveSynch(uint8 Copy_u8DataToTransmit, uint8 *Ptr_u8DataToReceive, uint32 Copy_u32Timeout)
{
	SPI_Errors_t Local_u8ErrorType = SPI_OK;
	uint32 timeoutCounter = 0;

	if(Ptr_u8DataToReceive != NULL)
	{
		/* Start transmission. */
		SPDR = Copy_u8DataToTransmit;

		/* Wait for transmission complete or timeout. */
		while(!(SPSR & SPI_INTERRUPT_FLAG) && (timeoutCounter < Copy_u32Timeout))
		{
			timeoutCounter++;
		}

		/* Check if the operation completed successfully. */
		if(SPSR & SPI_INTERRUPT_FLAG)
		{
			/* Transmission completed successfully. */
			*Ptr_u8DataToReceive = SPDR;
		}
		else
		{
			/* Timeout occurred. */
			Local_u8ErrorType = SPI_TIME_OUT;
		}
	}
	else
	{
		Local_u8ErrorType = SPI_PTR_ERROR;
	}
	return Local_u8ErrorType;
}

SPI_Errors_t SPI_u8SetCallBack(SPI_Interrupt_t Copy_u8TmrIntSource, void (*Copy_pvCallBackFunc)(void))
{
	SPI_Errors_t Local_u8ErrorState = SPI_OK;
	if(Copy_pvCallBackFunc != NULL)
	{
		SPI_pvCallBAckFuncArr[Copy_u8TmrIntSource]=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState = SPI_PTR_ERROR;
	}
	return Local_u8ErrorState;
}

void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{
	if ((SPI_pvCallBAckFuncArr[SPI_INTERRUPT])!=NULL)
	{
		SPI_pvCallBAckFuncArr[SPI_INTERRUPT]();
		/*SPIF is cleared by hardware when executing the corresponding interrupt handling vector.*/
	}
}
