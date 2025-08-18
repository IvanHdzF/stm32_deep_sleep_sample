# STM32 Deep Sleep Sample - Design Document

## Overview
This document describes the software architecture and design rationale for the STM32 Deep Sleep Sample project. The project is structured to maximize modularity, reusability, and testability, while balancing development effort and practical requirements.

## Layered Architecture

### 1. Entry Point: `main.c`
  - Initializes all required peripherals (GPIO, SPI, etc.).
  - Reads the application configuration from `config.h` (via the `APPLICATION_TO_RUN` macro).
  - Dispatches execution to the selected application module.

### 2. Application Layer
- **Location:** `apps/` (e.g., `main_app/ds_main.c`, `test_blink/`, etc.)
- **Responsibilities:**
  - Implements the main logic for each application scenario (e.g., deep sleep demo, sensor test, blink test).
  - Calls into service modules to perform hardware-related tasks.
  - Each application is selected at compile time via the `APPLICATION_TO_RUN` macro, enabling easy switching and code reuse.

#### Main Application Behavior
- The main application (`ds_main`) configures the accelerometer (LIS2DW12) for minimum power consumption.
- It programs an interrupt on the accelerometer to wake the MCU from deep sleep (STOP3 mode).
- After initialization, the MCU enters STOP3 sleep mode, waiting for the interrupt.
- Upon waking up (interrupt triggered), the application calls the blink service to blink an LED for 5 seconds, then returns to sleep.


##### Simplicity: No RTOS or State Machines
- The project does not use an RTOS or explicit state machines. This is a deliberate choice to keep the codebase simple and easy to understand, given the straightforward requirements.
- Additionally, avoiding an RTOS saves both process complexity and memory overhead, which is important for resource-constrained embedded systems and rapid development.
- For more complex applications, a state machine (using action and next state tables) or an RTOS could be considered. However, for this demo, the logic is linear and event-driven, so such abstractions were not necessary.
#### Future Work / TODO
- Implement an application that transitions all the way to standby mode (not just STOP3). This is currently deferred due to development time constraints.

### 3. Services Layer
- **Location:** `services/` (e.g., `lis2dw12_hal/`, `sleep/`, `blink/`)
- **Responsibilities:**
  - Encapsulates reusable hardware-related functionality.
  - **`lis2dw12_hal`**: Designed with low coupling and high configurability. Uses a configuration struct (`lis2dw12_hal_config_t`) to abstract hardware access, allowing the user to provide function pointers for register access and delays. This enables easy adaptation to different hardware platforms and facilitates unit testing.
  - **`sleep` and `blink`**: Tightly coupled to the STM32 HAL. These modules are intentionally simple and direct, as their functionality is trivial and does not warrant additional abstraction. This design choice reduces development overhead for non-critical modules.

### 4. Drivers and third party layer

This layer contains:
- **Drivers:** Auto-generated code from STM32CubeMX for STM32 peripherals (e.g., SPI, GPIO, HAL, startup files). These provide the hardware abstraction and initialization routines required by the rest of the system.
- **Third party:** External libraries and drivers, typically included as git submodules. These are used for interfacing with sensors or other hardware components (e.g., LIS2DW12 sensor driver). This approach allows easy updates and integration of vendor-provided or open-source code.

## Design Justification

### Modularity
- The separation of concerns between initialization, application logic, and services allows for clear boundaries and easier maintenance.
- New applications or services can be added with minimal impact on existing code.

### Reusability
- The `lis2dw12_hal` service demonstrates a reusable driver pattern, where the same code can be used across different projects or hardware setups by simply changing the configuration struct.
- The project structure supports plugging in new sensors or hardware components with minimal changes.

### Testability
- The decoupled design of `lis2dw12_hal` enables both unit and integration testing, as hardware dependencies can be mocked or replaced.
- The modular application and service layers make it easier to isolate and test individual components.

### Practicality
- Not all modules require the same level of abstraction. For simple services like `sleep` and `blink`, direct HAL coupling is justified to avoid over-engineering and to save development time.
- The template can be quickly adapted for new use cases, making it suitable for rapid prototyping and experimentation.

## Conclusion
This layered and modular approach provides a flexible foundation for STM32-based projects, balancing abstraction and simplicity according to the needs of each module. The design supports both extensibility and maintainability, while remaining practical for real-world development constraints.
