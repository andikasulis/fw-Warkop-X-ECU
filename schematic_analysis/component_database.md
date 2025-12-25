# ECU Component Database - Organized BOM

## Main ICs

### Microcontroller
- **U1**: STM32F407VGT6 (LQFP-100, 14x14mm, 0.5mm pitch)
  - ARM Cortex-M4, 1024KB Flash, 192KB RAM, 168MHz
  - 82 GPIO pins
  
### Voltage Regulators
- **U3**: AMS1117-3.3 (SOT-223-3)
  - 1A LDO, 3.3V fixed output
  - LCSC: C6186
  
- **U8**: NCV7805BTG (TO-263-3)
  - 5V regulator
  - MPN: NCV7805BTG
  - Digikey: NCV7805BTGOS-ND

### Motor Drivers & Buffers
- **U2**: TC4424AVOA (SOIC-8)
  - Dual MOSFET driver
  - LCSC: C44150
  
- **IC1, IC2**: SN74LVC2G17DBVR (SOT-23-6)
  - Dual Schmitt-trigger buffer
  - LCSC: C10429

### Op-Amps
- **U5, U6**: MCP6004 (SOIC-14)
  - Quad 1MHz low-power op-amp

### CAN Transceiver
- **U7**: TJA1051T/3/1J (SOIC-8)
  - High-speed CAN transceiver, 1Mbps
  - LCSC: C38695

### Sensors
- **U9**: LPS25HB (HLGA-10)
  - Pressure sensor
  - LCSC: C94049

### ESD Protection
- **U4**: SRV05-4 (SOT-23-6)
  - TVS diode array

---

## Power MOSFETs

### High-Power N-Channel
- **Q1, Q2, Q3, Q4, Q6, Q11**: STP62NS04Z (TO-252-3)
  - 6 units total
  - For injector/coil drivers

### Low-Power N-Channel
- **Q5, Q7, Q8, Q9, Q10**: AO3400A (SOT-23)
  - 5 units, 30V, 5.7A
  - LCSC: C20917

### High-Side Switch
- **Q12, Q13**: ISL9V3040D3S (TO-263-2)
  - 2 units
  - LCSC: C462128

---

## Capacitors

### Decoupling (100nF)
**Total: 27 units**
- Footprint: 0603 (1608 metric)
- Various MPNs:
  - FA18X8R1E104KNU06 (TDK) - 10 units: C10, C11, C15, C18, C20, C24, C3, C4, C47, C9
  - CC0603KRX7R9BB104 - 6 units: C19, C35, C38, C39, C40, C41
  - Generic 100nF - 7 units: C30, C42, C43, C44, C45, C46, C54
  - C1: 100n (C14663)

### Other Values
- **220nF**: C12, C13, C14, C48, C5, C6, C7 (7 units, LCSC: C21120)
- **1nF**: C16, C22, C49, C50, C51, C52, C53, C55 (8 units, LCSC: C1588)
- **10nF**: C2 (FA18X7R1H103KNU06)
- **470pF**: C8 (LCSC: C1620)
- **33pF**: C23, C26 (2 units, LCSC: C1663)
- **20pF**: C27, C28 (2 units, LCSC: C1648)
- **1uF**: C25, C29, C31, C33 (4 units)
- **2.2uF**: C32, C34 (2 units, LCSC: C23630)
- **10uF**: C17 (Electrolytic, 6.3x5.4mm, EEU-FC1H100L)
- **47uF**: C21, C37 (Electrolytic, EIA-6032-28)

---

## Resistors (0603 Package)

