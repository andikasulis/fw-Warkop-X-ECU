# TunerStudio Integration - How It Works

Penjelasan gimana TunerStudio bisa otomatis tampilkan setting tanpa coding manual.

---

## TL;DR

**Gak perlu coding TunerStudio manual!**

rusEFI pake **auto-generate system**:
1. Edit `rusefi_config.txt` (define parameters)
2. Build firmware → auto-generate `.ini` file
3. TunerStudio load `.ini` → UI muncul otomatis!

**Magic: Java config generator tools**

---

## How It Works (Step by Step)

### Step 1: Define Parameters di rusefi_config.txt

File: `ext/rusefi/firmware/integration/rusefi_config.txt`

```c
struct_no_prefix engine_configuration_s
    // Existing fields...
    
    // Idle Rumble Feature
    bit idleRumbleEnabled;Enable idle rumble effect
    uint8_t idleRumbleAmplitude;Rumble amplitude, 0, 100, 0;"%"
    uint8_t idleRumblePeriod;Rumble period, 1, 20, 0;"x100ms"
    
end_struct
```

**Syntax breakdown:**
```
[type] [name];[description], [min], [max], [digits];[unit]
```

**Contoh:**
```c
bit idleRumbleEnabled;Enable idle rumble effect
     ↑               ↑
     Type            Description (tampil di TS)

uint8_t idleRumbleAmplitude;Rumble amplitude, 0, 100, 0;"%"
        ↑                   ↑                 ↑  ↑   ↑  ↑
        Name                Description      Min Max Dig Unit
```

### Step 2: Build Firmware

```bash
cd ext/rusefi/firmware/
make -j8
```

**Apa yang terjadi saat build:**

```
┌─────────────────────────────────────────────┐
│ 1. Read rusefi_config.txt                   │
│    └─► Parse parameter definitions          │
│                                              │
│ 2. Java ConfigDefinition tool runs          │
│    └─► Generate C headers (.h)              │
│    └─► Generate TunerStudio .ini            │
│                                              │
│ 3. Compile firmware with generated headers  │
│                                              │
│ 4. Output files:                             │
│    ├─► rusefi.bin (firmware)                │
│    └─► rusefi_warkop_x.ini (TunerStudio)    │
└─────────────────────────────────────────────┘
```

**Generated files:**
- `generated/controllers/generated/engine_configuration_generated_structures.h` - C structs
- `generated/tunerstudio/generated/rusefi_warkop_x.ini` - TunerStudio config

### Step 3: TunerStudio Auto-Load

Saat connect TunerStudio:
1. Baca `.ini` file
2. Parse parameter definitions
3. **Auto-create UI elements!**

**Gak perlu coding manual!**

---

## Generated .ini File Example

File: `generated/tunerstudio/generated/rusefi_warkop_x.ini`

Dari config kita:
```c
bit idleRumbleEnabled;Enable idle rumble effect
uint8_t idleRumbleAmplitude;Rumble amplitude, 0, 100, 0;"%"
```

Auto-generate jadi:

```ini
[Constants]
   page = 1
   
   ; Idle Rumble
   idleRumbleEnabled = bits, U08, 123, [0:0], "Off", "On"
   idleRumbleAmplitude = scalar, U08, 124, "%", 1, 0, 0, 100, 0

[PcVariables]
   ; (real-time values)

[SettingGroups]
   ; UI layout definitions

[Dialogs]
   dialog = idleRumble, "Idle Rumble"
      field = "Enable", idleRumbleEnabled
      field = "Amplitude", idleRumbleAmplitude
```

**TunerStudio baca ini dan auto-create:**
- Checkbox untuk `idleRumbleEnabled`
- Slider/textbox untuk `idleRumbleAmplitude` (0-100%)
- Label "Enable" dan "Amplitude"

---

## Communication Protocol

### Baca Data (ECU → TunerStudio)

