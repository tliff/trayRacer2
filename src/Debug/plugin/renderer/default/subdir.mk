################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../plugin/renderer/default/renderer_default.cpp 

OBJS += \
./plugin/renderer/default/renderer_default.o 

CPP_DEPS += \
./plugin/renderer/default/renderer_default.d 


# Each subdirectory must supply rules for building sources it contributes
plugin/renderer/default/%.o: ../plugin/renderer/default/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

