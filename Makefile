# Makefile for mcu-hub project
# Multi-platform MCU project using Kconfig support

# Project name
PROJECT := mcuhub

# Build directory
BUILD_DIR := build

# Check if .config exists (only for build targets, not for config targets)
ifeq ($(filter menuconfig defconfig %_defconfig savedefconfig oldconfig olddefconfig clean distclean help,$(MAKECMDGOALS)),)
ifeq ($(wildcard .config),)
$(warning No .config found. Run 'make menuconfig' or 'make defconfig' first)
$(error Please run 'make menuconfig' or 'make defconfig' first)
else
# Include .config file
include .config
endif
endif

# Toolchain configuration from Kconfig
ifeq ($(CONFIG_CROSS_COMPILE_ARM_NONE_EABI),y)
CROSS_COMPILE ?= arm-none-eabi-
else ifeq ($(CONFIG_CROSS_COMPILE_XTENSA_ESP32_ELF),y)
CROSS_COMPILE ?= xtensa-esp32-elf-
else ifeq ($(CONFIG_CROSS_COMPILE_SDCC),y)
CROSS_COMPILE ?= sdcc-
else ifeq ($(CONFIG_CROSS_COMPILE_CUSTOM),y)
CROSS_COMPILE ?= $(CONFIG_CROSS_COMPILE_CUSTOM_PREFIX)
endif

# Add toolchain path if specified (non-empty and not just quotes)
TOOLCHAIN_PATH_VAL := $(patsubst "%",%,$(CONFIG_TOOLCHAIN_PATH))
ifneq ($(strip $(TOOLCHAIN_PATH_VAL)),)
CROSS_COMPILE := $(TOOLCHAIN_PATH_VAL)/$(CROSS_COMPILE)
PATH := $(TOOLCHAIN_PATH_VAL):$(PATH)
export PATH
endif

# Platform-specific toolchain setup
ifeq ($(CONFIG_CROSS_COMPILE_SDCC),y)
CC := $(CROSS_COMPILE)sdcc
AS := $(CROSS_COMPILE)as
CP := $(CROSS_COMPILE)objcopy
SZ := $(CROSS_COMPILE)size
else
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)gcc -x assembler-with-cpp
CP := $(CROSS_COMPILE)objcopy
SZ := $(CROSS_COMPILE)size
endif

# Export cross compile for sub-makes
export CC
export AS
export CP
export SZ

# MCU and architecture flags from Kconfig
MCU :=
ifeq ($(CONFIG_CORE_CORTEX_M4),y)
MCU += -mcpu=cortex-m4
endif
ifeq ($(CONFIG_CORE_CORTEX_M3),y)
MCU += -mcpu=cortex-m3
endif
ifeq ($(CONFIG_USE_FPU),y)
MCU += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
endif

# Default target (must be first target)
.PHONY: all
all: $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).hex $(BUILD_DIR)/$(PROJECT).bin
	@echo "Build complete!"
	@$(SZ) $(BUILD_DIR)/$(PROJECT).elf

# Kconfig targets
.PHONY: menuconfig defconfig savedefconfig oldconfig olddefconfig mconf conf

menuconfig: mconf
	@echo "Launching menuconfig..."
	scripts/kconfig/mconf Kconfig

defconfig: conf
	@echo "Creating default configuration from defconfig"
	@make -f scripts/kconfig.mk do_defconfig
	@cat .config

# Platform-specific defconfig targets
# Pattern rule for any platform defconfig
%_defconfig: conf
	@echo "Creating default configuration from configs/$@"
	@make -f scripts/kconfig.mk do_defconfig DEFCONFIG=$@
	@cat .config

# STM32F429 defconfig
stm32f429_defconfig: conf
	@echo "Creating default configuration from configs/stm32f429_defconfig"
	@make -f scripts/kconfig.mk do_defconfig DEFCONFIG=stm32f429_defconfig
	@cat .config

savedefconfig:
	@echo "Save minimal configuration to defconfig"
	@make -f scripts/kconfig.mk savedefconfig

oldconfig: conf
	@echo "Update current configuration"
	@make -f scripts/kconfig.mk oldconfig

olddefconfig: conf
	@echo "Update old defaults to new defaults"
	@make -f scripts/kconfig.mk olddefconfig

# Build mconf tool if not exists
mconf:
	@if [ ! -f scripts/kconfig/mconf ]; then \
		echo "Building mconf tool..."; \
		$(MAKE) -C scripts/kconfig mconf; \
	fi

# Build conf tool if not exists
conf:
	@if [ ! -f scripts/kconfig/conf ]; then \
		echo "Building conf tool..."; \
		$(MAKE) -C scripts/kconfig conf; \
	fi

# Platform directory and linker script
PLATFORM_DIR := platform/$(patsubst "%",%,$(CONFIG_PLATFORM))

# Linker script based on platform
ifeq ($(CONFIG_PLATFORM_STM32F429),y)
LINKER_SCRIPT := $(PLATFORM_DIR)/STM32F429XX_FLASH.ld
else ifeq ($(CONFIG_PLATFORM_STM32F1),y)
LINKER_SCRIPT := $(PLATFORM_DIR)/STM32F103XB_FLASH.ld
else ifeq ($(CONFIG_PLATFORM_ESP32),y)
LINKER_SCRIPT := $(PLATFORM_DIR)/esp32.ld
else ifeq ($(CONFIG_PLATFORM_STC89),y)
LINKER_SCRIPT := $(PLATFORM_DIR)/stc89.ld
else
LINKER_SCRIPT := $(PLATFORM_DIR)/$(patsubst "%",%,$(CONFIG_PLATFORM)).ld
endif

