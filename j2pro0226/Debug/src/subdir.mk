################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/loading.c \
../src/main.c \
../src/mini-game.c \
../src/result-day.c \
../src/result-life.c \
../src/serialize.c \
../src/tikka.c \
../src/title.c \
../src/utils.c 

OBJS += \
./src/loading.o \
./src/main.o \
./src/mini-game.o \
./src/result-day.o \
./src/result-life.o \
./src/serialize.o \
./src/tikka.o \
./src/title.o \
./src/utils.o 

C_DEPS += \
./src/loading.d \
./src/main.d \
./src/mini-game.d \
./src/result-day.d \
./src/result-life.d \
./src/serialize.d \
./src/tikka.d \
./src/title.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/makoto/Programming/SDL/lib-bin/include -I"/home/makoto/Programming/workspace/BreedTikka/src" -I/home/makoto/Programming/SDL/lib-bin/include/freetype2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


