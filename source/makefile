
#-include ../makefile.init

ifeq ($(PLATFORM), HOST)

OBJS = ./memory.c ./main.c ./conversion.c ./project3.c ./circbuf.c \
			 ./logger_que.c ./logger.c

CC = gcc
CFLAGS = -Wall -o0 -std=gnu99 -Werror
CPPFLAGS = -DPROJECT3 -DBBB

.PHONY: compile-all
compile-all:project3.elf
project3.elf: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: gcc'
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o "project3.elf" $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '



else ifeq ($(PLATFORM) , BBB)

OBJS = ./memory.c ./main.c ./conversion.c ./project3.c ./circbuf.c \
			 ./logger_que.c ./logger.c

CC = arm-none-gnueabihf-gcc
CFLAGS = -Wall -o0 -std=gnu99 -Werror
CPPFLAGS = -DPROJECT3 -DBBB

.PHONY: compile-all
compile-all:project3.elf
project3.elf: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: gcc'
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o "project3.elf" $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '



else ifeq ($(PLATFORM) , FRDM)
#do nothing. Please use kinetis to build for FRDM
endif


clean:
	-$(RM) $(SECONDARY_SIZE)$(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(SECONDARY_FLASH)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) project3.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:


