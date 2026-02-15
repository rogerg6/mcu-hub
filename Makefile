# Makefile for mcu-hub project
# STM32F429 MCU project using ARM GCC toolchain

# Project name
PROJECT := mcuhub

# Build directory
BUILD_DIR := build

# Cross compiler toolchain
CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)gcc -x assembler-with-cpp
CP := $(CROSS_COMPILE)objcopy
SZ := $(CROSS_COMPILE)size

# MCU specific flags
MCU := -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# Optimization and debug flags
DEBUG := 1
ifeq ($(DEBUG), 1)
OPT := -O0 -g3
else
OPT := -Os -g0
endif

# C compiler flags
CFLAGS := $(MCU)
CFLAGS += -Wall -fdata-sections -ffunction-sections
CFLAGS += $(OPT)
CFLAGS += -MMD -MP
CFLAGS += -std=c11

# ASM compiler flags
ASFLAGS := $(MCU)
ASFLAGS += -x assembler-with-cpp
ASFLAGS += $(OPT)

# Linker flags
LDFLAGS := $(MCU)
LDFLAGS += -specs=nano.specs
LDFLAGS += -T platform/stm32f429/STM32F429XX_FLASH.ld
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map,--cref
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--print-memory-usage

# Preprocessor definitions
DEFS := -DUSE_HAL_DRIVER -DSTM32F429xx
ifeq ($(DEBUG), 1)
DEFS += -DDEBUG
endif

# Include paths
INCLUDES := -Iplatform
INCLUDES += -Iplatform/stm32f429
INCLUDES += -Iplatform/stm32f429/STM32F4xx_HAL_Driver/Inc
INCLUDES += -Iplatform/stm32f429/CMSIS/Device/ST/STM32F4xx/Include
INCLUDES += -Iplatform/stm32f429/CMSIS/Include
INCLUDES += -Iapp
INCLUDES += -Idrivers/led
INCLUDES += -Idrivers/common
INCLUDES += -Idrivers/gpio

# Default target
all: $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).hex $(BUILD_DIR)/$(PROJECT).bin
	@echo "Build complete!"
	@$(SZ) $(BUILD_DIR)/$(PROJECT).elf

# Include Kbuild system
include scripts/Kbuild.include

# Build directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

flash:
	openocd -f interface/cmsis-dap.cfg -f target/stm32f4x.cfg -c "program $(BUILD_DIR)/$(PROJECT).elf verify reset exit"

# Clean build
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete!"

# Help
help:
	@echo "Usage:"
	@echo "  make              - Build the project"
	@echo "  make flash        - download program to flash"
	@echo "  make clean        - Clean build files"
	@echo "  make help         - Show this help message"

.PHONY: all clean help