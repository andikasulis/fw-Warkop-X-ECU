# Dokumentasi Firmware Warkop X ECU

Repository ini berisi dokumentasi pembelajaran untuk firmware RusEfi yang dikustomisasi untuk **Warkop X ECU** berbasis STM32F407VET6.

## 📚 Daftar Dokumentasi

### 1. [RusEfi Firmware Guide](rusefi_firmware_guide.md)
Panduan lengkap tentang arsitektur firmware RusEfi, mencakup:
- Arsitektur keseluruhan dan struktur modul
- Boot sequence dan initialization flow
- Main control loop (event-driven architecture)
- Trigger system untuk crank/cam decoding
- Fuel injection logic (VE table, corrections, STFT/LTFT)
- Ignition timing logic
- Sensor processing framework
- Communication protocols (TunerStudio, console)
- Periodic tasks dan scheduling
- Configuration management
- Build system dan optimasi untuk VET6 (512KB flash)

### 2. [VE Auto-Tune Explanation](ve_autotune_explanation.md)
Penjelasan detail tentang sistem auto-tuning VE table:
- Short Term Fuel Trim (STFT) - koreksi real-time
- Long Term Fuel Trim (LTFT) - learning algorithm
- Burning process ke VE table
- Flow diagram lengkap dari sensor sampai flash storage

### 3. [Firmware Comparison](firmware_comparison.md)
Perbandingan detail antara Warkop X ECU dan RusEfi Original:
- Perbedaan hardware (VET6 vs VGT6)
- Feature matrix comparison
- Performance benchmarks
- Cost-benefit analysis
- Use case scenarios
- Migration paths
- Recommendation matrix untuk berbagai aplikasi

- **Developer** yang ingin memahami internal RusEfi firmware
- **Tuner** yang ingin tahu cara kerja auto-tune dan fuel mapping
- **Hardware enthusiast** yang ingin customize board sendiri
- **Learner** yang ingin belajar embedded systems dan engine management

## 🚀 Warkop X ECU Specs

- **MCU**: STM32F407VET6 (512KB Flash, 192KB RAM)
- **Target**: Yamaha Vixion 150cc (2-cylinder, 4-stroke)
- **Build**: Custom optimized (384KB firmware + 128KB settings)
- **Features disabled**: Lua, ETB, Boost Control, CAN (untuk hemat flash)

## 📖 Cara Menggunakan

1. **Mulai dari Firmware Guide** - Pahami arsitektur secara keseluruhan
2. **Pelajari VE Auto-Tune** - Jika tertarik dengan fuel mapping otomatis
3. **Lihat source code** - Gunakan dokumentasi sebagai reference saat explore code

## 🔗 Link Berguna

- [RusEfi Official Wiki](https://rusefi.com)
- [RusEfi GitHub](https://github.com/rusefi/rusefi)
- [TunerStudio](https://www.tunerstudio.com)

## 📝 Kontribusi

Dokumentasi ini adalah hasil pembelajaran dan mungkin ada yang kurang akurat. 
Jika menemukan kesalahan atau ingin menambahkan, silakan buat PR atau issue.

---

**Last Updated**: 2025-12-23  
**Firmware Version**: RusEfi custom build for Warkop X ECU
