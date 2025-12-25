# Page 2: I/O Interfaces & Signal Conditioning

## Overview
Page 2 contains additional I/O circuits and signal conditioning for various MCU peripherals.

## Schmitt Trigger Buffers

### IC1, IC2: SN74LVC2G17DBVR (Dual Schmitt-Trigger Buffer)
**Package**: SOT-23-6
**Function**: Clean up noisy digital signals (VR sensors, digital inputs)

**Typical connections:**
- VCC (Pin 6): 3.3V or 5V
- GND (Pin 2): Ground
- Input A (Pin 1) → Output A (Pin 6)
- Input B (Pin 3) → Output B (Pin 4)

**IC1 Usage:**
- Input signals from connector J9
- Conditions crank/cam position signals
- Pull-up resistors on inputs: R? (10k)

**IC2 Usage:**
- Additional digital input conditioning
- Similar configuration to IC1

## Solder Jumper Configuration

### JP2, JP7: Pull-up Selection (2-pad jumpers)
- Enables/disables pull-up resistors on certain inputs
- DNP (Do Not Populate) by default
- Close jumper to enable pull-up

### JP8, JP9: Hall/VR Sensor Selection (3-pad jumpers)
**Purpose**: Select sensor type for crank/cam inputs

**Configuration:**
- Pad 1: HALL sensor mode (pulls signal to VCC)
- Pad 2: Common (signal input)
- Pad 3: VR sensor mode (pulls to GND via resistor)

**Associated resistors:**
- R25, R26, R41, R42 (2.7k) - Hall mode pull-ups
- R? - VR mode termination

## Additional I/O

**GPIO connections to J9:**
- Digital inputs with ESD protection
- Digital outputs with series resistors (R? 470Ω)
- Mixed analog/digital capable pins

**Input protection:**
- Resistor dividers for voltage scaling
- Clamping diodes to protect MCU
- RC filters for noise reduction

---

# Page 3: Power Supply Section

## Main Power Input

### J4, J7, J8: Power Input Connectors (2-pin)
- Accept 12V battery voltage
- Fused protection

### F1, F2: Resettable Fuses (PTC, 1206)
- F1: 0.5A for low-power circuits
- F2: Higher current rating for main power

## 5V Regulator

### U8: NCV7805BTG (Linear Regulator, TO-263-3)
**Input**: 12V battery
**Output**: 5V, 1A max
**Package**: TO-263-3 (D-PAK)

**Pin Configuration:**
- Pin 1 (Tab/Pin 2): GND
- Pin 2: VIN (12V from battery)
- Pin 3: VOUT (5V output)

**Input filtering:**
- C? (100nF ceramic) - High-freq filtering
- C21 (47µF electrolytic) - Bulk capacitance
- D15 (SMBJ40A) - TVS protection on 12V input

**Output filtering:**
- C? (100nF ceramic)
- C17 (10µF electrolytic)

## 3.3V Regulator

### U3: AMS1117-3.3 (SOT-223-3)
**Input**: 5V from U8
**Output**: 3.3V, 1A max

**Pin Configuration:**
- Pin 1: GND
- Pin 2 (Tab): VOUT (3.3V)
- Pin 3: VIN (5V)

**Input filtering:**
- C29, C31, C33 (1µF ceramic)

**Output filtering:**
- C32, C34 (2.2µF ceramic)
- Multiple 100nF decoupling caps distributed across PCB

## Power Distribution

**5V Rail Usage:**
- Some peripheral ICs
- Pull-up for 5V-tolerant inputs
- Sensor excitation

**3.3V Rail Usage:**
- STM32F407 VDD
- CAN transceiver
- Most digital logic

**12V Rail Usage:**
- High-power output drivers
- Injector/coil pre-drivers

## Reverse Polarity Protection

**D14**: SS14 Schottky diode (SMA, 1A)
- Series diode OR
- Shunt configuration with fuse
- Protects against reverse battery connection

---

# Page 4: Analog Input Conditioning

## Op-Amp Circuits

### U5, U6: MCP6004 (Quad Op-Amp, SOIC-14)
**Rail**: 3.3V single supply
**Function**: Condition analog sensor signals for MCU ADC

### Typical Sensor Input Circuit

**Example: MAP Sensor**
1. Input from J9 connector
2. ESD protection: D? (BAT54S dual Schottky)
3. Input resistor: R? (2.7k)
4. Op-amp buffer/amplifier stage
5. RC filter: R? (470Ω) + C? (220nF)
6. Output to MCU ADC pin

