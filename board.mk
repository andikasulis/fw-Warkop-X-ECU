include $(BOARD_DIR)/firmware/firmware.mk


BOARDINC += $(BOARD_DIR)/generated/controllers/generated

# defines SHORT_BOARD_NAME
include $(BOARD_DIR)/meta-info.env

# ========== MEMORY OPTIMIZATION ==========
# Disable wideband firmware update to save flash (~20-30KB)
DDEFS += -DEFI_WIDEBAND_FIRMWARE_UPDATE=FALSE

# Reserve 100 bytes RAM safety margin to prevent stack overflow
DDEFS += -DRAM_UNUSED_SIZE=100

# ========== ADC CONFIGURATION ==========
# Enable ADC2 for additional analog input channels
DDEFS += -DSTM32_ADC_USE_ADC2=TRUE

# Define STM32F407xE for VET6 variant (512KB flash instead of VGT6's 1024KB)
# The linker script will automatically use correct flash size from MCU definition
DDEFS += -DSTM32F407xE -DBOARD_EXPECTED_FLASH_SIZE=512 -DEXPECTED_BOARD_FLASH_SIZE=512 -DMIN_FLASH_SIZE=512

# Override linker script for VET6
LDSCRIPT = $(BOARD_DIR)/STM32F407VET6.ld

# ========== DISABLE HIGH IMPACT FEATURES (Save ~75-113 KB) ==========
# Disable Lua scripting (saves 40-60 KB, CAN dashboard still works!)
DDEFS += -DEFI_LUA=FALSE

# Disable Electronic Throttle Body (cable throttle only)
DDEFS += -DEFI_ELECTRONIC_THROTTLE_BODY=FALSE

# Disable Boost Control (naturally aspirated engine)
DDEFS += -DEFI_BOOST_CONTROL=FALSE

# Disable VVT control (no VVT hardware on Vixion OLD)
DDEFS += -DEFI_VVT=FALSE

# Disable Antilag System (street bike, not needed)
DDEFS += -DEFI_ANTILAG_SYSTEM=FALSE

# Disable SD Card support (saves ~15-20KB)
DDEFS += -DEFI_USB_MASS_STORAGE=FALSE -DEFI_STORAGE_SD=FALSE

# Disable GDI features (only for direct injection)
DDEFS += -DEFI_GDI=FALSE

# Disable more non-essential features (Save ~100-150KB total)
DDEFS += -DEFI_LAUNCH_CONTROL=FALSE -DEFI_HPFP=FALSE
DDEFS += -DEFI_LOGIC_ANALYZER=FALSE -DEFI_DYNO_VIEW=FALSE
DDEFS += -DEFI_TOOTH_LOGGER=FALSE -DEFI_TEXT_LOGGING=FALSE
DDEFS += -DEFI_WS2812=FALSE -DEFI_DAC=FALSE -DEFI_WIFI=FALSE -DEFI_ETHERNET=FALSE
DDEFS += -DEFI_BOSCH_YAW=FALSE -DEFI_SENT_CHANNELS_NUM=0
DDEFS += -DTRIGGER_EXTREME_LOGGING=FALSE

# ========== CAN BUS CONFIGURATION ==========
# Enable CAN bus for dashboard (adds ~15-20KB but critical for functionality)
DDEFS += -DEFI_CAN_SUPPORT=TRUE
# Keep CAN_SERIAL and CAN_GPIO disabled (not needed for basic dashboard)
DDEFS += -DEFI_CAN_SERIAL=FALSE -DEFI_CAN_GPIO=FALSE
# Disable verbose CAN TX to save RAM/Flash
DDEFS += -DEFI_VERBOSE_CAN_TX=FALSE

# ========== COMPILER OPTIMIZATIONS ==========
# Append size optimization flags (use += to preserve existing flags)
USE_OPT += -Os -fomit-frame-pointer -falign-functions=16

# Enable Link-Time Optimization (LTO) for better code size
USE_LTO = yes

# Remove unused functions and data
USE_OPT += -ffunction-sections -fdata-sections
USE_LDOPT += -Wl,--gc-sections


# ========== OPTIONAL FEATURES ==========
# Uncomment to enable knock detection (requires knock sensor + adds ~15-20KB)
# DDEFS += -DEFI_SOFTWARE_KNOCK=TRUE
# DDEFS += -DKNOCK_SPECTROGRAM=TRUE

# assign critical LED to a non-existent pin if you do not have it on your board
# good old PD14 is still the default value
# DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::I15

# EGT chip
#un-comment to enable
#DDEFS += -DEFI_MAX_31855=TRUE

#see main repo for details on this any many other optional subsystems. We have too many, one has to choose what fits into his choice of stm32
#DDEFS += -DEFI_ONBOARD_MEMS=TRUE
