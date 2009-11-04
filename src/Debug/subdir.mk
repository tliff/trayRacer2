################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cornellbox.cpp \
../diffuseshader.cpp \
../meshkd.cpp \
../normalshader.cpp \
../outputable.cpp \
../pathtraceshader.cpp \
../plane.cpp \
../plugin.cpp \
../pluginmanager.cpp \
../scalingtonemapper.cpp \
../sceneitemfactory.cpp \
../shader.cpp \
../sphere.cpp \
../test.cpp \
../transformedshape.cpp \
../trayRacer.cpp \
../triangle.cpp \
../vector3.cpp 

OBJS += \
./cornellbox.o \
./diffuseshader.o \
./meshkd.o \
./normalshader.o \
./outputable.o \
./pathtraceshader.o \
./plane.o \
./plugin.o \
./pluginmanager.o \
./scalingtonemapper.o \
./sceneitemfactory.o \
./shader.o \
./sphere.o \
./test.o \
./transformedshape.o \
./trayRacer.o \
./triangle.o \
./vector3.o 

CPP_DEPS += \
./cornellbox.d \
./diffuseshader.d \
./meshkd.d \
./normalshader.d \
./outputable.d \
./pathtraceshader.d \
./plane.d \
./plugin.d \
./pluginmanager.d \
./scalingtonemapper.d \
./sceneitemfactory.d \
./shader.d \
./sphere.d \
./test.d \
./transformedshape.d \
./trayRacer.d \
./triangle.d \
./vector3.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