**Voltage Dividers:**
- R? + R? (e.g., 10k + 2.7k) for scaling 5V sensors to 3.3V
- Protected by clamping diodes

**RC Low-Pass Filters:**
- Cutoff ~7kHz typical
- Remove RF interference
- Components: R (470-910Ω) + C (220nF-1nF)

## Sensor Types Conditioned

1. **MAP (Manifold Absolute Pressure)**
   - 0-5V analog output
   - Scaled to 0-3.3V via divider
   - Op-amp buffered

2. **TPS (Throttle Position Sensor)**
   - 0-5V potentiometric
   - Voltage divider + filter
   - Redundant sensing possible

3. **CLT (Coolant Temperature)**
   - Thermistor (NTC)
   - Pull-up resistor (2.7k typical)
   - Voltage divider measurement

4. **IAT (Intake Air Temperature)**
   - Similar to CLT
   - Separate input channel

5. **O2 Sensor (Narrowband)**
   - 0-1V signal
   - Direct ADC input
   - Simple RC filter

## Protection

**All analog inputs:**
- Series resistor (470Ω - 2.7k)
- Dual Schottky clamp to 3.3V/GND (BAT54S)
- RC filtering
- Op-amp buffering where needed

---

# Page 5: Output Driver Circuits

## High-Power MOSFET Drivers

### Q1, Q2, Q3, Q4, Q6, Q11: STP62NS04Z (N-Channel, TO-252-3)
**Rating**: 62A, 40V
**Function**: Drive high-current loads (injectors, ignition coils)

**Typical Circuit per MOSFET:**
1. Gate driver from U2
2. Gate resistor: R? (15Ω, 2512 package) - limits ringing
3. Flyback diode: D? (1N5819W Schottky) - clamps inductive kickback
4. Source current sense: Optional R (milliohms)
5. Drain to load (injector/coil)
6. Load connects to 12V

### U2: TC4424AVOA (Dual MOSFET Driver, SOIC-8)
**Function**: Drive gates of Q1-Q6 fast
**Input**: PWM signal from MCU (3.3V logic)
**Output**: High-current gate drive (0-12V or 0-5V)

**Pin Config:**
- VDD: 5V or 12V
- IN_A: MCU PWM signal
- OUT_A: To Q1 gate
- IN_B: MCU PWM signal  
- OUT_B: To Q2 gate
- GND

## Low-Power Output Drivers

### Q5, Q7, Q8, Q9, Q10: AO3400A (N-Channel, SOT-23)
**Rating**: 5.7A, 30V
**Function**: Drive relays, LEDs, low-current solenoids

**Typical Circuit:**
1. MCU GPIO → Gate via R (1k)
2. Drain to load
3. Source to GND
4. Flyback diode if driving inductive load

## High-Side Switches

### Q12, Q13: ISL9V3040D3S (P-Channel, TO-263-2)
**Function**: Switch 12V power to sensors/peripherals
**Control**: MCU GPIO through inverting driver

**Circuit:**
- MCU GPIO low → MOSFET ON → 12V to load
- MCU GPIO high → MOSFET OFF
- Gate pull-up resistor (10k)

## Protection & Current Limiting

**Flyback Diodes:**
- D13, D16, D25, D26, D29, D31, D32, D33 (1N5819W)
- Parallel to inductive loads
- Clamp voltage spikes

**Series Resistors:**
- Limit fault current
- Dampen ringing
- Values: 15Ω (power) to 470Ω (signal)

## Output Connectors

Connected to J9 main ECU connector:
- INJ1-INJ4: Injector outputs
- IGN1-IGN4: Ignition coil outputs  
- RELAY1, RELAY2: Relay drivers
- FAN, PUMP: Auxiliary outputs

---

# Page 6: CAN & Communication Interfaces

## CAN Transceiver

### U7: TJA1051T/3/1J (High-Speed CAN, SOIC-8)
**Speed**: Up to 1Mbps
**Standard**: ISO 11898-2

**Pin Configuration:**
- Pin 1: TXD (from MCU CAN_TX)
- Pin 2: GND
- Pin 3: VCC (5V)
- Pin 4: RXD (to MCU CAN_RX)
- Pin 5: VREF (not used)
- Pin 6: CANH
- Pin 7: CANL
- Pin 8: STB (Standby, tied to GND for normal mode)

**MCU Connection:**
- STM32 CAN1_TX (e.g., PB9) → Pin 1 (TXD)
- STM32 CAN1_RX (e.g., PB8) → Pin 4 (RXD)

