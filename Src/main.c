/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "main.h"

/* data declaration */

/* handle for our peripheries */
spi_handle_t SpiHandle;

i2c_handle_t i2c_handle;

uart_handle_t uart_handle, debug_handle;

int TestReady = 0;

#ifdef SPI_TEST
uint8_t master_write_data[4]={ 0xa, 0xb, 0xc, 0xd};

uint8_t slave_tx_buffer[4]={ 0x55, 0xaa, 0x55, 0xaa};
uint8_t slave_rx_buffer[4];
#endif  // to prevent warning

#ifdef SPI_TEST
	uint16_t ack_bytes = SPI_ACK_BYTES;
	uint8_t rcv_cmd[2];
	uint8_t ack_buf[2] = { 0XD5, 0XE5 };
	uint16_t master_cmd;
#endif	// to prevent warning

#ifdef UART_TEST
	uint8_t message1[] = "STM32F4xx Discovery board \n UART Sample App test\n May , 2021 \n";
	uint8_t message2[] = "Invalid Command !!! \n";
	uint8_t message3[] = "Success !! \n";
	uint8_t rx_buffer[4];
	uart_handle_t uart_handle, debug_handle;
#endif	// to prevent warning

int main(void) {


	spi_gpio_init();
	led_init();  										// configure LED
	i2c_gpio_init();
	button_init();  /* Configure USER Button as ext interrupt throw EXTI0 */
	uart_gpio_init();

	/**
	 ******************************************************************************
	 	 	 	 	 	 	 	 	 	 SPI CONFIG
	 ******************************************************************************
	 */

	_HAL_RCC_SPI2_CLK_ENABLE();

	/*fill up the SPI handle structure */
	SpiHandle.Instance				= SPI_2;

	SpiHandle.Init.BaudRatePrescaler = SPI_REG_CR1_BR_PCLK_DIV_32;
	SpiHandle.Init.Direction         = SPI_ENABLE_2_LINE_UNI_DIR;
	SpiHandle.Init.CLKPhase          = SPI_SECOND_CLOCK_TRANS;
	SpiHandle.Init.CLKPolarity       = SPI_CPOL_LOW;
	SpiHandle.Init.DataSize          = SPI_8BIT_DF_ENABLE;
	SpiHandle.Init.FirstBit          = SPI_MSB_FIRST;
	SpiHandle.Init.NSS               = SPI_SSM_ENABLE;
	SpiHandle.Init.Mode              = SPI_SLAVE_MODE_SEL;

	SpiHandle.State = HAL_SPI_STATE_READY;

	/* Call driver API to initialize the SPI device */
	hal_spi_init(&SpiHandle);

	/* Enable the IRQs in the NVIC */
	NVIC_EnableIRQ(SPI2_IRQn);
	/**
	 ******************************************************************************
	 	 	 	 	 	 	 	 	 	I2C CONFIG
	 ******************************************************************************
	 */
	_HAL_RCC_I2C1_CLK_ENABLE();
	i2c_handle.Instance = I2C_1;        // base address in memory
	i2c_handle.Init.ack_enable = I2C_ACK_ENABLE;
	i2c_handle.Init.AddressingMode = I2C_ADDRMODE_7BIT;
	i2c_handle.Init.ClockSpeed = 100000;
	i2c_handle.Init.DutyCycle = I2C_FM_DUTY_2; //care needs to taken
	i2c_handle.Init.GeneralCallMode = 0;
	i2c_handle.Init.NoStretchMode = I2C_ENABLE_CLK_STRETCH;
	i2c_handle.Init.OwnAddress1 = SLAVE_OWN_ADDRESS	;

	NVIC_EnableIRQ(I2Cx_ER_IRQn);
	NVIC_EnableIRQ(I2Cx_EV_IRQn);

	hal_i2c_init(&i2c_handle);
	hal_i2c_enable_peripheral(i2c_handle.Instance); // It need for something. I think 2IC enable occur in TX/RX function

	//hal_gpio_enable_interrupt(0);

	//val = i2c_handle.Instance->CR1;
	i2c_handle.State = HAL_I2C_STATE_READY;
	/**
	 ******************************************************************************
	 	 	 	 	 	 	 	 	 	 UART CONFIG
	 ******************************************************************************
	 */
	/*enable the clock for the USART2 Peripheral */
	_HAL_RCC_USART2_CLK_ENABLE();

	uart_handle.Instance          = USART_2;

	uart_handle.Init.BaudRate     = USART_BAUD_9600;
	uart_handle.Init.WordLength   = USART_WL_1S8B;
	uart_handle.Init.StopBits     = UART_STOPBITS_1;
	uart_handle.Init.Parity       = UART_PARITY_NONE;
	uart_handle.Init.Mode         = UART_MODE_TX_RX;
	uart_handle.Init.OverSampling = USART_OVER16_ENABLE;

	/*fill out the application callbacks */
	uart_handle.tx_cmp_cb = app_tx_cmp_callback;
	uart_handle.rx_cmp_cb = app_rx_cmp_callback;

	hal_uart_init(&uart_handle);

	/*enable the IRQ of USART2 peripheral */
	NVIC_EnableIRQ(USARTx_IRQn);

	while(uart_handle.tx_state != HAL_UART_STATE_READY );
	/*Send the message */
	hal_uart_tx(&uart_handle,message1, sizeof(message1)-1);


	/******************************************************************************/

	/**
	 ******************************************************************************
	 	 	 	 	 	 	 	 	 	UART CONFIG
	 ******************************************************************************
	 */

	/*enable the clock for the USART2 Peripheral */
	_HAL_RCC_USART2_CLK_ENABLE();

	uart_handle.Instance          = USART_2;

	uart_handle.Init.BaudRate     = USART_BAUD_9600;
	uart_handle.Init.WordLength   = USART_WL_1S8B;
	uart_handle.Init.StopBits     = UART_STOPBITS_1;
	uart_handle.Init.Parity       = UART_PARITY_NONE;
	uart_handle.Init.Mode         = UART_MODE_TX_RX;
	uart_handle.Init.OverSampling = USART_OVER16_ENABLE;

/*fill out the application callbacks */
	uart_handle.tx_cmp_cb = app_tx_cmp_callback;
	uart_handle.rx_cmp_cb = app_rx_cmp_callback;

	hal_uart_init(&uart_handle);

	/*enable the IRQ of USART2 peripheral */
	NVIC_EnableIRQ(USARTx_IRQn);

	while(uart_handle.tx_state != HAL_UART_STATE_READY );
	/*Send the message */
	hal_uart_tx(&uart_handle,message1, sizeof(message1)-1);



	/* Wait for user Button press before starting the communication. Toggles LED_ORANGE until then */
	/*while (TestReady != SET) {
		led_toggle(GPIOD, LED_RED);
		//LED3 (orange)
		delay_gen();
	}*/
	hal_gpio_write_to_pin(GPIOD, LED_RED, 0);

	while (1) {

#ifdef UART_TEST
		while(uart_handle.rx_state != HAL_UART_STATE_READY );
		/*receive the message */
		hal_uart_rx(&uart_handle,rx_buffer, 5 );
#endif

#ifdef I2C_TEST
		while (i2c_handle.State != HAL_I2C_STATE_READY)
			;
#ifdef I2C_MASTER_MODE_EN // code for MASTER implementation

		/*						Write to the slave						*/

		/* first send the master write cmd to slave */
		master_write_req = MASTER_WRITE_CMD;
		hal_i2c_master_tx(&i2c_handle, SLAVE_ADDRESS_WRITE,
				(uint8_t*) &master_write_req, 1);
		while (i2c_handle.State != HAL_I2C_STATE_READY)
			; // application can block here, or you can put here some useful task

		master_write_req = WRITE_LEN;
		/* Now send the number of bytes to be written */
		hal_i2c_master_tx(&i2c_handle, SLAVE_ADDRESS_WRITE,
				(uint8_t*) &master_write_req, 1);

		while (i2c_handle.State != HAL_I2C_STATE_READY)
			; // application can block here, or you can put here some useful task

		/* NOW send the data stream */
		hal_i2c_master_tx(&i2c_handle, SLAVE_ADDRESS_WRITE, master_tx_buffer,
				WRITE_LEN);

		while (i2c_handle.State != HAL_I2C_STATE_READY)
			; // application can block here, or you can put here some useful task

		/*						Read from the slave						*/


		/* first send the master read cmd to slave */
		master_read_req = MASTER_READ_CMD;
		hal_i2c_master_tx(&i2c_handle, SLAVE_ADDRESS_WRITE,
				(uint8_t*) &master_read_req, 1);
		while (i2c_handle.State != HAL_I2C_STATE_READY)
			; // application can block here, or you can put here some useful task

		master_read_req = READ_LEN;
		/* Now send the number of bytes to be read */
		hal_i2c_master_tx(&i2c_handle, SLAVE_ADDRESS_WRITE,
				(uint8_t*) &master_read_req, 1);

		while (i2c_handle.State != HAL_I2C_STATE_READY)
			; // application can block here, or you can put here some useful task

		memset(master_rx_buffer, 0, 5); // reset RX buffer
		/* NOW read the data stream */
		hal_i2c_master_rx(&i2c_handle, SLAVE_ADDRESS_READ, master_rx_buffer,
				READ_LEN);
		while (i2c_handle.State != HAL_I2C_STATE_READY)
			; // application can block here, or you can put here some useful task

		if (Buffercmp(slave_tx_buffer, master_rx_buffer, READ_LEN)) {
			hal_gpio_write_to_pin(GPIOD, LED_RED, 1);
		} else
			led_toggle(GPIOD, LED_BLUE);


		delay_gen();

#else   // code for SLAVE implementation
		/* first rcv the command from the master */
		hal_i2c_slave_rx(&i2c_handle, &slave_rcv_cmd, 1);
		while (i2c_handle.State != HAL_I2C_STATE_READY)
			;

		if (slave_rcv_cmd == MASTER_WRITE_CMD) {
			//prepare to rcv from the master
			//first rcv no bytes to be written by master
			hal_i2c_slave_rx(&i2c_handle, &slave_rcv_cmd, 1);
			while (i2c_handle.State != HAL_I2C_STATE_READY)
				;
			memset(slave_rx_buffer, 0, sizeof(slave_rx_buffer));
			hal_i2c_slave_rx(&i2c_handle, slave_rx_buffer, slave_rcv_cmd);
			while (i2c_handle.State != HAL_I2C_STATE_READY)
				;

			if (Buffercmp(slave_rx_buffer, master_tx_buffer, READ_LEN)) {
				hal_gpio_write_to_pin(GPIOD, LED_RED, 1);
			} else
				led_toggle(GPIOD, LED_BLUE);
		}

		if (slave_rcv_cmd == MASTER_READ_CMD) {
			//prepare to send data to the  master
			//first rcv no bytes to be written to master
			hal_i2c_slave_rx(&i2c_handle, &slave_rcv_cmd, 1);
			while (i2c_handle.State != HAL_I2C_STATE_READY)
				;

			hal_i2c_slave_tx(&i2c_handle, slave_tx_buffer, slave_rcv_cmd);
			while (i2c_handle.State != HAL_I2C_STATE_READY)
				;

		}

#endif  //	end master/slave choice
#endif  //	end I2C test scenario
#ifdef SPI_TEST
		/*Make sure that driver state is ready */
		while (SpiHandle.State != HAL_SPI_STATE_READY)
			;

		/* Receive the master command first */
		hal_spi_slave_rx(&SpiHandle, rcv_cmd, CMD_LENGTH);

		/* wait until driver finishes RXing and state becomes ready again */
		while (SpiHandle.State != HAL_SPI_STATE_READY)
			;

		/* This is the command slave got */
		master_cmd = (uint16_t) (rcv_cmd[1] << 8 | rcv_cmd[0]);

		/* is it a valid command ? */
		if (master_cmd == CMD_MASTER_WRITE || master_cmd == CMD_MASTER_READ) {
			/* yes, send out the ACK bytes */
			hal_spi_slave_tx(&SpiHandle, (uint8_t*) &ack_buf, ACK_LEN);
			while (SpiHandle.State != HAL_SPI_STATE_READY)
				;

		} else {
			/*  No, Error !*/
			led_toggle(GPIOD, LED_RED);
		}

		/* is it a write command from master ? */
		if (master_cmd == CMD_MASTER_WRITE) {
			/* master wants to write, so get ready to receive the data */
			hal_spi_slave_rx(&SpiHandle, slave_rx_buffer, DATA_LENGTH);

			/* wait until the recepion completes */
			while (SpiHandle.State != HAL_SPI_STATE_READY)
				;

			/* compare the received data with the expected data */
			if (Buffercmp(master_write_data, slave_rx_buffer, 4)) {
				/* doesnt match Error ! */
				led_toggle(GPIOD, LED_RED);
			} else {
				/*matches , tOggle the blue LED */
				led_toggle(GPIOD, LED_BLUE);
			}
		}

		/*  or, is it a read command from master ?*/
		if (master_cmd == CMD_MASTER_READ) {
			/* master wants to read, so transmit data to master  */
			hal_spi_slave_tx(&SpiHandle, slave_tx_buffer, DATA_LENGTH);

			/* hang on , till the TXing finishes */
			while (SpiHandle.State != HAL_SPI_STATE_READY)
				;
		}
#endif // SPI_TEST condition
	}
	return 0;
}

