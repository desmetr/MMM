################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/newCYK_CFG/CFG.cpp \
../src/newCYK_CFG/CYK.cpp \
../src/newCYK_CFG/basics.cpp \
../src/newCYK_CFG/main.cpp \
../src/newCYK_CFG/tinyxml2.cpp 

OBJS += \
./src/newCYK_CFG/CFG.o \
./src/newCYK_CFG/CYK.o \
./src/newCYK_CFG/basics.o \
./src/newCYK_CFG/main.o \
./src/newCYK_CFG/tinyxml2.o 

CPP_DEPS += \
./src/newCYK_CFG/CFG.d \
./src/newCYK_CFG/CYK.d \
./src/newCYK_CFG/basics.d \
./src/newCYK_CFG/main.d \
./src/newCYK_CFG/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
src/newCYK_CFG/%.o: ../src/newCYK_CFG/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__cplusplus=201103L -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


