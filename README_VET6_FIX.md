# Dokumentasi Perbaikan Bricking STM32F407VET6 (Vixion)

Dokumentasi ini menjelaskan solusi teknis untuk masalah "Serial Communication Error/Bricking" yang terjadi saat proses **Burn** di TunerStudio pada chip STM32F407VET6 (512KB Flash).

## 1. Analisis Masalah
ECU mengalami *brick* (macet total) setiap kali menyimpan setting karena terjadi **Conflict Flash Memory**.
*   **Default rusEFI**: Berasumsi chip memiliki 1024KB (VGT6). Firmware bisa berukuran hingga 800KB+.
*   **Hardware VET6**: Hanya memiliki 512KB.
*   **Konflik**: Firmware yang berukuran > 384KB akan meluap masuk ke **Sektor 7 (0x08060000)**. Sektor 7 adalah tempat rusEFI menyimpan setting. Saat klik "Burn", ECU menghapus Sektor 7, yang secara tidak sengaja menghapus sebagian kode program firmware itu sendiri.

## 2. Solusi Teknis (The Fix)

### A. Pembatasan Memori Fisik (Linker Script)
Kita menggunakan file kustom [STM32F407VET6.ld](file:///Users/andikasulispratama/Documents/_DATA%20ANDIKA/RusEfi/fw-Warkop-X-ECU/STM32F407VET6.ld) yang membagi memori secara ketat:
- **Firmware Area**: 0x08000000 - 0x0805FFFF (**Maksimal 384 KB**).
- **Settings Area**: 0x08060000 - 0x0807FFFF (**Eksklusif 128 KB**).

Jika file firmware hasil build melebihi 384 KB, proses build di GitHub Actions akan otomatis **Gagal (Error)**. Ini adalah fitur keamanan agar Anda tidak mem-flash file yang berisiko merusak ECU.

### B. Patch Sistem Build
File `ext/rusefi/firmware/hw_layer/ports/stm32/stm32f4/hw_ports.mk` diubah dari:
`LDSCRIPT = ...` menjadi `LDSCRIPT ?= ...`
Perubahan ini memastikan sistem build rusEFI wajib menghormati Linker Script kustom 384KB kita.

### C. Proteksi Runtime
File `ext/rusefi/firmware/hw_layer/ports/stm32/stm32f4/mpu_util.cpp` dipatch untuk:
- Memaksa deteksi chip sebagai **512 KB**.
- Mematikan fitur "Second Copy" settings yang berbahaya pada chip kecil untuk mencegah penulisan alamat memori ilegal.

## 3. Fitur yang Dinonaktifkan (Firmware Diet)
Untuk menjaga ukuran firmware tetap di bawah 384 KB, fitur-fitur berikut telah dimatikan di [board.mk](file:///Users/andikasulispratama/Documents/_DATA%20ANDIKA/RusEfi/fw-Warkop-X-ECU/board.mk):

| Kategori | Fitur yang Dimatikan |
| :--- | :--- |
| **Komunikasi** | CAN Bus (Serial, GPIO), Wi-Fi, Ethernet |
| **Penyimpanan** | SD Card Support, USB Mass Storage (ECU as Flashdisk) |
| **Logic/Mesin** | Lua Scripting, ETB (Drive-by-wire), Turbo Boost, VVT, GDI, HPFP |
| **Diagnosa** | Logic Analyzer, Tooth Logger, Text Logging, Spectrum Analyzer |
| **Aksesoris** | LED WS2812 (NeoPixel), Antilag, Launch Control |

## 4. Panduan Pemeliharaan (Maintenance)

### Jika ingin menambah fitur kembali:
Pastikan ukuran file `.bin` hasil build tetap **dibawah 384 KB**. Anda bisa memantau ukuran file di log GitHub Actions atau pada nama file artifact yang dihasilkan.

### Jika Build Gagal di GitHub:
Itu artinya firmware Anda sudah terlalu besar (> 384KB). Anda harus mematikan fitur lain di `board.mk` sebelum bisa menghasilkan firmware yang aman untuk di-flash.

---
**Status Terakhir**: 
- Binary Size: **384 KB (Enforced)**
- Burn Status: **SUCCESS & STABLE**
- Tanggal: 21 Desember 2025
