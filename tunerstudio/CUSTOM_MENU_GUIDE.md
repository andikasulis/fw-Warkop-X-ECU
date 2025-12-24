# Idle Rumble Custom Menu - Implementation Guide

Step-by-step guide untuk add custom "⚡ Idle Rumble" menu di TunerStudio.

---

## 📋 Prerequisites

- ✅ Download `rusefi_warkop_x.ini` dari GitHub Actions artifacts
- ✅ Text editor (Notepad++, VSCode, Sublime, atau Notepad biasa)
- ✅ TunerStudio installed

---

## 🚀 Quick Start (2 Methods)

### Method 1: Auto-Patch Script (EASIEST!) ⭐

```bash
# Make script executable (first time only)
chmod +x tunerstudio/patch_ini.sh

# Patch .ini file
./tunerstudio/patch_ini.sh ~/Downloads/rusefi_warkop_x.ini
```

Done! Skip to step "Load in TunerStudio" below.

---

### Method 2: Manual Edit

Follow step-by-step manual instructions below.

---

## 📝 Manual Implementation Steps

### Step 1: Download .ini File

1. Go to: https://github.com/andikasulis/fw-Warkop-X-ECU/actions
2. Click latest successful workflow run (green checkmark)
3. Scroll to "Artifacts"
4. Download: `tunerstudio-warkop-x.zip`
5. Extract → get `rusefi_warkop_x.ini`

---

### Step 2: Open .ini File

Open `rusefi_warkop_x.ini` dengan text editor:
- Windows: Notepad++ (recommended) or Notepad
- Mac: VSCode, Sublime, or TextEdit
- Linux: gedit, nano, vim

---

### Step 3: Find [Dialogs] Section

Press **Ctrl+F** (Cmd+F on Mac), search for:
```
[Dialogs]
```

You'll find a section that looks like:
```ini
[Dialogs]
   dialog = knockDialog, "Knock Settings"
      panel = knockPanel
   
   panel = knockPanel
      ; ... existing dialogs ...
```

---

### Step 4: Add Dialog Definition

Scroll to **END of [Dialogs] section** (before next `[SectionName]` starts).

Copy paste this complete code:

```ini
   ; Idle Rumble Custom Dialog - Warkop-X ECU
   dialog = idleRumbleDialog, "⚡ Idle Rumble - Drumbal Effect"
      panel = idleRumblePanel
      
   panel = idleRumblePanel
      field = "#Idle Rumble creates aggressive idle sound"
      field = "#Works with cable throttle (no idle valve)"
      field = ""
      field = "Enable Idle Rumble", idleRumbleEnabled
      field = ""
      field = "─────────── Basic Settings ───────────"
      field = "Rumble Amplitude (%)", idleRumbleAmplitude, {idleRumbleEnabled == 1}
      field = "Rumble Speed/Period", idleRumblePeriod, {idleRumbleEnabled == 1}
      field = ""
      field = "─────────── Rumble Method ───────────"
      field = "Method", idleRumbleMethod, {idleRumbleEnabled == 1}
      field = "  0=Timing 1=Fuel 2=Spark 3=Combined"
      field = ""
      field = "─────────── Advanced ───────────"
      field = "Max Timing Offset (deg)", idleRumbleTiming, {idleRumbleEnabled == 1 && (idleRumbleMethod == 0 || idleRumbleMethod == 3)}
      field = "Max Fuel Adjustment (%)", idleRumbleFuel, {idleRumbleEnabled == 1 && (idleRumbleMethod == 1 || idleRumbleMethod == 3)}
      field = ""
      field = "─────────── Activation Limits ───────────"
      field = "Max Active RPM", idleRumbleMaxRpm, {idleRumbleEnabled == 1}
      field = "Max Active TPS (%)", idleRumbleMaxTps, {idleRumbleEnabled == 1}
```

**Location example:**
```ini
[Dialogs]
   ; ... existing dialogs ...
   
   ; ← ADD HERE, at end of [Dialogs] section
   
[Menu]  ← Next section starts here
```

---

### Step 5: Find [Menu] Section

Search for:
```
[Menu]
```

Find the line:
```ini
menuDialog = main
```

---

### Step 6: Add Menu Item

Inside `menuDialog = main` block, add this line:

```ini
      subMenu = idleRumbleDialog, "⚡ Idle Rumble"
```

**Location example:**
```ini
[Menu]
   menuDialog = main
      subMenu = std_separator
      
      ; Existing menu items...
      subMenu = someDialog, "Some Setting"
      subMenu = anotherDialog, "Another Setting"
      
      ; ← ADD HERE
      subMenu = idleRumbleDialog, "⚡ Idle Rumble"
```

---

### Step 7: Save File

Save the modified `.ini` file:
- **Ctrl+S** (Cmd+S on Mac)
- Or File → Save

---

### Step 8: Load in TunerStudio

1. Open TunerStudio
2. **File → Project → Open Project** (or **Ctrl+O**)
3. Browse to your modified `rusefi_warkop_x.ini`
4. Click **Open**
5. Wait for project to load

---

### Step 9: Verify Menu Exists

Look at menu bar. You should see:

