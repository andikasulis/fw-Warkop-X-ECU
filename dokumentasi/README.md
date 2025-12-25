# 📁 Panduan Organisasi Folder - ECU Warkop X

## Struktur Folder Lengkap

```
ECU_Warkop_X/
│
├── 📁 dokumentasi/                    ← SEMUA DOKUMENTASI DI SINI
│   │
│   ├── 📁 panduan_kicad/              ← Panduan membuat schematic
│   │   ├── Panduan_Lengkap_KiCad_ECU.md      (UTAMA - baca ini dulu!)
│   │   ├── KiCad_Navigation_Guide.md         (Navigasi antar halaman)
│   │   └── KiCad_Guide_Pemula.md             (Panduan dasar KiCad)
│   │
│   ├── 📁 analisis_skema/             ← Hasil analisis dari PDF
│   │   ├── 📁 hd_images/              ← Gambar HD skema (JPG)
│   │   ├── component_database.md     ← Database 220+ komponen
│   │   ├── component_positions.csv   ← Koordinat PCB (228 komponen)
│   │   ├── page1_mcu_core.md         ← Analisis detail halaman 1
│   │   ├── pages2-8_complete.md      ← Analisis halaman 2-8
│   │   ├── Barometric_Sensor_Detail.md ← Detail sensor baro (U9)
│   │   ├── HD_Images_Verification_Report.md ← Laporan verifikasi
│   │   └── Schematics (1).pdf        ← PDF asli
│   │
│   └── 📁 referensi/                  ← Dokumen referensi
│       ├── Schematic_Section_Titles.md    ← Daftar section titles
│       └── Section_Titles_Update_Summary.md
│
├── 📁 KiCad_Recreation/               ← Project KiCad (Anda buat nanti)
│   ├── ECU_Warkop_X.kicad_pro
│   ├── ECU_Warkop_X.kicad_sch
│   └── sheets/
│       ├── Inti_MCU.kicad_sch
│       ├── Antarmuka_IO.kicad_sch
│       ├── Catu_Daya.kicad_sch
│       ├── Input_Analog.kicad_sch
│       ├── Pengendali_Output.kicad_sch
│       ├── Komunikasi.kicad_sch
│       └── Sensor_Lain.kicad_sch
│
├── 📁 ext/                            ← rusEFI firmware (sudah ada)
│   └── rusefi/
│
├── 📁 tunerstudio/                    ← TunerStudio config
│
└── 📁 .github/                        ← GitHub Actions workflows
```

---

## Cara Pakai Folder Ini

### 🚀 **Mulai dari mana?**

#### Jika Anda **Baru pertama kali** belajar KiCad:

**Urutan baca:**
1. `dokumentasi/panduan_kicad/Panduan_Lengkap_KiCad_ECU.md` ← **START HERE**
   - Baca dari awal sampai akhir
   - Cocok untuk pemula awam elektronik
   
2. `dokumentasi/panduan_kicad/KiCad_Navigation_Guide.md`
   - Pelajari cara navigasi antar halaman
   - Penting sebelum mulai membuat schematic

3. Mulai buat schematic di KiCad
   - Ikuti panduan step-by-step
   - Refer ke dokumentasi saat butuh

#### Jika mau **Lihat skema asli**:

1. Buka folder: `dokumentasi/analisis_skema/hd_images/`
2. Lihat file JPG: `Schematics (1)_page-0001.jpg` sampai `...-0008.jpg`
3. Atau buka PDF asli: `dokumentasi/analisis_skema/Schematics (1).pdf`

#### Jika **Cari komponen spesifik**:

1. Buka: `dokumentasi/analisis_skema/component_database.md`
2. Search (Ctrl+F) nama komponen, contoh: "LPS25HB", "STM32", "MOSFET"

#### Jika **Butuh koordinat untuk PCB**:

1. Buka: `dokumentasi/analisis_skema/component_positions.csv`
2. Format: X, Y, rotation, side, designator, value, footprint

---

## File Penting & Fungsinya

### 📘 Panduan Utama

| File | Fungsi | Untuk Siapa |
|------|--------|-------------|
| **Panduan_Lengkap_KiCad_ECU.md** | Panduan lengkap 1667 baris, semua halaman | **WAJIB BACA** untuk pemula |
| **KiCad_Navigation_Guide.md** | Cara navigasi hierarchical sheets | Pemula yang bingung pindah-pindah halaman |
| **KiCad_Guide_Pemula.md** | Pengenalan KiCad basics | Belum pernah pakai KiCad sama sekali |

### 📊 Analisis & Data

| File | Fungsi | Kapan Dipakai |
|------|--------|---------------|
| **component_database.md** | Database 220+ komponen | Saat place komponen, cek nilai/part number |
| **component_positions.csv** | Koordinat PCB exact | Saat PCB layout (import coordinates) |
| **page1_mcu_core.md** | Detail halaman 1 (MCU) | Deep dive halaman paling kompleks |
| **pages2-8_complete.md** | Overview halaman 2-8 | Quick reference circuit sections |
| **Barometric_Sensor_Detail.md** | Detail lengkap sensor baro U9 | Spesifik untuk sensor baro |

