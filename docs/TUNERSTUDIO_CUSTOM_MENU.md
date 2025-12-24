# TunerStudio Custom Menu Implementation - Research & Guide

Research results dan implementation guide untuk bikin custom menu di TunerStudio untuk idle rumble settings.

---

## TL;DR: BISA! ✅

**Ya, bisa bikin custom menu sendiri di TunerStudio**, tapi ada 2 cara:

1. **Via `rusefi.input` file** (rusEFI approach) - Auto-generate saat build
2. **Manual edit `.ini` file** (direct approach) - Edit file yang sudah di-generate

---

## Research Findings

### Key Information:

1. **TunerStudio UI didefinisikan di `.ini` file** (ECU Definition file)
2. **rusEFI auto-generate `.ini`** dari beberapa source files
3. **Custom dialogs & menus** fully supported via standard .ini syntax
4. **Ada 2 approaches**: rusEFI approach (recommended) vs manual editing

---

## Approach 1: rusEFI Method (Recommended)

### Files Involved:

```
ext/rusefi/firmware/tunerstudio/
├── rusefi.input        ← UI Definition (menus, dialogs)
├── tunerstudio.template.ini  ← Template
└── prepend.txt         ← Hide UI elements
```

### How It Works:

1. **Edit `rusefi.input`** - Define custom dialog & menu
2. **Build firmware** - `ConfigDefinition.jar` generates `.ini`
3. **Load `.ini`** - TunerStudio displays custom UI

### Problem untuk Kita:

❌ `rusefi.input` ada di **upstream rusEFI** repo (submodule)  
❌ Kalo edit, akan **conflict** saat update submodule  
❌ Fork maintenance **complex**

---

## Approach 2: Manual .ini Edit (Simpler for Our Case!)

### Concept:

Setelah firmware build sukses di GitHub Actions:

1. **Download** `.ini` file dari artifacts
2. **Edit manual** untuk add custom dialog
3. **Load** edited `.ini` di TunerStudio
4. **Done!**

### Advantages:

✅ Gak perlu touch submodule  
✅ Gak perlu rebuild firmware  
✅ Easy to maintain & update  
✅ Fully customizable

### Disadvantages:

⚠️ Perlu re-edit setiap kali download .ini baru  
⚠️ Manual process (tapi simple!)

---

## Implementation: Custom Idle Rumble Dialog

### `.ini` File Structure:

TunerStudio `.ini` file punya sections:

```ini
[Dialogs]      ← Define dialog panels
[Menu]         ← Define menu structure  
[Constants]    ← Parameter definitions (auto-generated)
[OutputChannels] ← Real-time data
[ControllerCommands] ← Custom commands
```

---

### Step-by-Step Implementation:

#### Step 1: Download `.ini` dari GitHub Actions

Get latest `rusefi_warkop_x.ini` from build artifacts.

---

#### Step 2: Add Custom Dialog

Open `.ini` dengan text editor, find section `[Dialogs]`.

Add di akhir section:

```ini
[Dialogs]
   ; ... existing dialogs ...
   
   ; ═════════════════════════════════════════════════
   ; Custom Idle Rumble Dialog - Warkop-X ECU
   ; ═════════════════════════════════════════════════
   dialog = idleRumbleDialog, "⚡ Idle Rumble (Drumbal Effect)"
      panel = idleRumblePanel
      
   panel = idleRumblePanel
      field = "Enable Idle Rumble", idleRumbleEnabled
      field = ""
      field = "═════ Basic Settings ═════"
      field = "Rumble Amplitude (%)", idleRumbleAmplitude, {idleRumbleEnabled == 1}
      field = "Rumble Speed (Period)", idleRumblePeriod, {idleRumbleEnabled == 1}
      field = ""
      field = "═════ Method ═════"
      field = "Rumble Method", idleRumbleMethod, {idleRumbleEnabled == 1}
      field = "  0 = Timing Only"
      field = "  1 = Fuel Only"
      field = "  2 = Spark Cut"
      field = "  3 = Combined (Timing + Fuel)"
      field = ""
      field = "═════ Advanced ═════"
      field = "Max Timing Offset (deg)", idleRumbleTiming, {idleRumbleEnabled == 1 && (idleRumbleMethod == 0 || idleRumbleMethod == 3)}
      field = "Max Fuel Adjustment (%)", idleRumbleFuel, {idleRumbleEnabled == 1 && (idleRumbleMethod == 1 || idleRumbleMethod == 3)}
      field = ""
      field = "═════ Activation Limits ═════"
      field = "Max Active RPM", idleRumbleMaxRpm, {idleRumbleEnabled == 1}
      field = "Max Active TPS (%)", idleRumbleMaxTps, {idleRumbleEnabled == 1}
      field = ""
      field = "═════ Info ═════"
      field = "Creates aggressive idle sound effect"
      field = "Works with cable throttle (no idle valve needed)"
      field = "Recommended: Method 3, Amplitude 50%, Period 5"
```

---

#### Step 3: Add to Menu

Find section `[Menu]`, add submenu:

```ini
[Menu]
   menuDialog = main
      ; ... existing menu items ...
      
      ; Custom Idle Rumble Menu
      subMenu = idleRumbleDialog, "⚡ Idle Rumble"
```

---

#### Step 4: Save & Load

1. Save edited `.ini` file
2. Load di TunerStudio: **File → Project → Open Project**
3. Browse to edited `.ini`
4. Open!

---

#### Step 5: Verify

Di TunerStudio, check menu bar:

