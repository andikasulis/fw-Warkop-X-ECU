# Cara Optimasi Flash & RAM di Warkop-X ECU

Bacaan cepet kalo mau hemat flash/RAM atau enable fitur tertentu.

## TL;DR

Setup current udah optimal. Total hemat ~300KB flash. Gak perlu diapa-apain lagi kecuali lu butuh fitur khusus.

```
Flash: 300KB/512KB (58% used) 
RAM:   ~90KB/128KB (70% used)
Free:  ~84KB flash (safety margin)
```

## Fitur Yang Udah Di-Disable

Ini yang udah di-matiin di `board.mk`:

- Lua scripting (40-60KB)
- Electronic throttle (15-20KB) 
- Boost control (10-15KB)
- VVT (5-8KB)
- SD card logging (15-20KB)
- WiFi/Ethernet (35-50KB)
- 15+ fitur lainnya

Total: **~300KB saved**

## Kalo Mau Enable Fitur Tertentu

### SD Card Logging

Butuh ini kalo mau log data ke SD card.

Edit `board.mk`:
```makefile
# Enable SD card
DDEFS += -DEFI_STORAGE_SD=TRUE
DDEFS += -DEFI_USB_MASS_STORAGE=TRUE  # optional, buat akses via USB
```

Cost: +25-30KB flash

### Launch Control

Buat drag racing.

```makefile
DDEFS += -DEFI_LAUNCH_CONTROL=TRUE
```

Cost: +3-5KB flash

### Tooth Logger

Debugging trigger wheel issues.

```makefile
DDEFS += -DEFI_TOOTH_LOGGER=TRUE
```

Cost: +3-5KB flash, +2KB RAM

## Kalo Pengen Hemat RAM Lebih

Motor single cylinder gak butuh buffer gede-gede.

### Disable Engine Sniffer

Oscilloscope di TunerStudio bakal ilang tapi hemat RAM lumayan.

```makefile
DDEFS += -DEFI_ENGINE_SNIFFER=FALSE
DDEFS += -DWAVE_CHART_MODE_SIZE=0
```

Save: ~5KB flas

h + ~15KB RAM

### Kurangin Buffer Size

```makefile
DDEFS += -DWAVE_CHART_MODE_SIZE=512      # default 2048
DDEFS += -DTOOTH_DATA_LENGTH=200         # default 800
DDEFS += -DMAX_CYLINDER_COUNT=1          # single cylinder
```

Save: ~20KB RAM

## Yang JANGAN Di-Disable

Ini critical, jangan dimatiin:

- `EFI_ENGINE_CONTROL` - core engine logic
- `EFI_SHAFT_POSITION_INPUT` - trigger decoder
- `EFI_TUNER_STUDIO` - gak bisa tuning tanpa ini
- `EFI_CAN_SUPPORT` - dashboard CAN bus
- `EFI_IDLE_CONTROL` - auto idle
- `EFI_INTERNAL_ADC` - baca sensor (TPS, CLT, dll)
- `EFI_GPIO_HARDWARE` - kontrol output (injector, coil)

## Cara Check Flash/RAM Usage

Setelah build, liat output `make`:

```
   text    data     bss     dec     hex filename
 300000   12000   50000  362000   58730 rusefi.elf
```

- `text` = code (flash)
- `data` + `bss` = RAM usage

Atau liat di GitHub Actions build log.

## Reference Lengkap

Liat file lainnya kalo butuh detail:
- `FEATURE_OPTIMIZATION_GUIDE.md` - semua feature flags
- `CURRENT_OPTIMIZATION_STATUS.md` - comparison detail

## Kesimpulan

Current setup udah bagus. Gak perlu optimize lebih kecuali:
1. Butuh SD logging
2. Mau drag racing (launch control)
3. Debugging trigger (tooth logger)
4. Pengen max RAM (disable sniffer)

Sisanya udah optimal.
