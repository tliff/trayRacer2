################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../plugin/camera/pinhole/camera_pinhole.cpp 

OBJS += \
./plugin/camera/pinhole/camera_pinhole.o 

CPP_DEPS += \
./plugin/camera/pinhole/camera_pinhole.d 


# Each subdirectory must supply rules for building sources it contributes
plugin/camera/pinhole/%.o: ../plugin/camera/pinhole/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


