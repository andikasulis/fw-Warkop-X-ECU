# Panduan Navigasi Antar Halaman di KiCad
## Untuk Pemula yang Awam

---

## Konsep Dasar: Apa itu Hierarchical Schematic?

### Analogi Sederhana:

**Bayangkan like buku dengan banyak bab:**
- **Halaman utama** = Daftar isi
- **Setiap bab** = Lembar (sheet) terpisah
- **References antar bab** = Hierarchical labels

Skema ECU kita punya **7 lembar** (sheet):
1. Inti MCU (Main)
2. Antarmuka IO
3. Catu Daya
4. Input Analog
5. Pengendali Output
6. Komunikasi
7. Sensor & Lain-lain

---

## Struktur File KiCad Project

```
ECU_Warkop_X/
├── ECU_Warkop_X.kicad_pro     (File project)
├── ECU_Warkop_X.kicad_sch     (Halaman UTAMA - daftar isi)
└── sheets/                     (Folder untuk sub-halaman)
    ├── Inti_MCU.kicad_sch
    ├── Antarmuka_IO.kicad_sch
    ├── Catu_Daya.kicad_sch
    ├── Input_Analog.kicad_sch
    ├── Pengendali_Output.kicad_sch
    ├── Komunikasi.kicad_sch
    └── Sensor_Lain.kicad_sch
```

### Halaman Utama (Root Schematic)

**File**: `ECU_Warkop_X.kicad_sch`

**Isinya**: Kotak-kotak yang merepresentasikan sub-halaman

```
┌─────────────────────────┐
│                         │
│   [Kotak: Inti MCU]     │
│                         │
└─────────────────────────┘

┌─────────────────────────┐
│                         │
│  [Kotak: Catu Daya]     │
│                         │
└─────────────────────────┘

┌─────────────────────────┐
│                         │
│  [Kotak: Input Analog]  │
│                         │
└─────────────────────────┘

(dan seterusnya...)
```

**Fungsi kotak-kotak ini:**
- **Visualisasi** struktur project
- **Pintu masuk** ke setiap sub-halaman
- **Koneksi** antar halaman via hierarchical pins

---

## Cara Navigasi: Langkah Demi Langkah

### 1. Buka Halaman Utama (Root Sheet)

**Cara:**
1. Buka KiCad (aplikasi utama)
2. Klik project `ECU_Warkop_X.kicad_pro`
3. Double-click `ECU_Warkop_X.kicad_sch` → Schematic Editor terbuka
4. Anda sekarang di **halaman utama** (melihat kotak-kotak sheet)

**Visual cue:**
- Title bar window: `ECU_Warkop_X.kicad_sch`
- Canvas: Ada kotak-kotak sheet (bukan komponen detail)

---

### 2. Masuk ke Sub-Halaman (Open Sheet)

**Cara 1: Double-Click (Paling Mudah)**
1. Double-click **kotak sheet** yang ingin dibuka
2. Contoh: Double-click kotak "Inti MCU"
3. Window sekarang menampilkan **isi sheet Inti MCU** (komponen detail)

**Cara 2: Via Hierarchical Navigator**
1. Klik menu **View > Show Hierarchical Navigator** (atau tekan Alt+3)
2. Panel muncul di kiri window
3. Klik sheet name di panel
4. Canvas berganti ke sheet itu

**Visual cue setelah masuk sheet:**
- Title bar berubah: `.../sheets/Inti_MCU.kicad_sch`
- Canvas: Ada komponen detail (U1, resistor, capacitor, dll)
- Breadcrumb di atas canvas: `ECU_Warkop_X > Inti_MCU`

---

### 3. Kembali ke Halaman Utama (Go Up)

**Cara 1: Breadcrumb Navigation**
1. Lihat **bagian atas canvas** - ada breadcrumb:
   ```
   ECU_Warkop_X > sheets/Inti_MCU
   ```
2. Klik **ECU_Warkop_X** (part pertama)
3. Langsung kembali ke halaman utama

