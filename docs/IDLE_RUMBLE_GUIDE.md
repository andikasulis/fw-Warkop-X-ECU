# Idle Rumble Effect - Aracer Style

Cara bikin idle "drumbal" kayak ECU Aracer di rusEFI.

---

## ⚠️ PENTING - Cable Throttle Note

**Vixion OLD pake throttle cable manual** (gak ada idle stepper/valve)!

Idle di-set pake **throttle stop screw** di throttle body, ECU **gak bisa kontrol** idle valve.

**Tapi masih bisa bikin rumble effect!** Caranya **BEDA**:

### Method untuk Cable Throttle:

❌ **Gak bisa:** Ubah target idle RPM (gak ada idle valve)  
✅ **Bisa:** Vary ignition timing  
✅ **Bisa:** Periodic fuel cut/add  
✅ **Bisa:** Spark cut pattern

**Baca section "Implementation for Cable Throttle" di bawah!**

---

## Apa Itu Idle Rumble?

Idle rumble = idle RPM naik-turun dikit (contoh: 1000-1200 RPM bolak-balik) buat effect suara yang lebih gahar.

Common di:
- Harley Davidson (V-twin lope)
- Motor racing/modif
- ECU aftermarket (Aracer, BRT, dll)

**Catatan:** Ini purely cosmetic, gak nambah power. Cuma buat suara doang.

---

## Cara Kerja

Ada 2 approach:

### 1. Variable Idle Target (Simple)

Ubah target idle RPM secara periodik:
- 500ms di 1000 RPM
- 500ms di 1200 RPM
- Repeat

### 2. Ignition Timing Variation (Advanced)

Ubah ignition timing sedikit buat bikin "misfire" ringan:
- Kadang retard timing → RPM turun
- Kadang normal timing → RPM naik

---

## Implementation for Cable Throttle (Vixion OLD)

Karena gak ada idle valve, rumble effect dibuat lewat **ignition/fuel manipulation**.

### Method 1: Ignition Timing Variation (RECOMMENDED)

Ubah ignition timing dikit-dikit buat bikin RPM bounce.

**How it works:**
- Retard timing 3-5° → RPM turun sedikit
- Normal timing → RPM naik balik
- Repeat

**Code example:**

```cpp
// File: idle_rumble.cpp

float getIdleRumbleTimingOffset() {
    // Only at idle
    if (getTPS() > 5) return 0;  // Not at idle
    if (getRPM() > 1500) return 0;  // Not at idle
    
    // Sine wave timing variation
    static float phase = 0;
    phase += 0.05;  // Speed
    if (phase > 6.28) phase = 0;
    
    // ±3 degrees timing swing
    // Negative = retard (RPM drop)
    return sin(phase) * 3.0;
}
```

**Apply di ignition calculation:**

```cpp
// In getAdvance() function
float advance = baseAdvance;

// Add rumble at idle
if (isIdleCondition()) {
    advance += getIdleRumbleTimingOffset();
}

return advance;
```

**Pros:**
- ✅ Smooth effect
- ✅ Gak bikin engine mati
- ✅ Adjustable

**Cons:**
- ⚠️ Effect subtle (gak se-extreme ubah RPM)

---

### Method 2: Periodic Fuel Cut

Cut fuel injection periodic buat bikin "stumble" effect.

**How it works:**
- Normal injection → RPM normal
- Skip 1 injection → RPM drop sedikit
- Repeat

**Code example:**

```cpp
bool shouldSkipInjection() {
    // Only at idle
    if (!isIdleCondition()) return false;
    
    static int cycleCount = 0;
    cycleCount++;
    
    // Skip every 8th injection (aggressive)
    // atau every 16th (subtle)
    if (cycleCount % 12 == 0) {
        return true;  // Skip this injection
    }
    
    return false;
}
```

**Apply di injection:**

```cpp
// In scheduleInjection() or getInjectionDuration()

if (shouldSkipInjection()) {
    return 0;  // Skip injection
}

// ... normal injection code
```

**Pros:**
- ✅ Effect lebih aggressive
- ✅ Suara lebih "popping"

**Cons:**
- ⚠️ Bisa bikin AFR spike (rich saat skip)
- ⚠️ Might cause stumble jika terlalu aggressive

---

### Method 3: Spark Cut Pattern

Cut spark (ignition) periodic.

**How it works:**
- Fire all cylinders → smooth
- Skip spark 1x → slight stumble
- Repeat

**Code example:**

```cpp
bool shouldSkipSpark() {
    if (!isIdleCondition()) return false;
    
    static int sparkCount = 0;
    sparkCount++;
    
    // Skip every 10th spark
    return (sparkCount % 10 == 0);
}
```

**Apply di ignition scheduling:**

```cpp
// In scheduleIgnition()

if (shouldSkipSpark()) {
    return;  // Don't fire this time
}

// ... normal ignition schedule
```

