# Dokumentasi Source Code Warkop-X ECU

Panduan buat yang mau nge-hack source code firmware.

**MCU:** STM32F407VET6 (512KB Flash)  
**Base:** rusEFI firmware  
**Motor:** Yamaha Vixion OLD 200cc

---

## Struktur Directory

```
fw-Warkop-X-ECU/
├── board.mk                    # Config utama (feature flags, optimization)
├── board_configuration.cpp     # Pin assignment, hardware setup
├── default_tune.cpp            # Default tune values (VE, ignition, dll)
├── STM32F407VET6.ld           # Linker script (memory layout)
├── meta-info.env              # Build metadata
│
├── docs/                      # Dokumentasi
│   ├── README.md
│   ├── CAN_BUS_PINOUT.md
│   └── ...
│
├── generated/                 # Auto-generated files (jangan edit manual!)
│   ├── controllers/generated/
│   └── tunerstudio/generated/
│
└── ext/rusefi/               # rusEFI core (git submodule)
    └── firmware/
        ├── controllers/      # Engine control logic
        ├── hw_layer/        # Hardware abstraction
        ├── ChibiOS/         # RTOS
        └── ...
```

---

## File Penting

### 1. board.mk

File konfigurasi utama. Isinya:

- Feature flags (`-DEFI_LUA=FALSE`)
- Compiler optimization (`-Os`, `-flto`)
- Memory settings (`RAM_UNUSED_SIZE`)
- Flash size definition

**Contoh:**
```makefile
# Disable Lua
DDEFS += -DEFI_LUA=FALSE

# Enable CAN
DDEFS += -DEFI_CAN_SUPPORT=TRUE

# Optimize size
USE_OPT += -Os -flto
```

### 2. board_configuration.cpp

Pin assignment dan hardware init.

**Fungsi utama:**
- `setBoardDefaultConfiguration()` - Set default config
- Pin mapping (TPS, CLT, IAT, injector, coil, dll)
- CAN bus pins

**Contoh:**
```cpp
// CAN pins
engineConfiguration->canTxPin = Gpio::A12;
engineConfiguration->canRxPin = Gpio::A11;

// TPS
engineConfiguration->tps1_1AdcChannel = EFI_ADC_4;  // PA4
```

### 3. default_tune.cpp

Default tune values. Diload pas first boot.

Isi:
- VE table
- Ignition table
- AFR target
- Idle settings
- Rev limit

**Kalo mau ganti default tune, edit file ini.**

### 4. STM32F407VET6.ld

Linker script. Tentuin memory layout.

```
Flash: 512 KB total
├── 384 KB untuk firmware (0x08000000)
└── 128 KB untuk settings (Sector 7)

RAM: 128 KB (0x20000000)
CCM: 64 KB (0x10000000)
```

**Jangan edit kecuali tau yang lu lakuin!**

---

## rusEFI Core (ext/rusefi/)

### Directory Structure

```
ext/rusefi/firmware/
│
├── controllers/             # Engine control logic
│   ├── algo/               # Core algorithms
│   │   ├── engine.cpp      # Main engine state
│   │   ├── fuel/           # Fuel calculations
│   │   └── ignition/       # Ignition timing
│   │
│   ├── math/               # Math utilities
│   │   ├── closed_loop_fuel.cpp    # STFT/LTFT
│   │   └── closed_loop_idle.cpp    # Idle control
│   │
│   ├── sensors/            # Sensor abstraction
│   ├── actuators/          # Output control
│   ├── trigger/            # Trigger decoder
│   └── can/               # CAN bus
│
├── hw_layer/               # Hardware abstraction
│   ├── ports/stm32/       # STM32 specific
│   ├── adc/               # ADC reading
│   └── drivers/           # Driver layers
│
├── console/               # TunerStudio communication
├── ChibiOS/              # RTOS
└── integration/          # Config definitions
```

### Key Components

**1. Engine Control Loop**

File: `controllers/algo/engine.cpp`

Main loop jalan di `periodicFastCallback()` (~100Hz):
1. Baca sensors (TPS, CLT, MAP, dll)
2. Hitung fuel amount
3. Hitung ignition timing
4. Schedule injector & coil events

**2. Trigger Decoder**

File: `controllers/trigger/trigger_decoder.cpp`

Decode crank/cam signals. Support 90+ trigger patterns.

Warkop-X pake: **Toothed wheel (12-1)**

**3. Fuel Control**

Files:
- `controllers/algo/fuel/fuel_computer.cpp` - Base fuel calc
- `controllers/math/closed_loop_fuel.cpp` - STFT/LTFT

Main function: `getInjectionDuration(rpm, load)`

**4. Ignition Control**

Files:
- `controllers/algo/advance_map.cpp` - Base advance
- `controllers/algo/ignition/ignition_control.cpp` - Timing calc