```
⚡ Idle Rumble  ← NEW MENU!
```

Click → Dialog with all settings muncul ✅

---

## Advanced: Conditional Field Visibility

### Syntax:

```ini
field = "Label", parameter, {condition}
```

### Examples:

**Show only when enabled:**
```ini
field = "Amplitude", idleRumbleAmplitude, {idleRumbleEnabled == 1}
```

**Show only for specific method:**
```ini
field = "Timing Offset", idleRumbleTiming, {idleRumbleMethod == 0 || idleRumbleMethod == 3}
```

**Complex condition:**
```ini
field = "Fuel Adjust", idleRumbleFuel, {idleRumbleEnabled == 1 && (idleRumbleMethod == 1 || idleRumbleMethod == 3)}
```

---

## Field Types & Formatting

### Text Field (Editable):

```ini
field = "Label", parameterName
```

### Label (Info Only):

```ini
field = "This is just text label"
```

### Separator:

```ini
field = ""
field = "═════ Section Name ═════"
```

### Dropdown (for bit fields):

Auto-generated from parameter definition in `[Constants]`.

---

## Complete Example `.ini` Addition

Here's complete code to add to `.ini`:

```ini
; ═════════════════════════════════════════════════
; Add this to [Dialogs] section
; ═════════════════════════════════════════════════
[Dialogs]
   ; ... (keep existing dialogs) ...
   
   dialog = idleRumbleDialog, "⚡ Idle Rumble"
      panel = idleRumbleMain
      
   panel = idleRumbleMain
      field = "#Enable idle rumble to create aggressive sound"
      field = ""
      field = "Enable Idle Rumble", idleRumbleEnabled
      field = ""
      field = "Rumble Amplitude (%)", idleRumbleAmplitude, {idleRumbleEnabled}
      field = "Rumble Speed", idleRumblePeriod, {idleRumbleEnabled}
      field = "Rumble Method", idleRumbleMethod, {idleRumbleEnabled}
      field = ""
      field = "Max Timing Offset", idleRumbleTiming, {idleRumbleEnabled && (idleRumbleMethod == 0 || idleRumbleMethod == 3)}
      field = "Max Fuel Adjust", idleRumbleFuel, {idleRumbleEnabled && (idleRumbleMethod == 1 || idleRumbleMethod == 3)}
      field = ""
      field = "Max Active RPM", idleRumbleMaxRpm, {idleRumbleEnabled}
      field = "Max Active TPS", idleRumbleMaxTps, {idleRumbleEnabled}

; ═════════════════════════════════════════════════
; Add this to [Menu] section
; ═════════════════════════════════════════════════
[Menu]
   menuDialog = main
      ; ... (keep existing menu items) ...
      subMenu = idleRumbleDialog, "⚡ Idle Rumble"
```

---

## Automation: Script untuk Auto-Patch `.ini`

Bisa bikin script untuk auto-add custom dialog setiap kali download .ini baru:

```bash
#!/bin/bash
# patch_ini.sh - Auto-add idle rumble dialog to .ini

INI_FILE="$1"

if [ ! -f "$INI_FILE" ]; then
    echo "Usage: ./patch_ini.sh <path-to-ini-file>"
    exit 1
fi

# Check if already patched
if grep -q "idleRumbleDialog" "$INI_FILE"; then
    echo "Already patched!"
    exit 0
fi

# Add dialog definition before last line of [Dialogs] section
# Add menu item to [Menu] section
# (implementation details...)

echo "Patched successfully!"
```

---

## Alternative: Post-Build Script di GitHub Actions

Bisa modify GitHub Actions workflow untuk auto-patch `.ini` setelah build:

```yaml
- name: Patch INI with custom dialogs
  run: |
    # Add custom idle rumble dialog to generated .ini
    python scripts/patch_ini.py generated/tunerstudio/rusefi_warkop_x.ini
```

---

## Kesimpulan

### ✅ BISA Custom Menu!

**3 Options:**

**Option 1: Manual Edit** (SIMPLEST!)  
- Download .ini dari GitHub Actions
- Edit manual add [Dialogs] & [Menu]
- Load edited .ini di TunerStudio
- ✅ Easy, ❌ Re-edit tiap update

**Option 2: Auto-Patch Script**  
- Download .ini
- Run script untuk auto-patch
- Load hasil patch
- ✅ Automated, ⚠️ Perlu maintain script

**Option 3: Fork rusEFI** (COMPLEX!)  
- Fork rusEFI, edit `rusefi.input`
- Point submodule ke fork
- Build generate .ini dengan custom dialog  
- ✅ Permanent, ❌ Maintain fork

---

## Recommendation untuk Warkop-X:

**PAKAI OPTION 1** (Manual Edit):

**Pros:**
- ✅ Simple & quick
- ✅ Gak touch codebase
- ✅ Easy iterate & customize
- ✅ No rebuild needed

**Steps:**
1. Download `rusefi_warkop_x.ini` from GitHub Actions
2. Add custom dialog code (copy dari example di atas)
3. Load edited .ini
4. Enjoy custom menu! 🎉

**Maintenance:**  
Setiap download .ini baru, re-apply edit (5 menit aja).

---

## Mau Saya Buatin?

Saya bisa:

1. ✅ Bikin complete `.ini` patch code
2. ✅ Bikin auto-patch script (bash/python)
3. ✅ Test verify works
4. ✅ Document step-by-step

Tinggal bilang! 🚀

---

Last Updated: 2024-12-24  
Reference: TunerStudio ECU Definition Specification
