# Panduan Optimasi Firmware rusEFI

Jadi gini, rusEFI itu punya banyak banget fitur. Masalahnya, kalo semua fitur di-enable, bisa makan flash sampe 800KB lebih. Padahal STM32F407VET6 kita cuma punya 512KB.

Solusinya: disable fitur yang gak kepake. Ini list lengkapnya.


## Yang Udah Kita Disable di Warkop-X

Ini fitur-fitur yang udah di-matiin di board.mk. Lumayan hemat ~300KB flash!

| Fitur | Hemat Flash | Hemat RAM | Aman di-disable? |
|-------|-------------|-----------|------------------|
| `EFI_LUA` | 40-60 KB | 60 KB CCM | Ya (kalo gak pake script Lua) |
| `EFI_ELECTRONIC_THROTTLE_BODY` | 15-20 KB | 2-3 KB | Ya (throttle kabel doang) |
| `EFI_BOOST_CONTROL` | 10-15 KB | 1-2 KB | Ya (mesin NA) |
| `EFI_VVT` | 5-8 KB | 1 KB | Ya (gak ada hardware VVT) |
| `EFI_ANTILAG_SYSTEM` | 5-10 KB | 500 B | Ya (motor harian) |
| `EFI_USB_MASS_STORAGE` | 8-12 KB | 2 KB | Hati-hati (akses SD via USB) |
| `EFI_STORAGE_SD` | 15-20 KB | 4 KB | Hati-hati (logging ke SD card!) |
| `EFI_GDI` | 10-15 KB | 1-2 KB | Ya (port injection) |
| `EFI_LAUNCH_CONTROL` | 3-5 KB | 500 B | Bisa di-enable kalo drag racing |
| `EFI_HPFP` | 8-12 KB | 1 KB | Ya (gak ada high pressure pump) |
| `EFI_LOGIC_ANALYZER` | 2-3 KB | 1 KB | Ya (tool buat debug) |
| `EFI_DYNO_VIEW` | 2-3 KB | 500 B | Berguna kalo mau dyno tune |
| `EFI_TOOTH_LOGGER` | 3-5 KB | 2 KB | Berguna buat debug trigger |
| `EFI_TEXT_LOGGING` | 5-8 KB | 2 KB | Ya (binary log udah cukup) |
| `EFI_WS2812` | 2-3 KB | 500 B | Ya (gak ada RGB LED) |
| `EFI_DAC` | 1-2 KB | 200 B | Ya (gak perlu DAC output) |
| `EFI_WIFI` | 15-20 KB | 5 KB | Ya (gak ada module WiFi) |
| `EFI_ETHERNET` | 20-30 KB | 8 KB | Ya (gak ada Ethernet) |
| `EFI_BOSCH_YAW` | 2-3 KB | 500 B | Ya (gak ada yaw sensor) |
| `EFI_CAN_SERIAL` | 3-5 KB | 1 KB | Ya (CAN bus beda sama CAN serial) |
| `EFI_CAN_GPIO` | 2-3 KB | 500 B | Ya (gak pake CAN GPIO) |
| `EFI_VERBOSE_CAN_TX` | 1-2 KB | 1 KB | Ya (verbose logging) |

**Total hemat: ~220-300 KB Flash, ~90-100 KB RAM**

---

## ✅ Currently ENABLED di Warkop-X ECU

| Feature Flag | Flash Cost | RAM Cost | Status | Notes |
|--------------|------------|----------|--------|-------|
| `EFI_CAN_SUPPORT` | 15-20 KB | 3-5 KB | ✅ ON | **PENTING** untuk dashboard CAN |
| `EFI_PROD_CODE` | - | - | ✅ ON | Production build (bukan simulator) |
| `EFI_ENGINE_CONTROL` | - | - | ✅ ON | Core engine control |
| `EFI_SHAFT_POSITION_INPUT` | - | - | ✅ ON | Trigger wheel decoder |
| `EFI_IDLE_CONTROL` | 5-8 KB | 1-2 KB | ✅ ON | Idle valve control |
| `EFI_TUNER_STUDIO` | 10-15 KB | 2-3 KB | ✅ ON | TunerStudio communication |
| `EFI_WIDEBAND_FIRMWARE_UPDATE` | 20-30 KB | 1 KB | ❌ **OFF** | AFR sensor firmware update |

