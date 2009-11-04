################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../plugin/sceneloader/xml/sceneloader_xml.cpp 

OBJS += \
./plugin/sceneloader/xml/sceneloader_xml.o 

CPP_DEPS += \
./plugin/sceneloader/xml/sceneloader_xml.d 


# Each subdirectory must supply rules for building sources it contributes
plugin/sceneloader/xml/%.o: ../plugin/sceneloader/xml/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


