################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CFG/CFG.cpp \
../CFG/tinyxml2.cpp 

OBJS += \
./CFG/CFG.o \
./CFG/tinyxml2.o 

CPP_DEPS += \
./CFG/CFG.d \
./CFG/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
CFG/%.o: ../CFG/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