**Cara 2: Keyboard Shortcut**
1. Tekan **Alt + Backspace** (Mac: Cmd + Backspace)
2. Naik satu level (kembali ke parent sheet)

**Cara 3: Via Hierarchical Navigator**
1. Panel kiri (Hierarchical Navigator)
2. Klik **root** atau nama halaman yang ingin dituju

---

### 4. Berpindah Antar Sub-Halaman (Sheet to Sheet)

**Scenario**: Anda di sheet "Inti MCU", mau ke sheet "Catu Daya"

**Cara 1: Via Halaman Utama**
1. Kembali ke root (Alt + Backspace)
2. Double-click kotak "Catu Daya"

**Cara 2: Via Hierarchical Navigator (Lebih Cepat)**
1. Di panel Hierarchical Navigator (kiri)
2. Klik langsung "Catu_Daya"
3. Canvas langsung switch

**Cara 3: Via Hierarchical Label (Advanced)**
- Jika ada hierarchical label yang terhubung ke sheet lain
- Right-click label → "Go to connected hierarchical label"
- Langsung jump ke sheet tujuan

---

## Hierarchical Navigator Panel

### Cara Buka:
**Menu**: View > Show Hierarchical Navigator  
**Shortcut**: Alt+3 (Windows/Linux) atau Cmd+3 (Mac)

### Tampilan Panel:

```
Hierarchical Navigator
┌────────────────────────┐
│ ▼ ECU_Warkop_X         │ ← Root (halaman utama)
│   ├─ Inti_MCU          │ ← Sheet 1
│   ├─ Antarmuka_IO      │ ← Sheet 2
│   ├─ Catu_Daya         │ ← Sheet 3
│   ├─ Input_Analog      │ ← Sheet 4
│   ├─ Pengendali_Output │ ← Sheet 5
│   ├─ Komunikasi        │ ← Sheet 6
│   └─ Sensor_Lain       │ ← Sheet 7
└────────────────────────┘
```

### Cara Pakai:
- **Single-click** nama sheet → Jump ke sheet itu
- **Expand/collapse** (▼/▶) untuk lihat sub-sheets (kalau ada nested)

---

## Hierarchical Labels: Koneksi Antar Halaman

### Konsep:

**Ibaratnya**: Seperti "walkie-talkie" antar ruangan
- Sheet A punya label `I2C_SCL` (output)
- Sheet B punya label `I2C_SCL` (input)
- KiCad automatically connect them (sama nama = terhubung)

### Jenis Hierarchical Labels:

#### 1. **Hierarchical Pin** (di Root Sheet)
- Muncul di **kotak sheet** di halaman utama
- Menunjukkan signal masuk/keluar dari sheet

#### 2. **Hierarchical Label** (di Sub-Sheet)
- Muncul di **dalam sheet**
- Connect ke hierarchical pin di root

### Cara Tambah Hierarchical Label:

**Di Sub-Sheet (contoh: Inti_MCU):**
1. Press **L** (Label tool)
2. Ketik nama: `I2C_SCL`
3. Dialog muncul - pilih **Type**: "Hierarchical"
4. Pilih **Shape**: 
   - Input (signal masuk ke sheet ini)
   - Output (signal keluar dari sheet ini)
   - Bidirectional (dua arah, contoh I2C)
5. Place label di net yang ingin di-export

**Di Root Sheet:**
1. Hierarchical pin **automatically** muncul di kotak sheet
2. Wire hierarchical pin ini ke sheet lain

### Contoh Koneksi:

**Sheet "Inti_MCU":**
- Label hirarkis: `I2C_SCL` (Output)
- Label hirarkis: `I2C_SDA` (Output)
- Internal: Connect ke U1 pin PB6, PB7

**Sheet "Sensor_Lain":**
- Label hirarkis: `I2C_SCL` (Input)
- Label hirarkis: `I2C_SDA` (Input)
- Internal: Connect ke U9 pin SCL, SDA

**Di Root Sheet:**
- Wire dari hierarchical pin `I2C_SCL` (sheet Inti_MCU)
- Ke hierarchical pin `I2C_SCL` (sheet Sensor_Lain)
- **Otomatis terhubung!**

