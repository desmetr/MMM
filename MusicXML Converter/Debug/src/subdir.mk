################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Attribute.cpp \
../src/BarLine.cpp \
../src/BarStyle.cpp \
../src/Clef.cpp \
../src/Division.cpp \
../src/Duration.cpp \
../src/InstrumentName.cpp \
../src/Key.cpp \
../src/Measure.cpp \
../src/MidiChannel.cpp \
../src/MidiInstrument.cpp \
../src/MidiProgram.cpp \
../src/MusicXML\ Converter.cpp \
../src/MusicXMLGenerator.cpp \
../src/MusicXMLMaps.cpp \
../src/MusicXMLParser.cpp \
../src/Note.cpp \
../src/Octave.cpp \
../src/Pan.cpp \
../src/Part.cpp \
../src/PartList.cpp \
../src/PartName.cpp \
../src/Pitch.cpp \
../src/ScoreInstrument.cpp \
../src/ScorePart.cpp \
../src/Stem.cpp \
../src/Step.cpp \
../src/Time.cpp \
../src/Type.cpp \
../src/Utilities.cpp \
../src/Voice.cpp \
../src/Volume.cpp \
../src/tinyxml2.cpp 

OBJS += \
./src/Attribute.o \
./src/BarLine.o \
./src/BarStyle.o \
./src/Clef.o \
./src/Division.o \
./src/Duration.o \
./src/InstrumentName.o \
./src/Key.o \
./src/Measure.o \
./src/MidiChannel.o \
./src/MidiInstrument.o \
./src/MidiProgram.o \
./src/MusicXML\ Converter.o \
./src/MusicXMLGenerator.o \
./src/MusicXMLMaps.o \
./src/MusicXMLParser.o \
./src/Note.o \
./src/Octave.o \
./src/Pan.o \
./src/Part.o \
./src/PartList.o \
./src/PartName.o \
./src/Pitch.o \
./src/ScoreInstrument.o \
./src/ScorePart.o \
./src/Stem.o \
./src/Step.o \
./src/Time.o \
./src/Type.o \
./src/Utilities.o \
./src/Voice.o \
./src/Volume.o \
./src/tinyxml2.o 

CPP_DEPS += \
./src/Attribute.d \
./src/BarLine.d \
./src/BarStyle.d \
./src/Clef.d \
./src/Division.d \
./src/Duration.d \
./src/InstrumentName.d \
./src/Key.d \
./src/Measure.d \
./src/MidiChannel.d \
./src/MidiInstrument.d \
./src/MidiProgram.d \
./src/MusicXML\ Converter.d \
./src/MusicXMLGenerator.d \
./src/MusicXMLMaps.d \
./src/MusicXMLParser.d \
./src/Note.d \
./src/Octave.d \
./src/Pan.d \
./src/Part.d \
./src/PartList.d \
./src/PartName.d \
./src/Pitch.d \
./src/ScoreInstrument.d \
./src/ScorePart.d \
./src/Stem.d \
./src/Step.d \
./src/Time.d \
./src/Type.d \
./src/Utilities.d \
./src/Voice.d \
./src/Volume.d \
./src/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/MusicXML\ Converter.o: ../src/MusicXML\ Converter.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"src/MusicXML Converter.d" -MT"src/MusicXML\ Converter.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


