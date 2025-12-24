# Idle Rumble Logic - Explained Simply

Penjelasan cara kerja idle rumble untuk Vixion OLD (cable throttle).

---

## TL;DR

**Problem:** Vixion gak ada idle valve, ECU gak bisa ubah RPM idle.

**Solution:** Bikin RPM "bounce" dengan cara:
- Vary ignition timing (retard/advance)
- Vary fuel amount (lean/rich)
- Skip spark periodic

Result: Idle RPM naik-turun dikit → suara "drumbal/rumble" 🏍️

---

## Konsep Dasar

### Normal Idle (Tanpa Rumble)

```
Time:    0ms   100ms  200ms  300ms  400ms
Timing:  10°    10°    10°    10°    10°   (constant)
Fuel:    100%   100%   100%   100%   100%  (constant)
RPM:     1000   1000   1000   1000   1000  (stable)
```

Idle smooth, RPM konstan.

---

### Idle dengan Rumble

```
Time:    0ms   100ms  200ms  300ms  400ms  500ms
Timing:  12°    10°     8°    10°    12°    10°   (varies!)
Fuel:    105%   100%   95%   100%   105%   100%  (varies!)
RPM:     1050  1000    950   1000   1050   1000  (bouncing!)
         ↑      ↓      ↓      ↑      ↑      ↓
        High   Drop   Drop   Rise   High   Drop
```

RPM naik-turun → Suara "drumbal" → Effect gahar! 🔥

---

## Logic Flow

### Step 1: Check Kondisi

```cpp
bool isIdleCondition() {
    // Check:
    // 1. RPM < 1500 (at idle range)
    // 2. TPS < 5% (throttle closed)
    // 3. CLT > 60°C (engine warm)
    
    if (rpm > 1500) return false;  // Not at idle
    if (tps > 5) return false;     // Throttle open
    if (clt < 60) return false;    // Engine cold
    
    return true;  // OK, at idle!
}
```

**Rumble cuma aktif saat:**
- ✅ Idle (RPM rendah)
- ✅ Throttle closed
- ✅ Engine warm

---

### Step 2: Generate Sine Wave

```cpp
float getRumbleEffect() {
    if (!enabled) return 0;
    if (!isIdleCondition()) return 0;
    
    // Generate sine wave
    phase += 0.05;  // Increment phase
    if (phase > 6.28) phase = 0;  // Reset at 2π
    
    float sine = sin(phase);  // -1.0 to +1.0
    
    return sine * amplitude;  // Scale by amplitude
}
```

**Sine wave output:**
```
Time:  0    100  200  300  400  500  600  700  800  900  1000ms
Phase: 0    0.5  1.0  1.5  2.0  2.5  3.0  3.5  4.0  4.5  5.0
Sine:  0   +0.5 +0.9 +1.0 +0.9 +0.5  0   -0.5 -0.9 -1.0 -0.9
       │    ↗    ↗    ←peak    ↘    │    ↘    ↘   ←trough ↗
```

**Smooth oscillation antara -1.0 dan +1.0**

---

### Step 3: Apply to Ignition Timing

```cpp
float getTimingOffset() {
    float effect = getRumbleEffect();  // -1.0 to +1.0
    
    float maxTiming = 4.0;  // ±4 degrees
    
    return effect * maxTiming;  // -4° to +4°
}

// In ignition calculation
float advance = baseAdvance + getTimingOffset();
```

**Example:**
```
Base timing: 10°

effect = +1.0 → timing = 10° + 4° = 14° (advance) → RPM naik!
effect =  0.0 → timing = 10° + 0° = 10° (normal)  → RPM normal
effect = -1.0 → timing = 10° - 4° = 6°  (retard)  → RPM turun!
```

**Timing varies → Power varies → RPM bounce!**

---

### Step 4: Apply to Fuel

```cpp
float getFuelMultiplier() {
    float effect = getRumbleEffect();  // -1.0 to +1.0
    
    float maxFuel = 10.0;  // ±10%
    
    float fuelPercent = effect * maxFuel;  // -10% to +10%
    
    return 1.0 + (fuelPercent / 100.0);  // 0.9x to 1.1x
}

// In fuel calculation
float fuel = baseFuel * getFuelMultiplier();
```

**Example:**
```
Base fuel: 10ms

effect = +1.0 → fuel = 10ms × 1.1 = 11ms (rich)  → More power, RPM naik!
effect =  0.0 → fuel = 10ms × 1.0 = 10ms (normal) → Normal
effect = -1.0 → fuel = 10ms × 0.9 = 9ms  (lean)   → Less power, RPM turun!
```

**Fuel varies → Power varies → RPM bounce!**

---

## Combined Method (Recommended)

**Apply BOTH timing AND fuel variation:**

```cpp
float effect = getRumbleEffect();  // -1.0 to +1.0

// Timing offset
float timingOffset = effect * 4.0;  // ±4°

// Fuel multiplier
float fuelMult = 1.0 + (effect * 0.1);  // 0.9x to 1.1x

// Apply both!
ignition.timing = baseAdvance + timingOffset;
injection.duration = baseFuel * fuelMult;
```

