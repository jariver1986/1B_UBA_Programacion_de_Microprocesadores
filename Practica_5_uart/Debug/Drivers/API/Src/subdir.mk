################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_Uart.c \
../Drivers/API/Src/API_debounce.c \
../Drivers/API/Src/API_delay.c 

OBJS += \
./Drivers/API/Src/API_Uart.o \
./Drivers/API/Src/API_debounce.o \
./Drivers/API/Src/API_delay.o 

C_DEPS += \
./Drivers/API/Src/API_Uart.d \
./Drivers/API/Src/API_debounce.d \
./Drivers/API/Src/API_delay.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/HP VICTUS/STM32CubeIDE/workspace_1.11.2/Practica_5_uart/Drivers/API/Inc" -I"C:/Users/HP VICTUS/STM32CubeIDE/workspace_1.11.2/Practica_5_uart/Drivers/API/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_Uart.d ./Drivers/API/Src/API_Uart.o ./Drivers/API/Src/API_Uart.su ./Drivers/API/Src/API_debounce.d ./Drivers/API/Src/API_debounce.o ./Drivers/API/Src/API_debounce.su ./Drivers/API/Src/API_delay.d ./Drivers/API/Src/API_delay.o ./Drivers/API/Src/API_delay.su

.PHONY: clean-Drivers-2f-API-2f-Src

