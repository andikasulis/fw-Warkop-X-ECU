# Quickshift Sensor Setup

Panduan pasang quickshift sensor di Warkop-X ECU.

---

## TL;DR

**Recommended pin:** PB0 atau PB1 (analog reserve)

Quick setup:
1. Solder quickshift wire ke pin PB0
2. Config di TunerStudio
3. Set cut time (biasanya 50-100ms)
4. Test & adjust

---

## Pin Options

### Option 1: PB0 (AC Input) - RECOMMENDED

**Currently:** AC pressure switch (gak kepake di motor)

Kenapa bagus:
- AC input jarang dipakai di motor
- Fast interrupt (EXTI0)
- Pin udah configured

Config:
```cpp
// di board_configuration.cpp
engineConfiguration->torqueReductionTriggerPin = Gpio::B0;
```

### Option 2: PB1 (Analog Reserve) - RECOMMENDED

**Currently:** Gak dipakai sama sekali

Kenapa bagus:
- Free pin, gak kepake
- Fast interrupt (EXTI1)
- Aman, gak bentrok

Config:
```cpp
engineConfiguration->torqueReductionTriggerPin = Gpio::B1;
```

### Option 3: PC4 (Clutch) - Alternatif

**Currently:** Clutch switch

Trade-off:
- Clutch switch ilang
- Bisa dipake kalo gak pake clutch safety

Config:
```cpp
engineConfiguration->torqueReductionTriggerPin = Gpio::C4;
```

---

## Hardware Connection

### Quickshift Sensor Types

**1. Mechanical Switch (Normally Open)**
```
Sensor           ECU
──────           ───
Terminal 1 ─────► PB0 (signal)
Terminal 2 ─────► GND
```

**2. Mechanical Switch (Normally Closed)**
```
Sensor           ECU
──────           ───
Terminal 1 ─────► PB0 (signal)
Terminal 2 ─────► +5V (atau +12V via resistor)
```

Kalo sensor NC, lu perlu pull-up resistor ~10kΩ.

### With Pull-Up Resistor

```
+5V
 │
 ├───[ 10kΩ ]───┬──► to PB0
 │              │
               QS Switch
                │
               GND
```

---

## Software Configuration

### TunerStudio Settings

1. **Enable Launch/Flat Shift**
   - Settings → Launch Control
   - Enable "Flat shift / no-lift upshift" 

2. **Pin Configuration**
   - Advanced → I/O Pins
   - "Torque reduction trigger pin" → set ke PB0 atau PB1

3. **Cut Settings**
   - "Flat shift duration" → 50-100ms (start dari 80ms)
   - "Launch activation mode" → Switch
   - "Launch switch polarity" → sesuaiin sama sensor (NO = Low, NC = High)

4. **Ignition Cut or Fuel Cut**
   - "Flat shift mode" → Ignition cut (lebih smooth)
   - Atau pake fuel cut (lebih agresif)

5. **Burn to ECU**

---

## Testing

### Bench Test

1. Gak pasang shift sensor dulu
2. Connect pin quickshift ke GND (simulate shift)
3. Monitor di TunerStudio:
   - Output Channels → "Launch/flat shift active"
   - Should trigger saat grounded

### On-Bike Test

1. Idle, neutral
2. Tekan shift lever (trigger sensor)
3. Check TunerStudio - active?
4. Kalo oke, test ride

### Test Ride

1. Start konservatif: 80ms cut time
2. Test shift di ~5000 RPM
3. Kalo masih kasar → tambahin cut time
4. Kalo gigi susah masuk → kurangin cut time
5. Sweet spot biasanya 60-100ms

---

## Tuning Cut Time

| Feel | Cut Time | Action |
|------|----------|--------|
| Gigi susah masuk, grind | 50-60ms | Tambahin 10ms |
| Shift smooth tapi lama | 100ms+ | Kurangin 10ms |
| Perfect, smooth, quick | 70-90ms | Keep it! |

Tiap motor beda, adjust sesuai feel lu.

---

## Troubleshooting

### Quickshift Gak Trigger

1. Check wiring - sensor ke pin correct?
2. Check polarity - NO vs NC
3. Check pin config di TS
4. Test continuity sensor saat shift

### Cut Terlalu Lama / Pendek

1. Adjust "Flat shift duration" di TS
2. Start dari 80ms
3. Increment 10ms sampe comfortable

### Engine Mati Saat Shift

1. Cut time terlalu lama - kurangin
2. Mixture terlalu lean - check AFR
3. Ignition cut terlalu agresif - coba fuel cut

### Shift Masih Kasar

1. Cut time kurang - tambahin
2. Clutchless shift technique - practice!
3. Gearbox issue - bukan masalah ECU

---

## Advanced: Adjustable Cut Time

Kalo mau cut time beda per RPM range:

Edit `controllers/actuators/torque_reduction.cpp`:

```cpp
// Example: Progressive cut time

float getCutTime(int rpm) {
    if (rpm < 5000) {
        return 60;  // Short cut low RPM
    } else if (rpm < 8000) {
        return 80;  // Medium cut mid RPM
    } else {
        return 100; // Long cut high RPM
    }
}
```

Build ulang firmware. Advanced users only!

---

## Wiring Diagram

```
Quickshift Sensor (NO)
        │
        ├───────► PB0 (ECU)
        │
       GND


With Pull-Up (NC):

+5V
 │
10kΩ
 │
 ├───────► PB0
 │
Sensor
 │
GND
```

---

## Recommended Parts

- Quickshift sensor: Any motorcycle quickshift (NO type recommended)
- Wire: 22 AWG, shielded kalo bisa
- Resistor (kalo NC): 10kΩ, 1/4W
- Connector: JST atau Deutsch

---

## Tips

1. Route wire away dari high-voltage ignition
2. Use shielded cable kalo possible
3. Start konservatif (80ms), adjust slowly
4. Practice clutchless shift technique
5. Gearbox harus sehat (gak aus)

---

## Safety

- Quickshift gak replace clutch! Masih perlu clutch buat starting/stopping
- Jangan quickshift saat cornering hard atau full lean
- Practice di jalan sepi dulu

---

Itu aja. Have fun quickshifting! 🏍️💨
