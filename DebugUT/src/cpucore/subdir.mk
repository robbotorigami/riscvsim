################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cpucore/InstructionDecode.cpp \
../src/cpucore/InstructionExecute.cpp \
../src/cpucore/InstructionFetch.cpp \
../src/cpucore/InstructionMemory.cpp \
../src/cpucore/InstructionWriteback.cpp \
../src/cpucore/Memory.cpp \
../src/cpucore/RISCVCpu.cpp \
../src/cpucore/RegisterFile.cpp \
../src/cpucore/Signals.cpp 

OBJS += \
./src/cpucore/InstructionDecode.o \
./src/cpucore/InstructionExecute.o \
./src/cpucore/InstructionFetch.o \
./src/cpucore/InstructionMemory.o \
./src/cpucore/InstructionWriteback.o \
./src/cpucore/Memory.o \
./src/cpucore/RISCVCpu.o \
./src/cpucore/RegisterFile.o \
./src/cpucore/Signals.o 

CPP_DEPS += \
./src/cpucore/InstructionDecode.d \
./src/cpucore/InstructionExecute.d \
./src/cpucore/InstructionFetch.d \
./src/cpucore/InstructionMemory.d \
./src/cpucore/InstructionWriteback.d \
./src/cpucore/Memory.d \
./src/cpucore/RISCVCpu.d \
./src/cpucore/RegisterFile.d \
./src/cpucore/Signals.d 


# Each subdirectory must supply rules for building sources it contributes
src/cpucore/%.o: ../src/cpucore/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DSILENT -I"/home/cyborg9/riscvsim/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT "$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


