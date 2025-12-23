# Warkop-X ECU - CAN Bus Pin Configuration

## CAN Bus Pins (CAN1)

| Signal | Pin | Alternative Pin | Function |
|--------|-----|-----------------|----------|
| CAN_RX | PA11 | PD0 | CAN Receive |
| CAN_TX | PA12 | PD1 | CAN Transmit |

## Hardware Connection

### CAN Transceiver (e.g., TJA1050, MCP2551)

```
STM32F407VET6          CAN Transceiver          CAN Bus
─────────────          ───────────────          ───────
PA12 (TX)     ───────► CANH (Pin 6)     ───────► CAN_H
PA11 (RX)     ◄─────── CANL (Pin 7)     ◄─────── CAN_L
GND           ───────► GND (Pin 2)
3.3V or 5V    ───────► VCC (Pin 3)
```

### Termination Resistor

- **120Ω resistor** between CAN_H and CAN_L at **both ends** of the CAN bus
- If your ECU is at the end of the bus, add termination resistor on the board

## CAN Bus Settings

### Default Configuration
- **Baud Rate**: 500 kbps (configurable in TunerStudio)
- **Protocol**: rusEFI native CAN protocol
- **Base CAN ID**: 0x200
- **Broadcast Rate**: 50 Hz (20ms interval)

### Broadcasted Data (Default)
- Engine RPM
- Throttle Position (TPS)
- Coolant Temperature (CLT)
- Intake Air Temperature (IAT)
- MAP (Manifold Absolute Pressure)
- Battery Voltage
- Engine Load
- Ignition Timing

## TunerStudio Configuration

### Enable CAN Broadcast
1. Open TunerStudio
2. Go to **Controllers → CAN Bus**
3. Enable **"CAN Write"**
4. Set **Baud Rate** to **500 kbps** (or 1000 kbps if dashboard supports)
5. Select **CAN protocol** (typically "rusEFI" or "Generic Dash")
6. Click **Burn** to save

### CAN Dashboard Protocols Supported
- **rusEFI native** (default)
- **MS/MegaSquirt CAN** (via canNbcType setting)
- **AiM** 
- **Haltech**
- **Generic OBD-II CAN**

### Advanced: Change CAN Base Address
If needed, change base CAN ID in TunerStudio:
- Navigate to **Controllers → CAN Bus → Base Address**
- Default: `0x200` (512 decimal)
- Range: `0x000` - `0x7FF` (standard 11-bit CAN ID)

## Troubleshooting

### Dashboard Not Receiving Data
1. **Check wiring**: Verify CAN_H and CAN_L are not swapped
2. **Check baud rate**: ECU and dashboard must match (500k or 1M)
3. **Check termination**: 120Ω resistors at both ends
4. **Check CAN enable**: Verify `canReadEnabled` and `canWriteEnabled` in code
5. **Check protocol**: Dashboard protocol must match ECU broadcast protocol

### CAN Bus Errors
- **Bus off**: Too many errors, check wiring and termination
- **No ACK**: No other device on bus, or wrong baud rate
- **Stuff error**: Electrical noise, add better grounding or shielding

## Wiring Recommendations

1. **Use twisted pair cable** for CAN_H and CAN_L (reduces noise)
2. **Keep CAN wires short** and away from high-current wires
3. **Use proper grounding** - single point ground for CAN transceiver
4. **Shield the cable** if running near ignition coils or injectors
5. **Maximum bus length**: 40m at 1Mbps, 100m at 500kbps

## Alternative Pins (if PA11/PA12 conflict with USB)

If PA11/PA12 are used for USB, use alternative CAN1 pins:

```cpp
// In board_configuration.cpp
engineConfiguration->canTxPin = Gpio::D1;  // CAN1_TX (alternative)
engineConfiguration->canRxPin = Gpio::D0;  // CAN1_RX (alternative)
```

## Notes

- STM32F407 has **2 CAN peripherals** (CAN1 and CAN2)
- Currently using **CAN1** (more compatible)
- CAN2 requires CAN1 to be enabled (shared clock)
- Maximum CAN bus speed: 1 Mbps
- Minimum: 25 kbps (not recommended for real-time data)
