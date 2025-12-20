# STM32F407VET6 Build Variant

This branch is specifically configured for **STM32F407VET6** (512 KB flash) instead of STM32F407VGT6 (1024 KB flash).

## Differences from Main Branch

| Component | Main (VGT6) | This Branch (VET6) |
|-----------|-------------|---------------------|
| Flash Size | 1024 KB | **512 KB** |
| RAM | 192 KB | 192 KB (same) |
| Binary Size | 297 KB | 297 KB (same) |
| Flash Usage | 29% | **58%** |
| Free Space | 727 KB (71%) | 215 KB (42%) |

## Build Instructions

### Method 1: Use Pre-built Binary (Recommended)

The binary size (297 KB) is small enough to work on VET6 without modifications:

```bash
# Flash directly using the main branch binary
st-flash write rusefi_warkop_x.bin 0x08000000
```

**Why this works:**
- Binary is 297 KB < 512 KB flash limit
- Firmware doesn't attempt to write beyond 512 KB
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
- Current binary (297 KB) fits comfortably with 42% margin
- If adding features, monitor binary size carefully
- Keep binary under 450 KB for safety

## Reverting to VGT6

To switch back to VGT6 variant:
```bash
git checkout main
```

---

**Status:** ✅ Tested and working with direct flash method  
**Last verified:** 2025-12-20
