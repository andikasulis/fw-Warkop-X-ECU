# Page 1: MCU Core - Ultra Detailed Step-by-Step

## Total Waktu: ~3-4 jam
## Tingkat Kesulitan: ⭐⭐⭐ (Medium - butuh ketelitian)

---

## Persiapan

### Yang Perlu Dibuka:
1. **KiCad Schematic Editor** - Sheet "MCU Core"
2. **File PNG `page-1.png`** - Untuk referensi visual
   - Lokasi: `schematic_analysis/page-1.png`
3. **Component Database** - Untuk cek nilai
   - Lokasi: `schematic_analysis/component_database.md`

### Tools KiCad yang **AKAN** Dipakai:
- **A** = Add Symbol (tambah komponen)
- **W** = Wire (sambung dengan kabel)
- **P** = Power Symbol (+3V3, GND)
- **L** = Label (beri nama net)
- **M** = Move (pindah komponen)
- **R** = Rotate (putar komponen)
- **E** = Edit properties
- **Delete** = Hapus

---

## PART 1: Place U1 (Microcontroller)

### Langkah 1.1: Add Symbol STM32
1. Press **A**
2. Ketik di search: `STM32F407VGT`
3. Jika muncul beberapa pilihan, pilih yang ada `VGT6` atau `LQFP100`
4. Klik di **tengah canvas**
5. Press **ESC**

**Hasil:** Ada kotak besar dengan banyak pin di canvas

### Langkah 1.2: Orient U1
1. Hover mouse di atas U1
2. Press **R** (Rotate) sampai pin-pin menghadap ke arah yang enak dilihat
   - Biasanya: Pin kiri = input, pin kanan = output
3. Press **M** (Move) kalau mau pindah posisi

### Langkah 1.3: Edit Reference & Value
1. Hover di atas symbol U1
2. Press **E** (Edit)
3. Dialog muncul:
   - **Reference**: Pastikan `U1` (sudah benar)
   - **Value**: Ganti jadi `STM32F407VGT6`
   - **Footprint**: LQFP-100_14x14mm_P0.5mm
4. Klik **OK**

---

## PART 2: Add Decoupling Capacitors (10 buah)

### Apa itu Decoupling Cap?
**Bayangkan:** Seperti "tangki air kecil" dekat setiap keran.
- MCU = rumah besar dengan banyak keran (pin VDD)
- Capacitor = tangki kecil per keran
- Fungsi: Sediakan air (listrik) cepat pas keran dibuka

### Yang Perlu Ditambah:
C3, C4, C9, C10, C11, C15, C18, C20, C24, C47 (10 buah)
- **Nilai semua**: 100nF
- **Package**: 0603

### Langkah 2.1: Add First Capacitor
1. Press **A**
2. Ketik: `C` (huruf C saja)
3. Pilih `C_Small` atau `C` (generic capacitor symbol)
4. Klik **dekat U1 pin VDD pertama**
5. Press **ESC**

**Hasil:** Muncul symbol capacitor (2 garis paralel)

### Langkah 2.2: Set Properties
1. Hover di capacitor yang baru
2. Press **E**
3. Edit:
   - **Reference**: `C3` (mulai dari C3 sesuai BOM)
   - **Value**: `100nF`
   - **Footprint**: `Capacitor_SMD:C_0603_1608Metric`
4. Klik **OK**

### Langkah 2.3: Copy untuk Capacitor Lainnya
**Cara cepat - Duplicate:**
1. Hover di C3
2. Press **Ctrl+D** (Duplicate)
3. Move ke posisi baru (dekat pin VDD lain)
4. Klik untuk place
5. Otomatis jadi C4
6. **Ulangi 8 kali lagi** untuk C9, C10, C11, C15, C18, C20, C24, C47

**Posisi capacitor:**
- **Tempatkan dekat pin VDD di U1**
- Tidak perlu tepat 100%, asal dekatan U1

**Tips:** Arrange dalam bentuk lingkaran mengelilingi U1

---

## PART 3: Add Power Symbols

