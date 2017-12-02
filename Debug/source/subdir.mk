################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/dma_memory.c \
../source/main.c \
../source/memory.c \
../source/systick.c 

OBJS += \
./source/dma_memory.o \
./source/main.o \
./source/memory.o \
./source/systick.o 

C_DEPS += \
./source/dma_memory.d \
./source/main.d \
./source/memory.d \
./source/systick.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DCPU_MKL25Z128VFM4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCPU_MKL25Z128VFM4_cm0plus -I../CMSIS -I../board -I../drivers -I../utilities -std=gnu99 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


