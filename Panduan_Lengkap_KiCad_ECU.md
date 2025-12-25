# Panduan Lengkap KiCad untuk Pemula - Skema ECU
## Versi Bahasa Indonesia (Untuk Orang Awam)

---

## 📖 Daftar Isi
1. [Pengenalan Dasar](#pengenalan-dasar)
2. [Pasang KiCad](#pasang-kicad)
3. [Mengenal Komponen Elektronik](#mengenal-komponen-elektronik)
4. [Tutorial Dasar KiCad](#tutorial-dasar-kicad)
5. [Membuat Proyek ECU](#membuat-proyek-ecu)
6. [Halaman 1: Inti MCU](#halaman-1-inti-mcu)
7. [Halaman 2-7: Sirkuit Lainnya](#halaman-2-7-sirkuit-lainnya)
8. [Pemeriksaan & Penyelesaian Masalah](#pemeriksaan)

---

## Pengenalan Dasar

### Apa itu Skema?
**Skema** = Gambar rencana rangkaian elektronik
- Seperti denah/peta rumah, tapi untuk alat elektronik
- Menunjukkan komponen apa saja yang dipakai
- Menunjukkan bagaimana komponen dihubungkan

### Apa itu PCB?
**PCB (Papan Sirkuit Cetak)** = Papan hijau tempat komponen ditempel
- Wujud fisik dari skema
- Tempat komponen di-solder (disatukan dengan timah panas)
- Jalur tembaga menggantikan kabel

### Alur Kerja Proyek Ini:
```
Skema PDF (sumber asli) 
    ↓
Dokumentasi (sudah selesai)
    ↓
Skema KiCad (yang akan kita buat) ← ANDA DI SINI
    ↓
Desain PCB KiCad
    ↓
File Gerber (untuk pabrik)
    ↓
PCB Jadi
```

---

## Pasang KiCad

### Langkah 1: Unduh KiCad

**Untuk macOS:**
1. Buka website: https://www.kicad.org/download/macos/
2. Unduh versi **8.0** (stabil, terbaru)
3. File berbentuk `.dmg` (~500-800 MB)

**Atau lewat Homebrew (lebih mudah):**
```bash
# Buka Terminal
brew install kicad
```

### Langkah 2: Pasang

1. Klik 2x file `.dmg`
2. Seret "KiCad" ke folder Applications (Aplikasi)
3. Buka KiCad dari Applications

### Langkah 3: Pengaturan Pertama Kali

1. KiCad akan tanya "Atur Pustaka Simbol Global"
   - **Pilih**: "Salin pustaka simbol global bawaan"
   - Klik **Lanjut**

2. KiCad akan tanya "Atur Pustaka Footprint Global"
   - **Pilih**: "Salin pustaka footprint global bawaan"  
   - Klik **Lanjut**

3. Selesai! KiCad siap dipakai.

---

## Mengenal Komponen Elektronik

### Komponen Dasar (yang ada di proyek ini)

#### 1. **Resistor / Tahanan (R)**
**Istilah sehari-hari**: Penghambat listrik
- **Fungsi**: Mengatur/membatasi aliran listrik
- **Ibaratnya**: Seperti keran air - mengatur deras/lambatnya air
- **Simbol**: Kotak atau garis zigzag
- **Nilai**: Ohm (Ω) - contoh 10k = 10,000 Ohm
- **Contoh di proyek**: R1, R2, R3 (ada ~100 resistor)

#### 2. **Kapasitor / Kondensator (C)**
**Istilah sehari-hari**: Bak penampung listrik
- **Fungsi**: Menyimpan listrik sementara, meredam gangguan
- **Ibaratnya**: Seperti tangki air cadangan
- **Simbol**: Dua garis sejajar
- **Nilai**: Farad (F) - contoh 100nF, 10µF
- **Contoh di proyek**: C1, C2, C3 (ada ~55 kapasitor)

#### 3. **IC/Chip/Sirkuit Terpadu (U)**
**Istilah sehari-hari**: Otak sirkuit
- **Fungsi**: Prosesor, pengatur tegangan, dll
- **Ibaratnya**: Seperti otak manusia - berpikir dan mengatur
- **Simbol**: Kotak dengan banyak kaki
- **Contoh di proyek**: 
  - U1 = STM32F407 (mikrokontroler utama / otak ECU)
  - U3 = AMS1117 (pengatur tegangan 3.3V)

#### 4. **Transistor/MOSFET (Q)**
**Istilah sehari-hari**: Saklar elektronik
- **Fungsi**: Menyalakan/mematikan aliran listrik
- **Ibaratnya**: Seperti saklar lampu, tapi dikendalikan elektronik
- **Simbol**: Bentuk panah
- **Contoh di proyek**: Q1-Q13 (pengendali injektor, koil)

#### 5. **Dioda/LED (D)**
**Istilah sehari-hari**: Pintu satu arah / lampu indikator
- **Fungsi**: Listrik hanya bisa lewat satu arah, lampu tanda
- **Ibaratnya**: Seperti pintu putar - hanya bisa masuk, tidak bisa balik
- **Simbol**: Segitiga + garis
- **Contoh di proyek**: D1-D34, LED1-LED3

#### 6. **Konektor / Soket (J)**
**Istilah sehari-hari**: Colokan sambungan
- **Fungsi**: Tempat colok kabel ke luar
- **Ibaratnya**: Seperti colokan listrik di dinding
- **Simbol**: Kotak dengan kaki
- **Contoh di proyek**: J1-J9 (colokan power, USB, konektor utama)

#### 7. **Kristal / Osilator (Y)**
**Istilah sehari-hari**: Jam/pewaktu
- **Fungsi**: Memberikan detak waktu yang akurat
- **Ibaratnya**: Seperti jam pada komputer
- **Simbol**: Kotak dengan 2 kaki
- **Contoh di proyek**: Y1 (8MHz), Y2 (32kHz)

---

## Tutorial Dasar KiCad

### Tampilan Utama KiCad

#### Jendela Utama
Ketika buka KiCad, ada beberapa ikon:
- **Editor Skema** ← Yang paling sering kita pakai
- **Editor PCB** ← Nanti setelah skema selesai
- **Editor Footprint**
- **Editor Simbol**

### Bagian Editor Skema

#### Menu Penting:
- **File > Proyek Baru**: Buat proyek baru
- **Place > Tambah Simbol**: Tambah komponen
- **Place > Tambah Kabel**: Hubungkan komponen
- **Place > Tambah Power**: Tambah simbol daya (VCC, GND)
- **Place > Tambah Label**: Beri nama pada sambungan

#### Tombol Pintas Keyboard:
- **A**: Tambah simbol (komponen)
- **W**: Kabel (sambung komponen)
- **P**: Simbol daya (listrik)
- **L**: Label (nama)
- **M**: Pindah
- **R**: Putar
- **Delete**: Hapus
- **Esc**: Batal

#### Mouse:
- **Klik Kiri**: Pilih
- **Klik Kanan**: Menu
- **Klik Tengah + Seret**: Geser tampilan
- **Roda Gulir**: Perbesar/perkecil

---

## Membuat Proyek ECU

### Langkah 1: Buat Proyek Baru

1. Buka KiCad
2. Klik **File > Proyek Baru**
3. Masuk ke folder:
   ```
   ~/Documents/_DATA ANDIKA/RusEfi/fw-Warkop-X-ECU/
   ```
4. Buat folder baru: `KiCad_Recreation`
5. Masuk ke folder itu
6. Nama proyek: `ECU_Warkop_X`
7. Klik **Simpan**

**Akan membuat 2 file:**
- `ECU_Warkop_X.kicad_pro` (file proyek)
- `ECU_Warkop_X.kicad_sch` (file skema)

### Langkah 2: Buka Editor Skema

1. Klik 2x `ECU_Warkop_X.kicad_sch`
2. Editor skema akan terbuka
3. Halaman putih besar = kanvas untuk menggambar

### Langkah 3: Atur Halaman

1. Klik **File > Pengaturan Halaman**
2. **Ukuran kertas**: A4 landscape (mendatar)
3. **Judul**: "ECU Warkop X - Skema Utama"
4. **Revisi**: "1.0"
5. **Tanggal**: (tanggal hari ini)
6. Klik **OK**

### Langkah 4: Buat Lembar Hirarkis

Kita akan buat 7 "lembar" terpisah untuk tiap halaman:

1. Klik **Place > Tambah Lembar Hirarkis** (atau tekan `S`)
2. Gambar kotak di kanvas (klik 2x untuk sudut)
3. Dialog muncul:
   - **Nama lembar**: "Inti MCU"
   - **Nama file lembar**: "sheets/Inti_MCU.kicad_sch"
   - **Buat sebagai file baru**: centang ✓
4. Klik **OK**

**Ulangi untuk 6 lembar lainnya:**
- Antarmuka_IO
- Catu_Daya  
- Input_Analog
- Pengendali_Output
- Komunikasi
- Sensor_Lain

**Atur kotak-kotak lembar di kanvas** agar rapi.

---

## Halaman 1: Inti MCU

### Gambaran Umum
Halaman ini berisi:
- U1 (STM32F407VGT6) - Chip otak utama
- Kapasitor untuk daya (C3, C4, C9, dll)
- Kristal 8MHz (Y1) dan 32kHz (Y2)
- Rangkaian reset (SW1, R3, C2)
- Konektor USB (J3)

### Langkah 1: Buka Lembar Inti MCU

1. Klik 2x kotak "Inti MCU" di skema utama
2. Jendela baru terbuka - ini lembar kosong
3. Atur ukuran halaman A4 mendatar

### Langkah 2: Tambah Simbol STM32F407

1. Tekan **A** (Tambah Simbol)
2. Di kotak pencarian, ketik: `STM32F407VGTx`
3. Pilih simbol (dari pustaka STMicroelectronics)
4. Klik di tengah kanvas untuk tempatkan
5. Tekan **Esc** untuk keluar dari mode penempatan

**Jika simbol tidak ditemukan:**
```
File > Preferensi > Kelola Pustaka Simbol
Klik "+" untuk tambah pustaka
Telusuri ke: 
/Applications/KiCad/KiCad.app/Contents/SharedSupport/symbols/
Pilih: MCU_ST_STM32F4.kicad_sym
```

### Langkah 3: Tambah Kapasitor Peredam

**Apa itu kapasitor peredam?** 
- Kapasitor kecil dekat kaki daya IC
- Fungsi: meredam gangguan, stabilkan listrik
- **Penting**: Setiap kaki VDD butuh 1 kapasitor

**Penempatan:**
1. Tekan **A**
2. Ketik: `C`
3. Pilih `C_Small` (kapasitor umum)
4. Tempatkan 10 buah di sekeliling U1

**Atur nilai kapasitor:**
1. Arahkan mouse ke C
2. Tekan **E** (Edit)
3. Di kolom "Value", ganti jadi: `100nF`
4. Klik **OK**

**Referensi komponen:**
- Ubah nama dari C1, C2, ... jadi C3, C4, C9, C10, C11, C15, C18, C20, C24, C47
- Cara: Arahkan, tekan **E**, edit "Reference"

### Langkah 4: Hubungkan Daya ke MCU

**Tambah simbol daya VDD:**
1. Tekan **P** (Power / Daya)
2. Ketik: `+3V3`
3. Tempatkan di atas U1
4. Tekan **W** (Wire / Kabel)
5. Klik dari simbol +3V3 ke kaki VDD di U1 (Kaki 1)
6. Ulangi untuk semua kaki VDD (Kaki 1, 11, 28, 50, 75, 100)

**Tambah GND (Ground / Tanah):**
1. Tekan **P**
2. Ketik: `GND`
3. Tempatkan di bawah U1
4. Kabel ke semua kaki GND/VSS

**Hubungkan kapasitor:**
- Sisi positif (atas) → kabel VDD
- Sisi negatif (bawah) → kabel GND

### Langkah 5: Tambah Rangkaian Kristal (8MHz)

**Komponen yang dibutuhkan:**
- Y1 (Kristal_8MHz)
- C23, C26 (33pF masing-masing)

**Penempatan:**
1. Tekan **A**, ketik `Crystal`, pilih `Crystal_Small`
2. Tempatkan di sebelah kiri U1
3. Tekan **A**, ketik `C`, tempatkan 2x kapasitor (C23, C26)

**Pengkabelan:**
1. Y1 Kaki 1 → U1 Kaki 12 (OSC_IN / PH0)
2. Y1 Kaki 2 → U1 Kaki 13 (OSC_OUT / PH1)
3. C23: Satu sisi ke OSC_IN, sisi lain ke GND
4. C26: Satu sisi ke OSC_OUT, sisi lain ke GND

**Atur nilai:**
- Y1: Value = `8MHz`
- C23: Value = `33pF`  
- C26: Value = `33pF`

### Langkah 6: Tambah Kristal 32kHz (RTC)

**Proses sama:**
- Y2: Crystal_Small, nilai `32.768kHz`
- C27, C28: 20pF masing-masing
- Hubungkan ke U1 Kaki 3 (PC14) dan Kaki 4 (PC15)

### Langkah 7: Rangkaian Reset

**Komponen:**
- SW1: Tombol tekan
- R3: Resistor 10k
- C2: Kapasitor 10nF

**Rangkaian:**
```
+3V3 → [R3] → NRST (U1 Kaki 14)
NRST → [SW1] → GND
NRST → [C2] → GND
```

### Langkah 8: Antarmuka USB (Sederhana)

**Untuk saat ini, tambahkan konektor saja:**
1. Tempatkan J3 (konektor Type-C)
2. Hubungkan D+ dan D- ke U1 PA12 (Kaki 77) dan PA11 (Kaki 76)
3. Tambah R81, R82 (resistor 22Ω)

---

## Halaman 2-7: Sirkuit Lainnya

### Halaman 2: Antarmuka IO

**Komponen yang ditambahkan:**
- IC1, IC2: `SN74LVC2G17` (pembentuk sinyal)
- JP2, JP7: Jumper solder
- JP8, JP9: Jumper 3-pad

### Halaman 3: Catu Daya

**Komponen:**
- U8: `NCV7805` (pengatur 5V)
- U3: `AMS1117-3.3` (pengatur 3.3V)
- Kapasitor input/output
- Sekering F1, F2

### Halaman 4: Input Analog

**Komponen:**
- U5, U6: `MCP6004` (penguat sinyal analog)
- Pembagi tegangan resistor
- Filter RC
- Dioda pelindung

### Halaman 5: Pengendali Output

**Komponen:**
- Q1-Q11: MOSFET (berbagai jenis)
- U2: `TC4424` (pengendali gerbang)
- Dioda flyback
- Resistor gerbang

### Halaman 6: Komunikasi

**Komponen:**
- U7: `TJA1051` (transceiver CAN)
- J5: soket microSD
- Resistor terminasi

### Halaman 7: Sensor

**Komponen:**
- U9: `LPS25HB` (sensor tekanan)
- LED dengan resistor
- Pembagi tegangan

---

## Pemeriksaan

### Pemeriksaan Aturan Listrik (ERC)

1. Klik **Inspect > Electrical Rules Checker**
2. Klik **Jalankan ERC**
3. Perbaiki semua **Kesalahan** (wajib)
4. Tinjau **Peringatan** (opsional, tapi lebih baik diperbaiki)

**Kesalahan umum:**
- Kaki tidak terhubung → Tambah kabel atau tanda "Tidak Dihubungkan"
- Ketidakcocokan daya → Periksa nama simbol daya
- Referensi duplikat → Ubah nama komponen

---

## Tips untuk Pemula

### 1. **Jangan Takut Salah**
- Ctrl+Z = Batalkan
- Bisa hapus dan tempatkan ulang
- Bisa edit kapan saja

### 2. **Simpan Sering**
- Ctrl+S setiap 5-10 menit
- KiCad auto-backup, tapi lebih baik simpan manual

### 3. **Perbesar/Kecilkan Tampilan**
- Roda gulir untuk zoom
- Pas ke layar: **View > Zoom to Fit**

### 4. **Tombol Pintas adalah Teman**
- Hafalkan: A (simbol), W (kabel), P (daya), L (label)
- Lebih cepat dari menu

### 5. **Lihat Skema Asli**
- Buka file PNG di folder `schematic_analysis/`
- Bandingkan dengan yang Anda buat

### 6. **Satu Halaman Setiap Waktu**
- Jangan buru-buru
- Selesaikan 1 halaman, test ERC, baru lanjut

### 7. **Tanya Jika Bingung**
- Kalau bingung, tanya saya
- Screenshot pesan error
- Forum KiCad juga membantu

---

## Langkah Selanjutnya

Setelah skema selesai:
1. **Tetapkan Footprint** (hubungkan simbol ke paket fisik)
2. **Buat Tata Letak PCB** (desain bentuk papan, tempatkan komponen)
3. **Rute Jalur** (hubungkan komponen di PCB)
4. **Buat Gerber** (file untuk pabrik PCB)
5. **Pesan PCB** (upload Gerber ke JLCPCB, PCBWay, dll)

---

## Perkiraan Waktu

| Tugas | Waktu (jam) |
|------|------------|
| Pasang & Atur | 0.5 |
| Halaman 1 (Inti MCU) | 3-4 |
| Halaman 2-7 | 4-6 |
| Pemeriksaan & Perbaikan | 1-2 |
| **TOTAL** | **8-12 jam** |

Jangan terburu-buru - kualitas lebih penting dari kecepatan!

---

**Siap mulai? Pasang KiCad dulu, lalu kita mulai Halaman 1 langkah demi langkah!** 🚀
# Halaman 2: Antarmuka IO - Panduan Detail
## Waktu: ~45 menit

---

## Gambaran Umum

Halaman ini mengatur **sinyal masuk dari sensor** agar lebih bersih dan stabil sebelum masuk ke otak MCU.

### Komponen yang Akan Ditambahkan:
- **IC1, IC2**: Pembentuk sinyal (biar sinyal tidak goyang-goyang)
- **JP8, JP9**: Jumper pemilih jenis sensor (Hall atau VR)
- **JP2, JP7**: Jumper pull-up (tarikan ke atas)

---

## Langkah 1: Buka Lembar Antarmuka IO

1. Dari skema utama, **klik 2x** kotak "Antarmuka_IO"
2. Jendela baru terbuka

---

## Langkah 2: Tambah IC Pembentuk Sinyal

### IC1 dan IC2: SN74LVC2G17

**Fungsi**: Membersihkan sinyal dari sensor yang bergetar/kotor

**Cara:**
1. Tekan **A**
2. Ketik: `SN74LVC2G17`
3. Tempatkan IC1 di kiri halaman
4. Tekan **A** lagi, tempatkan IC2 di sebelahnya

**Hubungkan daya:**
- Kaki VCC (kaki 6) → +3V3 atau +5V (sesuai sensor)
- Kaki GND (kaki 2) → GND

**Hubungkan sinyal:**
- Dari konektor J9 → IC1 kaki 1 (Input A)
- IC1 kaki 6 (Output A) → MCU U1 kaki tertentu
- Ulangi untuk IC2

---

## Langkah 3: Tambah Jumper Hall/VR

### JP8, JP9: Pemilih Jenis Sensor

**Fungsi**: 
- Sensor **Hall** = sensor magnet digital
- Sensor **VR** = sensor magnet analog

**Cara:**
1. Tekan **A**
2. Ketik: `Jumper_3`
3. Tempatkan JP8 dan JP9

**Pengkabelan:**
- Pad 1: Mode Hall (tarikan ke VCC)
- Pad 2: Sinyal input (tengah)
- Pad 3: Mode VR (tarikan ke GND)

**Resistor terkait:**
- R25, R26 (2.7k): Pull-up untuk mode Hall
- Tempatkan antara Pad 1 dan VCC

---

## Langkah 4: Tambah Jumper Pull-Up

### JP2, JP7: Pull-Up Optional

**Fungsi**: Tarikan ke atas untuk input tertentu

**Cara:**
1. Tekan **A**
2. Ketik: `Jumper_2` atau `SolderJumper`
3. Tempatkan JP2 dan JP7

**Gunakan saat:**
- Sensor butuh tarikan
- Tutup jumper = enable pull-up
- Buka jumper = disable

---

## Langkah 5: Hubungkan ke MCU

**Gunakan label hirarkis** untuk hubung ke Halaman 1 (Inti MCU):

1. Tekan **L** (Label)
2. Ketik nama sinyal, contoh: `CRANK_IN`
3. Tempatkan di ujung output IC1
4. Di Halaman 1, tambah label sama di kaki MCU yang sesuai

**Nama label contoh:**
- CRANK_IN (sinyal crankshaft)
- CAM_IN (sinyal camshaft)
- DIGITAL_IN_1
- DIGITAL_IN_2

---

## Verifikasi Halaman 2

- [ ] IC1, IC2 ter-place dengan benar
- [ ] Daya VCC dan GND terhubung
- [ ] Jumper JP8, JP9 lengkap dengan resistor
- [ ] Label hirarkis sesuai dengan Halaman 1
- [ ] Jalankan ERC, pastikan tidak ada error

---

# Halaman 3: Catu Daya - Panduan Detail
## Waktu: ~1 jam

---

## Gambaran Umum

Halaman ini mengubah **tegangan baterai 12V** menjadi:
- **5V** (untuk beberapa sensor dan IC)
- **3.3V** (untuk MCU dan logika digital)

### Komponen Utama:
- **U8**: Pengatur 12V → 5V
- **U3**: Pengatur 5V → 3.3V
- **F1, F2**: Sekering pengaman
- **D14, D15**: Pelindung polaritas terbalik

---

## Langkah 1: Buka Lembar Catu Daya

1. Klik 2x kotak "Catu_Daya"

---

## Langkah 2: Tambah Input Daya

### Konektor J4, J7, J8

**Fungsi**: Tempat masuk listrik 12V dari baterai

**Cara:**
1. Tekan **A**
2. Ketik: `Conn_01x02` (konektor 2-pin)
3. Tempatkan J4
4. Ulangi untuk J7, J8

**Hubungkan:**
- Pin 1: +12V dari baterai
- Pin 2: GND

---

## Langkah 3: Tambah Sekering

### F1, F2: Sekering Polimer

**Fungsi**: Putus otomatis kalau arus berlebih (pengaman)

**Cara:**
1. Tekan **A**
2. Ketik: `Fuse` atau `Polyfuse`
3. Tempatkan F1 (nilai 0.5A)
4. Tempatkan F2 (nilai lebih besar)

**Hubungkan:**
```
+12V input → [F1] → jalur 12V terlindungi
+12V input → [F2] → jalur daya utama
```

---

## Langkah 4: Tambah Pelindung Reverse Polarity

### D14: Dioda Schottky SS14

**Fungsi**: Kalau baterai terpasang terbalik, dioda ini melindungi

**Cara:**
1. Tekan **A**
2. Ketik: `D_Schottky`
3. Edit value: `SS14`
4. Package: `D_SMA`

**Hubungkan:**
- Anoda → +12V setelah sekering
- Katoda → Rail 12V sistem

---

## Langkah 5: Tambah TVS Dioda

### D15: SMBJ40A

**Fungsi**: Potong lonjakan tegangan tinggi (spike)

**Cara:**
1. Tekan **A**
2. Ketik: `D_TVS`
3. Value: `SMBJ40A`

**Hubungkan:**
- Parallel antara +12V dan GND

---

## Langkah 6: Pengatur 5V

### U8: NCV7805 (12V → 5V)

**Cara:**
1. Tekan **A**
2. Ketik: `NCV7805` atau `LM7805`
3. Package: `TO-263-3`

**Kaki:**
- Kaki 1 (GND/Tab): Ground
- Kaki 2 (VIN): +12V input
- Kaki 3 (VOUT): +5V output

**Kapasitor input:**
- C21: 47µF electrolytic (input)
- C?: 100nF ceramic (input)

**Kapasitor output:**
- C17: 10µF electrolytic (output)
- C?: 100nF ceramic (output)

**Hubungkan:**
```
+12V → C21+ → U8 VIN
U8 GND → GND
U8 VOUT → C17+ → +5V rail
```

---

## Langkah 7: Pengatur 3.3V

### U3: AMS1117-3.3 (5V → 3.3V)

**Cara:**
1. Tekan **A**
2. Ketik: `AMS1117-3.3`
3. Package: `SOT-223-3`

**Kaki:**
- Kaki 1: GND
- Kaki 2 (Tab): VOUT (3.3V)
- Kaki 3: VIN (5V)

**Kapasitor:**
- Input: C29, C31, C33 (1µF ceramic)
- Output: C32, C34 (2.2µF ceramic)

**Hubungkan:**
```
+5V → C29+ → U3 VIN
U3 GND → GND
U3 VOUT → C32+ → +3V3 rail
```

---

## Langkah 8: Distribusi Daya

**Tambah simbol daya:**
1. Tekan **P**
2. Pilih:
   - `+12V` (dari J4/baterai)
   - `+5V` (output U8)
   - `+3V3` (output U3)
   - `GND`

**Tempatkan di setiap output** untuk menunjukkan jalur daya global

---

## Verifikasi Halaman 3

- [ ] Konektor input terhubung +12V dan GND
- [ ] Sekering F1, F2 di jalur input
- [ ] D14 polaritas benar (anoda ke +, katoda ke sistem)
- [ ] D15 TVS parallel +12V-GND
- [ ] U8 (5V regulator) lengkap dengan kapasitor
- [ ] U3 (3.3V regulator) lengkap dengan kapasitor
- [ ] Simbol daya +12V, +5V, +3V3, GND ter-place
- [ ] ERC tidak ada error

---

# Halaman 4: Input Analog - Panduan Detail
## Waktu: ~1.5 jam

---

## Gambaran Umum

Halaman ini memproses **sinyal sensor analog** (seperti sensor suhu, tekanan, posisi throttle) agar aman dan stabil masuk ke MCU.

### Sensor yang Diproses:
1. **MAP** (Manifold Absolute Pressure) - tekanan intake
2. **TPS** (Throttle Position Sensor) - posisi gas
3. **CLT** (Coolant Temperature) - suhu air
4. **IAT** (Intake Air Temperature) - suhu udara
5. **O2** (Oxygen Sensor) - sensor oksigen

---

## Langkah 1: Buka Lembar Input Analog

1. Klik 2x kotak "Input_Analog"

---

## Langkah 2: Tambah Op-Amp

### U5, U6: MCP6004 (Quad Op-Amp)

**Fungsi**: Penguat dan penyangga sinyal

**Cara:**
1. Tekan **A**
2. Ketik: `MCP6004`
3. Package: `SOIC-14`
4. Tempatkan U5 dan U6

**Daya:**
- VDD (kaki 4) → +3V3
- VSS (kaki 11) → GND
- Tambah kapasitor 100nF dekat IC

---

## Langkah 3: Rangkaian MAP Sensor

**Input**: 0-5V dari sensor tekanan
**Output**: 0-3.3V ke MCU ADC

**Komponen:**
- Pembagi tegangan: R? (10k) + R? (2.7k)
- Filter: R? (470Ω) + C? (220nF)
- Pelindung: D? (BAT54S dual Schottky)

**Rangkaian:**
```
Sensor MAP → [R 10k] → titik tengah → [R 2.7k] → GND
                         ↓
                    [Filter RC] → MCU ADC
                         ↓
                    [Dioda BAT54S] (ke 3V3 dan GND)
```

---

## Langkah 4: Rangkaian TPS

**Sama seperti MAP:**
- Pembagi tegangan untuk turunkan 5V → 3.3V
- Filter RC untuk redam noise
- Dioda proteksi

---

## Langkah 5: Rangkaian CLT/IAT (Sensor Suhu)

**Jenis**: Termistor NTC (resistance turun saat panas)

**Rangkaian:**
```
+5V → [R pull-up 2.7k] → Sensor NTC → GND
           ↓
        [Filter] → MCU ADC
```

**Cara:**
1. Tempatkan resistor pull-up (2.7k)
2. Input dari sensor (konektor J9)
3. Filter RC (470Ω + 100nF)
4. Ke MCU ADC pin

---

## Langkah 6: Rangkaian O2 Sensor

**Output sensor**: 0-1V (narrowband)

**Rangkaian sederhana:**
- Input langsung dari sensor
- Filter RC (1kΩ + 220nF)
- Ke MCU ADC

**Tidak perlu pembagi tegangan** karena sudah < 3.3V

---

## Langkah 7: Pelindung ESD

### D?: BAT54S (Dual Schottky)

**Fungsi**: Proteksi dari static electricity

**Cara:**
1. Tekan **A**
2. Ketik: `BAT54S`
3. Package: `SOT-23`

**Hubungkan:**
- Kaki 1 (Anoda 1) → Input signal
- Kaki 2 (Katoda bersama) → +3V3
- Kaki 3 (Anoda 2) → GND

**Tempatkan 1 per input sensor**

---

## Langkah 8: Hubungkan ke MCU

**Label hirarkis ke ADC pins:**

1. Tekan **L**
2. Ketik nama, contoh:
   - `ADC_MAP` → ke U1 PA0
   - `ADC_TPS` → ke U1 PA1
   - `ADC_CLT` → ke U1 PA2
   - `ADC_IAT` → ke U1 PA3
   - `ADC_O2` → ke U1 PA4

---

## Verifikasi Halaman 4

- [ ] U5, U6 (op-amp) ter-place dengan daya
- [ ] Rangkaian MAP dengan pembagi tegangan
- [ ] Rangkaian TPS dengan pembagi tegangan
- [ ] Rangkaian CLT/IAT dengan pull-up resistor
- [ ] Rangkaian O2 dengan filter
- [ ] Dioda BAT54S proteksi di setiap input
- [ ] Label hirarkis ke MCU ADC pins
- [ ] ERC tidak ada error

---

# Halaman 5: Pengendali Output - Panduan Detail
## Waktu: ~2 jam

---

## Gambaran Umum

Halaman ini mengendalikan **beban daya tinggi** seperti:
- Injektor bahan bakar
- Koil pengapian
- Relay pompa/kipas
- Solenoid

### Komponen Utama:
- **Q1-Q6, Q11**: MOSFET daya tinggi (untuk injektor/koil)
- **U2**: Pengendali gerbang MOSFET
- **Q5, Q7-Q10**: MOSFET daya rendah (untuk relay/LED)
- **Q12, Q13**: Saklar sisi tinggi

---

## Langkah 1: Buka Lembar Pengendali Output

1. Klik 2x kotak "Pengendali_Output"

---

## Langkah 2: Tambah MOSFET Daya Tinggi

### Q1-Q6, Q11: STP62NS04Z

**Spesifikasi**: 62A, 40V N-Channel MOSFET
**Fungsi**: Nyalakan injektor, koil pengapian

**Cara:**
1. Tekan **A**
2. Ketik: `Q_NMOS_GDS`
3. Package: `TO-252-3`
4. Tempatkan Q1, lalu duplicate untuk Q2-Q6, Q11

**Kaki:**
- G (Gate / Gerbang): Dari pengendali
- D (Drain / Penyalur): Ke beban (injektor/koil)
- S (Source / Sumber): Ke GND

---

## Langkah 3: Tambah Pengendali Gerbang

### U2: TC4424AVOA (Dual MOSFET Driver)

**Fungsi**: Menguatkan sinyal dari MCU agar bisa nyalakan MOSFET cepat

**Cara:**
1. Tekan **A**
2. Ketik: `TC4424`
3. Package: `SOIC-8`

**Kaki:**
- VDD: +5V atau +12V (untuk gate drive kuat)
- GND: Ground
- IN_A: PWM dari MCU
- OUT_A: Ke Gate Q1
- IN_B: PWM dari MCU
- OUT_B: Ke Gate Q2

**Hubungkan:**
```
MCU PWM pin → U2 IN_A
U2 OUT_A → [R 15Ω] → Q1 Gate
Q1 Source → GND
Q1 Drain → Injektor → +12V
```

---

## Langkah 4: Tambah Resistor Gerbang

### R52, R53: 15Ω (Package 2512)

**Fungsi**: Batasi arus gate, redam getaran

**Cara:**
1. Tekan **A**
2. Ketik: `R`
3. Value: `15R` atau `15`
4. **Package: `R_2512_6332Metric`** (lebih besar dari 0603!)

**Tempatkan antara:**
- U2 OUT → [R 15Ω] → MOSFET Gate

---

## Langkah 5: Tambah Dioda Flyback

### D13, D16, D25-D33: 1N5819W

**Fungsi**: Proteksi dari kickback tegangan tinggi saat beban induktif mati

**Cara:**
1. Tekan **A**
2. Ketik: `D_Schottky`
3. Value: `1N5819W`
4. Package: `D_SOD-123`

**Hubungkan:**
- Anoda: MOSFET Drain (tempat beban)
- Katoda: +12V rail

**Ibaratnya**: Pintu darurat untuk arus balik

---

## Langkah 6: MOSFET Daya Rendah

### Q5, Q7-Q10: AO3400A

**Spesifikasi**: 5.7A, 30V
**Fungsi**: Relay, LED, solenoid kecil

**Cara:**
1. Tekan **A**
2. Ketik: `AO3400A`
3. Package: `SOT-23`
4. Tempatkan 5 buah

**Hubungkan lebih sederhana:**
```
MCU GPIO → [R 1k] → MOSFET Gate
MOSFET Drain → Beban (relay coil)
MOSFET Source → GND
Beban → +12V
```

**Tambah dioda flyback kalau beban induktif** (relay, solenoid)

---

## Langkah 7: Saklar Sisi Tinggi

### Q12, Q13: ISL9V3040D3S (P-Channel)

**Fungsi**: Nyalakan +12V ke sensor/peripheral

**Cara:**
1. Tekan **A**
2. Ketik: `Q_PMOS`
3. Package: `TO-263-2`

**Hubungkan:**
```
+12V → MOSFET Source
MOSFET Drain → Beban (sensor power)
MCU GPIO LOW → [inverter] → Gate (untuk ON)
```

**Pull-up resistor 10k** di Gate ke Source

---

## Langkah 8: Hubungkan ke MCU & Beban

**Dari MCU (Halaman 1):**
- Label hirarkis: `PWM_INJ1`, `PWM_INJ2`, `PWM_IGN1`, dll
- Connect ke U2 input atau langsung ke gate (untuk low-power)

**Ke Konektor J9 (beban):**
- Label: `OUT_INJ1`, `OUT_INJ2`, `OUT_IGN1`, `OUT_RELAY1`, dll

---

## Verifikasi Halaman 5

- [ ] Q1-Q6, Q11 (high-power MOSFET) ter-place
- [ ] U2 (gate driver) dengan daya VDD
- [ ] Resistor gate 15Ω (package 2512!)
- [ ] Dioda flyback di semua output induktif
- [ ] Q5, Q7-Q10 (low-power MOSFET) untuk relay
- [ ] Q12, Q13 (high-side switch) dengan pull-up
- [ ] Label hirarkis dari MCU PWM pins
- [ ] Label ke konektor output
- [ ] ERC tidak ada error

---

Lanjut ke Halaman 6 & 7...
# Halaman 6: Komunikasi - Panduan Detail
## Waktu: ~45 menit

---

## Gambaran Umum

Halaman ini menangani **komunikasi dengan alat lain**:
- **CAN Bus**: Komunikasi dengan ECU lain / dashboard
- **microSD**: Penyimpanan data log
- **USB**: Sudah di Halaman 1 (MCU Core)

---

## Langkah 1: Buka Lembar Komunikasi

1. Klik 2x kotak "Komunikasi"

---

## Langkah 2: Tambah CAN Transceiver

### U7: TJA1051T (CAN Transceiver)

**Fungsi**: Mengubah sinyal digital MCU menjadi sinyal CAN bus

**Cara:**
1. Tekan **A**
2. Ketik: `TJA1051`
3. Package: `SOIC-8`

**Kaki:**
- Pin 1 (TXD): Transmit dari MCU
- Pin 2 (GND): Ground
- Pin 3 (VCC): +5V
- Pin 4 (RXD): Receive ke MCU
- Pin 5 (VREF): Tidak dipakai (kosongkan)
- Pin 6 (CANH): CAN High
- Pin 7 (CANL): CAN Low
- Pin 8 (STB): Standby (sambung ke GND = always ON)

**Hubungkan daya:**
- VCC (pin 3) → +5V
- GND (pin 2) → GND
- Tambah kapasitor 100nF dekat IC

---

## Langkah 3: Hubungkan CAN ke MCU

**Dari Halaman 1 (MCU):**
- MCU CAN1_TX (contoh: PB9) → Label `CAN_TX`
- MCU CAN1_RX (contoh: PB8) → Label `CAN_RX`

**Di Halaman 6:**
- Label `CAN_TX` → U7 pin 1 (TXD)
- U7 pin 4 (RXD) → Label `CAN_RX`

---

## Langkah 4: Tambah Resistor Terminasi CAN

### R7: 120Ω

**Fungsi**: Terminasi bus CAN (hanya di ujung bus)

**Cara:**
1. Tekan **A**
2. Ketik: `R`
3. Value: `120R` atau `120`
4. Package: `R_0603_1608Metric`

**Hubungkan:**
- Antara CANH (pin 6) dan CANL (pin 7)

**Catatan**: Pasang resistor ini **hanya jika ECU di ujung bus**. Kalau di tengah, jangan pasang (lebih baik pakai jumper optional).

---

## Langkah 5: Tambah Pelindung ESD CAN

**Dioda TVS di garis CANH dan CANL:**

**Cara:**
1. Tekan **A**
2. Ketik: `D_TVS` atau gunakan yang existing
3. Parallel antara CANH-GND dan CANL-GND

---

## Langkah 6: Konektor CAN ke Luar

**Hubungkan ke konektor utama J9:**
- CANH → J9 pin tertentu (label: `CAN_H`)
- CANL → J9 pin tertentu (label: `CAN_L`)

---

## Langkah 7: Tambah microSD Socket

### J5: THD2528-11SD-GF (microSD Socket)

**Fungsi**: Simpan data logging

**Cara:**
1. Tekan **A**
2. Ketik: `MicroSD` atau `Card`
3. Package: `CUI_MSD-1-A`

**Pin SPI:**
- CLK: SPI clock
- MISO: Master In Slave Out
- MOSI: Master Out Slave In
- CS: Chip Select
- VCC: +3V3
- GND: Ground

---

## Langkah 8: Hubungkan SPI ke MCU

**Dari MCU (Halaman 1):**
- Label hirarkis:
  - `SPI_SCK` → MCU SPI2_SCK (contoh: PB13)
  - `SPI_MISO` → MCU SPI2_MISO (contoh: PB14)
  - `SPI_MOSI` → MCU SPI2_MOSI (contoh: PB15)
  - `SD_CS` → MCU GPIO (contoh: PB12)

**Di Halaman 6:**
- Label `SPI_SCK` → J5 CLK
- Label `SPI_MISO` → J5 MISO
- Label `SPI_MOSI` → J5 MOSI
- Label `SD_CS` → J5 CS

**Daya:**
- +3V3 → J5 VCC (tambah kapasitor 100nF dekat socket)
- GND → J5 GND

---

## Langkah 9: Card Detect (Optional)

**Pin CD (Card Detect) di socket:**
- Hubungkan ke MCU GPIO
- Pull-up resistor 10k ke +3V3
- Deteksi kartu terpasang atau tidak

---

## Verifikasi Halaman 6

- [ ] U7 (CAN transceiver) ter-place dengan daya
- [ ] CAN_TX dan CAN_RX terhubung ke MCU via label
- [ ] R7 (120Ω) antara CANH-CANL
- [ ] Dioda TVS untuk proteksi CAN
- [ ] CANH/CANL ke konektor J9
- [ ] J5 (microSD socket) ter-place
- [ ] SPI signals terhubung ke MCU via label
- [ ] Kapasitor dekat IC dan socket
- [ ] ERC tidak ada error

---

# Halaman 7: Sensor & Lain-lain - Panduan Detail
## Waktu: ~1 jam

---

## Gambaran Umum

Halaman ini berisi:
- Sensor tekanan barometrik
- LED indikator status
- Input voltage sensing
- Test points
- Jumper konfigurasi

---

## Langkah 1: Buka Lembar Sensor Lain

1. Klik 2x kotak "Sensor_Lain"

---

## Langkah 2: Tambah Sensor Tekanan

### U9: LPS25HB (Barometric Pressure Sensor)

**Fungsi**: Ukur tekanan udara (untuk koreksi ketinggian)

**Cara:**
1. Tekan **A**
2. Ketik: `LPS25HB`
3. Package: `ST_HLGA-10_2.5x2.5mm_P0.6mm`

**Antarmuka**: I2C

**Kaki penting:**
- VDD: +3V3
- GND: Ground
- SCL: I2C Clock
- SDA: I2C Data

---

## Langkah 3: Hubungkan I2C ke MCU

**Dari MCU (Halaman 1):**
- Label:
  - `I2C_SCL` → MCU I2C1_SCL (contoh: PB6)
  - `I2C_SDA` → MCU I2C1_SDA (contoh: PB7)

**Di Halaman 7:**
- Label `I2C_SCL` → U9 SCL
- Label `I2C_SDA` → U9 SDA

**Pull-up resistor:**
- R35, R36, R91 (2.7k): Pull-up pada SCL dan SDA
- Sambungkan ke +3V3

**Daya:**
- +3V3 → U9 VDD
- GND → U9 GND
- Kapasitor 100nF dekat IC

---

## Langkah 4: Tambah LED Status

### LED1, LED2, LED3: LED Indikator

**Fungsi**: Tanda visual status ECU

**Cara:**
1. Tekan **A**
2. Ketik: `LED` atau `LED_Small`
3. Value: `RED` (atau warna lain)
4. Package: `LED_0603_1608Metric`

**Hubungkan per LED:**
```
MCU GPIO → [R 470Ω] → LED Anoda (+)
LED Katoda (-) → GND
```

**Resistor pembatas arus:**
- R87, R88: 470Ω (package 0603)

**Fungsi LED:**
- LED1: Power ON / Heartbeat
- LED2: CAN Activity
- LED3: Error / Warning

---

## Langkah 5: Tambah LED di PCB

### D1-D8: LED Indikator PCB

**Sama seperti LED1-LED3:**
- Dari MCU GPIO
- Resistor 470Ω
- LED 0603
- Ke GND

**Tempatkan sebanyak yang diperlukan**

---

## Langkah 6: Voltage Sensing (Tegangan Baterai)

**Fungsi**: Monitor tegangan baterai 12V

**Rangkaian pembagi tegangan:**
```
+12V → [R 100k] → titik tengah → [R 10k] → GND
                      ↓
                  Filter RC
                      ↓
                  MCU ADC
```

**Komponen:**
- R?: 100k (pembagi atas)
- R?: 10k (pembagi bawah)
- C?: 100nF (filter)

**Perhitungan:**
- 12V x (10k / 110k) = ~1.09V → aman untuk ADC 3.3V

**Label:**
- `ADC_VBAT` → ke MCU ADC pin

---

## Langkah 7: Jumper Tegangan Pengapian

### JP1: 3-Pin Header (Ignition Voltage Selector)

**Fungsi**: Pilih sumber tegangan untuk sensor tertentu

**Cara:**
1. Tekan **A**
2. Ketik: `Conn_01x03` atau `Jumper_3`
3. Package: `PinHeader_1x03_P2.54mm_Vertical`

**Konfigurasi:**
- Pin 1-2: Gunakan +5V
- Pin 2-3: Gunakan +12V
- Pin 2 (tengah): Output ke sensor

---

## Langkah 8: Test Points

**Tambah test point untuk debugging:**

1. Tekan **A**
2. Ketik: `TestPoint`
3. Tempatkan di net penting:
   - +12V
   - +5V
   - +3V3
   - GND
   - Sinyal kritis

**Gunakan package:** `TestPoint_Pad_D1.5mm`

---

## Langkah 9: Knock Sensor Input (Optional)

**Jika ada sensor ketukan:**

**Rangkaian:**
- AC-coupling: Kapasitor 220nF
- High-pass filter
- Amplifier (op-amp dari U5/U6)
- Bandpass filter (~5-10kHz)
- Ke MCU ADC

**Komponen:**
- Kapasitor AC coupling
- Resistor bias
- Op-amp buffer/gain stage
- RC filter

---

## Verifikasi Halaman 7

- [ ] U9 (pressure sensor) dengan I2C connection
- [ ] Pull-up resistor pada I2C (2.7k)
- [ ] LED1-LED3 dengan resistor 470Ω
- [ ] Additional LEDs (D1-D8) dengan resistor
- [ ] Voltage sensing circuit (pembagi + filter)
- [ ] JP1 voltage selector jumper
- [ ] Test points di net penting
- [ ] Label hirarkis ke MCU
- [ ] Kapasitor decoupling dekat IC
- [ ] ERC tidak ada error

---

# Ringkasan Semua Halaman

## Checklist Final

### Halaman 1: Inti MCU ✓
- [ ] U1 STM32F407 dengan semua kaki terhubung
- [ ] 10x kapasitor decoupling 100nF
- [ ] Kristal 8MHz + 32kHz dengan load caps
- [ ] Reset circuit
- [ ] USB Type-C dengan proteksi
- [ ] SWD debug header

### Halaman 2: Antarmuka IO ✓
- [ ] IC1, IC2 pembentuk sinyal
- [ ] Jumper Hall/VR (JP8, JP9)
- [ ] Jumper pull-up (JP2, JP7)
- [ ] Label ke MCU

### Halaman 3: Catu Daya ✓
- [ ] U8 pengatur 12V→5V
- [ ] U3 pengatur 5V→3.3V
- [ ] Sekering F1, F2
- [ ] Proteksi reverse polarity
- [ ] TVS dioda
- [ ] Kapasitor filtering

### Halaman 4: Input Analog ✓
- [ ] U5, U6 op-amp
- [ ] Rangkaian MAP, TPS, CLT, IAT, O2
- [ ] Pembagi tegangan
- [ ] Filter RC
- [ ] Dioda BAT54S proteksi

### Halaman 5: Pengendali Output ✓
- [ ] Q1-Q11 MOSFET daya tinggi
- [ ] U2 gate driver
- [ ] Resistor gate 15Ω
- [ ] Dioda flyback
- [ ] Q5,Q7-Q10 MOSFET daya rendah
- [ ] Q12, Q13 high-side switch

### Halaman 6: Komunikasi ✓
- [ ] U7 CAN transceiver
- [ ] Resistor terminasi 120Ω
- [ ] J5 microSD socket
- [ ] SPI connection ke MCU
- [ ] Proteksi ESD

### Halaman 7: Sensor Lain ✓
- [ ] U9 pressure sensor (I2C)
- [ ] LED status dengan resistor
- [ ] Voltage sensing circuit
- [ ] JP1 voltage selector
- [ ] Test points

---

## Langkah Setelah Semua Halaman Selesai

### 1. Pemeriksaan Menyeluruh

**Jalankan ERC di setiap halaman:**
1. Buka tiap halaman
2. Inspect > Electrical Rules Checker
3. Fix semua error
4. Review warnings

**Periksa koneksi hirarkis:**
- Label di Halaman 1 (MCU) cocok dengan halaman lain
- Semua power rails (+12V, +5V, +3V3, GND) konsisten
- Tidak ada pin yang mengambang (tidak terhubung)

### 2. Generate Netlist

1. Di halaman utama, klik **File > Fabrication Outputs > Netlist**
2. Format: **KiCad**
3. Klik **Generate Netlist**
4. Simpan as `ECU_Warkop_X.net`

### 3. Tetapkan Footprint

**Untuk setiap komponen, assign physical package:**

1. Klik **Tools > Assign Footprints**
2. Window buka menunjukkan semua komponen
3. Untuk tiap komponen, pilih footprint dari kolom kanan:
   - U1 → `LQFP-100_14x14mm_P0.5mm`
   - Resistor 0603 → `R_0603_1608Metric`
   - Kapasitor 0603 → `C_0603_1608Metric`
   - Dll (lihat BOM untuk reference)
4. Klik **Apply, Save Schematic & Continue**

### 4. Update PCB dari Schematic

1. Buka PCB editor: `ECU_Warkop_X.kicad_pcb`
2. Klik **Tools > Update PCB from Schematic** (F8)
3. Review changes
4. Klik **Update PCB**
5. Semua komponen akan muncul di PCB (masih bertumpuk)

### 5. Siap untuk Layout PCB!

**Next:**
- Atur outline papan
- Tempatkan komponen (gunakan data position CSV!)
- Route jalur
- Design rule check
- Generate Gerber
- Pesan PCB

---

## Tips & Trik Tambahan

### Jika Simbol Tidak Ketemu

**Install library tambahan:**
1. File > Preferences > Manage Symbol Libraries
2. Klik tab "Global Libraries"
3. Klik "+" untuk tambah
4. Browse ke folder symbols KiCad
5. Pilih `.kicad_sym` file yang diperlukan

### Jika Footprint Tidak Cocok

**Buat custom footprint:**
1. Buka Footprint Editor
2. File > New Footprint
3. Gambar pads sesuai datasheet
4. Simpan di library custom
5. Assign ke komponen

### Backup Berkala

**Save version:**
- Setiap selesai 1 halaman, save
- Buat copy folder: `ECU_Warkop_X_backup_DDMMYY`
- Git commit (kalau pakai version control)

### Gunakan Hotkeys!

**Paling sering:**
- **A**: Add symbol
- **W**: Wire
- **P**: Power
- **L**: Label
- **M**: Move
- **R**: Rotate
- **E**: Edit
- **Ctrl+Z**: Undo
- **Ctrl+S**: Save
- **F**: Fit to screen

---

## Estimasi Waktu Total

| Halaman | Waktu |
|---------|-------|
| 1. Inti MCU | 3-4 jam |
| 2. Antarmuka IO | 45 menit |
| 3. Catu Daya | 1 jam |
| 4. Input Analog | 1.5 jam |
| 5. Pengendali Output | 2 jam |
| 6. Komunikasi | 45 menit |
| 7. Sensor Lain | 1 jam |
| **Pemeriksaan & Footprint** | 1-2 jam |
| **TOTAL** | **11-13 jam** |

**Jangan buru-buru!** Lebih baik lambat tapi benar.

---

**SELAMAT! Anda telah menyelesaikan skema ECU yang lengkap!** 🎉

**Next step**: Layout PCB dan pesan papan untuk manufaktur.
