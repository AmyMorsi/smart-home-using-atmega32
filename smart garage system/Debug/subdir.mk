################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CLCD.c \
../DIO.c \
../EXTI.c \
../ExitButton.c \
../GIE.c \
../GarageSystem.c \
../GateControl.c \
../IR.c \
../STEPPER.c \
../TIMER.c \
../USART.c \
../main.c 

OBJS += \
./CLCD.o \
./DIO.o \
./EXTI.o \
./ExitButton.o \
./GIE.o \
./GarageSystem.o \
./GateControl.o \
./IR.o \
./STEPPER.o \
./TIMER.o \
./USART.o \
./main.o 

C_DEPS += \
./CLCD.d \
./DIO.d \
./EXTI.d \
./ExitButton.d \
./GIE.d \
./GarageSystem.d \
./GateControl.d \
./IR.d \
./STEPPER.d \
./TIMER.d \
./USART.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


