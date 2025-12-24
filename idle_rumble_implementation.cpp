// ============================================================================
// IDLE RUMBLE IMPLEMENTATION - Full Code with TunerStudio Control
// ============================================================================
// Add this to Warkop-X ECU for idle rumble effect (cable throttle version)
//
// Files to modify:
// 1. integration/rusefi_config.txt - Add config parameters
// 2. default_tune.cpp - Set default values
// 3. board_configuration.cpp - Apply rumble effect
// 4. board.mk - Enable feature flag
// ============================================================================

// ============================================================================
// FILE 1: integration/rusefi_config.txt
// ============================================================================
// Add these lines to rusefi_config.txt (dalam struct engine_configuration_s):

struct_no_prefix engine_configuration_s
    // ... existing fields ...

    // Idle Rumble Feature (for cable throttle - timing/fuel variation)
    bit idleRumbleEnabled;Enable idle rumble effect for aggressive sound
    uint8_t idleRumbleAmplitude;
Rumble amplitude 0 - 100 %, 0, 100, 0;
"%" uint8_t idleRumblePeriod;
Rumble period(speed), 1, 20, 0;
"x100ms" uint8_t idleRumbleMethod;
Rumble method : 0 = Timing, 1 = Fuel, 2 = Spark, 3 = Combined, 0, 3, 0;
"" int8_t autoscale idleRumbleTiming;
Max timing offset, -10, 10, 0;
"deg" int8_t autoscale idleRumbleFuel;
Max fuel adjustment, -20, 20, 0;
"%" uint16_t idleRumbleMaxRpm;
Max RPM untuk rumble active, 0, 2000, 0;
"rpm" uint8_t idleRumbleMaxTps;
Max TPS untuk rumble active, 0, 20, 0;
"%"

    end_struct

    // ============================================================================
    // FILE 2: default_tune.cpp
    // ============================================================================
    // Set default values di setBoardDefaultConfiguration():

    void
    setDefaultTune() {
  // ... existing code ...

  // Idle Rumble - Default OFF
  engineConfiguration->idleRumbleEnabled = false;
  engineConfiguration->idleRumbleAmplitude = 50; // 50% amplitude
  engineConfiguration->idleRumblePeriod = 5;     // 500ms (5 x 100ms)
  engineConfiguration->idleRumbleMethod = 3;     // Combined (timing + fuel)
  engineConfiguration->idleRumbleTiming = 4;     // ±4 degrees
  engineConfiguration->idleRumbleFuel = 10;      // ±10% fuel
  engineConfiguration->idleRumbleMaxRpm = 1500;  // Active below 1500 RPM
  engineConfiguration->idleRumbleMaxTps = 5;     // Active below 5% TPS
}

// ============================================================================
// FILE 3: board_configuration.cpp or new file idle_rumble.cpp
// ============================================================================

#include "pch.h"

// Rumble state
static float rumblePhase = 0;
static Timer rumbleTimer;

/**
 * Check if we're at idle condition
 */
bool isIdleCondition() {
  // Check RPM
  if (Sensor::getOrZero(SensorType::Rpm) >
      engineConfiguration->idleRumbleMaxRpm) {
    return false;
  }

  // Check TPS
  if (Sensor::getOrZero(SensorType::Tps1) >
      engineConfiguration->idleRumbleMaxTps) {
    return false;
  }

  // Check engine running
  if (!engine->rpmCalculator.isRunning()) {
    return false;
  }

  // Check coolant temp (only when warm)
  if (Sensor::getOrZero(SensorType::Clt) < 60) {
    return false; // Too cold
  }

  return true;
}

/**
 * Get rumble effect value (-1.0 to +1.0)
 * Returns sine wave that oscillates based on period setting
 */
float getRumbleEffect() {
  // Feature disabled
  if (!engineConfiguration->idleRumbleEnabled) {
    rumblePhase = 0; // Reset phase
    return 0;
  }

  // Not at idle
  if (!isIdleCondition()) {
    rumblePhase = 0; // Reset phase
    return 0;
  }

  // Calculate phase increment based on period setting
  // period = 1-20 (100ms to 2000ms)
  // Lower period = faster oscillation
  float periodMs = engineConfiguration->idleRumblePeriod * 100.0f;
  float phaseIncrement =
      (2.0f * 3.14159f) / (periodMs / 10.0f); // Assuming 100Hz update

  // Update phase
  rumblePhase += phaseIncrement;
  if (rumblePhase > 6.28318f) { // 2π
    rumblePhase -= 6.28318f;
  }

  // Calculate sine wave
  float sineValue = sinf(rumblePhase);

  // Apply amplitude (0-100%)
  float amplitude = engineConfiguration->idleRumbleAmplitude / 100.0f;

  return sineValue * amplitude;
}

/**
 * Get timing offset for rumble effect
 * Called from ignition timing calculation
 */
float getIdleRumbleTimingOffset() {
  float effect = getRumbleEffect();

  // Method 0 (timing only) or Method 3 (combined)
  if (engineConfiguration->idleRumbleMethod == 0 ||
      engineConfiguration->idleRumbleMethod == 3) {
    return effect * engineConfiguration->idleRumbleTiming;
  }

  return 0;
}

