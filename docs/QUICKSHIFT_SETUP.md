# Quickshift Sensor Pin Options - Warkop X ECU

## 📌 Rekomendasi Pin untuk Quickshift Sensor

Quickshift sensor adalah **switch digital** yang trigger saat shift lever digerakkan. Sensor ini perlu digital input dengan interrupt capability untuk response time yang cepat.

---

## 🎯 **Option 1: AC Input (RECOMMENDED)** ⭐⭐⭐⭐⭐

**Pin:** `PB0` (EFI_ADC_8)  
**Current Use:** AC Pressure Switch  
**Type:** Analog input (bisa dipakai sebagai digital)

### Kenapa Bagus:
- ✅ AC input jarang dipakai di motor (lebih penting quickshift!)
- ✅ Pin sudah di-configure dan ready
- ✅ EXTI line 0 - fast interrupt response
- ✅ Tidak bentrok dengan fitur critical

### Cara Enable:
```cpp
// di board_configuration.cpp
// Ganti dari AC input jadi quickshift
engineConfiguration->tcuInputSpeedSensorPin = Gpio::B0;  // Quickshift input
// atau untuk shift torque reduction:
engineConfiguration->torqueReductionTriggerPin = Gpio::B0;
```

---

## 🎯 **Option 2: Analog Reserve 1** ⭐⭐⭐⭐⭐

**Pin:** `PB1` (EFI_ADC_9)  
**Current Use:** Analog Reserve (TIDAK DIPAKAI!)  
**Type:** Analog input (bisa digital)

### Kenapa Bagus:
- ✅ Pin **TIDAK DIPAKAI** sama sekali sekarang
- ✅ EXTI line 1 - fast interrupt
- ✅ Paling aman - zero conflict!
- ✅ Tetap ada 9 ADC channels lain untuk sensor analog

### Cara Enable:
```cpp
// di board_configuration.cpp
engineConfiguration->torqueReductionTriggerPin = Gpio::B1;  // Quickshift
```

---

## 🎯 **Option 3: Clutch Input (ALTERNATIVE)**

**Pin:** `PE13`  
**Current Use:** Clutch Switch  
**Type:** Digital switch input

### Kenapa Bisa:
- ✅ Clutch switch bisa share dengan quickshift
- ✅ Logic: Quickshift = clutch di-tekan + shift
- ⚠️ Tapi kurang ideal - quickshift sensor di shifter, bukan di clutch lever

### Cara Enable (Dual Purpose):
```cpp
// Pakai clutch input untuk detect shift ready state
engineConfiguration->clutchDownPin = Gpio::E13;
engineConfiguration->torqueReductionTriggerPin = Gpio::E13;  // Share
```

---

## 🎯 **Option 4: Tambah Pin Baru (BEST - kalau ada spare pin)**

Jika hardware ECU Anda punya spare pin yang belum di-map:

### Pin Digital GPIO yang Available:
- `PE0`, `PE1`, `PE2`, `PE3`, `PE4` (jika tidak dipakai untuk lain)
- `PD5`, `PD6` (jika tidak dipakai)
- `PC6` (jika tidak dipakai)

### Cara Enable:
```cpp
// Pilih salah satu pin spare
engineConfiguration->torqueReductionTriggerPin = Gpio::E0;  // Contoh
```

---

## 🔌 **Wiring Quickshift Sensor**

### Sensor Type: Normally Open (NO) Switch

```
Quickshift Sensor Wiring:
┌─────────────┐
│  Sensor     │
│  (NO Type)  │
│             │
│  Pin 1 ─────┼──── +5V (dari ECU)
│  Pin 2 ─────┼──── Signal pin (PB0 atau PB1)
│  Ground ────┼──── GND (dari ECU)
└─────────────┘

Internal pull-down di ECU:
Signal pin ──[10kΩ]── GND

Logic:
- Shift lever TIDAK di-tekan: 0V (LOW)
- Shift lever DI-TEKAN: 5V (HIGH) → Trigger ignition cut!
```

---

## ⚙️ **Configuration di TunerStudio**

Setelah pin dikonfigurasi, set di TunerStudio:

1. **Enable Shift Torque Reduction:**
   - Go to: `Shift Torque Reduction` menu
   - Enable: `Use Shift Torque Reduction`

2. **Set Pin:**
   - `Shift Input Pin`: Pilih pin yang Anda pakai (B0/B1)

3. **Timing Parameters:**
   - `Cut Duration`: 50-100 ms (coba mulai dari 80ms)
   - `Cut Type`: `Ignition Cut` atau `Fuel Cut` atau `Both`
   - `RPM Threshold`: 3000 RPM (aktif di atas RPM ini)
   - `TPS Threshold`: 50% (aktif saat gas buka >50%)

4. **Safety:**
   - `Max Cut RPM`: 11000 RPM (jangan cut di rev limit)

---

## 🏍️ **Hardware: Quickshift Sensor Options**

### Commercial Sensors:
- **Translogic QS-Pro**: $150-200 (plug & play)
- **Cordona Quickshifter**: $100-150
- **Generic Motorcycle QS**: $30-80 (eBay/AliExpress)

### DIY Option:
- **Micro Switch**: $5-10
- Mount di shift linkage
- Adjust gap: 1-2mm travel trigger

---

## 📋 **Implementation Checklist**

### Software:
- [ ] Choose pin (recommend: PB1 - Analog Reserve)
- [ ] Update `board_configuration.cpp`
- [ ] Update `connectors/custom_firmware.yaml`
- [ ] Recompile firmware
- [ ] Flash ke ECU

### Hardware:
- [ ] Beli quickshift sensor
- [ ] Pasang di shift linkage
- [ ] Wire ke ECU pin yang dipilih
- [ ] Wire 5V & GND

### Tuning:
- [ ] Set cut duration (start 80ms)
- [ ] Test shift di berbagai RPM
- [ ] Fine-tune timing untuk smoothness
- [ ] Verify no false triggers

---

## 🎯 **Rekomendasi Final**

**PAKAI PIN: `PB1` (EFI_ADC_9 - Analog Reserve 1)** ✅

**Alasan:**
1. Pin TIDAK DIPAKAI sekarang
2. Zero conflict dengan fitur lain
3. Fast interrupt (EXTI1)
4. Mudah wire (ADC header di board)
5. Masih ada 9 ADC channels lain

**Config yang perlu ditambahkan:**
```cpp
// di board_configuration.cpp, fungsi boardTuneDefaults()
engineConfiguration->torqueReductionTriggerPin = Gpio::B1;
engineConfiguration->torqueReductionEnabled = true;
engineConfiguration->torqueReductionTime = 80;  // ms
engineConfiguration->torqueReductionIgnitionCut = 6;  // cylinders to cut
```

---

**Mau saya configure sekarang untuk pin PB1?** 🚀
