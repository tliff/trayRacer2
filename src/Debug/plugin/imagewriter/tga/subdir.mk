################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../plugin/imagewriter/tga/imagewriter_tga.cpp 

OBJS += \
./plugin/imagewriter/tga/imagewriter_tga.o 

CPP_DEPS += \
./plugin/imagewriter/tga/imagewriter_tga.d 


# Each subdirectory must supply rules for building sources it contributes
plugin/imagewriter/tga/%.o: ../plugin/imagewriter/tga/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