### 🖼️ Gambar HD

| Folder/File | Fungsi | Kapan Dipakai |
|-------------|--------|---------------|
| **hd_images/*.jpg** | Skema 8 halaman HD (5.9MB) | Visual reference saat wiring |
| **Schematics (1).pdf** | PDF asli | Backup, print reference |

### 📚 Referensi

| File | Fungsi | Kapan Dipakai |
|------|--------|---------------|
| **Schematic_Section_Titles.md** | Daftar semua section titles | Cross-reference dengan skema asli |
| **Section_Titles_Update_Summary.md** | Summary update section titles | Info apa yang sudah ditambahkan |

---

## Tips Organisasi

### ✅ **DO (Lakukan)**:

1. **Bookmark folder `dokumentasi/`** di Finder/Explorer
   - Quick access ke semua panduan

2. **Buka Panduan_Lengkap** di editor terpisah saat coding
   - Split screen: KiCad | Panduan
   - Mudah refer bolak-balik

3. **Simpan KiCad project di `KiCad_Recreation/`**
   - Terpisah dari dokumentasi
   - Bersih dan terorganisir

4. **Print/Export panduan ke PDF** jika suka baca offline
   - Markdown → PDF via Pandoc atau export browser

### ❌ **DON'T (Jangan)**:

1. **Jangan edit file di folder `dokumentasi/analisis_skema/`**
   - Itu hasil analisis - keep as reference
   - Buat notes terpisah jika perlu

2. **Jangan pindah-pindah file antar folder**
   - Struktur sudah optimal
   - Nanti bingung cari

3. **Jangan hapus file apapun** (even yang kelihatan tidak penting)
   - Semua file saling berkaitan
   - Backup dulu jika mau cleanup

---

## Quick Reference: Di mana File X?

### "Saya mau mulai belajar KiCad"
→ `dokumentasi/panduan_kicad/Panduan_Lengkap_KiCad_ECU.md`

### "Saya butuh lihat skema asli"
→ `dokumentasi/analisis_skema/hd_images/` (JPG files)

### "Saya lupa nilai resistor R35"
→ `dokumentasi/analisis_skema/component_database.md` (search R35)

### "Saya bingung navigasi KiCad"
→ `dokumentasi/panduan_kicad/KiCad_Navigation_Guide.md`

### "Sensor baro ada di mana?"
→ `dokumentasi/analisis_skema/Barometric_Sensor_Detail.md`

### "Section 'Injector Driver 1' itu apa?"
→ `dokumentasi/referensi/Schematic_Section_Titles.md`

### "Koordinat Q1 di PCB?"
→ `dokumentasi/analisis_skema/component_positions.csv` (search Q1)

---

## Backup Strategy

### Penting untuk Backup:

**Folder yang WAJIB backup:**
- ✅ `dokumentasi/` - Semua panduan & analisis
- ✅ `KiCad_Recreation/` - Project KiCad Anda (saat sudah mulai)

**Cara backup:**
1. **Manual copy** ke USB/external drive tiap selesai session
2. **Git** (recommended):
   ```bash
   cd ~/Documents/_DATA\ ANDIKA/RusEfi/fw-Warkop-X-ECU
   git init
   git add dokumentasi/ KiCad_Recreation/
   git commit -m "Backup dokumentasi ECU"
   ```
3. **Cloud sync** (Dropbox, Google Drive)

---

## Next Steps

### Anda Sekarang di Sini: ✅ Dokumentasi Lengkap

**Langkah selanjutnya:**

1. **Install KiCad** (jika belum)
   ```bash
   brew install kicad
   ```

2. **Baca panduan lengkap**
   - File: `dokumentasi/panduan_kicad/Panduan_Lengkap_KiCad_ECU.md`
   - Waktu: ~30-60 menit (skim read)

3. **Create KiCad project**
   - Lokasi: `KiCad_Recreation/`
   - File: `ECU_Warkop_X.kicad_pro`

4. **Mulai Halaman 1**
   - Follow panduan step-by-step
   - Refer ke HD images saat wiring

5. **Lanjut ke Halaman 2-7**
   - One by one
   - Save sering!

6. **Assign footprints** → PCB layout → Order PCB!

---

## Troubleshooting

### "File X tidak ketemu"
- Check folder dokumentasi/
- Gunakan Finder/Explorer search
- Lihat structure diagram di atas

### "Terlalu banyak file, bingung"
- **Focus** di `Panduan_Lengkap_KiCad_ECU.md` dulu
- File lain = reference (buka saat perlu)

### "Mau tambah notes sendiri"
- Buat folder `dokumentasi/my_notes/`
- Jangan edit file existing

---

**Folder sudah terorganisir rapi! Tinggal mulai belajar & membuat schematic.** 🚀
