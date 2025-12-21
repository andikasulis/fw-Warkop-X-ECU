# Warkop X ECU - Custom RusEfi Firmware

Custom RusEfi firmware for **Yamaha Vixion OLD (3C1)** 200cc single cylinder motorcycle ECU.

**Board:** Warkop X ECU R1  
**MCU:** STM32F407VGT6 (1024 KB flash)  
**Firmware Version:** 0.1  
**Binary Size:** 297 KB (29% flash usage)

> **📌 STM32F407VET6 Variant (512 KB flash):** See [README_VET6.md](README_VET6.md) for VET6-specific build instructions. In this branch, the firmware is capped at **384 KB** to protect the settings sector!

---

## 🎯 Features

### ✅ Engine Control
- **Sequential Fuel Injection** - 4 individual injector outputs
- **Individual Coil Ignition** - 4 independent ignition outputs
- **Alpha-N Load Mode** - Optimized for single cylinder engines
- **Auto Idle Control** - Automatic idle valve control
- **Rev Limiter** - Hard limit at 12,000 RPM
- **Closed-Loop O2 Control** - AFR correction via wideband sensor

### ✅ Inputs & Sensors
- **Trigger System:**
  - CKP (Crankshaft Position) - 12-1 toothed wheel detection
  - CMP (Camshaft Position) - Sequential injection timing
- **Analog Sensors (6 channels):**
  - MAP (Manifold Absolute Pressure)
  - O2/AFR (Wideband Lambda Sensor)
  - TPS (Throttle Position Sensor)
  - CLT (Coolant Temperature)
  - IAT (Intake Air Temperature)
  - Battery Voltage
  - + 10 additional ADC channels available
- **Digital Inputs:**
  - VSS (Vehicle Speed Sensor)
  - AC Pressure Switch
  - Clutch Switch

### ✅ Outputs & Actuators
- **Relays:**
  - Fuel Pump Relay (auto-controlled)
  - Radiator Fan Relay (temp-controlled: 88-92°C)
  - AC Compressor Relay
  - Main Relay
- **PWM Outputs:**
  - Idle Control Valve
  - Tachometer Output
- **Communication:**
  - CAN Bus (external dashboard support)
  - UART1 (TunerStudio via USB/Bluetooth)
  - UART3 (auxiliary communication)

### ✅ Data Logging & Diagnostics
- **SD Card Logging** - Full datalog via SPI3
- **TunerStudio Support** - Complete tuning and monitoring
- **Real-time Sensor Display** - All channels available for logging
- **Communication LED** - Status indicator (Gpio B7)

### ✅ Advanced Features (Optional)
- **Launch Control** - Commented in code, ready to enable
- **Flex Fuel Support** - E85/gasoline detection ready
- **Knock Detection** - Hardware ready (requires knock sensor)

---

## ❌ Disabled Features (Flash Optimization)

The following features are **disabled** to save flash memory (~95-143 KB saved):

| Feature | Flash Saved | Reason |
|---------|-------------|--------|
| **Lua Scripting** | ~40-60 KB | CAN bus works without Lua |
| **Wideband FW Update** | ~20-30 KB | AFR sensor works normally |
| **Electronic Throttle Body** | ~15-20 KB | Cable throttle only |
| **Boost Control** | ~10-15 KB | Naturally aspirated engine |
| **VVT Control** | ~5-8 KB | No VVT hardware |
| **Antilag System** | ~5-10 KB | Street bike (not racing) |

**Note:** All critical features (CAN, AFR, SD logging) remain **FULLY FUNCTIONAL**!

---

## 🔧 Hardware Configuration

### Pin Mapping Summary (35 pins total)

**Ignition Outputs:**
- IGN1: PE15
- IGN2: PE14
- IGN3: PD13
- IGN4: PE5

**Injector Outputs:**
- INJ1: PD8
- INJ2: PB15
- INJ3: PB14
- INJ4: PB13

**Trigger Inputs:**
- CKP: PD3
- CMP: PD4

**Analog Inputs (ADC):**
- MAP: PA0 (ADC0)
- O2/AFR: PA1 (ADC1)
- Battery: PA2 (ADC2)
- TPS: PA3 (ADC3)
- CLT: PA4 (ADC4)
- IAT: PA5 (ADC5)
- AC Switch: PB0 (ADC8)
- Reserved: PB1 (ADC9)

**Relays & Actuators:**
- Fuel Pump: PC8
- Fan: PA15
- AC Compressor: PC7
- Main Relay: PE8
- Idle Valve: PD9
- Tacho: PC9

**Communication:**
- CAN TX: PD1
- CAN RX: PD0
- UART1 TX: PA9
- UART1 RX: PA10
- UART3 TX: PB10
- UART3 RX: PB11

**SD Card (SPI3):**
- CS: PD2
- MOSI: PC12
- MISO: PC11
- SCK: PC10

**LEDs:**
- Comms LED: PB7

> **Full pin mapping:** See `connectors/custom_firmware.yaml`

---

## 🏍️ Engine Specifications