# Platform-specific compiler definitions
ifeq ($(CONFIG_PLATFORM_STM32F429),y)
DEFS += -DSTM32F429xx
endif
ifeq ($(CONFIG_PLATFORM_STM32F1),y)
DEFS += -DSTM32F103xB
endif

# Optimization and debug flags based on config
ifeq ($(CONFIG_DEBUG_BUILD),y)
OPT := -O0 -g3
else ifeq ($(CONFIG_OPTIMIZE_SIZE),y)
OPT := -Os -g0
else ifeq ($(CONFIG_OPTIMIZE_SPEED),y)
OPT := -O3 -g0
else
OPT := -O2 -g0
endif

# C compiler flags
CFLAGS := $(MCU)
CFLAGS += -Wall -fdata-sections -ffunction-sections
CFLAGS += $(OPT)
CFLAGS += -MMD -MP

# Platform-specific C flags
ifeq ($(CONFIG_ARCH_ARM),y)
CFLAGS += -std=c11
CFLAGS += -mthumb
else ifeq ($(CONFIG_ARCH_8051),y)
CFLAGS += -std=c99
CFLAGS += -mmcs51
endif

# ASM compiler flags
ASFLAGS := $(MCU)
ASFLAGS += -x assembler-with-cpp
ASFLAGS += $(OPT)

ifeq ($(CONFIG_ARCH_ARM),y)
ASFLAGS += -mthumb
endif

# Linker flags
LDFLAGS := $(MCU)
LDFLAGS += -T $(LINKER_SCRIPT)
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(PROJECT).map,--cref
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--print-memory-usage

# Preprocessor definitions based on config
ifeq ($(CONFIG_USE_HAL_DRIVER),y)
DEFS += -DUSE_HAL_DRIVER
endif
ifeq ($(CONFIG_USE_LL_DRIVER),y)
DEFS += -DUSE_LL_DRIVER
endif
ifeq ($(CONFIG_DEBUG_BUILD),y)
DEFS += -DDEBUG
endif

# Standard library configuration (only for ARM platforms)
ifneq ($(CONFIG_STD_LIBC),)
ifneq ($(filter y,$(CONFIG_PLATFORM_STM32F429) $(CONFIG_PLATFORM_STM32F1)),)
LDFLAGS += -specs=$(CONFIG_STD_LIBC).specs
endif
endif

# Include paths
INCLUDES := -Iplatform
INCLUDES += -I$(PLATFORM_DIR)

# Platform-specific include paths
ifeq ($(CONFIG_PLATFORM_STM32F429),y)
INCLUDES += -I$(PLATFORM_DIR)/STM32F4xx_HAL_Driver/Inc
INCLUDES += -I$(PLATFORM_DIR)/CMSIS/Device/ST/STM32F4xx/Include
INCLUDES += -I$(PLATFORM_DIR)/CMSIS/Include
endif
ifeq ($(CONFIG_PLATFORM_STM32F1),y)
INCLUDES += -I$(PLATFORM_DIR)/STM32F1xx_HAL_Driver/Inc
INCLUDES += -I$(PLATFORM_DIR)/CMSIS/Device/ST/STM32F1xx/Include
INCLUDES += -I$(PLATFORM_DIR)/CMSIS/Include
endif
ifeq ($(CONFIG_PLATFORM_ESP32),y)
INCLUDES += -I$(PLATFORM_DIR)/esp-idf/components
INCLUDES += -I$(PLATFORM_DIR)/esp-idf/components/esp_common/include
endif

# Common include paths
INCLUDES += -Iapp
INCLUDES += -Idrivers/led
INCLUDES += -Idrivers/common
INCLUDES += -Idrivers/gpio
INCLUDES += -Idrivers/uart
INCLUDES += -Idrivers/i2c
INCLUDES += -Idrivers/spi

# Include Kbuild system with config support (only for build targets)
ifneq ($(filter menuconfig defconfig savedefconfig oldconfig olddefconfig clean,$(MAKECMDGOALS)),)
# Skip Kbuild for config targets
else
include Makefile.kbuild
endif

# Build directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

flash:
ifeq ($(CONFIG_PLATFORM_STM32F429),y)
	openocd -f interface/cmsis-dap.cfg -f target/stm32f4x.cfg -c "program $(BUILD_DIR)/$(PROJECT).elf verify reset exit"
else ifeq ($(CONFIG_PLATFORM_STM32F1),y)
	openocd -f interface/cmsis-dap.cfg -f target/stm32f1x.cfg -c "program $(BUILD_DIR)/$(PROJECT).elf verify reset exit"
else ifeq ($(CONFIG_PLATFORM_ESP32),y)
	esptool.py --chip esp32 -p /dev/ttyUSB0 -b 460800 write_flash 0x1000 $(BUILD_DIR)/$(PROJECT).bin
else
	@echo "Flash not configured for this platform"
endif

# Clean build
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete!"

# Clean build and configuration
distclean: clean
	@rm -f .config .config.old
	@rm -rf include/config include/generated
	@echo "Distclean complete!"

# Help
help:
	@echo "Usage:"
	@echo "  make              - Build the project"
	@echo "  make menuconfig   - Configure the project using menuconfig"
	@echo "  make defconfig    - Create default configuration"
	@echo "  make savedefconfig - Save minimal configuration"
	@echo "  make oldconfig    - Update current configuration"
	@echo "  make olddefconfig - Update old defaults to new defaults"
	@echo "  make flash        - Download program to flash"
	@echo "  make clean        - Clean build files"
	@echo "  make distclean    - Clean build and configuration files"
	@echo "  make help         - Show this help message"
	@echo ""
	@echo "Current configuration:"
	@echo "  Platform: $(CONFIG_PLATFORM)"
	@echo "  Debug: $(CONFIG_DEBUG_BUILD)"

.PHONY: all clean help