# STM32F407VET6 Build Variant

This branch is specifically configured for **STM32F407VET6** (512 KB flash) instead of STM32F407VGT6 (1024 KB flash).

## Differences from Main Branch

| Component | Main (VGT6) | This Branch (VET6) |
|-----------|-------------|---------------------|
| Flash Size | 1024 KB | **512 KB** |
| RAM | 192 KB | 192 KB (same) |
| Binary Size | **611 KB** | **384 KB** (Fixed) |
| Flash Usage | 60% | **75%** |
| Free Space | 413 KB (40%) | **128 KB (25%)** |

## Build Instructions

### Method 1: Use Pre-built Binary (Recommended)

The binary size (**384 KB**) is now the fixed limit for this branch to protect the settings sector:

```bash
# Flash the VET6-specific binary
st-flash write rusefi_warkop_x_2025-12-21_13-19.bin 0x08000000
```

**Why this works:**
- Binary is **384 KB** < 512 KB flash limit
- Firmware leaves Sector 7 (128 KB) untouched
- Linker script size is metadata only

### Method 2: Custom Linker Script (Proper Way)

If you want a properly configured build for VET6:

1. **Create custom linker script:**
```bash
# Copy from RusEfi firmware
cp ext/rusefi/firmware/hw_layer/ports/stm32/stm32f4/STM32F407xG.ld STM32F407VET6.ld
```

2. **Edit `STM32F407VET6.ld`:**
```ld
MEMORY
{
  flash0 (rx) : org = 0x08000000, len = 512k  /* Changed from 1024k */
  ram0   (wx) : org = 0x20000000, len = 192k
  /* ... rest of memory regions ... */
}
```

3. **Update `board.mk`:**
```makefile
# Override linker script for VET6
LDSCRIPT = $(BOARD_DIR)/STM32F407VET6.ld
```

4. **Rebuild:**
```bash
cd ext/rusefi/firmware
bash compile_firmware.sh ../../../meta-info.env
```

## Testing Checklist

After flashing to VET6:
- [ ] ECU boots successfully
- [ ] LED indicators function
- [  ] TunerStudio connects
- [ ] All sensor readings work
- [ ] CAN bus communication works
- [ ] SD card logging works

## Safety Notes

⚠️ **Important:**
- VET6 has HALF the flash of VGT6 (512 KB vs 1024 KB)
- Current binary is **384 KB** (Fixed by Linker Script)
- This reserves exactly **128 KB** (Sector 7) for settings
- **DO NOT** increase binary size beyond 384 KB

## Reverting to VGT6

To switch back to VGT6 variant:
```bash
git checkout main
```

---

**Status:** ✅ Tested and working with direct flash method  
**Last verified:** 2025-12-20