---

## Workflow Praktis: Membuat & Navigasi

### Scenario: Menghubungkan CAN dari MCU ke Transceiver

#### Step 1: Di Sheet "Inti_MCU"
1. Open sheet "Inti_MCU" (double-click dari root)
2. Find MCU pin CAN_TX (contoh: PB9)
3. Wire pin ini
4. Press **L** (label)
5. Ketik: `CAN_TX`
6. Pilih type: **Hierarchical - Output**
7. Place di net

**Ulangi untuk CAN_RX (PB8)**

#### Step 2: Kembali ke Root
1. Alt + Backspace (naik ke root)
2. Lihat kotak "Inti_MCU" - sekarang ada **hierarchical pins**:
   - `CAN_TX` (Output)
   - `CAN_RX` (Input)

#### Step 3: Di Sheet "Komunikasi"
1. Double-click kotak "Komunikasi"
2. Place U7 (CAN transceiver)
3. Find pin TXD (U7 pin 1)
4. Wire pin ini
5. Press **L**, ketik: `CAN_TX`
6. Type: **Hierarchical - Input**
7. Place

**Ulangi untuk pin RXD → label `CAN_RX`**

#### Step 4: Connect di Root (Optional)
1. Kembali ke root
2. Wire dari hierarchical pin `CAN_TX` (Inti_MCU)
3. Ke hierarchical pin `CAN_TX` (Komunikasi)

**Note**: Jika nama label **sama persis**, KiCad otomatis connect (tidak perlu wire eksplisit di root)

---

## Tips & Trik Navigasi

### 1. **Pakai Hierarchical Navigator Panel**
- **Selalu buka** panel ini (Alt+3)
- **Quick jump** antar sheet
- Lebih cepat dari bolak-balik root

### 2. **Breadcrumb Navigation**
- Lihat **breadcrumb di atas canvas**
- Click any level untuk jump langsung

### 3. **Keyboard Shortcuts**
- **Alt + Backspace**: Naik satu level (go up)
- **Alt+3**: Toggle Hierarchical Navigator
- **Ctrl+Tab**: Switch antar open windows (jika buka multiple sheets)

### 4. **Color Coding** (Di Root Sheet)
- Beri **warna berbeda** tiap kotak sheet untuk mudah identify
- Right-click kotak → Properties → Background color

### 5. **Naming Convention**
- Hierarchical labels **case-sensitive**!
- `I2C_SCL` ≠ `i2c_scl` ≠ `I2C_scl`
- **Konsisten** pakai naming (contoh: ALL_CAPS untuk bus signals)

### 6. **Cross-Probing**
- Right-click hierarchical label
- "Go to connected hierarchical label"
- Jump langsung ke sheet tujuan

---

## Common Mistakes & Solutions

### ❌ Mistake 1: Tidak Bisa Balik ke Root
**Problem**: Stuck di sub-sheet, bingung cara keluar

**Solution**:
- Press **Alt + Backspace**
- Atau click root di Hierarchical Navigator

### ❌ Mistake 2: Label Tidak Terhubung
**Problem**: Bikin label `CAN_TX` di 2 sheet, tapi tidak connect

**Causes & Solutions**:
- **Typo**: `CAN_TX` vs `CAN_Tx` → Check spelling, case-sensitive!
- **Bukan Hierarchical**: Pakai label biasa, bukan hierarchical → Ubah type ke "Hierarchical"
- **Scope berbeda**: Label di nested sheet berbeda → Pastikan same level hierarchy

### ❌ Mistake 3: Sheet Tidak Muncul di Navigator
**Problem**: Buat sheet baru, tapi tidak muncul di Hierarchical Navigator

**Solution**:
- Pastikan sheet di-place di **root schematic** sebagai hierarchical sheet
- Bukan file terpisah yang tidak linked

### ❌ Mistake 4: Edit Sheet, Tapi Tidak Tersimpan
**Problem**: Edit sub-sheet, close, buka lagi - changes hilang