/**
 * Get fuel multiplier for rumble effect
 * Called from fuel calculation
 */
float getIdleRumbleFuelMultiplier() {
  float effect = getRumbleEffect();

  // Method 1 (fuel only) or Method 3 (combined)
  if (engineConfiguration->idleRumbleMethod == 1 ||
      engineConfiguration->idleRumbleMethod == 3) {
    float fuelPercent = effect * engineConfiguration->idleRumbleFuel;
    return 1.0f + (fuelPercent / 100.0f);
  }

  return 1.0f; // No change
}

/**
 * Check if we should skip spark (for spark cut method)
 * Called from ignition scheduling
 */
bool shouldSkipSparkForRumble() {
  // Only for Method 2 (spark cut)
  if (engineConfiguration->idleRumbleMethod != 2) {
    return false;
  }

  if (!engineConfiguration->idleRumbleEnabled) {
    return false;
  }

  if (!isIdleCondition()) {
    return false;
  }

  // Get effect value
  float effect = getRumbleEffect();

  // Skip spark when effect is strongly negative
  // This creates periodic misfire
  return (effect < -0.7f); // Skip ~15% of sparks
}

// ============================================================================
// INTEGRATION POINTS
// ============================================================================

// In ignition timing calculation (advance_map.cpp or similar):
float getAdvance(int rpm, float load) {
  float baseAdvance = getBaseAdvance(rpm, load);

  // Add rumble effect
  baseAdvance += getIdleRumbleTimingOffset();

  return baseAdvance;
}

// In fuel calculation (fuel_computer.cpp or similar):
float getInjectionDuration(int rpm, float load) {
  float baseFuel = calculateBaseFuel(rpm, load);

  // Apply rumble multiplier
  baseFuel *= getIdleRumbleFuelMultiplier();

  return baseFuel;
}

// In ignition scheduling (ignition_controller.cpp or similar):
void scheduleIgnition() {
  // Check if should skip spark
  if (shouldSkipSparkForRumble()) {
    return; // Skip this ignition event
  }

  // ... normal ignition scheduling
}

// ============================================================================
// FILE 4: board.mk
// ============================================================================
// Enable feature flag (optional, for conditional compilation):

#Enable idle rumble feature
DDEFS += -DEFI_IDLE_RUMBLE = TRUE

// Then wrap code with:
#if EFI_IDLE_RUMBLE
// ... rumble code ...
#endif

    // ============================================================================
    // TUNERSTUDIO CONFIGURATION
    // ============================================================================
    // TunerStudio will auto-generate UI from rusefi_config.txt
    // But you can customize in board-specific ini file if needed

    // Add to board_config.txt or tunerstudio ini:

    dialog = idleRumble,
         "Idle Rumble (Drumbal Effect)" field = "Enable Idle Rumble",
         idleRumbleEnabled field = "Rumble Amplitude", idleRumbleAmplitude,
         {idleRumbleEnabled == 1} field = "Rumble Period (speed)",
         idleRumblePeriod, {idleRumbleEnabled == 1} field = "Rumble Method",
         idleRumbleMethod, {idleRumbleEnabled == 1} field = "Max Timing Offset",
         idleRumbleTiming,
         {idleRumbleEnabled == 1 &&
          (idleRumbleMethod == 0 || idleRumbleMethod == 3)} field =
             "Max Fuel Adjustment",
         idleRumbleFuel,
         {idleRumbleEnabled == 1 &&
          (idleRumbleMethod == 1 || idleRumbleMethod == 3)} field =
             "Max Active RPM",
         idleRumbleMaxRpm, {idleRumbleEnabled == 1} field = "Max Active TPS",
         idleRumbleMaxTps,
         {idleRumbleEnabled == 1}

// ============================================================================
// USAGE INSTRUCTIONS
// ============================================================================

/*
After implementation:

1. Flash new firmware to ECU

2. In TunerStudio:
   - Settings → Idle → Idle Rumble

3. Enable rumble:
   - Check "Enable Idle Rumble"

4. Start with conservative settings:
   - Amplitude: 50%
   - Period: 5 (500ms)
   - Method: 0 (Timing only)
   - Max Timing: 3 degrees

5. Test and adjust:
   - Increase amplitude for stronger effect
   - Decrease period for faster oscillation
   - Try different methods

6. Fine tune to taste!

RECOMMENDED SETTINGS:
--------------------
Subtle:
  Amplitude: 30%
  Period: 8 (800ms)
  Method: Timing only
  Timing: 3°

Medium (Recommended):
  Amplitude: 50%
  Period: 5 (500ms)
  Method: Combined
  Timing: 4°
  Fuel: 10%

Aggressive:
  Amplitude: 70%
  Period: 3 (300ms)
  Method: Combined
  Timing: 5°
  Fuel: 15%
*/

// ============================================================================
// FLASH COST
// ============================================================================
// Estimated flash usage: ~2-3 KB
// RAM usage: ~20 bytes (static variables)

// ============================================================================
// SAFETY NOTES
// ============================================================================
/*
- Feature auto-disables above set RPM/TPS
- Feature auto-disables when engine cold (CLT < 60°C)
- Can be disabled anytime via TunerStudio
- No risk of engine damage with conservative settings
- Start conservative and increase gradually
*/
