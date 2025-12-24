# Git Branching Strategy - Idle Rumble Feature

## Current Status

### Main Repo (Warkop-X-ECU)
```
Repo: https://github.com/andikasulis/fw-Warkop-X-ECU.git

Branches:
- main                    (stable)
- dev-VET6               
- dev-canbus-enable      
- dev-feat-rumble        ⭐ (current - idle rumble)
```

### Submodule (rusEFI)
```
Repo: https://github.com/andikasulis/rusefi-x-warkop (YOUR FORK!)
Current: master branch

Official upstream: https://github.com/rusefi/rusefi
```

**Good news:** Lu **UDAH FORK** rusEFI! (`rusefi-x-warkop`)

---

## Strategy: Feature Branch with Custom Submodule

Ide: **Setiap feature branch punya submodule commit sendiri**

```
fw-Warkop-X-ECU (main repo)
├── main branch
│   └── ext/rusefi → official rusEFI master
│
├── dev-canbus-enable
│   └── ext/rusefi → official rusEFI master
│
└── dev-feat-rumble  ⭐
    └── ext/rusefi → rusefi-x-warkop/feat-idle-rumble
                     (custom fork dengan idle rumble code!)
```

**Benefit:**
- ✅ Master tetap clean (official rusEFI)
- ✅ Experimental features di branch terpisah
- ✅ Easy switch antar branch
- ✅ Gak conflict saat merge

---

## Implementation Steps

### Step 1: Create Feature Branch di Fork rusEFI

Buat branch baru di `rusefi-x-warkop` untuk idle rumble:

```bash
cd ext/rusefi/

# Check current status
git status
git branch

# Create new branch for idle rumble
git checkout -b feat-idle-rumble

# Edit rusefi_config.txt
# Add idle rumble parameters
nano firmware/integration/rusefi_config.txt

# Commit changes
git add firmware/integration/rusefi_config.txt
git commit -m "feat: add idle rumble config parameters"

# Push to your fork
git push origin feat-idle-rumble
```

---

### Step 2: Point Submodule ke Fork Branch

Di main repo (Warkop-X), update submodule reference:

```bash
cd /path/to/fw-Warkop-X-ECU

# Make sure you're on dev-feat-rumble branch
git checkout dev-feat-rumble

# Update .gitmodules to point to your fork (if not already)
cat .gitmodules

# Should show:
# [submodule "ext/rusefi"]
#     path = ext/rusefi
#     url = https://github.com/andikasulis/rusefi-x-warkop
#     branch = master

# Update submodule to use feat-idle-rumble branch
cd ext/rusefi
git fetch origin
git checkout feat-idle-rumble
cd ../..

# Commit submodule change
git add ext/rusefi
git commit -m "chore: switch submodule to feat-idle-rumble branch"
git push origin dev-feat-rumble
```

---

### Step 3: Edit rusefi_config.txt di Fork

Now you can edit submodule without conflicts:

```bash
cd ext/rusefi/
git checkout feat-idle-rumble

# Edit config
nano firmware/integration/rusefi_config.txt
```

Add:
```c
struct_no_prefix engine_configuration_s
    // ... existing ...
    
    // Idle Rumble Feature - Added by Warkop-X
    bit idleRumbleEnabled;Enable idle rumble effect
    uint8_t idleRumbleAmplitude;Rumble amplitude, 0, 100, 0;"%"
    uint8_t idleRumblePeriod;Rumble period, 1, 20, 0;"x100ms"
    uint8_t idleRumbleMethod;Method, 0, 3, 0
    int8_t autoscale idleRumbleTiming;Max timing, -10, 10, 0;"deg"
    int8_t autoscale idleRumbleFuel;Max fuel, -20, 20, 0;"%"
    uint16_t idleRumbleMaxRpm;Max RPM, 0, 2000, 0;"rpm"
    uint8_t idleRumbleMaxTps;Max TPS, 0, 20, 0;"%"
    
end_struct
```

Commit:
```bash
git add firmware/integration/rusefi_config.txt
git commit -m "feat: add idle rumble configuration parameters"
git push origin feat-idle-rumble
```

---

### Step 4: Switch Between Branches

**Use master (production):**
```bash
git checkout main
git submodule update --init --recursive
# Now ext/rusefi points to official rusEFI master
```

**Use experimental (idle rumble):**
```bash
git checkout dev-feat-rumble
git submodule update --init --recursive
# Now ext/rusefi points to rusefi-x-warkop/feat-idle-rumble
```

---

## Workflow Example

### Develop Idle Rumble Feature

```bash
# 1. Switch to feature branch
git checkout dev-feat-rumble
git submodule update --init --recursive

# 2. Make changes to rusEFI submodule
cd ext/rusefi
# ... edit files ...
git add .
git commit -m "feat: implement idle rumble logic"
git push origin feat-idle-rumble

# 3. Make changes to main repo
cd ../..
# ... edit board_configuration.cpp, default_tune.cpp ...
git add .
git commit -m "feat: integrate idle rumble to Warkop-X"

# 4. Update submodule reference
git add ext/rusefi
git commit -m "chore: update submodule to latest feat-idle-rumble"

# 5. Push everything
git push origin dev-feat-rumble
```