```
┌────────────────┐                  ┌─────────────┐
│  TunerStudio   │                  │     ECU     │
├────────────────┤                  ├─────────────┤
│                │                  │             │
│ 1. Send "R"    │─────────────────►│             │
│    command     │                  │ 2. Read     │
│                │                  │    config   │
│                │                  │    struct   │
│                │◄─────────────────│             │
│ 3. Receive     │  Binary data     │ 3. Send     │
│    config      │                  │    data     │
│                │                  │             │
│ 4. Parse &     │                  │             │
│    display     │                  │             │
└────────────────┘                  └─────────────┘
```

**Protocol:**
- Command: `R` (Read)
- ECU reply: Binary dump of config struct
- TS parse sesuai `.ini` definition

### Tulis Data (TunerStudio → ECU)

```
┌────────────────┐                  ┌─────────────┐
│  TunerStudio   │                  │     ECU     │
├────────────────┤                  ├─────────────┤
│                │                  │             │
│ 1. User ubah   │                  │             │
│    setting     │                  │             │
│                │                  │             │
│ 2. Click       │                  │             │
│    "Burn"      │                  │             │
│                │                  │             │
│ 3. Send "W"    │─────────────────►│             │
│    + offset    │  Binary data     │ 4. Write to │
│    + data      │                  │    config   │
│                │                  │    struct   │
│                │◄─────────────────│             │
│ 5. Confirm     │   ACK/NACK       │ 5. Send     │
│                │                  │    confirm  │
└────────────────┘                  └─────────────┘
```

**Protocol:**
- Command: `W` + offset + value
- ECU: Write to config struct
- ECU: Save to flash (jika "Burn")
- ECU reply: ACK/NACK

---

## Custom Dialog (Optional)

Kalo mau customize UI, bisa override di `board_config.txt`:

File: `board_config.txt`

```ini
[Dialogs]
   dialog = idleRumble, "Idle Rumble (Drumbal Effect)"
      panel = idleRumblePanel
      
   panel = idleRumblePanel
      field = "Enable Idle Rumble", idleRumbleEnabled
      field = ""
      field = "===== Settings ====="
      field = "Rumble Amplitude (%)", idleRumbleAmplitude, {idleRumbleEnabled == 1}
      field = "Rumble Speed", idleRumblePeriod, {idleRumbleEnabled == 1}
      field = ""
      field = "===== Advanced ====="
      field = "Method", idleRumbleMethod, {idleRumbleEnabled == 1}
      field = "Max Timing Offset", idleRumbleTiming, {idleRumbleEnabled == 1}
      field = "Max Fuel Adjust", idleRumbleFuel, {idleRumbleEnabled == 1}
```

**Features:**
- Custom panel layout
- Conditional visibility: `{idleRumbleEnabled == 1}`
- Grouping dengan separator
- Custom labels

---

## Real Example - Current Warkop-X

Liat file yang udah ada:

```bash
cat generated/tunerstudio/generated/rusefi_warkop_x.ini | grep -A5 "rpmHardLimit"
```

Output:
```ini
rpmHardLimit = scalar, U16, 456, "rpm", 1, 0, 0, 20000, 0
```

**Breakdown:**
- `scalar` - Type (angka biasa, bukan bit)
- `U16` - Unsigned 16-bit
- `456` - Offset in config struct (byte 456)
- `"rpm"` - Unit display
- `1` - Multiplier (1x)
- `0` - Adder (+0)
- `0, 20000` - Min, Max
- `0` - Decimal digits

TunerStudio baca ini, auto-create:
```
┌──────────────────────────────────┐
│ Rev Limiter:  [12000   ] rpm     │
│               ─────────           │
│               Min: 0    Max: 20000│
└──────────────────────────────────┘
```

---

## Memory Layout

Config struct di ECU:

```c
// Auto-generated struct
struct engine_configuration_s {
    // Offset 0
    uint16_t rpmHardLimit;          // Byte 0-1
    
    // Offset 2
    uint8_t cylinderCount;          // Byte 2
    
    // ... много parameters ...
    
    // Offset 456 (example)
    bit idleRumbleEnabled;          // Byte 456, bit 0
    uint8_t idleRumbleAmplitude;    // Byte 457
    uint8_t idleRumblePeriod;       // Byte 458
    
    // ... more parameters
} __attribute__((packed));
```

