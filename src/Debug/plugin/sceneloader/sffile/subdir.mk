################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../plugin/sceneloader/sffile/sceneloader_sffile.cpp 

OBJS += \
./plugin/sceneloader/sffile/sceneloader_sffile.o 

CPP_DEPS += \
./plugin/sceneloader/sffile/sceneloader_sffile.d 


# Each subdirectory must supply rules for building sources it contributes
plugin/sceneloader/sffile/%.o: ../plugin/sceneloader/sffile/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


