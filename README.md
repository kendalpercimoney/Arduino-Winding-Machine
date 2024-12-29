# Winding Machine - README

## Overview
The Winding Machine automates the process of winding spools to specific lengths of wire or material. It uses a combination of sensors, a rotary encoder, and a motor control mechanism to ensure precision and user configurability.

---

## Features
- **Adjustable Length Settings**: Select lengths of 3m, 6m, 9m, 12m, or 15m using the rotary encoder.
- **Phototransistor Monitoring**: Ensures accurate detection of winding turns.
- **OLED Display**: Provides real-time feedback on selected length and operational status.
- **Button Control**: Single button to start the winding process.
- **Motor Control**: Automates the winding process with precise stops.

---

## Hardware Interface
### Pins:
- **Photo Transistor Pin**: `2` (Input) - Reads spool rotations.
- **Button Pin**: `4` (Input) - Starts the operation.
- **Motor Pin**: `8` (Output) - Controls motor operation.
- **Rotary Encoder**:
  - `CLK`: Pin `5`
  - `DT`: Pin `6`
  - `SW`: Pin `7`
- **OLED Display**:
  - Uses I2C address `0x3C`.

---

## Modes of Operation
1. **Idle Mode**:
   - The machine displays a welcome message and awaits a button press to begin.
   - Rotary encoder can adjust the target length in this mode.

2. **Active Mode**:
   - Once the button is pressed, the motor starts winding the spool until the selected length is reached.
   - The OLED displays the current progress and length settings.

3. **Completion Mode**:
   - The motor stops automatically when the target length is reached.
   - The machine resets, ready for the next operation.

---

## Operation Instructions
1. **Power On**:
   - Connect the machine to power. The OLED screen will display the startup message.
2. **Set Length**:
   - Use the rotary encoder to choose a winding length (3m, 6m, 9m, 12m, or 15m).
   - The current selection is shown on the OLED.
3. **Start Operation**:
   - Press the button to begin winding.
   - The motor will run, and the phototransistor will monitor the turns.
4. **Completion**:
   - The motor stops automatically at the selected length. The machine returns to Idle Mode.

---

## Notes
- **Turn Values**: The `turnValueX` constants define the number of phototransistor pulses for each length setting.
- **Rotary Encoder Debouncing**: Rotary encoder inputs are debounced to avoid miscounts.
- **Button Debouncing**: Button input includes a debounce delay of 50ms.

---

## Troubleshooting
- **Motor Does Not Start**:
  - Check the button connection.
  - Ensure the motor pin (`8`) is correctly wired.
- **Incorrect Length**:
  - Verify phototransistor alignment.
  - Check the `turnValueX` constants for proper calibration.
- **Display Issues**:
  - Ensure OLED connections are secure.
  - Confirm I2C address is set to `0x3C` in the code.

---

## Code Overview
### Key Functions
- **`WriteToDisplay()`**:
  - Updates the OLED display with current operation status.
- **`CheckTurnValue()`**:
  - Maps rotary encoder values to target lengths.
- **Main Loop**:
  - Manages the state transitions and motor control.

### Constants
- `turnValueX`: Defines the number of turns for each length.
- Pin assignments: Defined at the start of the code for easy modification.


 
[![Winding Machine Video](https://img.youtube.com/vi/5cZJSIIY1SE/0.jpg)](https://www.youtube.com/watch?v=5cZJSIIY1SE
