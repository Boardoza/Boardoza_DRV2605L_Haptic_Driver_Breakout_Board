#include <Wire.h>
#include "DRV2605L.h"

DRV2605L haptic;  // Create an instance of the DRV2605L class

void setup() {
  Serial.begin(115200);
  delay(100);

  // Initialize the library
  // If using an alternative TwoWire instance (e.g., Wire1), replace Wire accordingly
  if(!haptic.begin(Wire, 0x5A)) {
    Serial.println("DRV2605L connection failed!");
    while(1);
  }
  Serial.println("DRV2605L initialized.");

  // Example: Perform automatic calibration
  if(!haptic.autoCalibrate(0x50, 0x80)) {
    Serial.println("Auto calibration failed or timed out.");
  } else {
    Serial.println("Auto calibration successful.");
  }

  // LRA or ERM settings:
  // Configure RATED VOLTAGE and CLAMP VOLTAGE according to your haptic motor's datasheet.
  // Example:
  // haptic.setRatedVoltage(0x50);      // ~ 1.8V
  // haptic.setOverdriveClampVoltage(0x80);  // ~ 3.6V

  // Set to internal trigger mode (MODE 0)
  haptic.setMode(DRV2605L_MODE_INTTRIG);

  // Define waveform sequence (effects stored in ROM)
  // Example: Assign effect ID 1 to slot 1, and 0 (end) to slot 2
  haptic.setWaveform(1, 1);   // Slot 1: ROM effect ID = 1
  haptic.setWaveform(2, 0);   // Slot 2: 0 => end
}

void loop() {
  Serial.println("Playing effect...");
  haptic.go();    // Start waveform sequence
  delay(1000);    // Wait until the effect completes (duration depends on effect length)

  // To replay the effect, wait and call go() again
  delay(1000);
}