---

## ⚙️ Optional Features (Bisa di-Toggle)

### 🔥 **Engine Sniffer / Oscilloscope**

```makefile
# Disable untuk hemat RAM ~10-15KB
DDEFS += -DEFI_ENGINE_SNIFFER=FALSE
DDEFS += -DWAVE_CHART_MODE_SIZE=0
```

**Trade-off:** Hilang visual waveform di TunerStudio Tools → Engine Sniffer

---

### 🎚️ **Closed Loop Fuel Correction (STFT/LTFT)**

Tidak bisa disable via flag (part of core), tapi bisa disable via config:

```cpp
// In board_configuration.cpp
engineConfiguration->fuelClosedLoopCorrectionEnabled = false;
```

**Trade-off:** Tidak ada auto-correction AFR, harus tuning VE table manual yang akurat.

---

### 📊 **Cylinder Count Optimization**

```makefile
# Untuk single cylinder
DDEFS += -DMAX_CYLINDER_COUNT=1
```

**Savings:** ~2-5 KB RAM (reduce buffer sizes)

---

### 🔢 **Buffer Size Reduction**

```makefile
# Oscilloscope buffer (default 2048)
DDEFS += -DWAVE_CHART_MODE_SIZE=512

# Tooth logger (default 800)
DDEFS += -DTOOTH_DATA_LENGTH=200
DDEFS += -DTOOTH_PACKET_SIZE=32
```

**Savings:** ~5-10 KB RAM

---

## 🛡️ **CRITICAL Features - JANGAN DISABLE!**

| Feature | Why Critical |
|---------|--------------|
| `EFI_ENGINE_CONTROL` | Core engine logic |
| `EFI_SHAFT_POSITION_INPUT` | Trigger wheel decoder |
| `EFI_TUNER_STUDIO` | Cannot configure without TS |
| `EFI_PROD_CODE` | Production firmware build |
| `EFI_INTERNAL_ADC` | Read sensors (TPS, CLT, etc.) |
| `EFI_GPIO_HARDWARE` | Control outputs (injectors, coils) |

---

## 🏍️ **Motorcycle-Specific Optimizations**

### **Recommended Disables for Motorcycle ECU:**

```makefile
# === ALREADY DISABLED ===
-DEFI_BOOST_CONTROL=FALSE       # No turbo
-DEFI_VVT=FALSE                 # No VVT
-DEFI_GDI=FALSE                 # Port injection
-DEFI_HPFP=FALSE                # No high-pressure pump

# === COULD DISABLE ===
-DEFI_LAUNCH_CONTROL=FALSE      # Unless drag racing
-DEFI_DYNO_VIEW=FALSE           # Unless tuning on dyno
-DEFI_TOOTH_LOGGER=FALSE        # After trigger is confirmed working

# === KEEP ENABLED ===
-DEFI_CAN_SUPPORT=TRUE          # Dashboard communication
-DEFI_IDLE_CONTROL=TRUE         # Auto idle
-DEFI_TUNER_STUDIO=TRUE         # Tuning software
```

---

## 📦 **Feature Size Reference**

### **Large Features (>20KB Flash):**

- Lua Scripting: 40-60 KB
- USB Mass Storage: 8-12 KB + FAT driver
- Wideband FW Update: 20-30 KB
- Ethernet: 20-30 KB
- WiFi: 15-20 KB
- Electronic Throttle: 15-20 KB

### **Medium Features (10-20KB Flash):**

- Boost Control: 10-15 KB
- GDI: 10-15 KB
- HPFP: 8-12 KB
- SD Card (FatFS): 15-20 KB

### **Small Features (<10KB Flash):**

- VVT: 5-8 KB
- Antilag: 5-10 KB
- Launch Control: 3-5 KB
- Text Logging: 5-8 KB
- Tooth Logger: 3-5 KB
- Engine Sniffer: 3-5 KB
- CAN Serial: 3-5 KB
- DAC: 1-2 KB
- WS2812 LED: 2-3 KB

