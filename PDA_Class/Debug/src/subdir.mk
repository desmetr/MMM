################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PDA.cpp \
../src/PDA_Class.cpp \
../src/State.cpp \
../src/Transition.cpp 

OBJS += \
./src/PDA.o \
./src/PDA_Class.o \
./src/State.o \
./src/Transition.o 

CPP_DEPS += \
./src/PDA.d \
./src/PDA_Class.d \
./src/State.d \
./src/Transition.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


