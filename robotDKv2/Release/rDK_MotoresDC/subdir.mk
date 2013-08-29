################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../rDK_MotoresDC/rDK_MotoresDC.cpp 

OBJS += \
./rDK_MotoresDC/rDK_MotoresDC.o 

CPP_DEPS += \
./rDK_MotoresDC/rDK_MotoresDC.d 


# Each subdirectory must supply rules for building sources it contributes
rDK_MotoresDC/%.o: ../rDK_MotoresDC/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"D:\datos\electronica\arduino-1.0.5\hardware\arduino\cores\arduino" -I"D:\datos\electronica\arduino-1.0.5\hardware\arduino\variants\mega" -I"C:\Users\jcruz\Documents\GitHub\robotDKv2\robotDKv2" -I"D:\datos\electronica\arduino-1.0.5\libraries\AFMotor" -I"C:\Users\jcruz\Documents\GitHub\robotDKv2\robotDKv2\rDK_GLCD" -I"C:\Users\jcruz\Documents\GitHub\robotDKv2\robotDKv2\rDK_MotoresDC" -I"C:\Users\jcruz\Documents\GitHub\robotDKv2\robotDKv2\rDK_Mover" -I"D:\datos\electronica\arduino-1.0.5\libraries\SoftwareSerial" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=105 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '


