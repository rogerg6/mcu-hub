# Kconfig support Makefile
# This provides config file management using kernel's mconf tool

# Create default configuration
do_defconfig:
	@echo "Creating default configuration"
	@if [ -n "$(DEFCONFIG)" ]; then \
		if [ -f configs/$(DEFCONFIG) ]; then \
			cp configs/$(DEFCONFIG) .config; \
			echo "Default configuration created from configs/$(DEFCONFIG)"; \
		else \
			echo "Error: configs/$(DEFCONFIG) file not found"; \
			exit 1; \
		fi \
	elif [ -f defconfig ]; then \
		cp defconfig .config; \
		echo "Default configuration created from defconfig"; \
	else \
		echo "Error: defconfig file not found"; \
		exit 1; \
	fi

# Save minimal configuration
savedefconfig:
	@echo "Saving minimal configuration to defconfig"
	@$(MAKE) -f scripts/kconfig.mk _savedefconfig

_savedefconfig:
	@if [ -f .config ]; then \
		cp .config defconfig; \
		echo "Configuration saved to defconfig"; \
	else \
		echo "No .config found"; \
	fi

# Update configuration
oldconfig:
	@echo "Updating configuration"
	@scripts/kconfig/conf --oldconfig Kconfig

# Update old defaults to new defaults
olddefconfig:
	@echo "Updating old defaults to new defaults"
	@scripts/kconfig/conf --olddefconfig Kconfig