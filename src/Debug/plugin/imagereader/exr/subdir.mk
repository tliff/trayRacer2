################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../plugin/imagereader/exr/imagereader_exr.cpp 

OBJS += \
./plugin/imagereader/exr/imagereader_exr.o 

CPP_DEPS += \
./plugin/imagereader/exr/imagereader_exr.d 


# Each subdirectory must supply rules for building sources it contributes
plugin/imagereader/exr/%.o: ../plugin/imagereader/exr/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


