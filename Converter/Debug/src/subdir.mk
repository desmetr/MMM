################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Attribute.cpp \
../src/BarLine.cpp \
../src/Clef.cpp \
../src/Converter.cpp \
../src/Key.cpp \
../src/Measure.cpp \
../src/MidiInstrument.cpp \
../src/MusicXMLMaps.cpp \
../src/MusicXMLParser.cpp \
../src/Note.cpp \
../src/Part.cpp \
../src/PartList.cpp \
../src/Pitch.cpp \
../src/ScoreInstrument.cpp \
../src/ScorePart.cpp \
../src/Time.cpp \
../src/tinyxml2.cpp 

OBJS += \
./src/Attribute.o \
./src/BarLine.o \
./src/Clef.o \
./src/Converter.o \
./src/Key.o \
./src/Measure.o \
./src/MidiInstrument.o \
./src/MusicXMLMaps.o \
./src/MusicXMLParser.o \
./src/Note.o \
./src/Part.o \
./src/PartList.o \
./src/Pitch.o \
./src/ScoreInstrument.o \
./src/ScorePart.o \
./src/Time.o \
./src/tinyxml2.o 

CPP_DEPS += \
./src/Attribute.d \
./src/BarLine.d \
./src/Clef.d \
./src/Converter.d \
./src/Key.d \
./src/Measure.d \
./src/MidiInstrument.d \
./src/MusicXMLMaps.d \
./src/MusicXMLParser.d \
./src/Note.d \
./src/Part.d \
./src/PartList.d \
./src/Pitch.d \
./src/ScoreInstrument.d \
./src/ScorePart.d \
./src/Time.d \
./src/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


