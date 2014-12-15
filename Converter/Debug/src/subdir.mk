################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Converter.cpp \
../src/MusicXMLMaps.cpp \
../src/MusicXMLParser.cpp \
../src/PartList.cpp \
../src/ScoreInstrument.cpp \
../src/ScorePart.cpp \
../src/tinyxml2.cpp 

OBJS += \
./src/Converter.o \
./src/MusicXMLMaps.o \
./src/MusicXMLParser.o \
./src/PartList.o \
./src/ScoreInstrument.o \
./src/ScorePart.o \
./src/tinyxml2.o 

CPP_DEPS += \
./src/Converter.d \
./src/MusicXMLMaps.d \
./src/MusicXMLParser.d \
./src/PartList.d \
./src/ScoreInstrument.d \
./src/ScorePart.d \
./src/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


