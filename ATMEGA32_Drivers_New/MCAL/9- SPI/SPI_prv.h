
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : SPI_PRV.h        *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef SPI_PRV_H_
#define SPI_PRV_H_

/* SPI Control Register (SPCR). */
#define SPI_ENABLE                (1 << SPE)
#define SPI_DISABLE               (0 << SPE)
#define SPI_INTERRUPT_ENABLE      (1 << SPIE)
#define SPI_INTERRUPT_DISABLE     (0 << SPIE)
#define SPI_MASTER_MODE           (1 << MSTR)
#define SPI_SLAVE_MODE            (0 << MSTR)
#define SPI_DATA_ORDER_MSB        (0 << DORD)
#define SPI_DATA_ORDER_LSB        (1 << DORD)
#define SPI_CLOCK_POLARITY_HIGH   (1 << CPOL)
#define SPI_CLOCK_POLARITY_LOW    (0 << CPOL)
#define SPI_CLOCK_PHASE_SETUP     (1 << CPHA)
#define SPI_CLOCK_PHASE_SAMPLE    (0 << CPHA)
#define SPI_CLOCK_RATE_MASK       (0x03)
#define SPI_CLOCK_RATE_DIV4       (0x00)
#define SPI_CLOCK_RATE_DIV16      (0x01)
#define SPI_CLOCK_RATE_DIV64      (0x02)
#define SPI_CLOCK_RATE_DIV128     (0x03)
#define SPI_1X_SPEED              (0 << SPI2X)
#define SPI_2X_SPEED              (1 << SPI2X)

/* SPI Status Register (SPSR). */
#define SPI_INTERRUPT_FLAG        (1 << SPIF)
#define SPI_WRITE_COLLISION_FLAG  (1 << WCOL)
#define SPI_2X_SPEED_BIT          (1 << SPI2X)

/*SPI Node Configuration.*/
#define SPI_MASTER_MODE_NODE		1u
#define SPI_SLAVE_MODE_NODE			2u

typedef enum
{
	SPI_OK = 0u,
	SPI_PTR_ERROR = 1u,
	SPI_TIME_OUT = 2u,
}SPI_Errors_t;

#endif
