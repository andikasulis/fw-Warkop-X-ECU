# Daftar Section Titles di Skema ECU
## (Judul/Label untuk Navigasi - Cocokkan saat bikin KiCad)

Berikut adalah **judul section/bagian** yang terlihat di skema asli. Gunakan ini sebagai panduan saat membuat schematic di KiCad agar lebih mudah navigasi.

---

## Halaman 5: Output Drivers (Pengendali Output)

### Injector Drivers (Pengendali Injektor)

#### 📌 **Injector Driver 1** (Pengendali Injektor 1)
- Komponen: Q1 (STP62NS04Z)
- Gate resistor: R5 (1k)
- Pull-down: R17 (1k)
- Flyback diode: D? (1N5819W)
- LED indicator: D? dengan R (2.4k)
- Output: INJ-1-Out

#### 📌 **Injector Driver 2**
- Komponen: Q2 (STP62NS04Z)
- Gate resistor: R6 (1k)
- Pull-down: R18 (1k)
- Output: INJ-2-Out

#### 📌 **Injector Driver 3**
- Komponen: Q3 (STP62NS04Z)
- Gate resistor: R2 (100k)
- Pull-down: R15 (100k)
- Flyback diode: D32 (1N5819W)
- Output: INJ-3-Out

#### 📌 **Injector Driver 4** (Pengendali Injektor 4)
- Komponen: Q4 (STP62NS04Z)
- Gate resistor: R1 (100k)
- Pull-down: R16 (100k)
- Flyback diode: D33 (1N5819W, bottom)
- LED indicator: D? dengan R (470r)
- Output: INJ-4-Out

#### 📌 **Injector Driver** (Additional Channel)
- Komponen: Q6 (STP62NS04Z)
- Gate resistor: R43 (100k)
- Pull-down: R102/R103
- Output: Additional injector

---

### Ignition Drivers (Pengendali Koil Pengapian)

#### 📌 **Ignition Driver 1** (Pengendali Koil 1)
- Komponen: Q11 (STP62NS04Z)
- Gate resistor: R47 (1k)
- Pull-down: ?
- Flyback diode: D? (1N5819W)
- LED indicator: D1 (LED 0603) dengan R11 (470r)
- Jumper: JP1 (Ignition Voltage selector)
- Output: Ke koil pengapian

#### 📌 **Ignition Driver 2**
- Similar configuration
- Different MOSFET

#### 📌 **Ignition Driver 3**
- Similar configuration

#### 📌 **Ignition Driver 4**
- Similar configuration

---

## Halaman 3: Power Supply (Catu Daya)

### Section Titles:

#### 📌 **12V Input** (Input 12V)
- Connectors: J4, J7, J8
- Fuses: F1, F2
- Protection: D14 (reverse polarity), D15 (TVS)

#### 📌 **5V Regulator** (Pengatur 5V)
- IC: U8 (NCV7805BTG)
- Input: 12V
- Output: 5V @ 1A
- Filtering: C21 (47µF input), C17 (10µF output)

#### 📌 **3.3V Regulator** (Pengatur 3.3V)
- IC: U3 (AMS1117-3.3)
- Input: 5V
- Output: 3.3V @ 1A
- Filtering: C29, C31, C33 (input), C32, C34 (output)

---

## Halaman 4: Analog Inputs (Input Analog)

### Section Titles:

#### 📌 **MAP Sensor Input** (Input Sensor MAP)
- Op-amp buffer dari U5/U6
- Voltage divider
- RC filter
- Protection: BAT54S

#### 📌 **TPS Sensor Input** (Input Sensor TPS)
- Similar circuit to MAP
- Different channel

#### 📌 **CLT Sensor Input** (Input Sensor Suhu Air / Coolant)
- Thermistor configuration
- Pull-up resistor 2.7k
- Filter

#### 📌 **IAT Sensor Input** (Input Sensor Suhu Udara / Intake Air)
- Similar to CLT
- Separate channel

#### 📌 **O2 Sensor Input** (Input Sensor Oksigen)
- Direct input
- Simple RC filter
- No voltage divider needed

---

## Halaman 6: Communications (Komunikasi)

### Section Titles:

#### 📌 **CAN Transceiver** (Transceiver CAN)
- IC: U7 (TJA1051)
- Termination: R7 (120Ω)
- Signals: CANH, CANL

#### 📌 **microSD Card** (Kartu microSD)
- Socket: J5
- Interface: SPI
- Signals: SCK, MISO, MOSI, CS

#### 📌 **USB Interface** (already in Page 1)
- Connector: J3 (Type-C)
- Protection: U4 (SRV05-4)

---

## Halaman 7: Sensors & Misc (Sensor & Lain-lain)

### Section Titles:

#### 📌 **Barometric Pressure Sensor** (Sensor Tekanan Barometrik / Baro)
- IC: U9 (LPS25HB)
- Interface: I2C
- Pull-ups: R35, R36, R91 (2.7k)