**TunerStudio tau persis dimana tiap parameter** (via offset di `.ini`)

---

## Burn Process

### Saat klik "Burn" di TunerStudio:

```cpp
// Firmware code (auto-generated)

void handleBurnRequest() {
    // 1. Copy current config to flash buffer
    memcpy(flashBuffer, &engineConfiguration, sizeof(engine_configuration_s));
    
    // 2. Calculate CRC checksum
    uint32_t crc = calculateCrc(flashBuffer, sizeof(engine_configuration_s));
    
    // 3. Write to flash memory
    writeFlash(FLASH_CONFIG_ADDRESS, flashBuffer, size);
    
    // 4. Verify
    if (verifyCrc()) {
        sendAck();  // Success
    } else {
        sendNack(); // Failed
    }
}
```

**Settings disimpan di flash sector 7** (128KB reserved)

---

## Testing Without TunerStudio

Via serial console:

```bash
# Connect
screen /dev/ttyACM0 115200

# Read parameter
> get idleRumbleEnabled
idleRumbleEnabled = 0

# Set parameter
> set idleRumbleEnabled 1
idleRumbleEnabled = 1

# Save to flash
> writeconfig
Config saved to flash

# Reboot to test
> reset
```

---

## Custom Commands (Advanced)

Kalo mau custom command di TunerStudio:

Add to `.ini`:

```ini
[ControllerCommands]
   ; Custom commands
   cmd_test_rumble     = "t\x00\x01"    ; Test rumble
   cmd_reset_rumble    = "t\x00\x02"    ; Reset rumble

[UserDefined]
   dialog = customCommands, "Custom Commands"
      commandButton = "Test Rumble", cmd_test_rumble
      commandButton = "Reset", cmd_reset_rumble
```

Implement di firmware:

```cpp
void handleCustomCommand(uint8_t cmd) {
    switch (cmd) {
        case 0x01:  // Test rumble
            engineConfiguration->idleRumbleEnabled = true;
            engineConfiguration->idleRumbleAmplitude = 100;
            break;
            
        case 0x02:  // Reset
            engineConfiguration->idleRumbleEnabled = false;
            break;
    }
}
```

---

## Summary

### Gak Perlu Coding TunerStudio!

**Yang perlu:**
1. ✅ Edit `rusefi_config.txt` (define parameters)
2. ✅ Build firmware (auto-generate `.ini`)
3. ✅ Flash firmware
4. ✅ Load `.ini` di TunerStudio

**Auto-generated:**
- ✅ UI elements (checkbox, slider, textbox)
- ✅ Min/max validation
- ✅ Units display
- ✅ Read/write protocol
- ✅ Flash save/load

**Magic:** Java ConfigDefinition tool!

---

## Files Involved

```
Workflow:
=========

rusefi_config.txt          (manual edit - define params)
      ↓
ConfigDefinition.jar       (auto-run saat build)
      ↓
      ├─► engine_configuration.h     (C struct)
      ├─► signature_warkop_x.h       (CRC)
      └─► rusefi_warkop_x.ini        (TunerStudio UI)
            ↓
      TunerStudio              (load .ini, create UI)
```

---

## Example for Idle Rumble

**Input (rusefi_config.txt):**
```c
bit idleRumbleEnabled;Enable rumble
uint8_t idleRumbleAmplitude;Amplitude, 0, 100, 0;"%"
```

**Auto-generated (.ini):**
```ini
idleRumbleEnabled = bits, U08, 500, [0:0], "Off", "On"
idleRumbleAmplitude = scalar, U08, 501, "%", 1, 0, 0, 100, 0
```

**TunerStudio UI:**
```
┌──────────────────────────────────────┐
│ □ Enable rumble                      │
│                                      │
│ Amplitude:  [████████••] 80%         │
│             └─────────────┘          │
│              0          100          │
└──────────────────────────────────────┘
```

**Burn → Save to flash → Done!**

---

Jadi **gak ada coding TunerStudio manual**! Semua auto-generate! 🚀

Mau saya tunjukin generate process-nya? Bisa saya compile test!
