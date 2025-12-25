# Page 1: STM32F407VGT6 Microcontroller Core

## Main IC: U1 (STM32F407VGT6)
**Package**: LQFP-100 (14x14mm, 0.5mm pitch)
**Function**: Main ECU controller - ARM Cortex-M4, 168MHz

---

## Power Distribution Network

### VDD Pins (3.3V Power)
From schematic Page 1, STM32F407 has multiple VDD pins that need decoupling:

**Typical STM32F407VGT6 power pins:**
- VDD_1 (Pin 1)
- VDD_2 (Pin 11)
- VDD_3 (Pin 28) 
- VDD_4 (Pin 50)
- VDD_5 (Pin 75)
- VDD_6 (Pin 100)
- VDDA (Pin 13) - Analog supply
- VREF+ (Pin 21) - ADC reference
- VBAT (Pin 6) - Battery backup (RTC)

**Decoupling Capacitors** (all 100nF, 0603):
- C3, C4, C9, C10, C11, C15, C18, C20, C24, C47
- Each VDD pin gets 100nF cap to GND
- Placed close to IC pins

**VDDA Filtering:**
- FB1 (Ferrite bead, 0805) filters VDDA from VDD
- C8 (470pF) - high-frequency filtering
- C1 (100n) - bulk decoupling

**VBAT Circuit:**
- BT1 (CR1220) coin cell for RTC backup
- Connected to Pin 6 (VBAT)
- D? (diode) prevents battery discharge when main power present

---

## Clock Configuration

### Main Oscillator (8MHz)
**Y1**: 8MHz crystal (SMD 5032, X50328MSB2GI)
- Connected to:
  - Pin 12: OSC_IN (PH0)
  - Pin 13: OSC_OUT (PH1)
  
**Load Capacitors:**
- C23: 33pF (0603) - OSC_IN to GND
- C26: 33pF (0603) - OSC_OUT to GND

**Resistor:**
- R1 or R2: 100k feedback resistor (parallel to crystal)

### RTC Oscillator (32.768kHz)
**Y2**: 32.768kHz crystal (SMD 3215, Q13FC13500004)
- Connected to:
  - Pin 3: OSC32_IN (PC14)
  - Pin 4: OSC32_OUT (PC15)
  
**Load Capacitors:**
- C27: 20pF (0603) - OSC32_IN to GND
- C28: 20pF (0603) - OSC32_OUT to GND

---

## Reset Circuit

**NRST** (Pin 14):
- Connected to reset button SW1
- Pull-up resistor: R3 or R4 (10k to VDD)
- Decoupling cap: C2 (10nF) to GND
- External reset input from connector

---

## Boot Configuration

**BOOT0** (Pin 94):
- Determines boot source (Flash/System/SRAM)
- Pull-down resistor: R15 or R16 (100k to GND)  
- Connected to jumper JP? for manual boot selection

**BOOT1/PB2** (Pin 37):
- Not used (internal pull-down sufficient)

---

## USB Interface

**USB_DP** (Pin 77 / PA12):
**USB_DM** (Pin 76 / PA11):

Connected to J3 (USB Type-C connector):
- Series resistors for ESD protection:
  - R81: 22Ω on D+ line
  - R82: 22Ω on D- line

- Pull-up resistors to 3.3V:
  - R79: 5.1k (CC1 configuration)
  - R80: 5.1k (CC2 configuration)

**USB ID Detection:**
- Pin 78 (PA10) - USB ID
- Connected with pull-up

**ESD Protection:**
- U4 (SRV05-4) TVS diode array protects USB lines

---

## Debug Interface (SWD)

Connected to **J2** (ST-Link header):

- **SWDIO** (Pin 72 / PA13)
- **SWCLK** (Pin 76 / PA14)
- **SWO** (Pin 89 / PB3) - Serial Wire Output
- **NRST** - Reset line

Pull-up resistors on SWD lines:
- R? (10k) on SWDIO
- R? (10k) on SWCLK

---

## GPIO Breakout

Many GPIO pins broken out to main connector **J9** (33-pin TE connector):

**Examples visible:**
- PA0-PA7: Analog inputs / GPIO
- PB0-PB15: Various functions
- PC0-PC15: Mixed use
- PD0-PD15: Output drivers
- PE0-PE15: Additional I/O

*(Exact pin mapping requires tracing connections from Page 1 image)*

---

## LED Indicators

Status LEDs connected to GPIO:
- LED1 (RED): Connected to P? via R? (470Ω) - Status/Heartbeat  
- LED2 (RED): Connected to P? via R? (470Ω) - CAN activity
- LED3 (RED): Connected to P? via R? (470Ω) - Error indicator

---

## Notes from Page 1

1. All VDD pins must have individual 100nF decoupling caps
2. One bulk cap (likely C17 10uF electrolytic) near IC
3. Analog ground (AGND) may be separate from digital ground (DGND)
4. Crystal load caps calculated for specific crystal specs
5. Boot from flash by default (BOOT0 pulled low)

---

## Next: Trace Exact Pin Numbers

To complete Page 1 documentation, need to:
1. Read exact pin numbers for each GPIO connection from PNG
2. Document which peripherals used (CAN, SPI, I2C, UART, ADC, TIM)
3. Create complete pin assignment table
4. Verify all connections to other pages

EOF
