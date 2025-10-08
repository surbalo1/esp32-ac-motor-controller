# ESP32 AC Motor Speed Controller

Real-time AC motor speed control using phase-angle modulation with TRIAC and zero-crossing detection on ESP32.

## Description

This project implements a real-time speed controller for AC motors using an ESP32 development board and a TRIAC-based power control circuit. Motor speed is regulated by adjusting the TRIAC firing angle, which is controlled via serial commands. A zero-crossing detector circuit ensures precise synchronization with the AC waveform for stable operation.

## Features

- **Real-Time Speed Adjustment**: Modify motor speed by sending commands through the serial monitor
- **Phase-Angle Control**: Digital technique for regulating power delivered to the motor
- **Zero-Crossing Detection**: Precise synchronization with AC signal for stable control
- **Serial Interface**: Easy control via UART commands (0-180 degrees)

## Hardware Requirements

- **ESP32 Development Board**
- **TRIAC-based power control circuit**
- **Zero-crossing detection circuit** (connected to GPIO 17)
- **TRIAC gate control** (connected to GPIO 16)
- **AC motor** (compatible with TRIAC control)

## Software

- **Platform:** Arduino IDE / PlatformIO
- **Language:** C++ (Arduino framework)
- **Baud Rate:** 115200

## Pin Configuration

| Function | GPIO Pin |
|----------|----------|
| TRIAC Gate | 16 |
| Zero-Crossing Input | 17 |

## Installation

1. **Hardware Assembly**: Connect the TRIAC power circuit and zero-crossing detector to the ESP32 as specified in the pin configuration
2. **Load Firmware**: Upload `ac_motor_control.ino` to your ESP32 using Arduino IDE
3. **Open Serial Monitor**: Start serial communication at 115200 baud
4. **Send Commands**: Control motor speed by sending a numeric value between `0` and `180` (representing firing angle in degrees)
5. **Observe Results**: Motor adjusts speed dynamically based on the firing angle

## Usage

### Serial Commands

Send a value between 0-180 followed by a newline:

```
0    # Minimum speed
90   # Medium speed
180  # Maximum speed
```

### Example Code Snippet

```
void loop() {
  if (Serial.available() > 0) {
    int angle = Serial.parseInt();
    if (angle >= 0 && angle <= 180) {
      firingAngle = angle;
      Serial.print("Firing angle set to: ");
      Serial.println(firingAngle);
    }
  }
}
```

## How It Works

The main program continuously monitors the zero-crossing detector signal. When a zero-crossing is detected, it calculates a delay based on the `firingAngle` and, after that time elapses, sends a short pulse to the TRIAC gate to activate it. Commands to update the angle are received asynchronously through the serial port.

### Phase-Angle Control Principle

1. Detect AC zero-crossing
2. Wait for calculated delay (based on firing angle)
3. Send trigger pulse to TRIAC gate
4. TRIAC conducts for remainder of half-cycle
5. Repeat for each AC cycle

## Circuit Diagram

```
AC Line ──┬─── TRIAC ─── Motor
          │
          └─── Zero-Crossing Detector ──► GPIO 17
                          │
                     TRIAC Gate ◄──── GPIO 16 (ESP32)
```

## Safety Warning

⚠️ **This project involves working with AC mains voltage. Only attempt if you have proper knowledge of electrical safety. Use proper isolation and protection circuits.**

## Applications

- Variable speed fans
- Light dimmers
- Pump speed control
- Industrial motor controllers
- Power tools

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Authors

**Rafael Gonzalez**
- GitHub: [@surbalo1](https://github.com/surbalo1)
- LinkedIn: [Rafael Gonzalez](https://www.linkedin.com/in/rafael-glez-chong/)

**Jaime Joel Olivas Muñoz**
- Collaborator