**Solution**:
- **Save sub-sheet** (Ctrl+S) sebelum close
- Atau: File > Save All (save semua sheet sekaligus)

---

## Checklist Navigasi yang Benar

### Saat Mulai Kerja:
- [ ] Buka Hierarchical Navigator (Alt+3)
- [ ] Lihat struktur project di navigator
- [ ] Identify sheet mana yang akan dikerjakan

### Saat Edit Sub-Sheet:
- [ ] Jump ke sheet via navigator (click nama sheet)
- [ ] Edit komponen/wire
- [ ] Add hierarchical labels untuk koneksi antar sheet
- [ ] **Save sheet** (Ctrl+S) sebelum pindah

### Saat Hubungkan Antar Sheet:
- [ ] Add hierarchical label di sheet source (output)
- [ ] Add hierarchical label di sheet destination (input)
- [ ] **Nama harus sama persis** (case-sensitive)
- [ ] Verify connection di root sheet (optional)

### Saat Selesai Kerja:
- [ ] File > Save All (atau Ctrl+Shift+S)
- [ ] Close schematic editor
- [ ] Semua changes tersaved

---

## Latihan Praktis: Navigation Workout

### Latihan 1: Tour Keliling Sheets

**Tujuan**: Familiar dengan setiap sheet

**Steps:**
1. Buka root sheet
2. Open Hierarchical Navigator
3. Satu per satu, click tiap sheet di navigator:
   - Inti_MCU → Lihat sebentar
   - Antarmuka_IO → Lihat sebentar
   - Catu_Daya → Lihat sebentar
   - (dst untuk semua 7 sheets)
4. Kembali ke root (click root di navigator)

**Goal**: Hapal struktur project, tahu isi tiap sheet

### Latihan 2: Find Component Across Sheets

**Tujuan**: Cari komponen spesifik

**Challenge**: Cari **U7 (CAN transceiver)**

**Steps:**
1. Dari root, guess: U7 mungkin di sheet mana?
2. Open sheet "Komunikasi" (via navigator)
3. Search: Ctrl+F, ketik `U7`
4. Found!

**Ulangi untuk:**
- U9 (Baro sensor) → Di sheet mana?
- Q1 (MOSFET injektor) → Di sheet mana?
- Y1 (Crystal 8MHz) → Di sheet mana?

### Latihan 3: Trace Signal Path

**Tujuan**: Ikuti jalur signal antar sheet

**Challenge**: Trace signal `I2C_SCL` dari MCU ke sensor

**Steps:**
1. Open sheet "Inti_MCU"
2. Find MCU pin I2C_SCL (PB6)
3. Find hierarchical label `I2C_SCL` (output)
4. Right-click label → "Go to connected hierarchical label"
5. Jump ke sheet tujuan (Sensor_Lain)
6. Lihat label `I2C_SCL` terhubung ke U9

**Ulangi untuk:**
- `CAN_TX` (MCU → Transceiver)
- `PWM_INJ1` (MCU → MOSFET Q1)
- `ADC_MAP` (Sensor → MCU)

---

## Summary: Key Points

### Struktur:
- **1 Root sheet** (daftar isi)
- **7 Sub-sheets** (konten detail)
- **Hierarchical labels** (koneksi antar sheet)

### Navigasi:
- **Hierarchical Navigator** (Alt+3) → Quick jump
- **Breadcrumb** (atas canvas) → See context
- **Double-click kotak** di root → Enter sheet
- **Alt + Backspace** → Go up (exit sheet)

### Labels:
- **Hierarchical labels** untuk inter-sheet signals
- **Nama harus sama persis** (case-sensitive)
- **Type**: Input, Output, atau Bidirectional

### Best Practices:
- ✅ Selalu buka Hierarchical Navigator
- ✅ Save sering (Ctrl+S)
- ✅ Naming konsisten untuk labels
- ✅ Cross-probe untuk trace signals

---

**Dengan panduan ini, navigasi di KiCad jadi mudah!** 🎯

Bahkan untuk pemula yang awam, tinggal ikuti step-by-step dan latihan praktis.
