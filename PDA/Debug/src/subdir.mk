################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PDA.cpp \
../src/PDA_Main.cpp \
../src/State.cpp \
../src/Transition.cpp \
../src/tinystr.cpp \
../src/tinyxml.cpp \
../src/tinyxmlerror.cpp \
../src/tinyxmlparser.cpp 

OBJS += \
./src/PDA.o \
./src/PDA_Main.o \
./src/State.o \
./src/Transition.o \
./src/tinystr.o \
./src/tinyxml.o \
./src/tinyxmlerror.o \
./src/tinyxmlparser.o 

CPP_DEPS += \
./src/PDA.d \
./src/PDA_Main.d \
./src/State.d \
./src/Transition.d \
./src/tinystr.d \
./src/tinyxml.d \
./src/tinyxmlerror.d \
./src/tinyxmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


