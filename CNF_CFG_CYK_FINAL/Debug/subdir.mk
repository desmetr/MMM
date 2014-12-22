################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CFG.cpp \
../CNF.cpp \
../CYK.cpp \
../Formatter.cpp \
../basics.cpp \
../main.cpp \
../tinyxml2.cpp 

OBJS += \
./CFG.o \
./CNF.o \
./CYK.o \
./Formatter.o \
./basics.o \
./main.o \
./tinyxml2.o 

CPP_DEPS += \
./CFG.d \
./CNF.d \
./CYK.d \
./Formatter.d \
./basics.d \
./main.d \
./tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