void delay_gen(void) {
	uint32_t cnt = 800000;
	while (cnt--)
		;
}

void led_init(void){
	gpio_pin_conf_t gpio_pin_conf;

	_HAL_RCC_GPIOD_CLK_ENABLE();
	gpio_pin_conf.pin = LED_RED;
	gpio_pin_conf.mode = GPIO_PIN_OUTPUT_MODE;
	gpio_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
	gpio_pin_conf.pull = GPIO_PIN_NO_PULL_PUSH;
	gpio_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM;
	hal_gpio_init(GPIOD,&gpio_pin_conf);

	gpio_pin_conf.pin = LED_BLUE;
	hal_gpio_init(GPIOD, &gpio_pin_conf);

	gpio_pin_conf.pin = LED_ORANGE;
	hal_gpio_init(GPIOD, &gpio_pin_conf);

	gpio_pin_conf.pin = LED_GREEN;
	hal_gpio_init(GPIOD, &gpio_pin_conf);

}

void led_toggle(GPIO_TypeDef *GPIOx, uint16_t pin) {
	if (hal_gpio_read_from_pin(GPIOx, pin))
		hal_gpio_write_to_pin(GPIOx, pin, 0);
	else
		hal_gpio_write_to_pin(GPIOx, pin, 1);
}

