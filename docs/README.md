# Dokumentasi Warkop-X ECU

Kumpulan dokumentasi firmware Warkop-X ECU. Silakan baca sesuai kebutuhan.

## Daftar File

### Untuk Pengguna

**[OPTIMIZATION_QUICK_GUIDE.md](OPTIMIZATION_QUICK_GUIDE.md)** - Start di sini
- Panduan cepet optimasi flash/RAM
- Cara enable/disable fitur
- TL;DR version dari semua docs

**[CAN_BUS_PINOUT.md](CAN_BUS_PINOUT.md)**
- Wiring CAN bus ke dashboard
- Pin configuration
- TunerStudio setup

**[QUICKSHIFT_SETUP.md](QUICKSHIFT_SETUP.md)**
- Pasang quick shifter
- Konfigurasi cut time

### Untuk Developer

**[SOURCE_CODE_DOCUMENTATION.md](SOURCE_CODE_DOCUMENTATION.md)**
- Struktur codebase lengkap
- Penjelasan directory layout
- Build system

**[CLOSED_LOOP_REFERENCE.md](CLOSED_LOOP_REFERENCE.md)**
- Fuel trim (STFT/LTFT) logic
- Idle control functions
- Function locations

### Reference Lists

**[FEATURE_OPTIMIZATION_GUIDE.md](FEATURE_OPTIMIZATION_GUIDE.md)**
- Daftar semua feature flags rusEFI
- Flash/RAM cost per feature
- Template optimization

**[CURRENT_OPTIMIZATION_STATUS.md](CURRENT_OPTIMIZATION_STATUS.md)**
- Comparison: udah disabled vs belum
- Skenario use-case
- Current status

## Quick Links

### Pertama kali setup?
1. Flash firmware → Liat README.md utama
2. Setup CAN dashboard → [CAN_BUS_PINOUT.md](CAN_BUS_PINOUT.md)
3. Pasang quickshift (optional) → [QUICKSHIFT_SETUP.md](QUICKSHIFT_SETUP.md)

### Mau optimasi flash?
1. Baca [OPTIMIZATION_QUICK_GUIDE.md](OPTIMIZATION_QUICK_GUIDE.md) dulu
2. Kalo perlu detail → [FEATURE_OPTIMIZATION_GUIDE.md](FEATURE_OPTIMIZATION_GUIDE.md)

### Mau modif code?
1. Pahami struktur → [SOURCE_CODE_DOCUMENTATION.md](SOURCE_CODE_DOCUMENTATION.md)
2. Fuel trim logic → [CLOSED_LOOP_REFERENCE.md](CLOSED_LOOP_REFERENCE.md)

## Current Status

Setup saat ini udah optimal:
- Flash: ~300KB / 512KB (58%)
- RAM: ~90KB / 128KB (70%)
- Hemat: ~300KB dari disable fitur

Fitur aktif:
- CAN bus untuk dashboard
- Auto idle control
- Sequential injection
- Individual coil ignition

## Cara Cari Info

Search di docs:
```bash
grep -r "keyword" docs/
```

Atau buka file yang relevan di atas.

## File Konfigurasi Penting

File yang sering diedit:
- `board.mk` - Feature flags, optimization
- `board_configuration.cpp` - Pin assignment, hardware config
- `default_tune.cpp` - Default tune values

## External Links

- rusEFI wiki: https://github.com/rusefi/rusefi/wiki
- Forum: https://rusefi.com/forum/
- TunerStudio: https://www.tunerstudio.com/

## Specs

Hardware:
- MCU: STM32F407VET6
- Flash: 512KB (384KB usable)
- RAM: 128KB + 64KB CCM

Engine:
- Yamaha Vixion OLD (3C1)
- 200cc single cylinder
- Sequential injection

---

Update terakhir: 2024-12-24