---

## 🔍 **How to Check Current Flags**

### **1. Check board.mk:**

```bash
grep "^DDEFS" board.mk
```

### **2. Check compile output:**

Saat build, lihat line:
```
-DEFI_LUA=FALSE -DEFI_BOOST_CONTROL=FALSE ...
```

### **3. Check generated header:**

```bash
grep "EFI_" generated/controllers/generated/rusefi_generated_warkop_x.h
```

---

## 💡 **Rekomendasi untuk Warkop-X:**

### **Current Setup (SUDAH OPTIMAL):**

✅ **Good balance** antara fitur dan flash/RAM usage

### **Bisa Disable Lagi (Jika Perlu):**

1. **EFI_ENGINE_SNIFFER** → Save ~10KB RAM (jika tidak pakai oscilloscope)
2. **EFI_TOOTH_LOGGER** → Save ~3KB Flash + 2KB RAM (setelah trigger verified)
3. **EFI_DYNO_VIEW** → Save ~2KB Flash (jika tidak dyno tuning)

### **Jangan Disable:**

- ❌ `EFI_STORAGE_SD` sudah disabled → **Tidak bisa SD card logging**
- ❌ `EFI_LAUNCH_CONTROL` → Bisa berguna untuk drag racing
- ❌ `EFI_CAN_SUPPORT` → **PENTING** untuk dashboard

---

## 📝 **Template untuk Extreme Optimization:**

Jika benar-benar butuh hemat maksimal:

```makefile
# === DISABLE SEMUA NON-ESSENTIAL ===
DDEFS += -DEFI_LUA=FALSE
DDEFS += -DEFI_ELECTRONIC_THROTTLE_BODY=FALSE
DDEFS += -DEFI_BOOST_CONTROL=FALSE
DDEFS += -DEFI_VVT=FALSE
DDEFS += -DEFI_ANTILAG_SYSTEM=FALSE
DDEFS += -DEFI_LAUNCH_CONTROL=FALSE
DDEFS += -DEFI_GDI=FALSE
DDEFS += -DEFI_HPFP=FALSE
DDEFS += -DEFI_STORAGE_SD=FALSE
DDEFS += -DEFI_USB_MASS_STORAGE=FALSE
DDEFS += -DEFI_LOGIC_ANALYZER=FALSE
DDEFS += -DEFI_TOOTH_LOGGER=FALSE
DDEFS += -DEFI_ENGINE_SNIFFER=FALSE
DDEFS += -DEFI_DYNO_VIEW=FALSE
DDEFS += -DEFI_TEXT_LOGGING=FALSE
DDEFS += -DEFI_WS2812=FALSE
DDEFS += -DEFI_DAC=FALSE
DDEFS += -DEFI_WIFI=FALSE
DDEFS += -DEFI_ETHERNET=FALSE
DDEFS += -DEFI_CAN_SERIAL=FALSE
DDEFS += -DEFI_CAN_GPIO=FALSE
DDEFS += -DEFI_VERBOSE_CAN_TX=FALSE
DDEFS += -DEFI_BOSCH_YAW=FALSE
DDEFS += -DEFI_WIDEBAND_FIRMWARE_UPDATE=FALSE

# === REDUCE BUFFER SIZES ===
DDEFS += -DWAVE_CHART_MODE_SIZE=0
DDEFS += -DTOOTH_DATA_LENGTH=0
DDEFS += -DMAX_CYLINDER_COUNT=1

# === KEEP ESSENTIALS ===
DDEFS += -DEFI_ENGINE_CONTROL=TRUE
DDEFS += -DEFI_SHAFT_POSITION_INPUT=TRUE
DDEFS += -DEFI_IDLE_CONTROL=TRUE
DDEFS += -DEFI_CAN_SUPPORT=TRUE
DDEFS += -DEFI_TUNER_STUDIO=TRUE
```

**Expected Savings:** ~300KB Flash, ~100KB RAM

---

**Status Warkop-X saat ini: SUDAH SANGAT OPTIMAL! ✅**
