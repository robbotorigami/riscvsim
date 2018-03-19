################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/instruction/0_Instruction.cpp \
../src/instruction/BInstructions.cpp \
../src/instruction/IInstructions.cpp \
../src/instruction/InstructionSignals.cpp \
../src/instruction/JInstructions.cpp \
../src/instruction/RInstructions.cpp \
../src/instruction/SInstructions.cpp \
../src/instruction/UInstructions.cpp 

OBJS += \
./src/instruction/0_Instruction.o \
./src/instruction/BInstructions.o \
./src/instruction/IInstructions.o \
./src/instruction/InstructionSignals.o \
./src/instruction/JInstructions.o \
./src/instruction/RInstructions.o \
./src/instruction/SInstructions.o \
./src/instruction/UInstructions.o 

CPP_DEPS += \
./src/instruction/0_Instruction.d \
./src/instruction/BInstructions.d \
./src/instruction/IInstructions.d \
./src/instruction/InstructionSignals.d \
./src/instruction/JInstructions.d \
./src/instruction/RInstructions.d \
./src/instruction/SInstructions.d \
./src/instruction/UInstructions.d 


# Each subdirectory must supply rules for building sources it contributes
src/instruction/%.o: ../src/instruction/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DSILENT -I"/home/cyborg9/Documents/riscvsim/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -MT "$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