### By Value
- **100k**: R1, R2, R15, R16, R43, R102 (6 units, LCSC: C25803)
- **10k**: R3, R4, R27, R33, R45, R59, R62, R63, R84, R85, R90, R94 (12 units total)
- **1k**: R5, R6, R17, R18, R19, R20, R29, R37, R47, R8, R103 (11 units)
- **2.4k**: R9, R10, R23, R24 (4 units, LCSC: C22940)
- **2.7k**: R25, R26, R35, R36, R41, R42, R50, R51, R54, R55, R86, R91 (12 units)
- **470Ω**: R11, R12, R13, R21, R22, R28, R31, R32, R34, R38, R39, R40, R44, R48, R65-R78, R87, R88, R92 (many units)
- **910Ω**: R14, R67-R70, R75-R78 (9 units, LCSC: C140066)
- **3.9k**: R30 (LCSC: C23018)
- **100Ω**: R46, R60, R61, R89, R93 (5 units, LCSC: C22775)
- **15Ω**: R52, R53 (2 units, 2512 package!)
- **1MΩ**: R58 (LCSC: C22935)
- **120Ω**: R7 (LCSC: C23162)
- **5.1k**: R79, R80 (2 units, LCSC: C23186)
- **22Ω**: R81, R82 (2 units, LCSC: C23345)
- **4.7k**: R83 (LCSC: C23162)

---

## Diodes

### LEDs (0603)
- **D1-D4, D7, D8**: 6x general LED (151031SS04000, Wurth)
- **LED1, LED2, LED3**: 3x RED LED (SML-310LTT86, LCSC: C2286)

### Schottky Diodes
- **D10, D17-D20, D22-D24, D30, D9**: 10x BAT54S (SOT-23 dual Schottky, LCSC: C7420333)
- **D13, D16, D25, D26, D29, D31-D33**: 8x 1N5819W (SOD-123)
- **D34**: BAT54C (SOT-23, common cathode)

### Si Diodes
- **D11, D12, D5, D6**: 4x 1N4148WS (SOD-323, fast switching, LCSC: C2128)

### Power Diodes
- **D14**: SS14 (SMA, Schottky 1A, LCSC: C2480)
- **D15**: SMBJ40A (SMA, TVS 40V)

---

## Connectors

### Main ECU Connector
- **J9**: 1554458-2 (TE, 33-pin, 1.0x0.64mm pitch)
  - Mouser: 1554458-2
  - Main harness connection

### USB & Communication
- **J3**: TYPE-C 16PIN 2MD(073) (USB-C receptacle, LCSC: C2765186)
- **J5**: THD2528-11SD-GF (microSD socket, LCSC: C283232)
- **J6**: USB header (2x02, 2.54mm pitch)

### Debugging & Programming
- **J2**: ST-Link (1x04, 2.54mm pitch vertical)

### Power & Signals
- **J1**: 4-pin JST XH (S4B-XH-A-1, 2.5mm pitch)
- **J4, J7, J8**: 3x 2-pin headers (2.54mm pitch)
   
### Jumpers
- **JP1**: Ignition Voltage selector (1x03, 2.54mm, M20-9990345)
- **JP2, JP7**: 2x solder jumpers (PULLUP, DNP)
- **JP8, JP9**: 2x 3-pad solder jumpers (HALL/VR sensor select, DNP)

### Potentiometer
- **P1**: Dual VR C (DIP-8 socket, DNP - for testing)

---

## Crystals

- **Y1**: 8MHz (SMD 5032, X50328MSB2GI, LCSC: C115962)
- **Y2**: 32.768kHz (SMD 3215, Q13FC13500004, LCSC: C32346)

---

## Misc Components

### Switches
- **SW1, SW2**: Tactile switches (TSA363G25-250B, LCSC: C354943)

### Fuses
- **F1**: 0.5A PTC resettable fuse (1206)
- **F2**: PTC fuse (1206)

### Ferrite Bead
- **FB1**: Ferrite bead (0805, LCSC: C1015)

### Battery
- **BT1**: CR1220 coin cell (RTC backup)

---

## Component Count Summary

| Type | Quantity |
|------|----------|
| ICs | 9 |
| MOSFETs | 13 |
| Capacitors | ~55 |
| Resistors | ~100 |
| Diodes/LEDs | ~30 |
| Connectors | 10 |
| Crystals | 2 |
| Switches | 2 |
| Fuses | 2 |
| **TOTAL** | **~220+** |

