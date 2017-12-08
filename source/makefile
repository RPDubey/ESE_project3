
#-include ../makefile.init

RM := rm -rf


ifeq ($(PLATFORM), HOST)




OBJS = ./memory.c ./main.c ./conversion.c ./project3.c ./circbuf.c \
			 ./logger_que.c ./logger.c

CC = gcc
CFLAGS = -Wall -g -o0 -std=c99 -Werror
CPPFLAGS = -DPROJECT3 -DBBB

.PHONY: compile-all
compile-all: memory.o
memory.o: memory.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)
compile-all:conversion.o
conversion.o: conversion.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)
compile-all:project3.o
project1.o: project3.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)
compile-all:main.o
main.o:main.c
	$(CC) -c -o $@ $^ $(CPPFLAGS) $(INCLUDES)
compile-all:circbuf.asm
circbuf.asm:circbuf.c common.h
	$(CC) -c -S $@ $^ $(CPPFLAGS) $(INCLUDES)


compile-all:project3.elf
project3.elf: $(OBJS) #$(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: gcc'
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o "project3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '



else ifeq ($(PLATFORM) , BBB)

else ifeq ($(PLATFORM) , FRDM)
CC = arm-none-eabi-g++

CFLAGS = -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 \
 				 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3

CPPFLAGS = -DPROJECT3 -DFRDM

LDFLAGS = -T "../MKL25Z128xxx4_flash.ld" \
 					-Xlinker --gc-sections -Wl,-Map,"project3.map"\
					-Xlinker --print-map --specs=nano.specs -specs=nosys.specs\
					-Xlinker -z -Xlinker muldefs

					# Tool invocations
project3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM GNU C++ Linker'
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o "project3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '


endif







# Add inputs and outputs from these tool invocations to the build variables
SECONDARY_FLASH += \
project3.hex \

SECONDARY_SIZE += \
project3.siz \


# All Target
#all: project3.elf secondary-outputs


# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(SECONDARY_FLASH)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) project3.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
