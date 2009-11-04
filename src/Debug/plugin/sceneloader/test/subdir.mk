################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../plugin/sceneloader/test/sceneloader_test.cpp 

OBJS += \
./plugin/sceneloader/test/sceneloader_test.o 

CPP_DEPS += \
./plugin/sceneloader/test/sceneloader_test.d 


# Each subdirectory must supply rules for building sources it contributes
plugin/sceneloader/test/%.o: ../plugin/sceneloader/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