Main function: `getAdvance(rpm, load)`

**5. Idle Control**

File: `controllers/actuators/idle_controller.cpp`

PID loop. Target RPM vs actual RPM.

**6. CAN Bus**

File: `controllers/can/can_tx.cpp`, `can_dash.cpp`

Kirim data ke dashboard via CAN.

---

## Build System

### Compile Process

1. Run `make` di `ext/rusefi/firmware/`
2. Make baca `board.mk`
3. Generate config files (Java tools)
4. Compile C/C++ code (ARM GCC)
5. Link jadi `.elf`
6. Convert ke `.bin`, `.hex`, `.srec`

### Build Commands

```bash
cd ext/rusefi/firmware/

# Build firmware
make -j8

# Clean
make clean

# Upload via DFU
make dfu_upload
```

### Automated Build

GitHub Actions auto-build on push:
- File: `.github/workflows/build-firmware.yaml`
- Output: Artifacts (.bin, .hex, .ini)

---

## Configuration System

### Config Generator

rusEFI pake Java tools buat generate config files.

**Input:**
- `integration/rusefi_config.txt` - Config definitions
- `board_config.txt` - Board overrides

**Output:**
- `controllers/generated/*.h` - C headers
- `tunerstudio/generated/*.ini` - TunerStudio INI

### Custom Config

Edit `board_config.txt` buat override type definitions.

Contoh (TPS calibration fix):
```
! Custom TPS range (ADC count instead of voltage)
custom tps_limit_t 2 scalar, S16, @OFFSET@, "ADC", 1, 0, 0, 1023, 0
```

---

## Hardware Abstraction

### ADC Reading

File: `hw_layer/adc/adc_inputs.cpp`

Map ADC channel ke sensor:
```cpp
#define EFI_ADC_4  ADC_CHANNEL_IN4  // TPS
#define EFI_ADC_5  ADC_CHANNEL_IN5  // CLT
```

### GPIO Control

File: `hw_layer/drivers/gpio/gpio.cpp`

Control output pins (injector, coil, dll).

### PWM Output

File: `hw_layer/ports/stm32/stm32_pwm.cpp`

PWM untuk idle valve, VVT, dll.

---

## Development Workflow

### 1. Edit Config

Edit `board.mk` atau `board_configuration.cpp`

### 2. Build

```bash
cd ext/rusefi/firmware/
make -j8
```

### 3. Flash

Via ST-Link:
```bash
make flash
```

Via DFU:
```bash
make dfu_upload
```

### 4. Test

- Connect TunerStudio
- Check sensor readings
- Test outputs

### 5. Commit

```bash
git add board.mk board_configuration.cpp
git commit -m "feat: add CAN bus support"
git push
```

GitHub Actions auto-build artifacts.

---

## Debugging

### Serial Console

Connect via USB serial (115200 baud):
```bash
screen /dev/ttyACM0 115200
```

Commands:
- `help` - List commands
- `info` - ECU info
- `sensors` - Sensor readings
- `set <param> <value>` - Set parameter

### TunerStudio

Real-time gauges & logging.

Live data view:
- Tools → Live Data
- Tools → Engine Sniffer (oscilloscope)

### Tooth Logger

Debug trigger wheel:
- Tools → Trigger Tooth → Enable
- Record pattern
- Compare dengan expected

---

## Common Tasks

### Ganti Pin Assignment

Edit `board_configuration.cpp`:

```cpp
// Ubah TPS pin dari PA4 ke PA5
engineConfiguration->tps1_1AdcChannel = EFI_ADC_5;  // PA5
```

### Enable/Disable Feature

Edit `board.mk`:

```makefile
# Enable launch control
DDEFS += -DEFI_LAUNCH_CONTROL=TRUE
```

### Ganti Default Tune

Edit `default_tune.cpp`:

```cpp
// Naikin rev limit dari 10000 ke 12000
config->rpmHardLimit = 12000;
```

### Add CAN Message

Edit `controllers/can/can_dash.cpp`:

```cpp
// Kirim data custom
int16_t customData = engine->sensors.tps;
canMsg[0] = (customData >> 8) & 0xFF;
canMsg[1] = customData & 0xFF;
```

---

## Reference

Kalo masih bingung:
- rusEFI Wiki: https://github.com/rusefi/rusefi/wiki
- Forum: https://rusefi.com/forum/
- rusEFI Fuentes: https://rusefi.com/

File lain:
- `CLOSED_LOOP_REFERENCE.md` - Fuel trim & idle logic
- `CAN_BUS_PINOUT.md` - CAN wiring
- `OPTIMIZATION_QUICK_GUIDE.md` - Flash/RAM optimization

---

Itu aja. Good luck hacking! 🚀