**CAN Bus Termination:**
- R7: 120Ω (0603) between CANH and CANL
- Populate only if ECU is at end of bus

**ESD Protection:**
- D? (TVS diodes) on CANH/CANL lines
- Protects from voltage spikes

**Filtering:**
- C? (100nF) on VCC
- C? (100nF) between CANH and CANL (common-mode filter)

## Serial/UART Communications

**Connector**: J? or via J9 pins

**UART Signals:**
- TX (e.g., PA9)
- RX (e.g., PA10)
- Optional RTS/CTS for flow control

**Level Shifters** (if 5V devices):
- IC1/IC2 buffers can be used
- Or direct 3.3V-5V communication if pins are 5V-tolerant

## SPI (e.g., for SD Card)

### J5: microSD Socket (THD2528-11SD-GF)

**SPI Signals:**
- SCK: SPI clock (e.g., PB13)
- MISO: Master In (e.g., PB14)
- MOSI: Master Out (e.g., PB15)
- CS: Chip select (e.g., PB12)

**Power:**
- 3.3V to SD card
- Decoupling cap close to socket

**Card Detect:**
- GPIO input senses card presence
- Pull-up resistor

## I2C/Sensors

**Internal I2C for sensors:**
- SCL, SDA lines
- Pull-ups: R35, R36, R91 (2.7k)
- Connected to U9 (pressure sensor) and other I2C peripherals

---

# Page 7: Sensor Interfaces & Misc Circuits

## Pressure Sensor

### U9: LPS25HB (Barometric Pressure, HLGA-10)
**Interface**: I2C or SPI
**Function**: Measure atmospheric/manifold pressure

**I2C Connection:**
- SCL: To MCU I2C clock
- SDA: To MCU I2C data
- VDD: 3.3V
- GND: Ground

**Bypass caps:**
- C? (100nF) close to VDD pin

## Knock Sensor Input

**Connector Pin:** J9-?

**Circuit:**
- AC-coupled input via C? (220nF)
- High-pass filter (removes DC)
- Amplifier stage (op-amp from U5/U6)
- Bandpass filter (~5-10kHz for knock frequency)
- Output to MCU ADC
- Gain set by R divider

## Battery Voltage Sensing

**Divider:**
- R? (100k) + R? (10k) 
- Scales 12V → ~1V for ADC
- Protected by clamp diodes
- Filtered by C? (100nF)

## Ignition Voltage Selection

### JP1: 3-Pin Header (M20-9990345)
**Purpose**: Select logic voltage source

**Positions:**
- 1-2: Use 5V rail
- 2-3: Use 12V rail (or other)

**Usage**: Power certain sensors from selectable voltage

## Status LED

### D1-D4, D7, D8: LEDs (0603, Wurth 151031SS04000)
**Colors**: Various (likely red/green/yellow)

**Circuit per LED:**
- MCU GPIO → R (470Ω) → LED anode
- LED cathode → GND
- Current: ~7mA per LED

**Functions:**
- Power indicator
- CAN activity
- Error codes
- Heartbeat

## Test Points & Jumpers

**Dual VR Connector (P1):**
- DIP-8 socket
- DNP (for bench testing)
- Allows external potentiometers for TPS/MAP simulation

---

# Page 8: Title Block & Notes

## Schematic Information

**Title**: [ECU Board Name]
**Revision**: [Version from PDF]
**Date**: December 25, 2025 (or original date)
**Designer**: [From metadata if present]

## Design Notes

1. **PCB Layer Stack:**
   - Likely 4-layer: Signal / GND / Power / Signal
   - Or 2-layer for simpler design

2. **Grounding:**
   - Single-point star ground recommended
   - Analog ground separate from digital if possible
   - Heavy ground plane under MCU and power section

3. **Component Placement:**
   - Decoupling caps close to IC pins
   - Power section away from analog
   - High-current traces wide and short

4. **Firmware Notes:**
   - STM32F407VGT6 compatible with rusEFI firmware
   - See repository for configuration

5. **Testing Points:**
   - VCC test points
   - Signal test points on critical nets

## Bill of Materials Reference

*See separate BOM CSV file for complete component list*

## Manufacturing Notes

- PCB thickness: 1.6mm standard
- Copper weight: 1oz (35µm) or 2oz for high current
- Solder mask: Green (or as specified)
- Silkscreen: White
- Finish: HASL or ENIG

## Connector Pinouts

*Detailed pinout for J9 (33-pin main connector) would be documented here with signal names, pin numbers, and wire colors if applicable*

---

EOF