**Vehicle:** Yamaha Vixion OLD  
**Engine Code:** 3C1  
**Displacement:** 200cc  
**Configuration:** Single cylinder, 4-stroke  
**Bore:** 87.5 mm  
**Compression Ratio:** 9.0:1  
**Firing Order:** Single (FO_1)

**Defaults:**
- Injector Flow: 180 cc/min
- Injection Mode: Sequential
- Ignition Mode: Individual coils
- Idle Target: Cold ~1360 RPM, Warm ~900 RPM
- Cranking RPM: 450 RPM
- RPM Hard Limit: 12,000 RPM
- Fan On: 92°C
- Fan Off: 88°C

**Trigger Configuration:**
- Type: Toothed wheel (12-1)
- Total Teeth: 12
- Missing Teeth: 1
- Trigger Offset: 186.0°

---

## 📦 Build Information

**Platform:** RusEfi (STM32F4 architecture)  
**Compiler:** ARM GCC 14.2.Rel1  
**Build System:** ChibiOS RTOS + Makefile  
**GitHub Actions:** Automated build on push

**Flash Usage:**
```
Binary Size:  297 KB
Flash Total:  1024 KB
Flash Used:   29%
Free Space:   727 KB (71%)
```

**Build Status:**  
[![Build Firmware](https://github.com/andikasulis/fw-Warkop-X-ECU/actions/workflows/build-firmware.yaml/badge.svg)](https://github.com/andikasulis/fw-Warkop-X-ECU/actions)

---

## 🚀 Getting Started

### Prerequisites
- STM32F407VG-based Warkop X ECU hardware
- ST-Link V2 programmer or USB DFU mode
- TunerStudio MS (for tuning)

### 1. Download Firmware
Download the latest build artifacts from [GitHub Actions](https://github.com/andikasulis/fw-Warkop-X-ECU/actions):
- `rusefi_warkop_x.hex` - for ST-Link
- `rusefi_warkop_x.bin` - for DFU mode
- `rusefi_warkop_x.ini` - TunerStudio configuration

### 2. Flash to ECU

**Option A: ST-Link**
```bash
st-flash write rusefi_warkop_x.bin 0x08000000
```

**Option B: DFU Mode**
```bash
dfu-util -a 0 -s 0x08000000 -D rusefi_warkop_x.bin
```

### 3. Connect TunerStudio
1. Load `rusefi_warkop_x.ini` in TunerStudio
2. Select COM port (UART1: 115200 baud)
3. Connect to ECU
4. Verify sensor readings

### 4. Initial Setup
- [ ] Calibrate TPS (min/max values)
- [ ] Verify trigger pattern (12-1 toothed wheel)
- [ ] Check all sensor readings
- [ ] Test CAN bus communication
- [ ] Confirm SD card logging
- [ ] Set base timing with timing light

---

## 📚 Documentation

- **RusEfi Wiki:** https://github.com/rusefi/rusefi/wiki/Custom-Firmware
- **Pin Configuration:** `connectors/custom_firmware.yaml`
- **Board Setup:** `board_configuration.cpp`
- **Engine Defaults:** `default_tune.cpp`
- **Build Config:** `board.mk`

---

## 🛠️ Development

### Build Locally
```bash
cd ext/rusefi/firmware
bash compile_firmware.sh ../../../meta-info.env
```

### Modify Configuration
1. **Pin Mapping:** Edit `connectors/custom_firmware.yaml`
2. **Hardware Setup:** Edit `board_configuration.cpp`
3. **Engine Defaults:** Edit `default_tune.cpp`
4. **Flash Optimization:** Edit `board.mk`

### Enable Optional Features
Edit `board.mk` to enable:
```makefile
# Enable Lua scripting (adds ~40-60 KB)
DDEFS += -DEFI_LUA=TRUE

# Enable knock detection (adds ~15-20 KB, requires knock sensor)
DDEFS += -DEFI_SOFTWARE_KNOCK=TRUE
DDEFS += -DKNOCK_SPECTROGRAM=TRUE
```

---

## ⚠️ Important Notes

1. **Safety First:**
   - This firmware is for TESTING only
   - Always have backup ignition system during initial testing
   - Start with conservative timing and fuel maps
   - Monitor AFR closely during first runs

2. **Hardware Requirements:**
   - Wideband O2 sensor recommended for closed-loop
   - 12-1 toothed wheel on crankshaft
   - Individual ignition coils
   - Compatible injectors (180 cc/min or similar)

3. **Tuning:**
   - Base maps are conservative defaults
   - Professional tuning highly recommended
   - Use TunerStudio for all adjustments
   - Log data for analysis

---

## 📝 License

This project is based on [RusEfi](https://github.com/rusefi/rusefi) open-source ECU firmware.

**RusEfi License:** GPL v3

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

---

## 📧 Support

- **Issues:** [GitHub Issues](https://github.com/andikasulis/fw-Warkop-X-ECU/issues)
- **RusEfi Forums:** https://rusefi.com/forum/
- **RusEfi Slack:** https://rusefi.com/forum/viewtopic.php?f=13&t=1198

---

**Made with ❤️ for Yamaha Vixion OLD community**