**Pros:**
- ✅ Clean (gak affect fuel)
- ✅ Suara "popping" lebih jelas

**Cons:**
- ⚠️ Unburned fuel (minor)

---

### Method 4: Combined (Advanced)

Combine timing + fuel variation buat effect maksimal:

```cpp
float getRumbleEffect() {
    if (!isIdleCondition()) return 0;
    
    static float phase = 0;
    phase += 0.08;
    if (phase > 6.28) phase = 0;
    
    float sineValue = sin(phase);
    
    // When sine is negative: retard timing + reduce fuel
    // When sine is positive: normal timing + normal fuel
    
    return sineValue;
}

// Apply to timing
float timingOffset = getRumbleEffect() * 4.0;  // ±4 degrees

// Apply to fuel
float fuelMult = 1.0 + (getRumbleEffect() * 0.1);  // ±10% fuel
```

**Pros:**
- ✅ Effect paling kuat
- ✅ Suara paling gahar

**Cons:**
- ⚠️ Lebih complex
- ⚠️ Perlu tune carefully

---

## Implementation Options

### Option 1: Via Custom Code (Recommended)

Edit firmware langsung. Paling flexible.

**Pros:**
- Full control
- Gak makan flash banyak (~1-2KB)
- Bisa adjust parameter via TunerStudio

**Cons:**
- Perlu compile ulang firmware
- Modify source code

### Option 2: Via Lua Script

Pake Lua scripting buat ubah idle target.

**Pros:**
- Gak perlu recompile firmware
- Easy to adjust

**Cons:**
- Lua currently DISABLED (hemat 40-60KB flash)
- Perlu re-enable Lua di board.mk

### Option 3: Via TunerStudio Table

Pake idle timing table.

**Pros:**
- Gak modify code
- Adjust via TunerStudio

**Cons:**
- Limited control
- Might not work smooth

---

## Implementation: Custom Code

### Step 1: Add Config Parameters

Edit `default_tune.cpp`:

```cpp
// Idle rumble settings
config->idleRumbleEnabled = false;  // Enable via TS nanti
config->idleRumbleAmplitude = 200;  // ±200 RPM
config->idleRumblePeriodMs = 500;   // 500ms cycle
```

### Step 2: Add Logic

Buat file baru `idle_rumble.cpp`:

```cpp
#include "pch.h"
#include "idle_rumble.h"

static Timer rumbleTimer;
static bool rumbleHigh = false;

int getIdleRumbleOffset() {
    if (!engineConfiguration->idleRumbleEnabled) {
        return 0;  // Feature disabled
    }
    
    // Toggle every period
    if (rumbleTimer.hasElapsedMs(engineConfiguration->idleRumblePeriodMs)) {
        rumbleHigh = !rumbleHigh;
        rumbleTimer.reset();
    }
    
    // Return offset
    if (rumbleHigh) {
        return engineConfiguration->idleRumbleAmplitude / 2;
    } else {
        return -(engineConfiguration->idleRumbleAmplitude / 2);
    }
}
```

### Step 3: Integrate ke Idle Controller

Edit `idle_controller.cpp`:

```cpp
// Di function getTargetRpm() atau setTargetRpm()

int targetRpm = engineConfiguration->idleRpmTarget;

// Add rumble offset
#if EFI_IDLE_RUMBLE
targetRpm += getIdleRumbleOffset();
#endif

return targetRpm;
```

### Step 4: Add Feature Flag

Edit `board.mk`:

```makefile
# Enable idle rumble feature
DDEFS += -DEFI_IDLE_RUMBLE=TRUE
```

Cost: ~1-2KB flash

### Step 5: Compile & Flash

```bash
cd ext/rusefi/firmware/
make clean
make -j8
make dfu_upload
```

---

## Simple Version (Quick Hack)

Kalo gak mau ribet modify banyak file, tambahin langsung di `board_configuration.cpp`:

```cpp
// Add di setBoardDefaultConfiguration()

void setBoardDefaultConfiguration() {
    // ... existing code ...
    
    // IDLE RUMBLE HACK
    // Simple sine wave rumble
    static float rumblePhase = 0;
    
    // Update every fast callback (~100Hz)
    rumblePhase += 0.1;  // Speed
    if (rumblePhase > 6.28) rumblePhase = 0;  // Reset at 2π
    
    // Calculate offset: ±100 RPM sine wave
    int rumbleOffset = (int)(sin(rumblePhase) * 100);
    
    // Apply to idle target
    engineConfiguration->idleRpmTarget = 1000 + rumbleOffset;
}
```

**Warning:** Ini hack kasar, better pake proper implementation di atas.

---

## Via Lua Script (If Enabled)

Kalo lu mau enable Lua (cost +40-60KB flash):

### Enable Lua

Edit `board.mk`:
```makefile
DDEFS += -DEFI_LUA=TRUE
```

### Lua Script

Buat file `idle_rumble.lua`:

