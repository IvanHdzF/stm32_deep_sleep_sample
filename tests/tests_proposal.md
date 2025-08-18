# Test Proposal for STM32 Deep Sleep Sample

## Overview
This document outlines proposed test cases for the STM32 Deep Sleep Sample project. Tests are divided into integration tests (using the different application modes) and unit tests (targeting individual services).

---

## 1. Integration Testing
Integration tests are performed by selecting different applications via the `APPLICATION_TO_RUN` macro in `config.h` and observing system behavior on hardware.

### Test Cases
- **Deep Sleep Main Application**
  - Verify that the system enters STOP3 mode and wakes up on accelerometer interrupt.
  - Confirm that the LED blinks for 5 seconds after wakeup.
  - Check that the system returns to sleep after blinking.
- **Test Blink Application**
  - Verify that the blink service toggles the LED at the expected period and duration.
- **Test Sleep Application**
  - Confirm that the system enters and exits sleep mode as expected.
- **Test LIS2DW12 Application** (if implemented)
  - Validate sensor initialization, configuration, and data readout.

---

## 2. Unit Testing
Unit tests target individual service modules. Due to the current design, only the `lis2dw12_hal` service is fully decoupled and suitable for isolated unit testing. The `sleep` and `blink` services are tightly coupled to the STM32 HAL and are best tested via integration.

### LIS2DW12 HAL Service Unit Test Cases
- **Configuration Struct Validation**
  - Test that the service correctly accepts and stores a valid configuration struct.
  - Test error handling for invalid or incomplete configuration.
- **Register Access**
  - Mock the SPI interface and verify that register read/write functions are called with correct parameters.
- **Delay Function**
  - Mock the delay function and ensure it is called as expected during initialization or operation.
- **Initialization**
  - Test that the initialization function returns success/failure codes appropriately.

### Note
- Only the LIS2DW12 HAL service is currently unit-testable in isolation. This is by design, as the other services are intentionally simple and tightly coupled to the HAL for rapid development. However, all services are covered by integration tests through the application layer.

---

## Summary
- Integration testing is the primary method for validating overall system behavior.
- Unit testing is focused on the LIS2DW12 HAL service, leveraging its decoupled design.
- This approach ensures both the correctness of individual components and the reliability of the system as a whole.
