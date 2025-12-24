# STATUS: Idle Rumble Implementation

## ❌ **BELUM AKTIF!**

File yang sudah dibuat:
- ✅ `idle_rumble_implementation.cpp` - Template code (reference)
- ✅ `docs/IDLE_RUMBLE_GUIDE.md` - Dokumentasi
- ✅ `docs/TUNERSTUDIO_INTEGRATION.md` - Cara integrasi

**Tapi:** Code **BELUM TERINTEGRASI** ke firmware!

---

## Yang Perlu Dilakukan

### Step 1: Add Config Parameters

❌ **Belum:** Edit `ext/rusefi/firmware/integration/rusefi_config.txt`

**Perlu tambah:**
```c
struct_no_prefix engine_configuration_s
    // ... existing fields ...
    
    // Idle Rumble Feature
    bit idleRumbleEnabled;Enable idle rumble effect
    uint8_t idleRumbleAmplitude;Rumble amplitude, 0, 100, 0;"%"
    uint8_t idleRumblePeriod;Rumble period, 1, 20, 0;"x100ms"
    uint8_t idleRumbleMethod;Method: 0=Timing 1=Fuel 2=Spark 3=Combined, 0, 3, 0
    int8_t autoscale idleRumbleTiming;Max timing offset, -10, 10, 0;"deg"
    int8_t autoscale idleRumbleFuel;Max fuel adjust, -20, 20, 0;"%"
    uint16_t idleRumbleMaxRpm;Max RPM for rumble, 0, 2000, 0;"rpm"
    uint8_t idleRumbleMaxTps;Max TPS for rumble, 0, 20, 0;"%"
    
end_struct
```

**WARNING:** `rusefi_config.txt` ada di folder **submodule** (`ext/rusefi/`).
- Edit di sini akan **hilang** saat update submodule!
- Better: Pake board override atau custom implementation

---

### Step 2: Create Implementation File

❌ **Belum:** Buat file `idle_rumble.cpp` di root folder

**Action:** Copy from template, integrate ke build system

---

### Step 3: Set Default Values

❌ **Belum:** Edit `default_tune.cpp`

**Perlu tambah:**
```cpp
void setBoardDefaultConfiguration() {
    // ... existing code ...
    
    // Idle Rumble defaults
    engineConfiguration->idleRumbleEnabled = false;  // OFF by default
    engineConfiguration->idleRumbleAmplitude = 50;
    engineConfiguration->idleRumblePeriod = 5;  // 500ms
    engineConfiguration->idleRumbleMethod = 3;  // Combined
    engineConfiguration->idleRumbleTiming = 4;  // ±4°
    engineConfiguration->idleRumbleFuel = 10;   // ±10%
    engineConfiguration->idleRumbleMaxRpm = 1500;
    engineConfiguration->idleRumbleMaxTps = 5;
}
```

---

### Step 4: Integrate to Engine Control

❌ **Belum:** Hook ke ignition/fuel calculation

**Need to modify:**
1. Ignition timing calculation
2. Fuel calculation
3. Add rumble functions

---

### Step 5: Build System

❌ **Belum:** Add to Makefile

**Need:**
- Add `idle_rumble.cpp` ke CSRC list
- Optional: Add feature flag `-DEFI_IDLE_RUMBLE=TRUE`

---

## Problem: Submodule Conflicts

**Masalah besar:** rusEFI core ada di `ext/rusefi/` (git submodule)

Kalo edit `rusefi_config.txt`:
- ❌ Changes hilang saat `git submodule update`
- ❌ Conflict dengan upstream rusEFI
- ❌ Susah maintain

**Solusi:**

### Option A: Board-Specific Override (RECOMMENDED)

Gak edit `rusefi_config.txt`, tapi:
1. Buat custom config di `board_config.txt`
2. Implement langsung di `board_configuration.cpp`
3. Hardcode parameters (gak via TunerStudio)

**Pros:**
- ✅ Gak touch submodule
- ✅ Gak conflict
- ✅ Easy maintain

**Cons:**
- ❌ Gak ada UI di TunerStudio
- ❌ Harus recompile buat ubah settings

---

### Option B: Fork rusEFI Submodule (Advanced)

Fork `rusefi` repo, edit `rusefi_config.txt`, point submodule ke fork.

**Pros:**
- ✅ Full TunerStudio support
- ✅ Proper integration

**Cons:**
- ❌ Complex setup
- ❌ Maintain fork
- ❌ Merge conflicts saat update upstream