**When effect = +1.0 (peak):**
- Timing: Advanced +4°
- Fuel: Rich +10%
- Result: **Max power → RPM spike up!**

**When effect = -1.0 (trough):**
- Timing: Retarded -4°
- Fuel: Lean -10%
- Result: **Min power → RPM drop!**

**Result: RPM oscillates smoothly!**

---

## Visual Flow Diagram

```
┌─────────────────────────────────────────────┐
│  Main Engine Loop (100 Hz)                  │
└─────────────────┬───────────────────────────┘
                  │
                  ▼
        ┌─────────────────────┐
        │  isIdleCondition()   │
        │  - Check RPM         │
        │  - Check TPS         │
        │  - Check CLT         │
        └─────────┬───────────┘
                  │
         Yes ◄────┴────► No (skip rumble)
          │
          ▼
    ┌──────────────────┐
    │ getRumbleEffect() │
    │ - Update phase    │
    │ - Calculate sine  │
    │ - Apply amplitude │
    └─────┬────────────┘
          │
          ├──────────────────┬─────────────────┐
          │                  │                 │
          ▼                  ▼                 ▼
  ┌───────────────┐  ┌──────────────┐  ┌─────────────┐
  │ Timing Offset │  │ Fuel Adjust  │  │ Spark Skip  │
  │ ±4 degrees    │  │ ±10%         │  │ Periodic    │
  └───────┬───────┘  └──────┬───────┘  └──────┬──────┘
          │                  │                 │
          └──────────────────┴─────────────────┘
                             │
                             ▼
                    ┌─────────────────┐
                    │  Engine Output   │
                    │  RPM oscillates! │
                    │  "Drumbal" sound │
                    └──────────────────┘
```

---

## Tuning Parameters

### Amplitude (Kekuatan Effect)

```
amplitude = 30%  → Sine × 0.3 → Subtle effect
amplitude = 50%  → Sine × 0.5 → Medium effect ⭐ (recommended)
amplitude = 100% → Sine × 1.0 → Maximum effect
```

**Higher amplitude = Stronger rumble**

---

### Period (Kecepatan Oscillation)

```
period = 200ms  → Fast bounce (aggressive)
period = 500ms  → Medium bounce ⭐ (recommended)
period = 1000ms → Slow lope (Harley style)
```

**Shorter period = Faster RPM changes**

Phase increment = 2π / (period / 10ms)

---

### Method (Cara Bikin Rumble)

**0 = Timing Only**
```cpp
offset = effect × maxTiming
fuel = normal (no change)
```
Effect: Smooth, safe

**1 = Fuel Only**
```cpp
timing = normal (no change)
fuel = baseFuel × (1 + effect × maxFuel/100)
```
Effect: Aggressive, bisa rich/lean spike

**2 = Spark Cut**
```cpp
if (effect < -0.7) {
    skipSpark = true;  // Skip firing!
}
```
Effect: "Popping" sound

**3 = Combined** ⭐ (recommended)
```cpp
offset = effect × maxTiming
fuel = baseFuel × (1 + effect × maxFuel/100)
```
Effect: Maximum rumble, balanced

---

## Real Example

Settings:
```
amplitude = 50%
period = 500ms
method = Combined
maxTiming = 4°
maxFuel = 10%
```

Timeline:
```
Time    Phase   Sine    Effect  Timing  Fuel    RPM
----    -----   ----    ------  ------  ----    ---
0ms     0.0     0.00    0.00    10°     100%    1000
125ms   1.57    1.00    0.50    12°     105%    1050  ← Peak
250ms   3.14    0.00    0.00    10°     100%    1000
375ms   4.71   -1.00   -0.50    8°      95%     950   ← Trough
500ms   6.28    0.00    0.00    10°     100%    1000
625ms   1.57    1.00    0.50    12°     105%    1050  ← Peak
...
```

Result: RPM oscillates 950-1050 (±50 RPM) at 2 Hz (500ms period)

**Sound: "DUM-dum-DUM-dum-DUM-dum..."** 🏍️💨

---

## Safety Mechanisms

**Auto-disable jika:**
- RPM > maxRpm (default 1500)
- TPS > maxTps (default 5%)
- CLT < 60°C (engine cold)
- Feature disabled di TunerStudio

**Limits:**
- Timing: Max ±10° (prevents extreme advance/retard)
- Fuel: Max ±20% (prevents too lean/rich)
- Amplitude: 0-100% (scalable effect)

---

## Summary

**Idle rumble works by:**

1. ✅ Detect idle condition
2. ✅ Generate smooth sine wave
3. ✅ Vary ignition timing (±4°)
4. ✅ Vary fuel amount (±10%)
5. ✅ RPM oscillates (950-1050)
6. ✅ Creates "drumbal" sound

**Simple concept: Make engine power oscillate → RPM bounces!**

---

Gampang kan? Basically bikin power naik-turun pake timing & fuel, terus RPM ikut naik-turun! 🚀
