################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/RTC.c \
../source/circbuf.c \
../source/conversion.c \
../source/dma_memory.c \
../source/gpio.c \
../source/logger.c \
../source/logger_que.c \
../source/main.c \
../source/memory.c \
../source/nordic.c \
../source/project3.c \
../source/spi.c \
../source/systick.c \
../source/uart.c 

OBJS += \
./source/RTC.o \
./source/circbuf.o \
./source/conversion.o \
./source/dma_memory.o \
./source/gpio.o \
./source/logger.o \
./source/logger_que.o \
./source/main.o \
./source/memory.o \
./source/nordic.o \
./source/project3.o \
./source/spi.o \
./source/systick.o \
./source/uart.o 

C_DEPS += \
./source/RTC.d \
./source/circbuf.d \
./source/conversion.d \
./source/dma_memory.d \
./source/gpio.d \
./source/logger.d \
./source/logger_que.d \
./source/main.d \
./source/memory.d \
./source/nordic.d \
./source/project3.d \
./source/spi.d \
./source/systick.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DCPU_MKL25Z128VFM4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCPU_MKL25Z128VFM4_cm0plus -I../CMSIS -I../board -I../drivers -I../utilities -std=gnu99 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


