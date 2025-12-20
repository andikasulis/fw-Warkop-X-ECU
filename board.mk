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

# ========== MCU VARIANT CONFIGURATION (VET6 - 512KB Flash) ==========
# Override default VGT6 (1024K) to VET6 (512K) flash size
# This defines the correct MCU variant for linker and eliminates TunerStudio warning
DDEFS += -DSTM32F407xE
# Also define minimum flash size expected
DDEFS += -DMIN_FLASH_SIZE=524288

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