void i2c_gpio_init(void) {
	gpio_pin_conf_t i2c_pin;

	_HAL_RCC_GPIOB_CLK_ENABLE();

	i2c_pin.pin = I2C1_SCL_LINE;
	i2c_pin.mode = GPIO_PIN_ALT_FUN_MODE;
	i2c_pin.op_type = GPIO_PIN_OP_TYPE_OPENDRAIN;
	i2c_pin.pull = GPIO_PIN_PULL_UP;
	i2c_pin.speed = GPIO_PIN_SPEED_HIGH;

	hal_gpio_set_alt_function(GPIOB, I2C1_SCL_LINE, GPIO_PIN_AF4_I2C123);
	hal_gpio_init(GPIOB, &i2c_pin);

	i2c_pin.pin = I2C1_SDA_LINE;	// need change only pin number another have got same configuration

	hal_gpio_set_alt_function(GPIOB, I2C1_SDA_LINE, GPIO_PIN_AF4_I2C123);
	hal_gpio_init(GPIOB, &i2c_pin);
}

void spi_gpio_init(void){
	gpio_pin_conf_t gpio_pin_conf;

	_HAL_RCC_GPIOB_CLK_ENABLE();

	/* configure GPIOI_PIN_1 for SPI CLK functionality */
	gpio_pin_conf.pin = SPI_CLK_PIN;
	gpio_pin_conf.mode = GPIO_PIN_ALT_FUN_MODE;
	gpio_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
	gpio_pin_conf.pull = GPIO_PIN_PUSH_DOWN;
	gpio_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM;

	hal_gpio_set_alt_function(GPIOB, SPI_CLK_PIN, GPIO_PIN_AF5_SPI2);
	hal_gpio_init(GPIOB,&gpio_pin_conf);

	/* configure GPIOI_PIN_2 for SPI MISO functionality */
	gpio_pin_conf.pin = SPI_MISO_PIN;
	gpio_pin_conf.pull = GPIO_PIN_PULL_UP;

	hal_gpio_set_alt_function(GPIOB, SPI_MISO_PIN, GPIO_PIN_AF5_SPI2);
	hal_gpio_init(GPIOB, &gpio_pin_conf);

	/* configure GPIOI_PIN_3 for SPI MISO functionality */
	gpio_pin_conf.pin = SPI_MOSI_PIN;
	gpio_pin_conf.pull = GPIO_PIN_PULL_UP;

	hal_gpio_set_alt_function(GPIOB, SPI_MOSI_PIN, GPIO_PIN_AF5_SPI2);
	hal_gpio_init(GPIOB, &gpio_pin_conf);
}