---

### Option C: Runtime Settings (Compromise)

Use existing unused parameters atau custom commands.

**Example:**
```cpp
// Pake parameter yang udah ada tapi gak kepake
// idleRumbleEnabled = use bit di launchActivationMode (unused bits)
// idleRumbleAmplitude = use unused byte di config
```

**Pros:**
- ✅ Gak edit submodule
- ✅ Bisa configure via TS

**Cons:**
- ❌ Hacky
- ❌ Limited UI
- ❌ Confusing parameter names

---

## Recommended Approach: Simple Hardcoded Version

Implement **WITHOUT** TunerStudio UI (for now):

### Implementation:

1. **Buat file `idle_rumble.cpp`** di root
2. **Hardcode settings** di code
3. **Hook ke ignition timing**
4. **Build & test**

Later bisa add TunerStudio support kalo worth it.

### Pros:
- ✅ Simple
- ✅ Quick implement
- ✅ Gak touch submodule
- ✅ Easy test

### Cons:
- ⚠️ Gak bisa adjust via TunerStudio
- ⚠️ Perlu recompile buat ubah settings

---

## Simple Implementation (Hardcoded)

Buat file baru `idle_rumble.cpp`:

```cpp
#include "pch.h"

// Hardcoded settings (gak ada TunerStudio UI)
#define RUMBLE_ENABLED       false  // Set true to enable
#define RUMBLE_AMPLITUDE     50      // 0-100%
#define RUMBLE_PERIOD_MS     500     // milliseconds
#define RUMBLE_METHOD        3       // 0=Timing, 1=Fuel, 2=Spark, 3=Combined
#define RUMBLE_MAX_TIMING    4.0f    // degrees
#define RUMBLE_MAX_FUEL      10.0f   // percent
#define RUMBLE_MAX_RPM       1500    // rpm
#define RUMBLE_MAX_TPS       5.0f    // percent

static float rumblePhase = 0;

bool isIdleCondition() {
    int rpm = Sensor::getOrZero(SensorType::Rpm);
    float tps = Sensor::getOrZero(SensorType::Tps1);
    float clt = Sensor::getOrZero(SensorType::Clt);
    
    return (rpm > 0 && rpm < RUMBLE_MAX_RPM && 
            tps < RUMBLE_MAX_TPS && 
            clt > 60);  // Warm only
}

float getRumbleEffect() {
    if (!RUMBLE_ENABLED) return 0;
    if (!isIdleCondition()) return 0;
    
    // Update phase (assuming 100Hz call rate)
    float increment = (2.0f * 3.14159f) / (RUMBLE_PERIOD_MS / 10.0f);
    rumblePhase += increment;
    if (rumblePhase > 6.28318f) rumblePhase = 0;
    
    // Sine wave
    float sine = sinf(rumblePhase);
    return sine * (RUMBLE_AMPLITUDE / 100.0f);
}

float getIdleRumbleTimingOffset() {
    if (RUMBLE_METHOD == 0 || RUMBLE_METHOD == 3) {
        return getRumbleEffect() * RUMBLE_MAX_TIMING;
    }
    return 0;
}

float getIdleRumbleFuelMultiplier() {
    if (RUMBLE_METHOD == 1 || RUMBLE_METHOD == 3) {
        float percent = getRumbleEffect() * RUMBLE_MAX_FUEL;
        return 1.0f + (percent / 100.0f);
    }
    return 1.0f;
}
```

Add to `board_configuration.cpp`:

```cpp
// Di akhir file, add hook
#include "idle_rumble.cpp"
```

---

## Next Steps

**Option 1: Simple Hardcoded** (Recommended untuk test)
1. Buat `idle_rumble.cpp` (hardcoded version)
2. Include di `board_configuration.cpp`
3. Hook ke ignition timing
4. Build & test

**Option 2: Full TunerStudio Support** (Advanced)
1. Fork rusEFI submodule
2. Edit `rusefi_config.txt`
3. Full implementation
4. Maintain fork

---

## Mau Saya Implement?

Saya bisa:
1. ✅ Buat simple hardcoded version (quick test)
2. ✅ Integrate ke codebase
3. ✅ Test compile
4. ✅ Later add TunerStudio support (if needed)

Atau mau langsung full TunerStudio version (lebih ribet)?

**Recommendation:** Start simple, test, then add TunerStudio later kalo worth it.

---

Last Updated: 2025-12-24