#### 📌 **Status LEDs** (LED Indikator Status)
- LED1: Power/Heartbeat (RED)
- LED2: CAN Activity (RED)
- LED3: Error/Warning (RED)
- Current limiting: 470Ω each

#### 📌 **Battery Voltage Sensing** (Pendeteksi Tegangan Baterai)
- Voltage divider: 100k + 10k
- Filter: 100nF
- To ADC pin

#### 📌 **Test Points** (Titik Test untuk Debugging)
- Various signal test points
- Power rail test points

---

## Halaman 1: MCU Core (Inti Mikrokontroler)

### Section Titles:

#### 📌 **Main Microcontroller** (Mikrokontroler Utama)
- IC: U1 (STM32F407VGT6)
- Package: LQFP-100

#### 📌 **Power Distribution** (Distribusi Daya)
- VDD pins: 6 locations
- Decoupling: 10x 100nF capacitors
- VDDA filtering: FB1 + capacitors

#### 📌 **Clock System** (Sistem Clock)
- Main oscillator: Y1 (8MHz) + C23, C26 (33pF)
- RTC oscillator: Y2 (32kHz) + C27, C28 (20pF)

#### 📌 **Reset Circuit** (Rangkaian Reset)
- Button: SW1
- Pull-up: R3/R4 (10k)
- Filter: C2 (10nF)

#### 📌 **USB Interface** (Antarmuka USB)
- Connector: J3 (Type-C)
- Series resistors: R81, R82 (22Ω)
- CC pull-down: R79, R80 (5.1k)
- ESD protection: U4 (SRV05-4)

#### 📌 **Debug Interface** (Antarmuka Debug)
- Header: J2 (ST-Link, 4-pin)
- Signals: SWDIO, SWCLK, SWO, RST

#### 📌 **Battery Backup** (Backup Baterai)
- Battery: BT1 (CR1220)
- For RTC

---

## Halaman 2: I/O Interfaces (Antarmuka I/O)

### Section Titles:

#### 📌 **Schmitt Trigger Buffers** (Buffer Pembentuk Sinyal)
- IC1: SN74LVC2G17DBVR
- IC2: SN74LVC2G17DBVR
- For cleaning noisy digital signals

#### 📌 **Hall/VR Sensor Selection** (Pemilih Jenis Sensor)
- Jumpers: JP8, JP9
- Pull-up mode (Hall): R25, R26 (2.7k)
- Pull-down mode (VR): R41, R42 (2.7k)

#### 📌 **Optional Pull-ups** (Pull-up Opsional)
- Jumpers: JP2, JP7
- Solder jumpers untuk enable/disable

---

## Cara Menggunakan Section Titles di KiCad

### Saat Membuat Schematic:

1. **Gunakan Text Labels** di KiCad untuk section titles:
   - Tekan **T** untuk text tool
   - Ketik title: "Injector Driver 1", "5V Regulator", dll
   - Font size: Besar (misal 20pt)
   - Bold untuk title utama

2. **Group Related Components**:
   - Tempatkan komponen section yang sama berdekatan
   - Tambahkan box/rectangle mengelilingi section
   - Beri label jelas

3. **Konsisten dengan Skema Asli**:
   - Refer ke gambar PNG/JPG dari skema asli
   - Copy exact title text
   - Posisi similar (tapi tidak harus exact coordinates)

4. **Hierarchical Labels**:
   - Input signals: (dari kiri)
   - Output signals: (ke kanan)
   - Power: (dari atas)
   - Ground: (ke bawah)

---

## Checklist Section Titles untuk Setiap Halaman

### Halaman 1: MCU Core
- [ ] "Main Microcontroller" / "Mikrokontroler Utama"
- [ ] "Power Distribution" / "Distribusi Daya"
- [ ] "Clock System" / "Sistem Clock"
- [ ] "Reset Circuit" / "Rangkaian Reset"
- [ ] "USB Interface"
- [ ] "Debug Interface"

### Halaman 2: I/O
- [ ] "Schmitt Trigger Buffers"
- [ ] "Hall/VR Sensor Selection"

### Halaman 3: Power
- [ ] "12V Input"
- [ ] "5V Regulator"
- [ ] "3.3V Regulator"

### Halaman 4: Analog
- [ ] "MAP Sensor Input"
- [ ] "TPS Sensor Input"
- [ ] "CLT Sensor Input"
- [ ] "IAT Sensor Input"
- [ ] "O2 Sensor Input"

### Halaman 5: Drivers
- [ ] "Injector Driver 1" sampai "Injector Driver 4"
- [ ] "Ignition Driver 1" (atau lebih)
- [ ] "MOSFET Gate Driver" (U2)

### Halaman 6: Communication
- [ ] "CAN Transceiver"
- [ ] "microSD Card"

### Halaman 7: Sensors
- [ ] "Barometric Pressure Sensor" / "Sensor Baro"
- [ ] "Status LEDs"
- [ ] "Battery Voltage Sensing"

---

**Gunakan file ini sebagai referensi** saat membuat schematic di KiCad - biar section titles sama dengan original dan tidak bingung! 📋
