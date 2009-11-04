################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../plugin/renderobserver/pixeltoaster/renderobserver_pixeltoaster.cpp 

OBJS += \
./plugin/renderobserver/pixeltoaster/renderobserver_pixeltoaster.o 

CPP_DEPS += \
./plugin/renderobserver/pixeltoaster/renderobserver_pixeltoaster.d 


# Each subdirectory must supply rules for building sources it contributes
plugin/renderobserver/pixeltoaster/%.o: ../plugin/renderobserver/pixeltoaster/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


