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
  engineConfiguration->ignitionPins[0] = Gpio::E15; // Ignition 1
  engineConfiguration->ignitionPins[1] = Gpio::E14; // Ignition 2
  engineConfiguration->ignitionPins[2] = Gpio::D13; // Ignition 3
  engineConfiguration->ignitionPins[3] = Gpio::E5;  // Ignition 4

  // ========== INJECTION OUTPUTS ==========
  engineConfiguration->injectionPins[0] = Gpio::D8;  // Injector 1
  engineConfiguration->injectionPins[1] = Gpio::B15; // Injector 2
  engineConfiguration->injectionPins[2] = Gpio::B14; // Injector 3
  engineConfiguration->injectionPins[3] = Gpio::B13; // Injector 4

  engineConfiguration->triggerInputPins[0] =
      Gpio::D3; // CKP - Crankshaft Position
  engineConfiguration->triggerInputPins[1] =
      Gpio::Unassigned; // CMP - Camshaft Position (Unassigned to avoid
                        // conflict)

  // ========== SENSOR ADC CHANNELS ==========
  engineConfiguration->map.sensor.hwChannel = EFI_ADC_0; // MAP sensor on PA0
  engineConfiguration->afr.hwChannel = EFI_ADC_1;        // O2 sensor on PA1
  engineConfiguration->vbattAdcChannel = EFI_ADC_2;  // Battery voltage on PA2
  engineConfiguration->tps1_1AdcChannel = EFI_ADC_3; // TPS on PA3
  engineConfiguration->clt.adcChannel = EFI_ADC_4;   // Coolant temp on PA4
  engineConfiguration->iat.adcChannel = EFI_ADC_5;   // Intake air temp on PA5

  // ========== ADDITIONAL ANALOG INPUTS ==========
  engineConfiguration->auxAnalogInputs[0] =
      EFI_ADC_9; // Analog Reserve 1 on PB1

  // ========== DIGITAL INPUTS ==========
  engineConfiguration->acSwitch = Gpio::B0;                   // AC Input
  engineConfiguration->clutchDownPin = Gpio::E13;             // Clutch Input
  engineConfiguration->vehicleSpeedSensorInputPin = Gpio::D7; // VSS

  // ========== RELAYS & ACTUATORS ==========
  engineConfiguration->fuelPumpPin = Gpio::C8;             // Fuel Pump Relay
  engineConfiguration->fanPin = Gpio::A15;                 // Fan Relay
  engineConfiguration->malfunctionIndicatorPin = Gpio::E8; // Main Relay
  engineConfiguration->acRelayPin = Gpio::C7; // AC Compressor Relay

  // ========== IDLE CONTROL ==========
  engineConfiguration->idle.solenoidPin = Gpio::D9; // Idle Control 1

  // ========== OUTPUTS ==========
  engineConfiguration->tachOutputPin = Gpio::C9; // Tacho Output

  // ========== VOLTAGE DIVIDER CONFIGURATION ==========
  // 5.6k high side/10k low side = 1.47 ratio divider
  engineConfiguration->analogInputDividerCoefficient = 1.47f;

  // ========== ADC REFERENCE VOLTAGE ==========
  // STM32 usually runs at 3.3V
  engineConfiguration->adcVcc = 3.3f;

  // ========== THERMISTOR CONFIGURATION ==========
  // 2.49k bias resistor for temperature sensors
  engineConfiguration->clt.config.bias_resistor = 2490;
  engineConfiguration->iat.config.bias_resistor = 2490;

  // ========== SD CARD CONFIGURATION (SPI3) ==========
  engineConfiguration->isSdCardEnabled = true;
  engineConfiguration->sdCardSpiDevice = SPI_DEVICE_3;
  engineConfiguration->spi3mosiPin = Gpio::C12;
  engineConfiguration->spi3misoPin = Gpio::C11;
  engineConfiguration->spi3sckPin = Gpio::C10;
  engineConfiguration->is_enabled_spi_3 = true;
  engineConfiguration->sdCardCsPin = Gpio::D2;

  // ========== CAN BUS CONFIGURATION ==========
  engineConfiguration->canTxPin = Gpio::D1;
  engineConfiguration->canRxPin = Gpio::D0;

  // ========== UART CONFIGURATION ==========
  // UART1 - Primary serial communication (Console/TS)
  // TX: PA9, RX: PA10
}

void customBoardTsAction(uint16_t subSystem, uint16_t index) {
  // Custom TunerStudio command handler
}

void setup_custom_board_overrides() {
  custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
  custom_board_ts_command = customBoardTsAction;
}