### 3.1: Add +3V3 (Power Positive)
1. Press **P** (Power symbol)
2. Ketik: `+3V3` atau cari `+3.3V`
3. Place **di atas U1**
4. Press **ESC**

**Kalau tidak ada +3V3:**
- Gunakan `VCC` atau `+3.3V`
- Nanti bisa rename

### 3.2: Add GND (Ground)
1. Press **P**
2. Ketik: `GND`
3. Place **di bawah U1**
4. Press **ESC**

**Hasil:** Ada simbol +3V3 di atas, GND di bawah

---

## PART 4: Wire Power to U1

### Konsep Wiring:
Kabel (wire) = sambungan hijau di KiCad.
- Start point = klik pertama
- End point = klik kedua  
- Auto-bend = KiCad buat belokan otomatis

### 4.1: Connect +3V3 to VDD Pins

**Cari pin VDD di U1:**
- Zoom ke U1 (scroll wheel)
- Cari label pin yang bertuliskan "VDD", "VDD_1", dll
- STM32F407 punya 6 pin VDD: Pin 1, 11, 28, 50, 75, 100

**Wire +3V3 ke VDD:**
1. Press **W** (Wire mode)
2. Klik di **+3V3 symbol**
3. Drag ke **Pin VDD pertama** (Pin 1)
4. Klik di pin untuk finish wire
5. Press **ESC**

**Ulangi untuk 5 pin VDD lainnya:**
- Bisa wire dari +3V3 langsung ke tiap pin
- Atau: Wire antar pin VDD dulu (bentuk bus), baru wire 1x ke +3V3

### 4.2: Connect GND to VSS Pins

**Sama seperti VDD, tapi ke pin VSS (ground pins):**
- Wire dari GND symbol ke semua pin VSS di U1
- STM32F407 punya banyak VSS pin juga

**Tips:** 
- Jangan panik kalau belum sempurna
- Bisa edit wire kapan saja (Delete + re-wire)

### 4.3: Connect Capacitors

**Setiap capacitor:**
- **Top side** (positive) → Wire ke **VDD net** (kabel yang connect ke +3V3)
- **Bottom side** (negative) → Wire ke **GND net** (kabel yang connect ke GND)

**Cara:**
1. Press **W**
2. Klik pin atas capacitor
3. Drag ke wire VDD terdekat
4. Klik untuk finish
5. Repeat untuk pin bawah ke GND

**Check:** Semua 10 capacitor harus:
- Atas connected ke +3V3 (via net)
- Bawah connected ke GND (via net)

---

## PART 5: Add Crystal 8MHz (Y1)

### Komponen:
- Y1: 8MHz crystal
- C23, C26: 33pF load capacitors
- (Optional) R?: 100k feedback resistor

### 5.1: Place Y1
1. Press **A**
2. Ketik: `Crystal`
3. Pilih `Crystal_Small` (2-pin symbol)
4. Place **di sebelah kiri U1**
5. Edit properties:
   - Reference: `Y1`
   - Value: `8MHz`
   - Footprint: `Crystal:Crystal_SMD_5032-2Pin_5.0x3.2mm`

### 5.2: Place Load Capacitors
1. Press **A**, ketik `C`, place 2 capacitors
2. Edit C23:
   - Value: `33pF`
   - Footprint: `C_0603_1608Metric`
3. Edit C26:
   - Value: `33pF`
   - Footprint: `C_0603_1608Metric`

**Arrange:**
```
        Y1 (crystal)
       /  \
     C23  C26
      |    |
     GND  GND
```

### 5.3: Wire Crystal Circuit

**Connections:**
1. **Y1 Pin 1** → **U1 Pin 12** (OSC_IN / PH0)
   - Cari di U1 pin yang label "OSC_IN" atau "PH0"
2. **Y1 Pin 2** → **U1 Pin 13** (OSC_OUT / PH1)
   - Label "OSC_OUT" atau "PH1"
3. **C23 top** → Wire ke **OSC_IN** (same net as Y1 Pin 1)
4. **C23 bottom** → **GND**
5. **C26 top** → Wire ke **OSC_OUT** (same net as Y1 Pin 2)
6. **C26 bottom** → **GND**

