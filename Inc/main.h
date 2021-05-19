/*
 * main.h
 *
 *  Created on: Apr 15, 2021
 *      Author: User
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "gpio_driver.h"
#include "uart_driver.h"
#include "SPI_driver.h"
#include "i2c_driver.h"
#include "i2c_int_handler.h"
#include <stdint.h>
#include "stm32f4xx.h"
#include "string.h"

#define UART_TEST
//#define I2C_TEST
//#define I2C_MASTER_MODE_EN    // if this line is commented application will work in slave mode
//#define SPI_TEST

/* Defines used for transfer communication SIP */
#define CMD_MASTER_READ                               ((uint16_t)0x1234)
#define CMD_MASTER_WRITE                              ((uint16_t)0x5678)
#define CMD_LENGTH                                     2
#define DATA_LENGTH                                    4
#define ACK_LEN                                        2
#define SPI_ACK_BYTES                                  0xD5E5
/********************************************************************************/

/* Defines used for transfer communication I2C */
#define SLAVE_OWN_ADDRESS      (uint8_t)0x53;
#define SLAVE_ADDRESS_READ    (uint8_t) 0xA7
#define SLAVE_ADDRESS_WRITE    (uint8_t) 0xA6

#define GENERAL_CALL_ADDRESS    (uint8_t)0x00

#define MASTER_WRITE_CMD       0xC1
#define MASTER_READ_CMD        0XC2

#define READ_LEN    5
#define WRITE_LEN   5

uint8_t master_tx_buffer[5] = { 0xa5, 0x55, 0xa5, 0x55, 0xb0 };
uint8_t master_rx_buffer[5];

uint8_t slave_tx_buffer[5] = { 0xa5, 0x55, 0xa5, 0x55, 0xc0 };
uint8_t slave_rx_buffer[5];

uint8_t master_write_req;
uint8_t master_read_req;

uint8_t slave_rcv_cmd;
/********************************************************************************/

/* Defines used for transfer communication UART */

uint8_t message1[] = "STM32F4xx Discovery board \n UART Sample App test\n June , 2016 \n";
uint8_t message2[] = "Invalid Command !!! \n";
uint8_t message3[] = "Success !! \n";
uint8_t rx_buffer[4];
/********************************************************************************/




/********************************************************************************/
/* Definition for SPIx's NVIC */
#define SPIx_IRQn                       SPI2_IRQn
#define SPIx_IRQHandler                 SPI2_IRQHandler

#define EXTIx_IRQn                 		EXTI0_IRQn              // if it for interrupt define need EXTI15 from GPIOG!!!
#define EXTIx_IRQHandler           		EXTI0_IRQHandler

/* Definition for I2Cx's NVIC */
#define I2Cx_EV_IRQn                    I2C1_EV_IRQn
#define I2Cx_EV_IRQHandler              I2C1_EV_IRQHandler

#define I2Cx_ER_IRQn                    I2C1_ER_IRQn
#define I2Cx_ER_IRQHandler              I2C1_ER_IRQHandler

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                     USART2_IRQn
#define USARTx_IRQHandler               USART2_IRQHandler

#define EXTIx_IRQn                 		EXTI0_IRQn
#define EXTIx_IRQHandler           		EXTI0_IRQHandler

/* Button details */
#define GPIO_BUTTON_PIN   				0             //  define for interrupt
#define GPIO_BUTTON_PORT  				GPIOA

/* Macros used for Configuring gpios for SPI functionality */
#define GPIOB_PIN_13      				13
#define GPIOB_PIN_14      				14
#define GPIOB_PIN_15      				15

#define GPIOx_PIN_0      				0
#define GPIOx_PIN_1      				1
#define GPIOx_PIN_2      				2
#define GPIOx_PIN_3      				3
#define GPIOx_PIN_4      				4
#define GPIOx_PIN_5      				5
#define GPIOx_PIN_6      				6
#define GPIOx_PIN_7      				7
#define GPIOx_PIN_8      				8
#define GPIOx_PIN_9      				9
#define GPIOx_PIN_10     				10
#define GPIOx_PIN_11     				11
#define GPIOx_PIN_12     				12
#define GPIOx_PIN_13     				13
#define GPIOx_PIN_14     				14
#define GPIOx_PIN_15     				15

/* SPI pin definition */
#define SPI_CLK_PIN   					GPIOB_PIN_13
#define SPI_MISO_PIN   					GPIOB_PIN_14
#define SPI_MOSI_PIN   					GPIOB_PIN_15

/* I2C pin definition */
#define I2C1_SCL_LINE   				GPIOx_PIN_6
#define I2C1_SDA_LINE   				GPIOx_PIN_9

/* UART pin definition */

#define USARTx_TX_PIN 					GPIOx_PIN_2
#define USARTx_TX_GPIO_PORT             GPIOA

#define USARTx_RX_PIN 					GPIOx_PIN_3
#define USARTx_RX_GPIO_PORT             GPIOA

/* I2C/SPI alternate functionality value */
#define GPIO_PIN_AF5_SPI2   			0x05
#define ALT_FUN_4                       0x04
#define GPIO_PIN_AF4_I2C123             ALT_FUN_4

/* UART alternate functionality value */
//#define GPIO_AF7_USART1        		((uint8_t)0x07)  /* USART1 Alternate Function mapping     */
#define GPIO_AF7_USART2        			((uint8_t)0x07)  /* USART2 Alternate Function mapping     */
//#define GPIO_AF7_USART3        `		((uint8_t)0x07)  /* USART3 Alternate Function mapping     */
#define USARTx_TX_AF                    GPIO_AF7_USART2
#define USARTx_RX_AF                     GPIO_AF7_USART2

/********************************************************************************/
/*                                                                            	*/
/*                        		function defifnition		                 	*/
/* 																				*/
/********************************************************************************/

void uart_gpio_init(void);
void spi_gpio_init(void);
void i2c_gpio_init(void);
void led_init(void);
void button_init(void);
void led_toggle(GPIO_TypeDef *GPIOx, uint16_t pin);
void delay_gen(void);
void assert_error(void);
static uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/*								Function for UART								*/

void error_handler(void);
void handle_cmd(int cmd, int led);
void parse_cmd(uint8_t *cmd);
void app_tx_cmp_callback(void *size);
void app_rx_cmp_callback(void *size);

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#endif /* MAIN_H_ */
