#include "pch.h"
#include "table_helper.h"

void boardTuneDefaults() {
  // ========== ENGINE SPECIFICATIONS ==========
  // Yamaha Vixion OLD 3C1 - 200cc Single Cylinder
  engineConfiguration->displacement = 0.2f;
  engineConfiguration->cylindersCount = 1;
  engineConfiguration->firingOrder = firing_order_e::FO_1;
  engineConfiguration->cylinderBore = 87.5f;

  // ========== COMPRESSION & FUEL ==========
  engineConfiguration->compressionRatio = 9.0f;
  engineConfiguration->fuelAlgorithm = engine_load_mode_e::LM_ALPHA_N;

  // ========== INJECTOR CONFIGURATION ==========
  engineConfiguration->injector.flow = 180.0f;
  engineConfiguration->injectionMode = injection_mode_e::IM_SEQUENTIAL;

  // ========== IGNITION CONFIGURATION ==========
  engineConfiguration->ignitionMode = ignition_mode_e::IM_INDIVIDUAL_COILS;
  engineConfiguration->timing_offset_cylinder[0] = 0;

  // ========== TRIGGER CONFIGURATION ==========
  engineConfiguration->trigger.type = trigger_type_e::TT_TOOTHED_WHEEL;
  engineConfiguration->trigger.customTotalToothCount = 12;
  engineConfiguration->trigger.customSkippedToothCount = 1;
  engineConfiguration->globalTriggerAngleOffset = 186.0f;

  // ========== RPM LIMITS ==========
  engineConfiguration->rpmHardLimit = 12000;
  engineConfiguration->cranking.rpm = 550;

  // ========== IDLE CONFIGURATION ==========
  engineConfiguration->idleMode = idle_mode_e::IM_AUTO;
  engineConfiguration->idleRpmPid.pFactor = 0.05f;
  engineConfiguration->idleRpmPid.iFactor = 0.002f;

  // ========== TEMPERATURE THRESHOLDS ==========
  engineConfiguration->fanOnTemperature = 92;  // °C
  engineConfiguration->fanOffTemperature = 88; // °C

  // ========== CRANKING PARAMETERS ==========
  engineConfiguration->crankingTimingAngle = 6.0f;
  engineConfiguration->ignitionDwellForCrankingMs = 6.0f;

  // ========== VEHICLE INFO ==========
  strcpy(engineConfiguration->engineMake, "Yamaha");
  strcpy(engineConfiguration->engineCode, "3C1");
  strcpy(engineConfiguration->vehicleName, "VIXION");

  // ========== TUNING TABLES FROM MSQ ==========

  // 1. VE Table Axis Bins
  static const float veRpmBins[16] = {650,  800,  1100, 1400, 1700, 2000,
                                      2300, 2600, 2900, 3200, 3500, 3800,
                                      4100, 4400, 4700, 7000};
  static const float veLoadBins[16] = {10, 20,  30,  40,  50,  60,  70,  80,
                                       90, 100, 110, 120, 130, 140, 150, 160};
  copyArray(config->veRpmBins, veRpmBins);
  copyArray(config->veLoadBins, veLoadBins);

  // 2. VE Table (16x16)
  static const float veTable[16][16] = {
      {60.0, 60.0, 60.1, 49.6, 50.2, 51.4, 52.6, 53.8, 54.4, 54.6, 54.4, 53.7,
       52.8, 51.8, 50.9, 50.0},
      {60.3, 61.4, 62.6, 54.1, 57.5, 60.7, 62.9, 64.4, 65.0, 65.0, 64.5, 63.5,
       62.3, 61.1, 60.0, 58.8},
      {67.4, 69.2, 72.8, 58.5, 62.7, 66.1, 68.2, 69.7, 70.2, 70.1, 69.5, 68.4,
       67.1, 65.8, 64.5, 63.3},
      {70.1, 73.3, 79.9, 63.5, 68.0, 71.4, 73.5, 74.9, 75.3, 75.2, 74.5, 73.3,
       71.8, 70.4, 69.0, 67.7},
      {72.8, 77.5, 87.0, 70.7, 75.1, 78.3, 80.3, 81.7, 82.1, 81.9, 81.1, 79.7,
       78.1, 76.5, 75.0, 73.5},
      {56.4, 64.4, 68.7, 74.5, 78.7, 81.8, 83.8, 85.1, 85.5, 85.3, 84.4, 83.0,
       81.3, 79.6, 78.0, 76.4},
      {60.7, 70.2, 74.5, 79.9, 83.8, 86.8, 88.9, 90.2, 90.6, 90.3, 89.4, 87.8,
       86.0, 84.2, 82.5, 80.8},
      {65.8, 76.0, 80.0, 85.0, 88.8, 91.8, 93.9, 95.2, 95.6, 95.3, 94.3, 92.6,
       90.7, 88.8, 87.0, 85.2},
      {69.4, 79.1, 82.9, 87.8, 91.7, 94.8, 97.0, 98.3, 98.8, 98.4, 97.4, 95.6,
       93.5, 91.5, 89.6, 87.7},
      {73.0, 82.2, 85.9, 90.7, 94.6, 97.8, 100.0, 101.5, 101.9, 101.6, 100.4,
       98.5, 96.4, 94.2, 92.2, 90.2},
      {76.6, 85.3, 88.8, 93.5, 97.4, 100.7, 103.1, 104.6, 105.1, 104.7, 103.5,
       101.5, 99.2, 96.9, 94.8, 92.6},
      {80.3, 88.5, 91.8, 96.4, 100.3, 103.7, 106.2, 107.8, 108.2, 107.8, 106.5,
       104.4, 102.0, 99.7, 97.4, 95.1},
      {83.9, 91.6, 94.7, 99.2, 103.2, 106.7, 109.2, 110.9, 111.4, 110.9, 109.6,
       107.4, 104.8, 102.4, 99.9, 97.6},
      {87.7, 94.9, 97.8, 102.0, 106.1, 109.7, 112.3, 114.0, 114.5, 114.1, 112.6,
       110.3, 107.7, 105.1, 102.5, 100.1},
      {91.3, 98.0, 100.8, 104.9, 108.9, 112.6, 115.3, 117.2, 117.7, 117.2,
       115.7, 113.3, 110.5, 107.8, 105.1, 102.5},
      {94.9, 101.1, 103.7, 107.7, 111.8, 115.6, 118.4, 120.3, 120.8, 120.3,
       118.7, 116.2, 113.3, 110.5, 107.7, 105.0}};
  copyTable(config->veTable, veTable);

  // 3. Ignition Table Axis Bins
  static const float ignRpmBins[16] = {650,  800,  1100, 1400, 1700, 2000,
                                       2300, 2600, 2900, 3200, 3500, 3800,
                                       4100, 4400, 4700, 7000};
  static const float ignLoadBins[16] = {21, 27, 33, 39, 48, 54,  60,  66,
                                        72, 81, 87, 93, 99, 108, 114, 120};
  copyArray(config->ignitionRpmBins, ignRpmBins);
  copyArray(config->ignitionLoadBins, ignLoadBins);

  // 4. Ignition Table (16x16)
  static const float ignitionTable[16][16] = {
      {14.1, 16.4, 20.9, 25.5, 25.9, 29.9, 33.8, 37.7, 41.6, 42.9, 42.9, 42.9,
       42.9, 42.9, 42.9, 42.9},
      {14.0, 16.2, 20.7, 25.1, 25.6, 29.5, 33.3, 37.2, 41.0, 42.3, 42.3, 42.3,
       42.3, 42.3, 42.3, 42.3},
      {12.0, 13.9, 17.7, 21.5, 25.3, 29.1, 32.8, 36.6, 40.4, 41.7, 41.7, 41.7,
       41.7, 41.7, 41.7, 41.7},
      {11.8, 13.7, 17.4, 21.2, 24.9, 28.7, 32.4, 36.1, 39.9, 41.1, 41.1, 41.1,
       41.1, 41.1, 41.1, 41.1},
      {11.6, 13.5, 17.1, 20.8, 24.4, 28.1, 31.7, 35.3, 39.0, 40.2, 40.2, 40.2,
       40.2, 40.2, 40.2, 40.2},
      {11.5, 13.3, 16.9, 20.5, 24.1, 27.7, 31.2, 34.8, 38.4, 39.6, 39.6, 39.6,
       39.6, 39.6, 39.6, 39.6},
      {11.4, 13.2, 16.7, 20.2, 23.7, 27.3, 30.8, 34.3, 37.8, 39.0, 39.0, 39.0,
       39.0, 39.0, 39.0, 39.0},
      {11.3, 13.0, 16.5, 19.9, 23.4, 26.9, 30.3, 33.8, 37.2, 38.4, 38.4, 38.4,
       38.4, 38.4, 38.4, 38.4},
      {11.1, 12.8, 16.2, 19.6, 23.0, 26.5, 29.9, 33.3, 36.7, 37.8, 37.8, 37.8,
       37.8, 37.8, 37.8, 37.8},
      {10.9, 12.6, 15.9, 19.2, 22.5, 25.9, 29.2, 32.5, 35.8, 36.9, 36.9, 36.9,
       36.9, 36.9, 36.9, 36.9},
      {10.8, 12.4, 15.7, 18.9, 22.2, 25.5, 28.7, 32.0, 35.2, 36.3, 36.3, 36.3,
       36.3, 36.3, 36.3, 36.3},
      {10.7, 12.3, 15.5, 18.7, 21.9, 25.1, 28.2, 31.4, 34.6, 35.7, 35.7, 35.7,
       35.7, 35.7, 35.7, 35.7},
      {10.5, 12.1, 15.2, 18.4, 21.5, 24.7, 27.8, 30.9, 34.1, 35.1, 35.1, 35.1,
       35.1, 35.1, 35.1, 35.1},
      {10.5, 12.1, 15.2, 18.3, 21.5, 24.6, 27.7, 30.8, 34.0, 35.0, 35.0, 35.0,
       35.0, 35.0, 35.0, 35.0},
      {10.5, 12.1, 15.2, 18.3, 21.5, 24.6, 27.7, 30.8, 34.0, 35.0, 35.0, 35.0,
       35.0, 35.0, 35.0, 35.0},
      {10.5, 12.1, 15.2, 18.3, 21.5, 24.6, 27.7, 30.8, 34.0, 35.0, 35.0, 35.0,
       35.0, 35.0, 35.0, 35.0}};
  copyTable(config->ignitionTable, ignitionTable);

  // 5. Idle Target RPM Table
  static const float cltIdleRpmBins[16] = {
      -30, -20, -10, 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
  static const float cltIdleRpm[16] = {1360, 1360, 1300, 1200, 1160, 1100,
                                       1060, 1000, 1000, 960,  960,  940,
                                       900,  900,  1000, 1100};
  copyArray(config->cltIdleRpmBins, cltIdleRpmBins);
  copyArray(config->cltIdleRpm, cltIdleRpm);

  // 6. Warmup Enrichment (CLT Fuel Correction)
  static const float cltFuelCorrBins[16] = {
      -40, -30, -20, -10, 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
  static const float cltFuelCorr[16] = {1.5,  1.5, 1.42, 1.36, 1.28, 1.19,
                                        1.12, 1.1, 1.06, 1.06, 1.03, 1.01,
                                        1.0,  1.0, 1.0,  1.0};
  copyArray(config->cltFuelCorrBins, cltFuelCorrBins);
  copyArray(config->cltFuelCorr, cltFuelCorr);
}
