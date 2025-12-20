#include "pch.h"

void boardTuneDefaults() {
  // ========== ENGINE SPECIFICATIONS ==========
  // Yamaha Vixion OLD 3C1 - 200cc Single Cylinder
  engineConfiguration->displacement = 0.2; // 200cc in Liters
  engineConfiguration->cylindersCount = 1;
  engineConfiguration->firingOrder = FO_1;
  engineConfiguration->cylinderBore = 87.5; // mm

  // ========== COMPRESSION & FUEL ==========
  engineConfiguration->compressionRatio = 9.0;
  engineConfiguration->fuelAlgorithm =
      LM_ALPHA_N; // Alpha-N for single cylinder

  // ========== INJECTOR CONFIGURATION ==========
  engineConfiguration->injector.flow = 180.0; // cc/min
  engineConfiguration->injectionMode = IM_SEQUENTIAL;

  // ========== IGNITION CONFIGURATION ==========
  engineConfiguration->ignitionMode = IM_INDIVIDUAL_COILS;
  engineConfiguration->timing_offset_cylinder[0] = 0;

  // ========== TRIGGER CONFIGURATION ==========
  // 12-1 toothed wheel (custom)
  engineConfiguration->trigger.type = TT_TOOTHED_WHEEL;
  engineConfiguration->trigger.customTotalToothCount = 12;
  engineConfiguration->trigger.customSkippedToothCount = 1;
  engineConfiguration->globalTriggerAngleOffset = 186.0;

  // ========== RPM LIMITS ==========
  engineConfiguration->rpmHardLimit = 12000; // High revving single cylinder
  engineConfiguration->cranking.rpm = 450;

  // ========== IDLE CONFIGURATION ==========
  // Cold idle ~1360 RPM, warm idle ~900 RPM (from MSQ)
  engineConfiguration->idleMode = IM_AUTO;
  engineConfiguration->idleRpmPid.pFactor = 0.05;
  engineConfiguration->idleRpmPid.iFactor = 0.002;

  // ========== TEMPERATURE THRESHOLDS ==========
  engineConfiguration->fanOnTemperature = 92;  // °C
  engineConfiguration->fanOffTemperature = 88; // °C

  // ========== CRANKING PARAMETERS ==========
  engineConfiguration->cranking.baseFuel = 7.4;   // mg
  engineConfiguration->crankingTimingAngle = 6.0; // degrees
  engineConfiguration->ignitionDwellForCrankingMs = 6.0;

  // ========== SPARK DWELL ==========
  // Average dwell ~3.5ms across RPM range
  engineConfiguration->sparkDwellRpmBins[0] = 1000;
  engineConfiguration->sparkDwellRpmBins[1] = 3000;
  engineConfiguration->sparkDwellRpmBins[2] = 5000;
  engineConfiguration->sparkDwellRpmBins[3] = 7000;

  engineConfiguration->sparkDwellValues[0] = 4.0;
  engineConfiguration->sparkDwellValues[1] = 3.5;
  engineConfiguration->sparkDwellValues[2] = 3.2;
  engineConfiguration->sparkDwellValues[3] = 3.0;

  // ========== VEHICLE INFO ==========
  strcpy(engineConfiguration->engineMake, "Yamaha");
  strcpy(engineConfiguration->engineCode, "3C1");
  strcpy(engineConfiguration->vehicleName, "Vixion OLD");
}
