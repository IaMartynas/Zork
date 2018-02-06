################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Action.cpp \
../Border.cpp \
../Condition.cpp \
../Container.cpp \
../Creature.cpp \
../Inventory.cpp \
../Item.cpp \
../Map.cpp \
../Player.cpp \
../Room.cpp \
../Trigger.cpp \
../main.cpp 

OBJS += \
./Action.o \
./Border.o \
./Condition.o \
./Container.o \
./Creature.o \
./Inventory.o \
./Item.o \
./Map.o \
./Player.o \
./Room.o \
./Trigger.o \
./main.o 

CPP_DEPS += \
./Action.d \
./Border.d \
./Condition.d \
./Container.d \
./Creature.d \
./Inventory.d \
./Item.d \
./Map.d \
./Player.d \
./Room.d \
./Trigger.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