/**
 ******************************************************************************
 	 	 	 	 	 	 	 	 	 	I2C CONFIG
 ******************************************************************************
 */
void uart_gpio_init(void) {
	gpio_pin_conf_t uart_pin_conf;

	/*enable the clock for the GPIO port A */
	_HAL_RCC_GPIOA_CLK_ENABLE();

	/*configure the GPIO_PORT_A_PIN_2 as TX */
	uart_pin_conf.pin = USARTx_TX_PIN;
	uart_pin_conf.mode = GPIO_PIN_ALT_FUN_MODE;
	uart_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
	uart_pin_conf.speed = GPIO_PIN_SPEED_HIGH;
	uart_pin_conf.pull = GPIO_PIN_NO_PULL_PUSH;
	hal_gpio_set_alt_function(GPIOA, USARTx_TX_PIN, USARTx_TX_AF);
	hal_gpio_init(GPIOA, &uart_pin_conf);

	/*configure the GPIO_PORT_A_PIN_3 as RX */
	uart_pin_conf.pin = USARTx_RX_PIN;
	hal_gpio_set_alt_function(GPIOA, USARTx_RX_PIN, USARTx_TX_AF);
	hal_gpio_init(GPIOA, &uart_pin_conf);
}

void error_handler(void) {
	while (uart_handle.tx_state != HAL_UART_STATE_READY)
		;
	hal_uart_tx(&uart_handle, message2, sizeof(message2) - 1);
}