---

### Merge to Master (When Stable)

```bash
# 1. Test on dev-feat-rumble thoroughly
# 2. When ready for production:

git checkout main

# Option A: Merge feature branch
git merge dev-feat-rumble

# Option B: Cherry-pick specific commits
git cherry-pick <commit-hash>

# 3. Update submodule if needed
# (or keep official rusEFI on master)
```

---

## .gitmodules Configuration

Check current config:
```bash
cat .gitmodules
```

Should show:
```ini
[submodule "ext/rusefi"]
    path = ext/rusefi
    url = https://github.com/andikasulis/rusefi-x-warkop
    branch = master  # Default branch
```

**You can specify branch per repo branch!**

For dev-feat-rumble:
```bash
git checkout dev-feat-rumble

# Update .gitmodules
cat > .gitmodules << 'EOF'
[submodule "ext/rusefi"]
    path = ext/rusefi
    url = https://github.com/andikasulis/rusefi-x-warkop
    branch = feat-idle-rumble
EOF

git add .gitmodules
git commit -m "chore: use feat-idle-rumble branch for submodule"
```

For main:
```bash
git checkout main

# Keep official rusEFI or master branch
cat > .gitmodules << 'EOF'
[submodule "ext/rusefi"]
    path = ext/rusefi
    url = https://github.com/rusefi/rusefi
    branch = master
EOF

git add .gitmodules
git commit -m "chore: use official rusEFI master"
```

---

## Automated Script

Create helper script `switch-rusEfi-branch.sh`:

```bash
#!/bin/bash
# Switch rusEFI submodule branch

BRANCH=$1

if [ -z "$BRANCH" ]; then
    echo "Usage: ./switch-rusEfi-branch.sh <branch>"
    echo "Example: ./switch-rusEfi-branch.sh feat-idle-rumble"
    exit 1
fi

echo "Switching rusEFI submodule to branch: $BRANCH"

cd ext/rusefi
git fetch origin
git checkout $BRANCH
git pull origin $BRANCH
cd ../..

git add ext/rusefi
echo "Submodule switched to $BRANCH"
echo "Run: git commit -m 'chore: update submodule to $BRANCH'"
```

Usage:
```bash
chmod +x switch-rusEfi-branch.sh
./switch-rusEfi-branch.sh feat-idle-rumble
```

---

## GitHub Actions Considerations

Update `.github/workflows/build-firmware.yaml`:

```yaml
# Different builds for different branches
name: Build Firmware

on:
  push:
    branches:
      - main
      - dev-feat-rumble

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v3
        with:
          submodules: recursive  # Important!
      
      # Submodule will automatically use branch specified in that branch's .gitmodules
      
      - name: Build
        run: |
          cd ext/rusefi/firmware
          make -j8
```

---

## Best Practices

### 1. Branch Naming Convention

```
Main repo:
- main                     (production)
- dev-<feature>           (development)
- feat-<feature>          (new feature)
- fix-<bug>               (bug fix)

Fork rusEFI:
- master                   (clean fork of upstream)
- feat-<feature>          (experimental features)
- warkop-<feature>        (Warkop-specific changes)
```

### 2. Commit Messages

```bash
# Submodule changes
git commit -m "feat(rusefi): add idle rumble parameters"

# Main repo changes
git commit -m "feat(warkop): integrate idle rumble"

# Submodule reference update
git commit -m "chore: update rusefi submodule to feat-idle-rumble"
```

### 3. Keep Fork Synced

Periodically sync your fork with upstream:

```bash
cd ext/rusefi

# Add upstream remote (if not exists)
git remote add upstream https://github.com/rusefi/rusefi
git fetch upstream

# Update master from upstream
git checkout master
git merge upstream/master
git push origin master

# Rebase feature branch
git checkout feat-idle-rumble
git rebase master
git push origin feat-idle-rumble --force-with-lease
```

---

## Current Recommendation

**Right now, you're on `dev-feat-rumble` branch. Perfect!**

### Action Plan:

1. **Create branch di fork:**
   ```bash
   cd ext/rusefi
   git checkout -b feat-idle-rumble
   ```

2. **Edit rusefi_config.txt:**
   Add idle rumble parameters

3. **Commit & push to fork:**
   ```bash
   git add firmware/integration/rusefi_config.txt
   git commit -m "feat: add idle rumble config"
   git push origin feat-idle-rumble
   ```

4. **Update main repo:**
   ```bash
   cd ../..
   git add ext/rusefi
   git commit -m "chore: use feat-idle-rumble submodule branch"
   git push origin dev-feat-rumble
   ```

5. **Main tetap clean:**
   ```bash
   git checkout main
   # Uses official rusEFI or your master fork
   ```

---

## Summary

**Yes, BISA!** Strategy:

✅ **Master branch** → Official rusEFI (clean)  
✅ **dev-feat-rumble** → Fork dengan idle rumble  
✅ **Easy switch** antar branch  
✅ **No conflicts** saat update  

**Mau saya bantuin implement sekarang?** 🚀
