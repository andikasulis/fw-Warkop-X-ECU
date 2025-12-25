#!/bin/bash
# Manual fix for idle rumble .ini file
# Moves dialog definition to correct location inside [UserDefined] section

INI_FILE="$1"

if [ -z "$INI_FILE" ]; then
    echo "Usage: $0 <path_to_ini_file>"
    exit 1
fi

if [ ! -f "$INI_FILE" ]; then
    echo "Error: File not found: $INI_FILE"
    exit 1
fi

# Backup
cp "$INI_FILE" "${INI_FILE}.backup"
echo "Created backup: ${INI_FILE}.backup"

# Remove old dialog definition (outside UserDefined)
awk '
/^   dialog = idleRumbleDialog/,/^$/ {
    if (/^   dialog = idleRumbleDialog/ || /^      / || /^   panel = idleRumblePanel/) {
        next
    }
}
{ print }
' "$INI_FILE" > "${INI_FILE}.tmp1"

# Add dialog inside [UserDefined] section
awk '
BEGIN { added=0 }
/^\[UserDefined\]/ {
    print
    print ""
    print "   dialog = idleRumbleDialog, \"Idle Rumble Settings\""
    print "      panel = idleRumblePanel"
    print ""
    print "   panel = idleRumblePanel"
    print "      field = \"Enable Idle Rumble\", idleRumbleEnabled"
    print "      field = \"\""
    print "      field = \"Rumble Amplitude (%)\", idleRumbleAmplitude"
    print "      field = \"Rumble Speed/Period\", idleRumblePeriod"
    print "      field = \"Method (0=Timing,1=Fuel,2=Spark,3=Combined)\", idleRumbleMethod"
    print "      field = \"Max Timing Offset (deg)\", idleRumbleTiming"
    print "      field = \"Max Fuel Adjustment (%)\", idleRumbleFuel"
    print "      field = \"Max Active RPM\", idleRumbleMaxRpm"
    print "      field = \"Max Active TPS (%)\", idleRumbleMaxTps"
    print ""
    added=1
    next
}
{ print }
' "${INI_FILE}.tmp1" > "$INI_FILE"

rm "${INI_FILE}.tmp1"

echo "✅ Fixed: $INI_FILE"
echo "📝 Reload project in TunerStudio"