void handle_cmd(int cmd, int led) {
	if (cmd == 'H') {
		if (led == (int) 0xff){
			hal_gpio_write_to_pin(GPIOD, LED_ORANGE, 1);
			hal_gpio_write_to_pin(GPIOD, LED_BLUE, 1);
			hal_gpio_write_to_pin(GPIOD, LED_GREEN, 1);
			hal_gpio_write_to_pin(GPIOD, LED_RED, 1);
		} else {
			hal_gpio_write_to_pin(GPIOD, led, 1);
		}
		hal_uart_tx(&uart_handle, message3, sizeof(message3) - 1);
	} else if (cmd == 'L') {
		if (led == (int) 0xff) {
			hal_gpio_write_to_pin(GPIOD, LED_ORANGE, 0);
			hal_gpio_write_to_pin(GPIOD, LED_BLUE, 0);
			hal_gpio_write_to_pin(GPIOD, LED_GREEN, 0);
			hal_gpio_write_to_pin(GPIOD, LED_RED, 0);
		} else
			hal_gpio_write_to_pin(GPIOD, led, 0);

		hal_uart_tx(&uart_handle, message3, sizeof(message3) - 1);
	} else {
		error_handler();
	}
}

void parse_cmd(uint8_t *cmd) {

	if (cmd[0] == 'L' && cmd[1] == 'E' && cmd[2] == 'D') {
		if (cmd[3] == 'O') {
			handle_cmd(cmd[4], LED_ORANGE);
		} else if (cmd[3] == 'B') {
			handle_cmd(cmd[4], LED_BLUE);
		} else if (cmd[3] == 'G') {
			handle_cmd(cmd[4], LED_GREEN);
		} else if (cmd[3] == 'R') {
			handle_cmd(cmd[4], LED_RED);
		} else if (cmd[3] == 'A') {
			handle_cmd(cmd[4], 0xff);
		} else {
			;
		}
	} else {
		error_handler();
	}
}

