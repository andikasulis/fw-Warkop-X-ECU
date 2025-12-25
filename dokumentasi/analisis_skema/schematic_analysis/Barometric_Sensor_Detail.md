# Sensor Barometrik (Baro Sensor) - Detail Lengkap

## Identifikasi

**Designator**: U9  
**Part Number**: LPS25HB  
**Package**: HLGA-10 (2.5mm x 2.5mm, pitch 0.6mm)  
**Manufacturer**: STMicroelectronics  
**LCSC**: C94049

---

## Lokasi di PCB

**Posisi**: X = 177.325mm, Y = -75.8mm  
**Layer**: Top  
**Rotasi**: 0° (tidak diputar)  
**Halaman Skema**: Halaman 7 (Sensor & Lain-lain)

---

## Fungsi

**Sensor Tekanan Barometrik / Atmospheric Pressure Sensor**

- Mengukur tekanan udara atmosphere (tekanan barometrik)
- Range: 260 hingga 1260 mbar (hPa)
- Akurasi: ±1.5 mbar
- Digunakan untuk:
  - **Kompensasi altitude** (ketinggian)
  - **Koreksi MAP sensor** untuk engine tuning
  - **Weather monitoring**

---

## Interface & Komunikasi

**Digital Interface**: I2C (Inter-Integrated Circuit)

### Pin I2C:
- **SCL** (Serial Clock): Label `I2C_SCL` → ke MCU PB6
- **SDA** (Serial Data): Label `I2C_SDA` → ke MCU PB7

### I2C Address:
- Default: 0x5C atau 0x5D (tergantung konfigurasi pin SDO/SA0)

### Pull-Up Resistors:
- **R35**: 2.7kΩ (pada line SCL)
- **R36**: 2.7kΩ (pada line SDA)  
- **R91**: 2.7kΩ (tambahan pull-up)

**Catatan**: I2C membutuhkan pull-up resistors untuk komunikasi yang stable.

---

## Power Supply

**VDD (Power)**: +3.3V dari regulator U3  
**VSS (Ground)**: GND

**Decoupling Capacitor**:
- C? (100nF ceramic, 0603) - **harus dekat IC** untuk filtering noise

**Consumption**:
- Active mode: ~12.5 µA
- Power down: ~1 µA

---

## Rangkaian Lengkap di Halaman 7

```
+3V3 ──┬── VDD (U9)
       │
       └── [C 100nF] ── GND

MCU PB6 (I2C_SCL) ──[R35 2.7k]── +3V3
                    │
                    └── SCL (U9)

MCU PB7 (I2C_SDA) ──[R36 2.7k]── +3V3
                    │
                    └── SDA (U9)

GND ── VSS (U9)
```

---

## Cara Kerja

1. **MCU mengirim request** via I2C ke address sensor
2. **Sensor mengukur** tekanan atmosfer internal
3. **Sensor mengirim data** digital (24-bit) kembali via I2C
4. **MCU memproses** data:
   - Convert ke mbar/hPa
   - Hitung altitude (jika perlu)
   - Gunakan untuk koreksi MAP sensor

---

## Penggunaan di ECU

### Altitude Compensation (Kompensasi Ketinggian):

**Kenapa penting?**
- Tekanan udara berbeda di ketinggian berbeda
- Sea level: ~1013 mbar
- Dataran tinggi 1000m: ~898 mbar
- Puncak gunung 3000m: ~700 mbar

**Efek ke Engine**:
- Udara lebih tipis = kurang oksigen
- Perlu adjustment fuel injection
- Perlu timing adjustment

**Rumus sederhana**:
```
Altitude (m) ≈ 44330 × (1 - (P/P0)^0.1903)
Dimana:
  P = Tekanan saat ini (dari LPS25HB)
  P0 = Tekanan standard (1013.25 mbar)
```

### MAP Sensor Correction:

**MAP sensor** mengukur tekanan intake manifold:
- Absolute pressure di intake
- Tapi perlu reference = tekanan atmosfer
- **Baro sensor** sebagai reference

**Calculation**:
```
Vacuum / Boost = MAP - Baro
Contoh:
  MAP = 800 mbar
  Baro = 1000 mbar (sea level)
  → Vacuum = -200 mbar (engine sedang vacuum)

  MAP = 1500 mbar
  Baro = 1000 mbar
  → Boost = +500 mbar = 0.5 bar boost!
```

---

## Software Driver

### Initialization (rusEFI firmware):

```cpp
// LPS25HB I2C initialization
#define LPS25HB_ADDR 0x5C

void initBaroSensor() {
    // Configure I2C bus
    i2c_init(I2C1, 100000); // 100kHz
    
    // Check WHO_AM_I register (should return 0xBD)
    uint8_t whoami = i2c_read_reg(LPS25HB_ADDR, 0x0F);
    
    // Configure sensor
    i2c_write_reg(LPS25HB_ADDR, 0x20, 0x90); // CTRL_REG1: Power on, 1Hz
}

float readBaroPressure() {
    // Read 24-bit pressure data
    uint8_t pxl = i2c_read_reg(LPS25HB_ADDR, 0x28);
    uint8_t pl = i2c_read_reg(LPS25HB_ADDR, 0x29);
    uint8_t ph = i2c_read_reg(LPS25HB_ADDR, 0x2A);
    
    int32_t pressure_raw = (ph << 16) | (pl << 8) | pxl;
    float pressure_mbar = pressure_raw / 4096.0; // LSB/mbar
    
    return pressure_mbar;
}
```

---

## Dalam Panduan KiCad

Anda akan menemukan sensor ini di:

**Panduan_Lengkap_KiCad_ECU.md** - Halaman 7, Langkah 2:

> ### U9: LPS25HB (Barometric Pressure Sensor)
> 
> **Fungsi**: Ukur tekanan udara (untuk koreksi ketinggian)
>
> **Cara:**
> 1. Tekan **A**
> 2. Ketik: `LPS25HB`
> 3. Package: `ST_HLGA-10_2.5x2.5mm_P0.6mm`

---

## Checklist untuk KiCad Entry

Halaman 7:
- [ ] Place U9 (LPS25HB) dengan footprint HLGA-10
- [ ] Connect VDD ke +3V3
- [ ] Connect VSS ke GND
- [ ] Add decoupling capacitor 100nF dekat IC
- [ ] Connect SCL ke label `I2C_SCL`
- [ ] Connect SDA ke label `I2C_SDA`
- [ ] Add pull-up R35, R36, R91 (2.7kΩ) pada SCL/SDA
- [ ] Verify I2C labels di Halaman 1 (MCU pins PB6, PB7)

---

## Datasheet Reference

**STMicroelectronics LPS25HB**
- Range: 260-1260 mbar
- Resolution: 24-bit
- Interface: I2C, SPI
- Supply: 1.7V - 3.6V
- Temp range: -40°C to +85°C

**Download**: [ST.com LPS25HB Datasheet](https://www.st.com/resource/en/datasheet/lps25hb.pdf)

---

## Summary

✅ **U9 = LPS25HB = Sensor Barometrik / Baro Sensor**

- Ada di Halaman 7 skema
- Posisi PCB: 177.325, -75.8 (top layer)
- Interface: I2C (SCL/SDA ke MCU PB6/PB7)
- Fungsi: Ukur tekanan atmosfer untuk altitude compensation
- Sudah lengkap di BOM & position CSV
- Sudah di panduan KiCad Indonesia

**Jadi sensor baro SUDAH ADA dan terdokumentasi!** 🎯