---

## PART 6: Add 32kHz Crystal (Y2)

**Same process as 8MHz, tapi beda pin & nilai:**

### Place Components:
- Y2: Crystal_Small, value `32.768kHz`
- C27, C28: Value `20pF` each

### Wire:
- **Y2 Pin 1** → **U1 Pin 3** (OSC32_IN / PC14)
- **Y2 Pin 2** → **U1 Pin 4** (OSC32_OUT / PC15)
- C27, C28 same arrangement as C23, C26

---

## PART 7: Reset Circuit

### Components:
- SW1: Push button
- R3: 10k pull-up resistor
- C2: 10nF filter cap

### Place & Wire:
1. Place SW1 (symbol `SW_Push`)
2. Place R3 (value `10k`)
3. Place C2 (value `10nF`)

**Connections:**
```
+3V3 ---[R3]--- NRST (U1 Pin 14)
                 |
                [SW1]
                 |
                GND
                 
NRST ---[C2]--- GND
```

**Maksudnya:**
- Normal: R3 menarik NRST ke +3V3 (MCU running)
- Tekan SW1: NRST jadi GND (MCU reset)
- C2: Filter noise

---

## PART 8: USB Interface (Simplified)

**Full circuit akan di page 6, tapi minimal:**

### Place:
- J3: USB Type-C connector
- R81, R82: 22Ω resistors
- R79, R80: 5.1k resistors

### Wire:
- **USB D+** (J3 pin) ---[R81]--- **U1 Pin 77** (PA12 / USB_DP)
- **USB D-** (J3 pin) ---[R82]--- **U1 Pin 76** (PA11 / USB_DM)
- **R79 (5.1k)**: USB CC1 to GND
- **R80 (5.1k)**: USB CC2 to GND

---

## PART 9: Debug Connector (SWD)

### Place:
- J2: 1x04 pin header (2.54mm pitch)

### Wire:
- Pin 1: +3V3
- Pin 2: **SWDIO** → **U1 Pin 72** (PA13)
- Pin 3: **SWCLK** → **U1 Pin 76** (PA14)
- Pin 4: GND

**Optional:** Add pull-up resistors (10k) on SWDIO/SWCLK

---

## PART 10: Verification

### Checklist:
- [ ] U1 placed with correct footprint
- [ ] 10x 100nF caps around U1
- [ ] All VDD pins connected to +3V3
- [ ] All VSS pins connected to GND
- [ ] All caps wired (top to VDD, bottom to GND)
- [ ] Y1 (8MHz) + 2x 33pF caps wired to OSC_IN/OUT
- [ ] Y2 (32kHz) + 2x 20pF caps wired to OSC32_IN/OUT
- [ ] Reset circuit (SW1 + R3 + C2) complete
- [ ] USB connector with resistors
- [ ] Debug header J2 wired

### Run ERC (Electrical Rules Check):
1. Klik **Inspect > Electrical Rules Checker**
2. Klik **Run ERC**
3. **Fix all ERRORS** - harus 0 errors
4. Review warnings

**Common errors Page 1:**
- "Pin not connected" → Add wire atau No-Connect flag
- "Power pin not driven" → Check +3V3/GND symbols
- "Duplicate reference" → Rename components

---

## Selesai Page 1! 🎉

**Save your work:**
- **Ctrl+S** atau **File > Save**

**Next:** Lanjut ke Page 2 (IO Interfaces) atau review dulu?

---

## Troubleshooting

### "Symbol tidak ketemu"
→ Install library dulu (File > Preferences > Manage Symbol Libraries)

### "Wire tidak nyambung"
→ Pastikan klik **tepat di pin** (ada dot kecil muncul)

### "Capac itor terbalik?"
→ Ceramic cap (100nF, 33pF, dll) **tidak ada polaritas** - bebas arah

### "ERC error banyak"
→ Screenshot error dan tanya saya

---

**Questions? Tanya sekarang sebelum lanjut ke page berikutnya!**
