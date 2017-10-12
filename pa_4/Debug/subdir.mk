################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FindPath.c \
../Graph.c \
../GraphTest.c \
../List.c \
../ListClient.c 

OBJS += \
./FindPath.o \
./Graph.o \
./GraphTest.o \
./List.o \
./ListClient.o 

C_DEPS += \
./FindPath.d \
./Graph.d \
./GraphTest.d \
./List.d \
./ListClient.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


