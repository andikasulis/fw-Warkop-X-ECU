# CAN Bus Setup - Warkop-X ECU

Pin configuration dan wiring buat CAN bus ke dashboard.

---

## Pin CAN Bus (CAN1)

| Signal | Pin | Pin Alternatif |
|--------|-----|----------------|
| CAN_RX | PA11 | PD0 |
| CAN_TX | PA12 | PD1 |

Default pake PA11/PA12.

---

## Wiring Hardware

### CAN Transceiver (TJA1050 / MCP2551)

```
STM32              Transceiver         Dashboard
─────              ──────────          ─────────
PA12 (TX)  ──────► Pin 6 (CANH) ─────► CAN_H
PA11 (RX)  ◄────── Pin 7 (CANL) ◄───── CAN_L
GND        ──────► Pin 2 (GND)
3.3V/5V    ──────► Pin 3 (VCC)
```

### Termination Resistor

- **120Ω** antara CAN_H dan CAN_L
- Pasang di **kedua ujung** CAN bus
- Kalo ECU di ujung bus, pasang resistor di board

---

## Settings CAN

### Config Default

- **Baud rate:** 500 kbps
- **Protocol:** rusEFI native
- **Base ID:** 0x200
- **Rate:** 50 Hz (kirim tiap 20ms)

### Data yang Dikirim

Default broadcast:
- RPM engine
- TPS (throttle position)
- CLT (coolant temp)
- IAT (intake temp)
- Vehicle speed
- AFR (kalo ada sensor)

### CAN Addresses

| Data | CAN ID | Bytes | Format |
|------|--------|-------|--------|
| RPM | 0x200 | 0-1 | uint16 |
| TPS | 0x200 | 2-3 | uint16 |
| CLT | 0x201 | 0-1 | int16 |
| IAT | 0x201 | 2-3 | int16 |
| Speed | 0x202 | 0-1 | uint16 |
| AFR | 0x202 | 2-3 | uint16 |

---

## TunerStudio Config

### Enable CAN Bus

1. Buka TunerStudio
2. Settings → CAN Bus
3. Check "Enable CAN"
4. Set baud rate: **500 kbps**
5. Burn to ECU

### Custom CAN Messages

Kalo mau kirim data custom:

1. Advanced → Custom CAN
2. Add message
3. Set ID, data, rate
4. Burn

---

## Dashboard Wiring

### Typical Dashboard Connection

```
Dashboard           ECU
─────────           ───
CAN_H      ◄──────► PA12 (via transceiver)
CAN_L      ◄──────► PA11 (via transceiver)
GND        ◄──────► GND
+12V       ◄──────► VBatt (untuk power dashboard)
```

### Tips

- Twist CAN_H dan CAN_L cables buat reduce noise
- Jangan panjang-panjang kabel (max 5m kalo gak pake shield)
- Kalo interference banyak, pake shielded cable

---

## Troubleshooting

### Dashboard Gak Nyala

1. Check power dashboard (12V)
2. Check ground
3. Check baud rate match (500 kbps)
4. Check termination resistor

### Data Gak Muncul / Gak Update

1. Check CAN_H/CAN_L wiring (jangan kebalik!)
2. Check termination resistor (120Ω)
3. Monitor CAN di TunerStudio → CAN Monitor
4. Check CAN ID match dengan dashboard

### Data Aneh / Corrupt

1. Noise - pake shielded cable
2. Baud rate salah - set 500 kbps
3. Termination gak ada - pasang 120Ω
4. Cable terlalu panjang - keep under 5m

---

## Testing

### Via TunerStudio

1. Tools → CAN Bus Monitor
2. Liat messages yang keluar
3. Check ID dan data values

### Via Multimeter

1. Check voltage:
   - CAN_H: ~3.5V (idle)
   - CAN_L: ~1.5V (idle)
   - Differential: ~2V

2. Check resistance:
   - CAN_H to CAN_L: ~60Ω (dengan termination 120Ω di 2 ujung)

---

## Advanced: Custom CAN Protocol

Kalo dashboard butuh protocol khusus (kayak J1939, OBD2, dll):

Edit `controllers/can/can_dash.cpp`:

```cpp
// Example: Custom CAN message
void sendCustomCAN() {
    CANTxFrame frame;
    frame.IDE = CAN_IDE_STD;    // Standard ID
    frame.SID = 0x300;          // Custom ID
    frame.DLC = 8;              // 8 bytes
    
    // Pack data
    frame.data8[0] = (rpm >> 8) & 0xFF;
    frame.data8[1] = rpm & 0xFF;
    frame.data8[2] = tps;
    // ... dll
    
    canTransmit(&CAND1, CAN_ANY_MAILBOX, &frame, TIME_IMMEDIATE);
}
```

Build ulang firmware.

---

## Wiring Diagram

```
        ECU (STM32F407VET6)
        ┌─────────────────┐
    3.3V│                 │
     GND│    CAN1         │
    PA11│  (RX/TX)        │
    PA12│                 │
        └────┬────────────┘
             │
         ┌───▼──────┐
         │TJA1050   │ CAN Transceiver
         │          │
         │ H  ──────┼─────► CAN_H ───► Dashboard
         │ L  ──────┼─────► CAN_L ───► Dashboard
         │          │
         └──────────┘
              │
            120Ω (termination)
```

---

## Reference

- rusEFI CAN wiki: https://github.com/rusefi/rusefi/wiki/CAN-Bus
- TJA1050 datasheet
- MCP2551 datasheet

File terkait:
- `board_configuration.cpp` - CAN pin config
- `controllers/can/can_dash.cpp` - CAN messages
- `board.mk` - CAN feature flags

---

Itu aja. Kalo masih error, tanya di forum atau check wiki.
