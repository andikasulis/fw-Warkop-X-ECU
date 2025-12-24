#!/bin/bash
# ════════════════════════════════════════════════════════════════════════════
# Auto-Patch Script for Idle Rumble Custom Menu
# ════════════════════════════════════════════════════════════════════════════
# 
# Usage:
#   ./patch_ini.sh path/to/rusefi_warkop_x.ini
#
# Description:
#   Automatically adds idle rumble custom dialog to TunerStudio .ini file
#
# ════════════════════════════════════════════════════════════════════════════

set -e  # Exit on error

# Check argument
if [ -z "$1" ]; then
    echo "❌ Error: No .ini file specified"
    echo ""
    echo "Usage: $0 <path-to-ini-file>"
    echo "Example: $0 ~/Downloads/rusefi_warkop_x.ini"
    exit 1
fi

INI_FILE="$1"

# Check if file exists
if [ ! -f "$INI_FILE" ]; then
    echo "❌ Error: File not found: $INI_FILE"
    exit 1
fi

# Check if already patched
if grep -q "idleRumbleDialog" "$INI_FILE"; then
    echo "✅ File already patched with idle rumble dialog!"
    echo ""
    echo "To re-patch, download fresh .ini from GitHub Actions"
    exit 0
fi

echo "🔧 Patching $INI_FILE with idle rumble custom menu..."
echo ""

# Create backup
BACKUP_FILE="${INI_FILE}.backup.$(date +%Y%m%d_%H%M%S)"
cp "$INI_FILE" "$BACKUP_FILE"
echo "📦 Backup created: $BACKUP_FILE"

# Create temp file with patch
PATCH_FILE=$(mktemp)

cat > "$PATCH_FILE" << 'EOF_PATCH'

   ; ═══════════════════════════════════════════════════════════
   ; Idle Rumble Custom Dialog - Auto-patched by script
   ; ═══════════════════════════════════════════════════════════
   dialog = idleRumbleDialog, "⚡ Idle Rumble - Drumbal Effect"
      panel = idleRumblePanel
      
   panel = idleRumblePanel
      field = "#Idle Rumble creates aggressive idle sound via timing/fuel variation"
      field = "#Works with cable throttle (no idle valve needed)"
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
      field = "─────────── Limits ───────────"
      field = "Max Active RPM", idleRumbleMaxRpm, {idleRumbleEnabled == 1}
      field = "Max Active TPS (%)", idleRumbleMaxTps, {idleRumbleEnabled == 1}

EOF_PATCH

# Find [Dialogs] section and add dialog before next section
awk -v patch="$(cat $PATCH_FILE)" '
/^\[Dialogs\]/ { dialogs_section=1; print; next }
dialogs_section && /^\[/ { print patch; dialogs_section=0 }
{ print }
' "$INI_FILE" > "${INI_FILE}.tmp"

mv "${INI_FILE}.tmp" "$INI_FILE"

# Add menu item to [Menu] section
MENU_PATCH='      subMenu = idleRumbleDialog, "⚡ Idle Rumble"'

awk -v menu_patch="$MENU_PATCH" '
/menuDialog = main/ { in_menu=1; print; next }
in_menu && /^   / && !menu_added { print menu_patch; menu_added=1 }
{ print }
' "$INI_FILE" > "${INI_FILE}.tmp"

mv "${INI_FILE}.tmp" "$INI_FILE"

# Cleanup
rm "$PATCH_FILE"

echo ""
echo "✅ Patch applied successfully!"
echo ""
echo "Next steps:"
echo "1. Open TunerStudio"
echo "2. File → Project → Open Project"
echo "3. Select: $INI_FILE"
echo "4. Look for '⚡ Idle Rumble' menu!"
echo ""
echo "Backup saved at: $BACKUP_FILE"