```
File  Edit  Tools  ... ⚡ Idle Rumble  Help
                        ↑
                     NEW MENU!
```

---

### Step 10: Test Dialog

Click **⚡ Idle Rumble** menu.

Dialog should open with:
- ✅ Enable checkbox
- ✅ Amplitude slider
- ✅ Period setting
- ✅ Method dropdown
- ✅ Advanced settings (conditionally visible)
- ✅ Limits settings
- ✅ Info text

---

## 🎨 Dialog Features

### Conditional Visibility

Settings auto-hide/show based on:

**When Disabled:**
```
☐ Enable Idle Rumble
```
All other fields hidden/greyed out.

**When Enabled:**
```
☑ Enable Idle Rumble
─────────── Basic Settings ───────────
Rumble Amplitude (%): [50  ]
Rumble Speed/Period:  [5   ]
...
```

**Method-Specific Fields:**

**Method = 0 (Timing) or 3 (Combined):**
Shows: `Max Timing Offset`

**Method = 1 (Fuel) or 3 (Combined):**
Shows: `Max Fuel Adjustment`

**Method = 2 (Spark Cut):**
Hides both timing and fuel fields.

---

## 📦 Files Created

```
tunerstudio/
├── idle_rumble_menu_patch.ini  ← Complete .ini code snippet
├── patch_ini.sh                ← Auto-patch script
└── CUSTOM_MENU_GUIDE.md        ← This guide
```

---

## 🔄 Update Workflow

Setiap download .ini baru dari GitHub Actions:

**Option A: Auto-Patch**
```bash
./tunerstudio/patch_ini.sh ~/Downloads/rusefi_warkop_x.ini
```

**Option B: Manual**
1. Copy patch code from `idle_rumble_menu_patch.ini`
2. Paste to new .ini file
3. Save → Load in TunerStudio

Takes ~2 minutes manual, ~5 seconds with script.

---

## 🐛 Troubleshooting

### "Menu tidak muncul"

**Причин:**
- .ini not loaded correctly
- Syntax error in patch

**Fix:**
1. Restart TunerStudio
2. Verify .ini file loaded: Help → About
3. Check for typos in patch code

---

### "Settings greyed out"

**Normal!** Settings are conditional.

**Fix:**
- Set `Enable Idle Rumble = 1`
- Settings will become active

---

### "Search gak ketemu idleRumbleEnabled"

**Причин:**
- Wrong .ini loaded
- .ini doesn't have idle rumble parameters

**Fix:**
1. Verify .ini from latest build (commit 2c48c8a1+)
2. Check [Constants] section for `idleRumbleEnabled`
3. Re-download from GitHub Actions

---

### "Syntax error when loading .ini"

**Причин:**
- Patch code incomplete
- Missing brackets/quotes

**Fix:**
1. Restore from backup: `rusefi_warkop_x.ini.backup.*`
2. Use auto-patch script (less error-prone)
3. Verify complete code copied

---

## 💡 Tips

### Save Patched .ini

Keep patched .ini separate:
```
~/TunerStudio/
├── rusefi_warkop_x.ini              ← Original
└── rusefi_warkop_x_rumble.ini       ← Patched with menu
```

### Auto-Patch on Download

Add to your workflow:
```bash
# After download
cd ~/Downloads
unzip tunerstudio-warkop-x.zip
./patch_ini.sh rusefi_warkop_x.ini
```

---

## 📸 Expected Result

After implementation, menu should look like:

```
┌─────────────────────────────────────────────┐
│ ⚡ Idle Rumble - Drumbal Effect             │
├─────────────────────────────────────────────┤
│ Idle Rumble creates aggressive idle sound  │
│ Works with cable throttle (no idle valve)   │
│                                             │
│ Enable Idle Rumble: [✓]                     │
│                                             │
│ ─────────── Basic Settings ─────────────    │
│ Rumble Amplitude (%): [50  ]  ←→            │
│ Rumble Speed/Period:  [5   ]                │
│                                             │
│ ─────────── Rumble Method ─────────────     │
│ Method: [3 - Combined       ▼]              │
│   0=Timing 1=Fuel 2=Spark 3=Combined        │
│                                             │
│ ─────────── Advanced ─────────────          │
│ Max Timing Offset (deg): [4   ]             │
│ Max Fuel Adjustment (%): [10  ]             │
│                                             │
│ ─────────── Activation Limits ─────────     │
│ Max Active RPM:  [1500]                     │
│ Max Active TPS (%): [5   ]                  │
│                                             │
│        [Apply]  [Burn]  [Cancel]            │
└─────────────────────────────────────────────┘
```

---

## ✅ Success Checklist

- [ ] Downloaded latest .ini from GitHub Actions
- [ ] Opened .ini in text editor
- [ ] Added dialog code to [Dialogs] section
- [ ] Added menu item to [Menu] section
- [ ] Saved .ini file
- [ ] Loaded in TunerStudio
- [ ] Verified "⚡ Idle Rumble" menu appears
- [ ] Clicked menu - dialog opens
- [ ] All fields present and functional
- [ ] Conditional visibility works

---

Last Updated: 2024-12-24  
Tested with: TunerStudio MS 3.1.x, rusEFI firmware dev-feat-rumble
