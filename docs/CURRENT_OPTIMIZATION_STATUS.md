# Perbandingan Optimasi Firmware

Comparison antara apa yang udah di-disable vs yang masih bisa di-optimize.

---

## Udah Di-Disable

Ini yang udah di-matiin di board.mk:

| Fitur | Hemat Flash | Notes |
|-------|-------------|-------|
| Lua scripting | 40-60 KB | Udah OFF |
| Electronic throttle | 15-20 KB | Throttle kabel doang |
| Boost control | 10-15 KB | Mesin NA |
| VVT | 5-8 KB | Gak ada hardware VVT |
| Antilag | 5-10 KB | Motor harian |
| SD card | 15-20 KB | Gak bisa logging ke SD |
| USB Mass Storage | 8-12 KB | Gak bisa akses SD via USB |
| GDI | 10-15 KB | Port injection doang |
| Launch control | 3-5 KB | Bisa di-enable lagi kalo drag |
| High pressure pump | 8-12 KB | Gak ada HPFP |
| Logic analyzer | 2-3 KB | Debug tool |
| Dyno view | 2-3 KB | Gak ada dyno |
| Tooth logger | 3-5 KB | Trigger debugger |
| Text logging | 5-8 KB | Binary log udah cukup |
| RGB LED (WS2812) | 2-3 KB | Gak ada LED |
| DAC output | 1-2 KB | Gak perlu |
| WiFi | 15-20 KB | Gak ada module |
| Ethernet | 20-30 KB | Gak ada Ethernet |
| Yaw sensor | 2-3 KB | Gak ada sensor |
| SENT sensors | 3-5 KB | Gak kepake |
| CAN serial | 3-5 KB | Beda sama CAN bus |
| CAN GPIO | 2-3 KB | Gak kepake |
| Verbose CAN | 1-2 KB | Verbose logging |

**Total hemat: ~300 KB**

---

## Masih Enabled Tapi Bisa Di-Disable

### Kategori: Low Risk

Bisa dimatiin kalo butuh hemat lebih:

| Fitur | Flash | RAM | Currently |
|-------|-------|-----|-----------|
| Engine Sniffer | 3-5 KB | 10-15 KB | ON (oscilloscope di TS) |
| Wave Chart Buffer | - | 8-16 KB | 2048 (bisa dikurangin) |
| Tooth Data Buffer | - | 3-5 KB | 800 (bisa dikurangin) |

**Potential save: ~5-10 KB Flash, ~25-35 KB RAM**

Trade-off: Hilang view oscilloscope di TunerStudio

### Kategori: JANGAN Matiin

Ini critical, jangan disable:

- CAN bus support - Buat dashboard
- Idle control - Auto idle
- TunerStudio - Gak bisa tuning
- Engine control - Core logic
- Trigger decoder - Baca RPM
- ADC - Baca sensor
- GPIO - Kontrol output

---

## Comparison Table

| Fitur | Warkop-X | Default rusEFI | Notes |
|-------|----------|----------------|-------|
| Lua | OFF | ON | Keep OFF |
| E-Throttle | OFF | ON | Keep OFF (throttle kabel) |
| Boost | OFF | ON | Keep OFF (NA) |
| VVT | OFF | ON | Keep OFF |
| SD Card | OFF | ON | Bisa di-enable kalo butuh log |
| Launch Control | OFF | ON | Bisa di-enable kalo drag |
| CAN Bus | ON | ON | Must ON (dashboard!) |
| Engine Sniffer | ON | ON | Bisa di-disable (save RAM) |
| Tooth Logger | OFF | ON | Keep OFF |
| Idle Control | ON | ON | Must ON |

---

## Optimasi Tambahan (Opsional)

### 1. Kurangin Buffer Size

Belum diterapkan, bisa dicoba:

```makefile
DDEFS += -DWAVE_CHART_MODE_SIZE=512      # default: 2048
DDEFS += -DTOOTH_DATA_LENGTH=200         # default: 800
DDEFS += -DTOOTH_PACKET_SIZE=32          # default: 128
```

Impact: Save ~15-20 KB RAM

### 2. Cylinder Limit

```makefile
DDEFS += -DMAX_CYLINDER_COUNT=1          # single cylinder
```

Impact: Save ~3-5 KB RAM

### 3. Disable Engine Sniffer

```makefile
DDEFS += -DEFI_ENGINE_SNIFFER=FALSE
DDEFS += -DWAVE_CHART_MODE_SIZE=0
```

Impact: Save ~5 KB Flash + ~10-15 KB RAM  
Trade-off: No oscilloscope di TunerStudio

---

## Skenario Use Case

### Skenario 1: Current Setup (Recommended)

Keep as is. Udah optimal.

- Flash: 300KB/512KB (58%)
- RAM: ~90KB/128KB (70%)
- Semua fitur penting enable

### Skenario 2: Butuh SD Logging

Enable SD card:

```makefile
DDEFS += -DEFI_STORAGE_SD=TRUE
DDEFS += -DEFI_USB_MASS_STORAGE=TRUE    # optional
```

Compensate dengan disable Engine Sniffer:

```makefile
DDEFS += -DEFI_ENGINE_SNIFFER=FALSE
DDEFS += -DWAVE_CHART_MODE_SIZE=0
```

Net: +18KB Flash, -15KB RAM

### Skenario 3: Max RAM Optimization

Tambah ke current setup:

```makefile
DDEFS += -DEFI_ENGINE_SNIFFER=FALSE
DDEFS += -DWAVE_CHART_MODE_SIZE=0
DDEFS += -DTOOTH_DATA_LENGTH=0
DDEFS += -DMAX_CYLINDER_COUNT=1
```

Result: Save ~30 KB RAM tambahan

Trade-off: Gak ada oscilloscope, minimal debug

### Skenario 4: Drag Racing

Enable launch control:

```makefile
DDEFS += -DEFI_LAUNCH_CONTROL=TRUE
```

Impact: +3-5 KB Flash (masih muat)

---

## Budget Flash & RAM

Current:

```
Flash (512 KB Total):
├── Firmware:      ~300 KB (58%)
├── Settings:       128 KB (25%)
└── Free:           ~84 KB (16%)

RAM (128 KB Total):
├── Used:          ~90 KB (70%)
└── Free:          ~38 KB (30%)

CCM RAM (64 KB):
├── Lua Heap:        0 KB (OFF)
└── Available:      64 KB (100%)
```

---

## Kesimpulan

**Current: UDAH OPTIMAL**

Yang udah di-disable:
- 25+ fitur besar
- Hemat ~300 KB Flash
- Hemat ~100 KB RAM

Masih bisa disable lagi (opsional):
1. Engine Sniffer → +5 KB Flash, +15 KB RAM
2. Buffer reduction → +20 KB RAM
3. Cylinder limit → +5 KB RAM

Yang HARUS tetap ON:
- CAN bus (dashboard)
- Idle control
- TunerStudio
- Core engine logic

**No further optimization needed kecuali butuh fitur khusus.**
