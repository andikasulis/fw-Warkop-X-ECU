#include <ch.hpp>

// Break include sorting
#include "pch.h"

// Break include sorting
#include "board_overrides.h"

Gpio getCommsLedPin() { return Gpio::B7; }

Gpio getRunningLedPin() { return Gpio::Unassigned; }

Gpio getWarningLedPin() { return Gpio::Unassigned; }

// board-specific configuration setup
static void customBoardDefaultConfiguration() {
  // ========== IGNITION OUTPUTS ==========
  engineConfiguration->ignitionPins[0] = Gpio::Unassigned;
  engineConfiguration->ignitionPins[1] = Gpio::Unassigned;
  engineConfiguration->ignitionPins[2] = Gpio::Unassigned;
  engineConfiguration->ignitionPins[3] = Gpio::Unassigned;

  // ========== INJECTION OUTPUTS ==========
  engineConfiguration->injectionPins[0] = Gpio::Unassigned;
  engineConfiguration->injectionPins[1] = Gpio::Unassigned;
  engineConfiguration->injectionPins[2] = Gpio::Unassigned;
  engineConfiguration->injectionPins[3] = Gpio::Unassigned;

  // ========== TRIGGER INPUTS ==========
  engineConfiguration->triggerInputPins[0] = Gpio::Unassigned;
  engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;

  // ========== SENSOR ADC CHANNELS ==========
  engineConfiguration->map.sensor.hwChannel = EFI_ADC_NONE;
  engineConfiguration->afr.hwChannel = EFI_ADC_NONE;
  engineConfiguration->vbattAdcChannel = EFI_ADC_NONE;
  engineConfiguration->tps1_1AdcChannel = EFI_ADC_3; // TPS PA3
  engineConfiguration->clt.adcChannel = EFI_ADC_4;   // CLT PA4 (ADC4)
  engineConfiguration->iat.adcChannel = EFI_ADC_NONE;

  // ========== ADDITIONAL ANALOG INPUTS ==========
  engineConfiguration->auxAnalogInputs[0] = EFI_ADC_NONE;

  // ========== DIGITAL INPUTS ==========
  engineConfiguration->acSwitch = Gpio::Unassigned;
  engineConfiguration->clutchDownPin = Gpio::Unassigned;
  engineConfiguration->vehicleSpeedSensorInputPin = Gpio::Unassigned;

  // ========== RELAYS & ACTUATORS ==========
  engineConfiguration->fuelPumpPin = Gpio::Unassigned;
  engineConfiguration->fanPin = Gpio::Unassigned;
  engineConfiguration->malfunctionIndicatorPin = Gpio::Unassigned;
  engineConfiguration->acRelayPin = Gpio::Unassigned;

  // ========== IDLE CONTROL ==========
  engineConfiguration->idle.solenoidPin = Gpio::Unassigned;

  // ========== OUTPUTS ==========
  engineConfiguration->tachOutputPin = Gpio::Unassigned;

  // ========== VOLTAGE DIVIDER CONFIGURATION ==========
  engineConfiguration->analogInputDividerCoefficient = 1.47f;
  engineConfiguration->adcVcc = 3.3f;

  // ========== THERMISTOR CONFIGURATION ==========
  engineConfiguration->clt.config.bias_resistor = 2490;
  engineConfiguration->iat.config.bias_resistor = 2490;

  // ========== SD CARD CONFIGURATION ==========
  engineConfiguration->isSdCardEnabled = false;
  engineConfiguration->sdCardSpiDevice = SPI_NONE;
  engineConfiguration->spi3mosiPin = Gpio::Unassigned;
  engineConfiguration->spi3misoPin = Gpio::Unassigned;
  engineConfiguration->spi3sckPin = Gpio::Unassigned;
  engineConfiguration->sdCardCsPin = Gpio::Unassigned;

  // ========== CAN BUS CONFIGURATION ==========
  // CAN1 on PB8 (RX) and PB9 (TX) - Standard STM32F407 CAN1 pins
  engineConfiguration->canTxPin = Gpio::B9; // CAN1_TX
  engineConfiguration->canRxPin = Gpio::B8; // CAN1_RX

  // Alternative pins if PB8/PB9 not available:
  // PA11 (CAN1_RX) and PA12 (CAN1_TX)
  // PD0 (CAN1_RX) and PD1 (CAN1_TX)
}

void boardTuneDefaults();

void customBoardTsAction(uint16_t subSystem, uint16_t index) {
  // Custom TunerStudio command handler
}

void setup_custom_board_overrides() {
  custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
  custom_board_ConfigOverrides = boardTuneDefaults;
  custom_board_ts_command = customBoardTsAction;
}