```lua
-- Idle Rumble Script
rumbleEnabled = true
rumbleAmp = 100        -- ±100 RPM
rumblePeriod = 500     -- ms
rumblePhase = 0

function onTick()
    if not rumbleEnabled then
        return
    end
    
    -- Sine wave rumble
    rumblePhase = rumblePhase + 0.1
    if rumblePhase > 6.28 then
        rumblePhase = 0
    end
    
    offset = math.sin(rumblePhase) * rumbleAmp
    setIdleAdd(offset)
end
```

Upload via TunerStudio.

---

## TunerStudio Configuration

Setelah implement, add controls di TunerStudio:

1. **Enable/Disable**
   - Settings → Idle → Rumble Enable (checkbox)

2. **Amplitude**
   - Slider: 0-500 RPM
   - Recommended: 100-200 RPM

3. **Period**
   - Slider: 100-2000 ms
   - Fast (200ms) = aggressive
   - Slow (1000ms) = smooth lope

4. **Pattern**
   - Sine wave (smooth)
   - Square wave (abrupt)
   - Random (unpredictable)

---

## Tuning Tips

### Amplitude (RPM Swing)

| Amplitude | Effect |
|-----------|--------|
| 50-100 | Subtle, barely noticeable |
| 100-200 | Noticeable rumble, smooth |
| 200-300 | Aggressive, Harley-style |
| 300+ | Terlalu extreme, gak stabil |

Start dari 150 RPM.

### Period (Speed)

| Period | Effect |
|--------|--------|
| 200-300ms | Fast, aggressive |
| 500ms | Medium, balanced |
| 1000ms+ | Slow, lope style |

V-twin style: 800-1000ms  
Racing style: 300-500ms

### Pattern

**Sine wave:** Smooth naik-turun  
**Square wave:** Abrupt jump  
**Random:** Unpredictable (paling gahar tapi bisa annoying)

---

## Safety Considerations

**Jangan pake kalo:**
- Idle gak stabil (fix dulu)
- Vacuum leak
- Idle valve rusak

**Warning:**
- Rumble bikin vibrations lebih
- Mungkin gak comfortable buat daily riding
- Bisa bikin penumpang pusing

**Best practice:**
- Enable via switch (bisa on/off)
- Disable otomatis saat gear in (safety)
- Disable saat AC on (kalo ada AC)

---

## Advanced: Conditional Rumble

Rumble cuma aktif di kondisi tertentu:

```cpp
int getIdleRumbleOffset() {
    // Only enable when:
    // 1. In neutral
    // 2. Engine warm (CLT > 60°C)
    // 3. Not moving (VSS = 0)
    
    if (!engine->rpmCalculator.isRunning()) return 0;
    if (engine->sensors.clt < 60) return 0;  // Cold
    if (!engineConfiguration->idleRumbleEnabled) return 0;
    
    // Check if in neutral (via clutch or gear sensor)
    if (!isInNeutral()) return 0;
    
    // All clear, apply rumble
    return calculateRumble();
}
```

---

## Alternative: Ignition-based Rumble

Instead of RPM, vary ignition timing:

```cpp
// Di ignition timing calculation

float getIdleTimingOffset() {
    if (!atIdle()) return 0;
    if (!engineConfiguration->idleRumbleEnabled) return 0;
    
    // Randomly retard timing 0-5 degrees
    // Creates slight misfire effect
    return -(random() % 5);
}
```

Ini lebih advanced, effect lebih subtle.

---

## Example Settings

### Harley V-Twin Style
```
Amplitude: 250 RPM
Period: 900ms
Pattern: Sine wave
Base idle: 900 RPM
```

### Racing Aggressive
```
Amplitude: 150 RPM
Period: 300ms
Pattern: Square wave
Base idle: 1200 RPM
```

### Subtle Daily
```
Amplitude: 80 RPM
Period: 600ms
Pattern: Sine wave
Base idle: 1000 RPM
```

---

## Troubleshooting

### Idle Terlalu Kasar

- Kurangin amplitude
- Perlambat period
- Ganti ke sine wave

### Effect Gak Kerasa

- Naikin amplitude
- Percepat period
- Check implementation udah jalan

### Engine Mati

- Amplitude terlalu besar
- Base idle terlalu rendah
- Idle control gak optimal

---

## Kesimpulan

Fitur ini:
- ✅ Bisa diimplement di rusEFI
- ✅ Relatively simple (1-2KB code)
- ✅ Adjustable via TunerStudio
- ⚠️ Purely cosmetic (sound effect)
- ⚠️ Might not be comfortable daily

**Recommendation:**
- Implement custom code (Option 1)
- Start conservative (100 RPM, 500ms)
- Make it toggle-able
- Test extensively

**Cost:**
- Flash: ~1-2 KB
- Effort: Medium (few hours coding)
- Cool factor: High 😎

---

Want me to create the actual implementation? Let me know! 🏍️
