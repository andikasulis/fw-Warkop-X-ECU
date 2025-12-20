#include "pch.h"

void boardTuneDefaults() {
  // ========== ENGINE SPECIFICATIONS ==========
  // Yamaha Vixion OLD 3C1 - 200cc Single Cylinder
  engineConfiguration->displacement = 0.2; // 200cc in Liters
  engineConfiguration->cylindersCount = 1;
  engineConfiguration->firingOrder = firing_order_e::FO_1;
  engineConfiguration->cylinderBore = 87.5; // mm

  // ========== COMPRESSION & FUEL ==========
  engineConfiguration->compressionRatio = 9.0;
  engineConfiguration->fuelAlgorithm =
      engine_load_mode_e::LM_ALPHA_N; // Alpha-N for single cylinder

  // ========== INJECTOR CONFIGURATION ==========
  engineConfiguration->injector.flow = 180.0; // cc/min
  engineConfiguration->injectionMode = injection_mode_e::IM_SEQUENTIAL;

  // ========== IGNITION CONFIGURATION ==========
  engineConfiguration->ignitionMode = ignition_mode_e::IM_INDIVIDUAL_COILS;
  engineConfiguration->timing_offset_cylinder[0] = 0;

  // ========== TRIGGER CONFIGURATION ==========
  // 12-1 toothed wheel (custom)
  engineConfiguration->trigger.type = trigger_type_e::TT_TOOTHED_WHEEL;
  engineConfiguration->trigger.customTotalToothCount = 12;
  engineConfiguration->trigger.customSkippedToothCount = 1;
  engineConfiguration->globalTriggerAngleOffset = 186.0;

  // ========== RPM LIMITS ==========
  engineConfiguration->rpmHardLimit = 12000; // High revving single cylinder
  engineConfiguration->cranking.rpm = 450;

  // ========== IDLE CONFIGURATION ==========
  // Cold idle ~1360 RPM, warm idle ~900 RPM (from MSQ)
  engineConfiguration->idleMode = idle_mode_e::IM_AUTO;
  engineConfiguration->idleRpmPid.pFactor = 0.05;
  engineConfiguration->idleRpmPid.iFactor = 0.002;

  // ========== TEMPERATURE THRESHOLDS ==========
  engineConfiguration->fanOnTemperature = 92;  // °C
  engineConfiguration->fanOffTemperature = 88; // °C

  // ========== CRANKING PARAMETERS ==========
  // Note: cranking.baseFuel removed in newer RusEfi - using firmware defaults
  engineConfiguration->crankingTimingAngle = 6.0; // degrees
  engineConfiguration->ignitionDwellForCrankingMs = 6.0;

  // ========== SPARK DWELL ==========
  // Note: sparkDwellRpmBins/Values removed in newer RusEfi - using firmware
  // defaults Default dwell configuration is managed by the firmware

  // ========== VEHICLE INFO ==========
  strcpy(engineConfiguration->engineMake, "Yamaha");
  strcpy(engineConfiguration->engineCode, "3C1");
  strcpy(engineConfiguration->vehicleName, "Vixion OLD");
}
