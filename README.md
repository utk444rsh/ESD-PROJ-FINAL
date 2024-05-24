# Motion Detection System with LPC1768

## Overview
This project integrates an IR sensor with the LPC1768 microcontroller to create a robust motion detection system. The system is designed to trigger a buzzer upon detecting motion. By leveraging the Analog-to-Digital Converter (ADC) output, the system enhances its motion detection capabilities, allowing it to respond to environmental changes more effectively.

## Features
- *IR Sensor Integration:* Detects motion and provides input to the microcontroller.
- *Buzzer Activation:* Alerts users upon motion detection.
- *ADC Utilization:* Improves detection accuracy by analyzing environmental changes.
- *LPC1768 Microcontroller:* Acts as the central control unit, offering flexibility and programmability.

## Components
- *LPC1768 Microcontroller:* The brain of the system, coordinating all components.
- *IR Sensor:* Senses motion and sends signals to the microcontroller.
- *Buzzer:* Provides audible alerts when motion is detected.
- *Analog-to-Digital Converter (ADC):* Enhances motion detection by processing environmental data.

## How It Works
1. *Motion Detection:* The IR sensor detects motion and sends a signal to the LPC1768 microcontroller.
2. *Signal Processing:* The ADC processes the signal to account for environmental changes, improving detection accuracy.
3. *Trigger Alert:* Upon confirming motion, the microcontroller activates the buzzer.
4. *System Coordination:* The LPC1768 efficiently manages inputs from the IR sensor and ADC, ensuring accurate and timely alerts.

## Benefits
- *Enhanced Detection:* Utilizes ADC for better sensitivity to environmental changes.
- *Programmable Flexibility:* The LPC1768 microcontroller allows for customization and scaling.
- *Reliable Alerts:* Ensures prompt and clear notifications of motion detection.

## Getting Started
### Requirements
- LPC1768 microcontroller
- IR sensor module
- Buzzer
- ADC module (integrated within LPC1768)
- Connecting wires and breadboard (for prototyping)

### Setup Instructions
1. *Connect the IR Sensor:* Wire the IR sensor to the appropriate GPIO pins on the LPC1768.
2. *Integrate the Buzzer:* Connect the buzzer to the designated output pin of the microcontroller.
3. *Configure the ADC:* Ensure the ADC is set up to read signals from the IR sensor.
4. *Upload the Code:* Program the LPC1768 with the provided code, which includes logic for motion detection and buzzer activation.

### Example Code
```c
#include "LPC17xx.h"

// Initialization and configuration functions
void initIRSensor(void);
void initBuzzer(void);
void initADC(void);

// Main function
int main(void) {
    SystemInit();
    initIRSensor();
    initBuzzer();
    initADC();
    
    while (1) {
        if (isMotionDetected()) {
            triggerBuzzer();
        }
    }
}

// Implement the initialization and utility functions
