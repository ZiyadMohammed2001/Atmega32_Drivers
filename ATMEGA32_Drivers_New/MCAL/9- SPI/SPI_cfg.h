
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : SPI_CFG.h        *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef SPI_CFG_H_
#define SPI_CFG_H_

/* Define SPI mode, Options:
 * 							1- SPI_MASTER_MODE_NODE: Configure the SPI as Master.
 * 							2- SPI_SLAVE_MODE_NODE: Configure the SPI as Slave.
 */
#define SPI_MODE		SPI_MASTER_MODE_NODE

#if SPI_MODE	==	SPI_MASTER_MODE_NODE		/*These options are effective only in Master mode.*/

/* SPI Clock Rate Divider, Options:
 * 									1- SPI_CLOCK_RATE_DIV4: SPI Clock divided by 4.
 * 									2- SPI_CLOCK_RATE_DIV16: SPI Clock divided by 16.
 * 									3- SPI_CLOCK_RATE_DIV64: SPI Clock divided by 64.
 * 									4- SPI_CLOCK_RATE_DIV128: SPI Clock divided by 128.
 */
#define SPI_CLOCK_RATE_DIV       SPI_CLOCK_RATE_DIV128

#endif


/* SPI Data Order, Options:
 * 							1- SPI_DATA_ORDER_MSB: MSB of the data is transmitted first.
 * 							2- SPI_DATA_ORDER_LSB: LSB of the data is transmitted first.
 */
#define SPI_DATA_ORDER           SPI_DATA_ORDER_MSB

/* SPI Clock Polarity (CPOL), Options:
 * 										1- SPI_CLOCK_POLARITY_LOW: SCK is low when idle.
 * 										2- SPI_CLOCK_POLARITY_HIGH: SCK is high when idle.
 */
#define SPI_CLOCK_POLARITY       SPI_CLOCK_POLARITY_LOW

/* SPI Clock Phase (CPHA), Options:
 * 									1- SPI_CLOCK_PHASE_SAMPLE: Data is sampled at the leading edge of SCK and setup at the trailing edge.
 * 									2- SPI_CLOCK_PHASE_SETUP: Data is setup at the leading edge of SCK and sampled at the trailing edge.
 */
#define SPI_CLOCK_PHASE          SPI_CLOCK_PHASE_SAMPLE

/* SPI Double Speed Bit, Options:
 * 										1- SPI_1X_SPEED: SPI Normal Speed.
 * 										2- SPI_2X_SPEED: SPI Double Speed.
 */
#define SPI_SPEED_X						SPI_1X_SPEED

/* SPI Interrupt State, Options:
 * 										1- SPI_INTERRUPT_ENABLE: SPI Normal Speed.
 * 										2- SPI_INTERRUPT_DISABLE: SPI Double Speed.
 */
#define SPI_INTERRUPT_STATE				SPI_INTERRUPT_DISABLE
#endif /*SPI_CFG_H_*/

