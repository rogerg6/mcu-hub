# mcu-hub Kconfig Configuration Guide

## Overview

The mcu-hub project now supports a Linux kernel-style Kconfig configuration system. You can selectively compile modules and drivers through configuration files.

## Configuration Commands

### make menuconfig
Launch the interactive configuration menu (recommended):
```bash
make menuconfig
```
- Uses the native menuconfig from kconfig-frontends if installed
- Otherwise uses the project's built-in Python simplified menuconfig

### make defconfig
Create default configuration:
```bash
make defconfig
```

### make savedefconfig
Save minimal configuration to defconfig file:
```bash
make savedefconfig
```

### make oldconfig
Update current configuration:
```bash
make oldconfig
```

### make olddefconfig
Update old defaults to new defaults:
```bash
make olddefconfig
```

## Kbuild Syntax

### obj-${CONFIG_XXX}
Use conditional compilation syntax in Kbuild files:

```makefile
# drivers/Kbuild
obj-$(CONFIG_DRIVER_GPIO) += gpio/gpio_stm32f429.c
obj-$(CONFIG_DRIVER_LED) += led/led.c
```

When `CONFIG_DRIVER_GPIO=y`, the file will be compiled; otherwise it will not be included.

### Directory Selection
You can also selectively compile entire directories:

```makefile
# Top-level Kbuild
obj-y += app/
obj-y += drivers/
obj-y += platform/
```

## Configuration Options

### Platform Selection
- `CONFIG_PLATFORM_STM32F429` - STM32F429 Cortex-M4 platform
- `CONFIG_PLATFORM_STM32F1` - STM32F1 Cortex-M3 platform
- `CONFIG_PLATFORM_ESP32` - ESP32 Xtensa platform
- `CONFIG_PLATFORM_STC89` - STC89 8051 platform

### Toolchain Configuration
- `CONFIG_CROSS_COMPILE_ARM_NONE_EABI` - ARM GCC toolchain
- `CONFIG_CROSS_COMPILE_XTENSA_ESP32_ELF` - ESP32 toolchain
- `CONFIG_CROSS_COMPILE_SDCC` - SDCC 8051 toolchain
- `CONFIG_CROSS_COMPILE_CUSTOM` - Custom toolchain prefix
- `CONFIG_TOOLCHAIN_PATH` - Optional toolchain path

### Driver Selection
- `CONFIG_DRIVER_GPIO` - Enable GPIO driver
- `CONFIG_DRIVER_LED` - Enable LED driver
- `CONFIG_DRIVER_UART` - Enable UART driver
- `CONFIG_DRIVER_I2C` - Enable I2C driver
- `CONFIG_DRIVER_SPI` - Enable SPI driver

### Build Options
- `CONFIG_DEBUG_BUILD` - Debug build (optimizations disabled)
- `CONFIG_OPTIMIZE_SIZE` - Optimize for size
- `CONFIG_OPTIMIZE_SPEED` - Optimize for speed
- `CONFIG_USE_HAL_DRIVER` - Use STM32 HAL driver (ARM platforms)
- `CONFIG_USE_LL_DRIVER` - Use STM32 LL driver (ARM platforms)
- `CONFIG_STD_LIBC` - Standard library: nano or standard

### Platform-Specific Options

#### STM32F429
- `CONFIG_STM32F429_CHIP` - Chip variant (e.g., STM32F429IG)
- `CONFIG_STM32F429_CLOCK` - System clock in MHz

#### STM32F1
- `CONFIG_STM32F1_CHIP` - Chip variant (e.g., STM32F103ZG)
- `CONFIG_STM32F1_CLOCK` - System clock in MHz

#### ESP32
- `CONFIG_ESP32_CHIP` - Chip variant (e.g., ESP32-WROOM-32)
- `CONFIG_ESP32_CPU_FREQ` - CPU frequency in MHz

#### STC89
- `CONFIG_STC89_CHIP` - Chip variant (e.g., STC89C52RC)
- `CONFIG_STC89_CLOCK` - Crystal frequency in MHz

## Usage Examples

1. Configure the project:
```bash
make menuconfig
```

2. Build the project:
```bash
make
```

3. Clean build:
```bash
make clean
```

4. Flash to device:
```bash
make flash
```

## Configuration Files

- `.config` - Current configuration (read by make)
- `defconfig` - Default configuration template
- `Kconfig` - Configuration option definitions

## Dependencies

Some options have dependencies. For example, `CONFIG_DRIVER_GPIO` depends on the platform configuration. If dependencies are not enabled, sub-options will be disabled.

## Automatic Toolchain and Macro Configuration

The build system automatically configures the toolchain and compiler macros based on your Kconfig selections:

- **Cross Compiler**: Automatically selected based on platform
- **Architecture Flags**: Automatically set (e.g., `-mcpu=cortex-m4`)
- **Core Configuration**: Automatically set (e.g., Cortex-M4, FPU)
- **Preprocessor Definitions**: Automatically added (e.g., `-DSTM32F429xx`)
- **Linker Script**: Automatically selected based on platform
- **Standard Library**: Automatically configured

No source code modifications required - all platform-specific configurations are managed through Kconfig.

## Help

View current configuration and available commands:
```bash
make help
```