#!/usr/bin/env python3
"""
Quick fix for Idle Rumble .ini file
Removes problematic conditionals and ensures fields display correctly
"""

import sys
import re

def fix_ini_file(ini_path):
    """Remove conditional syntax from idle rumble fields"""
    
    with open(ini_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    # Backup
    with open(ini_path + '.backup', 'w', encoding='utf-8') as f:
        f.write(content)
    
    # Remove conditionals from idleRumble fields
    # Pattern: field = "...", variable, {conditional}
    content = re.sub(
        r'(field\s*=\s*"[^"]*",\s*idleRumble\w+),\s*\{[^}]+\}',
        r'\1',
        content
    )
    
    # Write fixed content
    with open(ini_path, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print(f"✅ Fixed: {ini_path}")
    print(f"📦 Backup: {ini_path}.backup")
    print("\n🔧 Removed conditional syntax from idle rumble fields")
    print("📝 Reload project in TunerStudio to see changes")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 fix_ini_idle_rumble.py <path_to_ini_file>")
        sys.exit(1)
    
    ini_file = sys.argv[1]
    fix_ini_file(ini_file)
