################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/SPI_driver.c \
../Src/gpio_driver.c \
../Src/i2c_int_handler.c \
../Src/i2s_driver.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f4xx.c \
../Src/uart_driver.c 

OBJS += \
./Src/SPI_driver.o \
./Src/gpio_driver.o \
./Src/i2c_int_handler.o \
./Src/i2s_driver.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f4xx.o \
./Src/uart_driver.o 

C_DEPS += \
./Src/SPI_driver.d \
./Src/gpio_driver.d \
./Src/i2c_int_handler.d \
./Src/i2s_driver.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f4xx.d \
./Src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Src/SPI_driver.o: ../Src/SPI_driver.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/SPI_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/gpio_driver.o: ../Src/gpio_driver.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/gpio_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/i2c_int_handler.o: ../Src/i2c_int_handler.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/i2c_int_handler.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/i2s_driver.o: ../Src/i2s_driver.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/i2s_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/main.o: ../Src/main.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/system_stm32f4xx.o: ../Src/system_stm32f4xx.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/uart_driver.o: ../Src/uart_driver.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Inc" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Include" -I"C:/Users/User/STM32CubeIDE/workspace_1.6.1/HAL_DIS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/uart_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