void app_tx_cmp_callback(void *size){
}

void app_rx_cmp_callback(void *size){
	//we got a command,  parse it
	parse_cmd(rx_buffer);
}

void assert_error(void) {
	while (1) {
		led_toggle(GPIOD, LED_RED);
		delay_gen();
	}
}

void button_init(void) {
	_HAL_RCC_GPIOA_CLK_ENABLE();
	gpio_pin_conf_t gpio_pin_conf;
	gpio_pin_conf.pin = GPIO_BUTTON_PIN;
	gpio_pin_conf.mode = GPIO_PIN_INPUT_MODE;
	gpio_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
	gpio_pin_conf.pull = GPIO_PIN_NO_PULL_PUSH;
	gpio_pin_conf.speed = GPIO_PIN_SPEED_MEDIUM;
	hal_gpio_init(GPIO_BUTTON_PORT, &gpio_pin_conf);

	//RCC->APB2ENR |= (1 << 14);
	//SYSCFG->EXTICR[0] &= (0b1111 << 12);
	hal_gpio_configure_interrupt(GPIO_BUTTON_PIN, INT_FALLING_EDGE);
	hal_gpio_enable_interrupt(GPIO_BUTTON_PIN, EXTI0_IRQn);
}

#if defined(I2C_TEST) || defined(SIP_TEST)
static uint16_t Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2,
		uint16_t BufferLength) {
	while (BufferLength--) {
		if ((*pBuffer1) != *pBuffer2) {
			return BufferLength;
		}
		pBuffer1++;
		pBuffer2++;
	}
	return 0;
}
#endif






/*
 * @brief  brief  This function handles EXTI15-10 interrupt request.
 * @param  none
 * @retval none
 */
void EXTI0_IRQHandler(void){
	hal_gpio_clear_interrupt(GPIO_BUTTON_PIN);
	TestReady = SET;
}


/*
 * @brief  This function handles I2C event interrupt request.
 * @param  none
 * @retval none
 */
void I2C1_EV_IRQHandler(void){
	HAL_I2C_EV_IRQHandler(& i2c_handle);
}


/*
 * @brief  This function handles I2C error interrupt request.
 * @param  none
 * @retval none
 */
void I2C1_ER_IRQHandler(void){
	HAL_I2C_ER_IRQHandler(& i2c_handle);
}


/*
 * @brief  This function handles SPI2 interrupt request.
 * @param  none
 * @retval none
 */
void SPI2_IRQHandler(void) {
	/* call the driver api to process this interrupt */
	hal_spi_irq_handler(&SpiHandle);
}

void USARTx_IRQHandler(void) {
	/* call the driver api to process this interrupt */
	hal_uart_handle_interrupt(&uart_handle);
}


