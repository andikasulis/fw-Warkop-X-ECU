# rusEFI Closed Loop Logic - Function Reference

## 🎯 Overview

rusEFI menggunakan **closed loop control** untuk 2 sistem utama:
1. **Fuel Correction** (AFR/Lambda control via STFT/LTFT)
2. **Idle Control** (Target RPM via PID)

---

## 1. 🔥 Closed Loop Fuel Control (STFT/LTFT)

### Main Files
| File | Purpose |
|------|---------|
| `closed_loop_fuel.cpp` | STFT (Short Term Fuel Trim) implementation |
| `closed_loop_fuel_cell.h` | Individual correction cell logic |
| `closed_loop_controller.h` | Base template class untuk semua closed loop |

### Key Class: `ShortTermFuelTrim`

**Location**: `firmware/controllers/math/closed_loop_fuel.cpp`

#### Main Functions:

##### 1. `getCorrection(rpm, fuelLoad)` - Line 118
**Fungsi utama** untuk mendapatkan fuel correction

```cpp
ClosedLoopFuelResult ShortTermFuelTrim::getCorrection(float rpm, float fuelLoad)
```

**Flow**:
1. Check enabled state → `getCorrectionState()`
2. Tentukan region (Idle/Cruise/Power/Overrun) → `computeStftBin()`
3. Update setiap bank/cell
4. Return correction percentage

**Return**: `ClosedLoopFuelResult` dengan correction per bank

---

##### 2. `getCorrectionState()` - Line 39
Check apakah STFT enabled/disabled

```cpp
stft_state_e ShortTermFuelTrim::getCorrectionState()
```

**Checks** (disabled jika):
- ❌ User disabled (`fuelClosedLoopCorrectionEnabled = FALSE`)
- ❌ Tuning aktif (VE table editing di TunerStudio)
- ❌ Engine not running
- ❌ Startup delay belum lewat
- ❌ CLT terlalu rendah

**Return**: `stftEnabled` atau reason for disable

---

##### 3. `computeStftBin(rpm, load, cfg)` - Line 16
Tentukan region mana yang aktif

```cpp
ft_region_e ShortTermFuelTrim::computeStftBin(float rpm, float load, stft_s& cfg)
```

**Logic**:
- **Low RPM** → `ftRegionIdle` (< maxIdleRegionRpm)
- **Low Load** → `ftRegionOverrun` (< maxOverrunLoad)
- **High Load** → `ftRegionPower` (> minPowerLoad)
- **Default** → `ftRegionCruise`

**Return**: Region index (0-3)

---

##### 4. `getLearningState(sensor)` - Line 72
Check apakah learning/correction boleh jalan untuk sensor tertentu

```cpp
stft_state_e ShortTermFuelTrim::getLearningState(SensorType sensor)
```

**Pause learning jika**:
- ❌ AFR out of range (< minAfr atau > maxAfr)
- ❌ DFCO (Decel Fuel Cut Off) baru aktif
- ❌ TPS accel enrichment baru aktif
- ❌ Fuel cut baru aktif

**Purpose**: Hindari learning saat transient/unstable condition

---

### Key Class: `ClosedLoopFuelCellImpl`

**Location**: `firmware/controllers/math/closed_loop_fuel_cell.h`

#### Main Functions:

##### `update(lambdaDeadband, ignoreErrorMagnitude)` - Line 8
Update internal state cell, adjust fuel up/down

```cpp
void ClosedLoopFuelCellBase::update(float lambdaDeadband, bool ignoreErrorMagnitude)
```

**Logic**:
- Read lambda error dari sensor
- Apply deadband (ignore error kecil)
- Integrator: adjustment += error * gain
- Clamp ke min/max adjustment

---

##### `getAdjustment()` - Line 11
Get current correction percentage

```cpp
float ClosedLoopFuelCellBase::getAdjustment() const
```

**Return**: Fuel adjustment (e.g., 0.05 = +5% fuel)

---

## 2. 🔄 Closed Loop Idle Control

### Main Files
| File | Purpose |
|------|---------|
| `actuators/idle_thread.cpp` | Main idle control logic |
| `math/closed_loop_idle.cpp` | Closed loop idle PID |
| `actuators/idle_hardware.cpp` | Hardware abstraction (solenoid/stepper) |

### Key Class: `IdleController`

**Location**: `firmware/controllers/actuators/idle_thread.h` (line 56)

#### Main Function: PID Controller

Idle control menggunakan **PID** untuk maintain target RPM:

```
output = Kp * error + Ki * ∫error + Kd * d(error)/dt
```

**Inputs**:
- Target RPM (from idle table based on CLT, AC on/off, etc.)
- Current RPM

**Output**:
- Solenoid duty cycle (%)
- Atau stepper motor steps

---

## 3. 🎛️ Generic Closed Loop Template

**Location**: `firmware/controllers/closed_loop_controller.h`

### Base Class: `ClosedLoopController<TInput, TOutput>`

Template class untuk semua closed loop control.

#### Virtual Functions:

```cpp
// 1. Get target value
virtual expected<TInput> getSetpoint() = 0;

// 2. Observe current state
virtual expected<TInput> observePlant() = 0;

// 3. Calculate open loop output
virtual expected<TOutput> getOpenLoop(TInput setpoint) = 0;

// 4. Calculate closed loop correction
virtual expected<TOutput> getClosedLoop(TInput setpoint, TInput observation) = 0;

// 5. Set output to actuator
virtual void setOutput(expected<TOutput> outputValue) = 0;
```

**Final Output**: `openLoop + closedLoop`

---

## 📊 Summary Table

| Feature | Main Class | Key Function | File Location |
|---------|-----------|--------------|---------------|
| **STFT** | `ShortTermFuelTrim` | `getCorrection()` | `math/closed_loop_fuel.cpp:118` |
| **STFT Cell** | `ClosedLoopFuelCellImpl` | `update()` | `math/closed_loop_fuel_cell.h:8` |
| **LTFT** | (TODO) | (TODO) | (TODO) |
| **Idle Control** | `IdleController` | PID logic | `actuators/idle_thread.cpp` |
| **Base Template** | `ClosedLoopController` | `update()` | `closed_loop_controller.h:12` |

---

## 🔍 How to Find More

### Search commands:
```bash
# Find all closed loop related files
find firmware -name "*closed*loop*"

# Search for specific function
grep -r "getCorrection" firmware/controllers/

# Search for STFT configuration
grep -r "stft_s" firmware/
```

### Key config structs:
- `stft_s` - STFT configuration (CFG file, rusefi_config.txt)
- `stft_cell_cfg_s` - Per-cell configuration
- `pid_s` - PID configuration (for idle/boost/etc.)

---

## 💡 Untuk Motorcycle Optimization

Jika ingin **disable closed loop** (hemat CPU/RAM):

```cpp
// di board_configuration.cpp
engineConfiguration->fuelClosedLoopCorrectionEnabled = false;
```

Atau di TunerStudio: **Fuel → Fuel Correction → Closed Loop Fuel Correction = Disabled**

**Trade-off**: ECU tidak akan auto-correct AFR, harus tuning VE table manual yang akurat.
