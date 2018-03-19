################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test/test_instructiondecode.cpp \
../src/test/test_instructionexecution.cpp \
../src/test/test_instructionfetch.cpp \
../src/test/test_instructions.cpp \
../src/test/test_memory.cpp \
../src/test/test_parsing.cpp \
../src/test/test_registerfile.cpp \
../src/test/test_riscvcpu.cpp \
../src/test/test_signals.cpp \
../src/test/unittest.cpp 

OBJS += \
./src/test/test_instructiondecode.o \
./src/test/test_instructionexecution.o \
./src/test/test_instructionfetch.o \
./src/test/test_instructions.o \
./src/test/test_memory.o \
./src/test/test_parsing.o \
./src/test/test_registerfile.o \
./src/test/test_riscvcpu.o \
./src/test/test_signals.o \
./src/test/unittest.o 

CPP_DEPS += \
./src/test/test_instructiondecode.d \
./src/test/test_instructionexecution.d \
./src/test/test_instructionfetch.d \
./src/test/test_instructions.d \
./src/test/test_memory.d \
./src/test/test_parsing.d \
./src/test/test_registerfile.d \
./src/test/test_riscvcpu.d \
./src/test/test_signals.d \
./src/test/unittest.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/%.o: ../src/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DSILENT -I"/home/cyborg9/Documents/riscvsim/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -MT "$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


