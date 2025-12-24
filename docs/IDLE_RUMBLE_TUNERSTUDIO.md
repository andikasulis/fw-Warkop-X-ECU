# Idle Rumble - TunerStudio Menu Location

Cara akses Idle Rumble settings di TunerStudio.

---

## Default Location (Auto-Generated)

Settings idle rumble akan muncul di section yang auto-generate dari field definitions.

### Cara Cari Settings:

**Method 1: Via Search (PALING MUDAH!)**

1. Open TunerStudio
2. Connect ke ECU
3. Press **Ctrl+F** (Windows) atau **Cmd+F** (Mac)
4. Type: `idle rumble` atau `idleRumble`
5. Jump to settings!

---

**Method 2: Via Settings Tree**

Navigate manual:

```
TunerStudio
 └─ Settings (gear icon)
    └─ Engine
       └─ Advanced
          └─ (scroll down cari "Idle Rumble" fields)
```

atau

```
TunerStudio
 └─ Controller
    └─ Calibrations
       └─ (scroll cari "Idle Rumble" fields)
```

---

## Available Settings

All idle rumble parameters yang bisa di-adjust:

### Basic

- **idleRumbleEnabled** - Enable/disable (0 atau 1)
- **idleRumbleAmplitude** - Kekuatan effect (0-100%)
- **idleRumblePeriod** - Kecepatan rumble (1-20, x100ms)

### Method

- **idleRumbleMethod** - Cara bikin rumble:
  - `0` = Timing only
  - `1` = Fuel only
  - `2` = Spark cut
  - `3` = Combined (timing + fuel) ⭐ recommended

### Advanced

- **idleRumbleTiming** - Max timing offset (-10 to +10 degrees)
- **idleRumbleFuel** - Max fuel adjustment (-20 to +20%)

### Limits

- **idleRumbleMaxRpm** - Max RPM untuk active (0-2000, default 1500)
- **idleRumbleMaxTps** - Max TPS untuk active (0-20%, default 5%)

---

## Recommended Starting Values

```
idleRumbleEnabled:   1       (enabled)
idleRumbleAmplitude: 50      (50%)
idleRumblePeriod:    5       (500ms)
idleRumbleMethod:    3       (combined)
idleRumbleTiming:    4       (±4 degrees)
idleRumbleFuel:      10      (±10%)
idleRumbleMaxRpm:    1500    (active below 1500 RPM)
idleRumbleMaxTps:    5       (active below 5% TPS)
```

---

## Quick Setup Guide

### Step 1: Find Settings

Use **Ctrl+F** (Cmd+F), search `idleRumbleEnabled`

### Step 2: Enable

Set `idleRumbleEnabled = 1`

### Step 3: Set Basic Values

```
Amplitude: 50
Period: 5
Method: 3
```

### Step 4: Burn to ECU

Click "Burn" button

### Step 5: Test

1. Start engine
2. Let idle warm up (CLT > 60°C)
3. Listen for rumble effect!

---

## Tuning Tips

**Too Strong?**
- Lower amplitude (try 30)
- Or increase period (try 8)

**Too Weak?**
- Increase amplitude (try 70)
- Or decrease period (try 3)

**Want Different Style?**

**Harley V-Twin Style:**
```
Amplitude: 60
Period: 9 (900ms - slow lope)
Method: 3
```

**Racing Aggressive:**
```
Amplitude: 70
Period: 3 (300ms - fast)
Method: 3
```

**Subtle Daily:**
```
Amplitude: 30
Period: 6 (600ms)
Method: 0 (timing only)
```

---

## Troubleshooting

### Can't Find Settings

Try search terms:
- `idleRumble`
- `rumble`
- `drumbal`
- Find any one field, others akan nearby

### Settings Greyed Out

Load correct `.ini` file:
- File → Load Tune
- Select `rusefi_warkop_x.ini`

### Changes Not Applied

1. Make sure to click "Burn"
2. Wait for confirmation
3. Check ECU flash success

---

## Alternative: Edit .ini Directly

Kalo settings gak muncul di UI, bisa edit `.ini` file:

1. Close TunerStudio
2. Open `rusefi_warkop_x.ini` di text editor
3. Find `[Constants]` section
4. Look for `idleRumble` parameters
5. Edit values directly
6. Save file
7. Reopen TunerStudio

**Warning:** Advanced users only!

---

## Custom Dialog (Future Enhancement)

Untuk bikin custom dialog yang dedicated, perlu:

1. Edit TunerStudio template file
2. atau Create custom .ini override
3. atau Modify generated .ini post-build

**For now:** Use search function (Ctrl+F) - paling mudah! 🔍

---

Last Updated: 2025-12-24
