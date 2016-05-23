################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Application.c \
../Sources/Detection.c \
../Sources/Events.c \
../Sources/FDC1004.c \
../Sources/SH7776.c \
../Sources/VL6180X.c \
../Sources/main.c 

OBJS += \
./Sources/Application.o \
./Sources/Detection.o \
./Sources/Events.o \
./Sources/FDC1004.o \
./Sources/SH7776.o \
./Sources/VL6180X.o \
./Sources/main.o 

C_DEPS += \
./Sources/Application.d \
./Sources/Detection.d \
./Sources/Events.d \
./Sources/FDC1004.d \
./Sources/SH7776.d \
./Sources/VL6180X.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Cornel/Documents/BDA_3D/Static_Code/PDD" -I"C:/Users/Cornel/Documents/BDA_3D/Static_Code/IO_Map" -I"C:/Users/Cornel/Documents/BDA_3D/Sources" -I"C:/Users/Cornel/Documents/BDA_3D/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


