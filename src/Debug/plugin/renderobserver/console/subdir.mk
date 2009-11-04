################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../plugin/renderobserver/console/renderobserver_console.cpp 

OBJS += \
./plugin/renderobserver/console/renderobserver_console.o 

CPP_DEPS += \
./plugin/renderobserver/console/renderobserver_console.d 


# Each subdirectory must supply rules for building sources it contributes
plugin/renderobserver/console/%.o: ../plugin/renderobserver/console/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


