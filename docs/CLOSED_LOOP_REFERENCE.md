# Closed Loop Control - Fuel & Idle

Referensi cepet kalo mau ngoprek fuel trim atau idle control.

---

## Overview

rusEFI punya 2 closed loop system:

1. **Fuel Correction** - STFT/LTFT (koreksi AFR pake lambda sensor)
2. **Idle Control** - PID (maintain target RPM)

---

## Fuel Trim (STFT/LTFT)

### File Locations

| File | Isi |
|------|-----|
| `closed_loop_fuel.cpp` | STFT implementation |
| `closed_loop_fuel_cell.h` | Individual cell logic |
| `closed_loop_controller.h` | Base template class |

### Main Class: ShortTermFuelTrim

**Location:** `firmware/controllers/math/closed_loop_fuel.cpp`

#### Fungsi Penting

**1. getCorrection(rpm, fuelLoad) - Line 118**

Fungsi utama buat dapetin fuel correction:

```cpp
ClosedLoopFuelResult ShortTermFuelTrim::getCorrection(float rpm, float fuelLoad)
```

Returns: Fuel multiplier (contoh: 1.05 = +5% fuel)

**2. update(lambdaError) - Line 50**

Update correction based lambda error:

```cpp
void ShortTermFuelTrim::update(float lambdaError)
```

Lambda error = target lambda - actual lambda

**3. getBin(rpm, load) - Line 87**

Tentuin bin index dari RPM/load:

```cpp
size_t getBin(float rpm, float load)
```

STFT punya table 16x16 bins.

### How It Works

1. Baca lambda dari wideband sensor
2. Hitung error: `lambdaError = targetLambda - actualLambda`
3. Update correction per bin
4. Apply correction ke base fuel

Correction limits:
- Min: -10% (0.9x)
- Max: +10% (1.1x)

### Config Parameters

Di TunerStudio → Advanced → STFT:

- `stftCorrectionEnabled` - Enable/disable STFT
- `stftMinActivitySpeed` - Min RPM
- `stftMaxCellActivity` - Max correction rate

### Long Term (LTFT)

LTFT = Average dari STFT over time.

Disave ke flash, persistent antar restart.

Logic sama kayak STFT tapi lebih lambat.

---

## Idle Control

### File Location

`firmware/controllers/actuators/idle_controller.cpp`

### How It Works

PID loop:
1. Target RPM from config
2. Actual RPM from trigger 
3. Error = Target - Actual
4. PID calculate output
5. Adjust idle valve PWM

### PID Formula

```
output = (P * error) + (I * integral) + (D * derivative)
```

Where:
- P = Proportional gain (instant response)
- I = Integral gain (eliminate steady-state error)
- D = Derivative gain (damping, prevent overshoot)

### Config Parameters

Di TunerStudio → Idle Settings:

- `idleRpmPid.pFactor` - P gain
- `idleRpmPid.iFactor` - I gain
- `idleRpmPid.dFactor` - D gain
- `idleRpmTarget` - Target RPM

### Tuning Tips

**P gain terlalu tinggi:** Oscillating, gak stabil  
**I gain terlalu tinggi:** Overshoot, lambat settle  
**D gain terlalu tinggi:** Jittery, sensitive

Start dengan:
- P = 0.5
- I = 0.1
- D = 0.01

Adjust sambil monitor idle RPM.

---

## Idle Adaptive Learning (LTIT)

Long Term Idle Trim - Belajar idle fuel correction based on CLT.

### File Location

`firmware/controllers/math/closed_loop_idle.cpp`

### How It Works

1. Monitor idle stability
2. Record fuel correction per CLT bin
3. Save to flash
4. Apply on next start

Table: 16 bins CLT vs correction

Good kalo idle gak stabil after warm-up.

---

## Common Functions Reference

### Get Fuel Correction

```cpp
// Get STFT correction
auto result = engine->stft.getCorrection(rpm, load);
float correction = result.correction;  // 0.9 - 1.1
```

### Get Idle Target

```cpp
// Get target idle RPM
int targetRpm = getTargetRpm();
```

### Check if in Closed Loop

```cpp
// Check if STFT active
bool inClosedLoop = engine->module<closedLoopFuel>()->active;
```

---

## Debugging

### Via TunerStudio

**STFT debugging:**
- Tools → Live Data → STFT table
- Liat per-bin correction
- Warm color = add fuel, cold = cut fuel

**Idle debugging:**
- Live gauges: Target RPM vs Actual RPM
- Idle valve duty cycle
- PID output

### Via Serial Console

```bash
# Check STFT status
> stft

# Check idle control
> idle
```

---

## Typical Issues

### Issue 1: STFT gak aktif

**Symptoms:** Correction selalu 1.0, gak berubah

**Causes:**
- Lambda sensor rusak/unplugged
- `stftCorrectionEnabled = false`
- RPM dibawah minimum threshold

**Fix:** Check sensor, enable di config

### Issue 2: Idle hunting (naik-turun)

**Symptoms:** RPM oscillate ±50 RPM

**Causes:**
- P gain terlalu tinggi
- Vacuum leak
- Idle valve sticky

**Fix:** Kurangin P gain, check hardware

### Issue 3: Idle terlalu tinggi

**Symptoms:** Idle 1500+ RPM padahal target 1000

**Causes:**
- Air leak
- LTIT salah belajar
- Throttle stop screw terlalu buka

**Fix:** Check vacuum leak, reset LTIT

---

## Code Example

### Custom Fuel Correction

Kalo mau add custom correction logic:

```cpp
// Di default_tune.cpp atau board_configuration.cpp

void applyCustomCorrection() {
    float baseCorrection = 1.0;
    
    // Example: add 5% fuel saat cold start
    if (engine->sensors.clt < 50) {
        baseCorrection += 0.05;
    }
    
    engineConfiguration->fuelClosedLoopCorrectionEnabled = true;
}
```

### Custom Idle Target

```cpp
// Dynamic idle target based on CLT

int customIdleTarget() {
    float clt = Sensor::getOrZero(SensorType::Clt);
    
    if (clt < 50) {
        return 1500;  // Cold idle
    } else {
        return 1000;  // Warm idle
    }
}
```

---

## Reference

Kalo masih bingung:
- rusEFI Wiki: Tuning → Closed Loop
- Forum: Search "STFT" atau "idle control"

File lain:
- `SOURCE_CODE_DOCUMENTATION.md` - Overview codebase
- `OPTIMIZATION_QUICK_GUIDE.md` - Feature optimization

---

That's it. Good luck tuning! 🏍️
