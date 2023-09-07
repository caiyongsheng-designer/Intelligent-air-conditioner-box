################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_icu/r_icu.c 

C_DEPS += \
./ra/fsp/src/r_icu/r_icu.d 

OBJS += \
./ra/fsp/src/r_icu/r_icu.o 

SREC += \
123.srec 

MAP += \
123.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_icu/%.o: ../ra/fsp/src/r_icu/%.c
	$(file > $@.in,-mcpu=cortex-m23 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -gdwarf-4 -D_RENESAS_RA_ -D_RA_CORE=CM23 -I"C:/Users/admin/e2_studio/workspace/123/src" -I"C:/Users/admin/e2_studio/workspace/123/ra/fsp/inc" -I"C:/Users/admin/e2_studio/workspace/123/ra/fsp/inc/api" -I"C:/Users/admin/e2_studio/workspace/123/ra/fsp/inc/instances" -I"C:/Users/admin/e2_studio/workspace/123/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/admin/e2_studio/workspace/123/ra_gen" -I"C:/Users/admin/e2_studio/workspace/123/ra_cfg/fsp_cfg/bsp" -I"C:/Users/admin/e2_studio/workspace/123/ra_cfg/fsp_cfg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

