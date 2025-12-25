# Panduan Lengkap KiCad untuk Pemula - ECU Schematic

## 📖 Daftar Isi
1. [Pengenalan Dasar](#pengenalan-dasar)
2. [Install KiCad](#install-kicad)
3. [Mengenal Komponen Elektronik](#mengenal-komponen-elektronik)
4. [Tutorial KiCad Dasar](#tutorial-kicad-dasar)
5. [Membuat Project ECU](#membuat-project-ecu)
6. [Page 1: MCU Core (Step by Step)](#page-1-mcu-core)
7. [Page 2-7: Sirkuit Lainnya](#page-2-7-sirkuit-lainnya)
8. [Verifikasi & Troubleshooting](#verifikasi)

---

## Pengenalan Dasar

### Apa itu Schematic?
**Schematic** = Gambar rencana sirkuit elektronik
- Seperti peta/blueprint rumah, tapi untuk elektronik
- Menunjukkan komponen apa saja yang dipakai
- Menunjukkan bagaimana komponen di-hubungkan

### Apa itu PCB?
**PCB (Printed Circuit Board)** = Papan sirkuit cetak
- Implementasi fisik dari schematic
- Tempat komponen di-solder
- Jalur tembaga menggantikan kabel

### Workflow Project Ini:
```
Schematic PDF (sumber) 
    ↓
Dokumentasi (sudah selesai)
    ↓
KiCad Schematic (yang akan kita buat) ← YOU ARE HERE
    ↓
KiCad PCB Layout
    ↓
Gerber Files (untuk pabrik)
    ↓
PCB Jadi
```

---

## Install KiCad

### Langkah 1: Download KiCad

**Untuk macOS:**
1. Buka website: https://www.kicad.org/download/macos/
2. Download versi **8.0** (stable, terbaru)
3. File akan berbentuk `.dmg` (~500-800 MB)

**Atau via Homebrew (lebih mudah):**
```bash
# Buka Terminal
brew install kicad
```

### Langkah 2: Install

1. Double-click file `.dmg`
2. Drag "KiCad" ke folder Applications
3. Buka KiCad dari Applications

### Langkah 3: First Run Setup

1. KiCad akan tanya "Configure Global Symbol Library"
   - **Pilih**: "Copy default global symbol library"
   - Klik **Next**

2. KiCad akan tanya "Configure Global Footprint Library"
   - **Pilih**: "Copy default global footprint library"  
   - Klik **Next**

3. Selesai! KiCad siap digunakan.

---

## Mengenal Komponen Elektronik

### Komponen Dasar (yang ada di project ini)

#### 1. **Resistor (R)**
- **Fungsi**: Membatasi arus listrik
- **Simbol**: Kotak atau zigzag
- **Nilai**: Ohm (Ω) - contoh 10k = 10,000 Ohm
- **Contoh di project**: R1, R2, R3 (ada ~100 resistor)

#### 2. **Capacitor (C)**
- **Fungsi**: Menyimpan energi, filter noise
- **Simbol**: Dua garis sejajar
- **Nilai**: Farad (F) - contoh 100nF, 10µF
- **Contoh di project**: C1, C2, C3 (ada ~55 capacitor)

#### 3. **IC/Chip (U)**
- **Fungsi**: Otak sirkuit (prosesor, regulator, dll)
- **Simbol**: Kotak dengan banyak pin
- **Contoh di project**: 
  - U1 = STM32F407 (microcontroller utama)
  - U3 = AMS1117 (voltage regulator 3.3V)

#### 4. **Transistor/MOSFET (Q)**
- **Fungsi**: Switch elektronik
- **Simbol**: Bentuk panah
- **Contoh di project**: Q1-Q13 (driver untuk injector, coil)

#### 5. **Diode/LED (D)**
- **Fungsi**: Arus searah, proteksi, lampu indikator
- **Simbol**: Segitiga + garis
- **Contoh di project**: D1-D34, LED1-LED3

#### 6. **Connector (J)**
- **Fungsi**: Sambungan ke dunia luar
- **Simbol**: Kotak dengan pin
- **Contoh di project**: J1-J9 (power input, USB, main connector)

#### 7. **Crystal (Y)**
- **Fungsi**: Clock/timing
- **Simbol**: Kotak dengan 2 pin
- **Contoh di project**: Y1 (8MHz), Y2 (32kHz)

---

## Tutorial KiCad Dasar

### Interface KiCad

#### Main Window
Ketika buka KiCad, akan ada beberapa icon:
- **Schematic Editor** ← Yang akan kita pakai banyak
- **PCB Editor** ← Nanti setelah schematic selesai
- **Footprint Editor**
- **Symbol Editor**

### Schematic Editor Basics

#### Menu Penting:
- **File > New Project**: Buat project baru
- **Place > Add Symbol**: Tambah komponen
- **Place > Add Wire**: Sambungkan komponen
- **Place > Add Power**: Tambah simbol power (VCC, GND)
- **Place > Add Label**: Beri nama pada net/wire

#### Shortcut Keyboard:
- **A**: Add symbol (komponen)
- **W**: Wire (kabel)
- **P**: Power symbol
- **L**: Label
- **M**: Move
- **R**: Rotate
- **Delete**: Hapus
- **Esc**: Cancel

#### Mouse:
- **Left Click**: Select
- **Right Click**: Menu
- **Middle Click + Drag**: Pan (geser view)
- **Scroll Wheel**: Zoom in/out

---

## Membuat Project ECU

### Step 1: Create New Project

1. Buka KiCad
2. Klik **File > New Project**
3. Navigate ke folder:
   ```
   ~/Documents/_DATA ANDIKA/RusEfi/fw-Warkop-X-ECU/
   ```
4. Buat folder baru: `KiCad_Recreation`
5. Masuk ke folder itu
6. Nama project: `ECU_Warkop_X`
7. Klik **Save**

**Akan create 2 files:**
- `ECU_Warkop_X.kicad_pro` (project file)
- `ECU_Warkop_X.kicad_sch` (schematic file)

### Step 2: Open Schematic Editor

1. Double-click `ECU_Warkop_X.kicad_sch`
2. Schematic editor akan terbuka
3. Grid putih besar = canvas untuk gambar

### Step 3: Setup Page

1. Klik **File > Page Settings**
2. **Paper size**: A4 landscape
3. **Title**: "ECU Warkop X - Main Schematic"
4. **Revision**: "1.0"
5. **Date**: (today's date)
6. Klik **OK**

### Step 4: Create Hierarchical Sheets

Kita akan buat 8 "sheets" terpisah untuk tiap halaman:

1. Klik **Place > Add Hierarchical Sheet** (atau tekan `S`)
2. Draw kotak di canvas (klik 2x untuk corner)
3. Dialog muncul:
   - **Sheet name**: "MCU Core"
   - **Sheet file name**: "sheets/MCU_Core.kicad_sch"
   - **Create as new file**: checked ✓
4. Klik **OK**

**Ulangi untuk 6 sheets lainnya:**
- IO_Interfaces
- Power_Supply  
- Analog_Inputs
- Output_Drivers
- Communications
- Sensors_Misc

**Arrange kotak-kotak sheet di canvas** agar rapi (3x3 grid).

---

## Page 1: MCU Core

### Overview
Halaman ini berisi:
- U1 (STM32F407VGT6) - Chip utama
- Capacitor untuk power (C3, C4, C9, dll)
- Crystal 8MHz (Y1) dan 32kHz (Y2)
- Reset circuit (SW1, R3, C2)
- USB connector (J3)

### Step 1: Open MCU Core Sheet

1. Double-click kotak "MCU Core" di main schematic
2. New window terbuka - ini sheet kosong
3. Set page size A4 landscape

### Step 2: Add STM32F407 Symbol

1. Press **A** (Add Symbol)
2. Di search box, ketik: `STM32F407VGTx`
3. Pilih symbol (dari library STMicroelectronics)
4. Klik di tengah canvas untuk place
5. Press **Esc** untuk exit placement mode

**Jika symbol tidak ditemukan:**
```
File > Preferences > Manage Symbol Libraries
Klik "+" untuk add library
Browse ke: 
/Applications/KiCad/KiCad.app/Contents/SharedSupport/symbols/
Pilih: MCU_ST_STM32F4.kicad_sym
```

### Step 3: Add Decoupling Capacitors

**Apa itu decoupling cap?** 
- Capacitor kecil dekat power pin IC
- Fungsi: filter noise, stabilkan power
- **Penting**: Setiap pin VDD butuh 1 capacitor

**Placement:**
1. Press **A**
2. Ketik: `C`
3. Pilih `C_Small` (generic capacitor)
4. Place 10 biji di sekeliling U1

**Set nilai capacitor:**
1. Hover mouse di atas C
2. Press **E** (Edit)
3. Di field "Value", ganti jadi: `100nF`
4. Klik **OK**

**Component reference:**
- Rename reference dari C1, C2, ... menjadi C3, C4, C9, C10, C11, C15, C18, C20, C24, C47
- Cara: Hover, press **E**, edit "Reference"

### Step 4: Connect Power to MCU

**Add VDD power symbol:**
1. Press **P** (Power)
2. Ketik: `+3V3` (atau `+3.3V`)
3. Place di atas U1
4. Press **W** (Wire)
5. Click dari +3V3 symbol ke pin VDD di U1 (Pin 1)
6. Repeat untuk semua pin VDD (Pin 1, 11, 28, 50, 75, 100)

**Add GND:**
1. Press **P**
2. Ketik: `GND`
3. Place di bawah U1
4. Wire ke semua pin GND/VSS

**Connect caps:**
- Positive side (atas) → VDD wire
- Negative side (bawah) → GND wire

### Step 5: Add Crystal Circuit (8MHz)

**Components needed:**
- Y1 (Crystal_8MHz)
- C23, C26 (33pF each)
- R? (100k feedback resistor - optional)

**Placement:**
1. Press **A**, ketik `Crystal`, pilih `Crystal_Small`
2. Place di sebelah kiri U1
3. Press **A**, ketik `C`, place 2x capacitor (C23, C26)

**Wiring:**
1. Y1 Pin 1 → U1 Pin 12 (OSC_IN / PH0)
2. Y1 Pin 2 → U1 Pin 13 (OSC_OUT / PH1)
3. C23: One side to OSC_IN, other to GND
4. C26: One side to OSC_OUT, other to GND

**Set values:**
- Y1: Value = `8MHz`
- C23: Value = `33pF`  
- C26: Value = `33pF`

### Step 6: Add 32kHz Crystal (RTC)

**Same process:**
- Y2: Crystal_Small, value `32.768kHz`
- C27, C28: 20pF each
- Connect to U1 Pin 3 (PC14) and Pin 4 (PC15)

### Step 7: Reset Circuit

**Components:**
- SW1: Push button
- R3: 10k pull-up
- C2: 10nF filter

**Circuit:**
1. Place SW1 (symbol: `SW_Push`)
2. Place R3 (resistor, 10k)
3. Place C2 (cap, 10nF)

**Wiring:**
```
+3V3 → R3 → NRST (U1 Pin 14)
NRST → SW1 → GND
NRST → C2 → GND
```

### Step 8: USB Interface (Simplified)

**For now, just add connector:**
1. Place J3 (Type-C connector symbol)
2. Connect D+ and D- to U1 PA12 (Pin 77) and PA11 (Pin 76)
3. Add R81, R82 (22Ω series resistors)

*(Full USB circuit details akan di page Communications)*

---

## Page 2-7: Sirkuit Lainnya

### Page 2: IO Interfaces

**Components to place:**
- IC1, IC2: `SN74LVC2G17` (schmitt trigger)
- JP2, JP7: Solder jumpers
- JP8, JP9: 3-pad jumpers

**Connections:** Akan detailed di separate guide per page

### Page 3: Power Supply

**Components:**
- U8: `NCV7805` (5V regulator)
- U3: `AMS1117-3.3` (3.3V regulator)
- Input/output caps
- Fuses F1, F2

### Page 4: Analog Inputs

**Components:**
- U5, U6: `MCP6004` (quad op-amp)
- Resistor dividers
- RC filters
- Protection diodes

### Page 5: Output Drivers

**Components:**
- Q1-Q11: MOSFETs (various types)
- U2: `TC4424` (gate driver)
- Flyback diodes
- Gate resistors

### Page 6: Communications

**Components:**
- U7: `TJA1051` (CAN transceiver)
- J5: microSD socket
- Termination resistor

### Page 7: Sensors

**Components:**
- U9: `LPS25HB` (pressure sensor)
- LEDs with resistors
- Voltage dividers

---

## Verifikasi

### Electrical Rules Check (ERC)

1. Klik **Inspect > Electrical Rules Checker**
2. Klik **Run ERC**
3. Fix semua **Errors** (wajib)
4. Review **Warnings** (optional, tapi better fix)

**Common errors:**
- Pin not connected → Add wire atau "No Connect" flag
- Pin power mismatch → Check power symbol names
- Duplicate references → Rename components

### Generate Netlist

1. Klik **File > Fabrication Outputs > Netlist**
2. Pilih format: **KiCad**
3. Klik **Generate Netlist**
4Save 

---

## Tips untuk Pemula

### 1. **Jangan Takut Salah**
- Ctrl+Z = Undo
- Bisa delete dan place ulang
- Bisa edit kapan saja

### 2. **Save Sering**
- Ctrl+S setiap 5-10 menit
- KiCad auto-backup, tapi lebih baik save manual

### 3. **Zoom In/Out**
- Scroll wheel untuk zoom
- Fit to screen: **View > Zoom to Fit**

### 4. **Shortcut is Your Friend**
- Hafalkan: A (symbol), W (wire), P (power), L (label)
- Lebih cepat dari menu

### 5. **Refer to Original Schematic**
- Buka file PNG di folder `schematic_analysis/`
- Compare dengan yang Anda buat

### 6. **One Page at a Time**
- Jangan buru-buru
- Selesaikan 1 page dulu, test ERC, baru lanjut

### 7. **Ask for Help**
- Kalau bingung, tanya saya
- Screenshot error message
- KiCad forum juga helpful

---

## Next Steps

Setelah schematic selesai:
1. **Assign Footprints** (hubungkan symbol ke physical package)
2. **Create PCB Layout** (design board shape, place components)
3. **Route Traces** (connect components on PCB)
4. **Generate Gerber** (files untuk pabrik PCB)
5. **Order PCB** (upload Gerber ke JLCPCB, PCBWay, dll)

---

## Estimated Time

| Task | Time (jam) |
|------|------------|
| Install & Setup | 0.5 |
| Page 1 (MCU Core) | 3-4 |
| Pages 2-7 | 4-6 |
| Verification & Fix | 1-2 |
| **TOTAL** | **8-12 jam** |

Jangan rush - quality over speed!

---

**Siap mulai? Install KiCad dulu, lalu kita mulai Page 1 step by step!** 🚀
