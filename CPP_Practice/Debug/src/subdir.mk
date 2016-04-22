################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CPP_Practice.cpp \
../src/CheggChess.cpp \
../src/Queue.cpp \
../src/queue_struct.cpp 

OBJS += \
./src/CPP_Practice.o \
./src/CheggChess.o \
./src/Queue.o \
./src/queue_struct.o 

CPP_DEPS += \
./src/CPP_Practice.d \
./src/CheggChess.d \
./src/Queue.d \
./src/queue_struct.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


