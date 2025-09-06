/**
 * @file ac_motor_control.ino
 * @author Rafael Ignacio Gonzalez Chong & Jaime Joel Olivas Muñoz
 * @brief Real-time AC motor speed control using digital phase-angle control.
 * @date 2024
 * 
 * @details This program regulates the speed of an AC motor by adjusting the
 * firing angle of a TRIAC. The firing angle is received via the serial port,
 * allowing for dynamic speed control. Zero-crossing detection is used to
 * synchronize the firing pulse with the AC waveform.
 * 
 * Hardware:
 *  - ESP32 Development Board
 *  - TRIAC-based power control circuit
 *  - Zero-crossing detection circuit connected to pin 17
 *  - TRIAC gate connected to pin 16
 */

// --- Global Variables ---
String inputString = "";              // Buffer to store incoming serial data
bool isCommandReady = false;          // Flag to indicate a complete command has been received
int firingAngle = 0;                  // Desired firing angle in degrees (0-180)
float delayBeforeFire = 1300;         // Calculated delay before TRIAC trigger (in microseconds)
const int PULSE_WIDTH_US = 1000;      // Duration of the TRIAC gate trigger pulse (in microseconds)

// --- Pin Definitions ---
const int TRIAC_GATE_PIN = 16;
const int ZERO_CROSS_PIN = 17;


void setup() {
  Serial.begin(115200);
  pinMode(TRIAC_GATE_PIN, OUTPUT);
  pinMode(ZERO_CROSS_PIN, INPUT_PULLDOWN);

  digitalWrite(TRIAC_GATE_PIN, LOW); // Ensure TRIAC is off at startup
}


void loop() {
  int edge = detectEdge(ZERO_CROSS_PIN);

  // Check if a new command has been received from the serial port
  if (isCommandReady) {
    inputString.trim();
    firingAngle = inputString.toInt();

    // Convert the firing angle (0-180 degrees) to a time delay in microseconds.
    // Assumes a 60Hz AC supply (8.333ms per half-cycle).
    delayBeforeFire = (firingAngle * 8333.33) / 180.0;
    
    inputString = "";
    isCommandReady = false;
  }

  // A rising edge indicates a zero-crossing point in the AC cycle
  if (edge == 1) {
    // Wait for the calculated delay period before firing the TRIAC
    delayMicroseconds(delayBeforeFire);

    // Send a short pulse to the TRIAC gate to turn it on
    digitalWrite(TRIAC_GATE_PIN, HIGH);
    delayMicroseconds(PULSE_WIDTH_US);
    digitalWrite(TRIAC_GATE_PIN, LOW);
  }
}


/**
 * @brief Reads incoming serial data asynchronously.
 * This function is automatically called when data is available.
 */
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      isCommandReady = true;
    } else {
      inputString += inChar;
    }
  }
}


/**
 * @brief Detects a state change (edge) on a digital input pin.
 * @param pin The pin to monitor.
 * @return 1 for a rising edge, -1 for a falling edge, 0 for no change.
 */
int detectEdge(int pin) {
  static bool lastState = digitalRead(pin);
  bool currentState = digitalRead(pin);

  if (currentState != lastState) {
    lastState = currentState;
    return (currentState == HIGH) ? 1 : -1;
  }
  return 0; // No change detected
}
