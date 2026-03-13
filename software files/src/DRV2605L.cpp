#include "DRV2605L.h"

/**
 * @brief Default constructor for the DRV2605L class.
 *
 * Initializes the I2C address with the default DRV2605L I2C address
 * and sets the I2C interface pointer to nullptr.
 */
DRV2605L::DRV2605L() {
  _i2c = nullptr;
  _i2cAddr = DRV2605L_I2C_ADDR;
}

/**
 * @brief Initializes the DRV2605L device.
 *
 * This function initializes the I2C communication with the specified I2C interface
 * and sets the device's I2C address. It also performs basic setup such as
 * reading the status register, setting the mode to auto-calibration, and 
 * selecting the waveform library.
 *
 * @param wirePort Reference to the TwoWire I2C object (Wire or Wire1).
 * @param i2cAddr  The I2C address of the DRV2605L device.
 * @return true if initialization is successful.
 */
bool DRV2605L::begin(TwoWire &wirePort, uint8_t i2cAddr) {
  _i2c = &wirePort;
  _i2cAddr = i2cAddr;

  _i2c->begin();

  uint8_t status = readRegister8(DRV2605L_REG_STATUS);

  writeRegister8(DRV2605L_REG_MODE, DRV2605L_MODE_AUTOCAL);

  writeRegister8(DRV2605L_REG_LIBRARY, 0x06);

  return true;
}

/**
 * @brief Sets the operating mode of the DRV2605L.
 *
 * The DRV2605L supports multiple modes such as standby, real-time playback, 
 * and auto-calibration. This function sets the mode by writing to the mode register.
 *
 * @param mode The desired operating mode (0-7).
 */
void DRV2605L::setMode(uint8_t mode) {
  writeRegister8(DRV2605L_REG_MODE, mode & 0x07);
}

/**
 * @brief Writes an 8-bit value to a specified register of the DRV2605L.
 *
 * This function sends a command via I2C to write a given value to a specific 
 * register of the DRV2605L haptic driver.
 *
 * @param reg The register address to write to.
 * @param val The 8-bit value to be written to the register.
 */
void DRV2605L::writeRegister8(uint8_t reg, uint8_t val) {
  _i2c->beginTransmission(_i2cAddr);
  _i2c->write(reg);
  _i2c->write(val);
  _i2c->endTransmission();
}

/**
 * @brief Reads an 8-bit value from a specified register of the DRV2605L.
 *
 * This function requests a single byte from the specified register
 * of the DRV2605L over the I2C bus.
 *
 * @param reg The register address to read from.
 * @return The 8-bit value read from the register. Returns 0 if no data is available.
 */
uint8_t DRV2605L::readRegister8(uint8_t reg) {
  _i2c->beginTransmission(_i2cAddr);
  _i2c->write(reg);
  _i2c->endTransmission(false);

  _i2c->requestFrom((int)_i2cAddr, 1);
  if (_i2c->available()) {
    return _i2c->read();
  }
  return 0;
}

/**
 * @brief Sets a waveform sequence slot in the DRV2605L.
 *
 * The DRV2605L supports up to 8 waveform slots, each storing a waveform effect. 
 * This function assigns a waveform to a specific slot, defining the sequence 
 * of haptic effects to be played.
 *
 * @param slot The waveform sequence slot (1-8).
 * @param waveform The waveform ID to assign to the slot.
 */
void DRV2605L::setWaveform(uint8_t slot, uint8_t waveform) {
  // slot = 1 -> 0x04 (WAVESEQ1)
  // slot = 2 -> 0x05 (WAVESEQ2), vb.
  // Basitçe: 0x04 + (slot - 1)
  if(slot < 1) slot = 1;
  if(slot > 8) slot = 8; // Maksimum 8 slot var
  writeRegister8(DRV2605L_REG_WAVESEQ1 + slot - 1, waveform);
}

/**
 * @brief Starts haptic playback.
 *
 * This function sets the GO bit (bit 0) in the DRV2605L control register
 * to initiate haptic playback using the configured waveform sequence.
 */
void DRV2605L::go() {
  writeRegister8(DRV2605L_REG_GO, 0x01);
}

/**
 * @brief Stops haptic playback.
 *
 * This function clears the GO bit (bit 0) in the DRV2605L control register,
 * stopping any currently playing haptic effects.
 */
void DRV2605L::stop() {
  writeRegister8(DRV2605L_REG_GO, 0x00);
}

/**
 * @brief Sets the real-time playback (RTP) value.
 *
 * The real-time playback feature allows direct control of the actuator
 * output by writing an 8-bit value to the RTP register. The RTP mode must 
 * be enabled beforehand.
 *
 * @param rtpVal The 8-bit RTP value (0-255) to control actuator strength.
 */
void DRV2605L::setRealtimeValue(uint8_t rtpVal) {
  writeRegister8(DRV2605L_REG_RTP_IN, rtpVal);
}

/**
 * @brief Sets the rated voltage for the actuator.
 *
 * This function sets the rated voltage register, which defines the normal 
 * operating voltage for the actuator. It is used during automatic calibration 
 * to optimize the output drive.
 *
 * @param val The 8-bit rated voltage value.
 */
void DRV2605L::setRatedVoltage(uint8_t val) {
  writeRegister8(DRV2605L_REG_RATEDV, val);
}

/**
 * @brief Sets the overdrive clamp voltage.
 *
 * The overdrive clamp voltage defines the maximum allowable voltage applied 
 * during the overdrive phase of haptic playback. This setting can affect 
 * the intensity and duration of effects.
 *
 * @param val The 8-bit overdrive clamp voltage value.
 */
void DRV2605L::setOverdriveClampVoltage(uint8_t val) {
  writeRegister8(DRV2605L_REG_CLAMPV, val);
}

/**
 * @brief Performs automatic calibration of the DRV2605L haptic driver.
 *
 * This function configures the necessary registers and initiates the 
 * auto-calibration process for the DRV2605L, ensuring optimal actuator 
 * performance based on the provided rated and clamp voltages.
 *
 * The function sets the feedback and control registers, enters auto-calibration mode,
 * and monitors the calibration process. It returns whether the calibration was 
 * successful or not.
 *
 * @param ratedVolt The rated voltage value for the actuator.
 * @param clampVolt The overdrive clamp voltage value.
 * @return true if calibration is successful, false if it fails.
 */
bool DRV2605L::autoCalibrate(uint8_t ratedVolt, uint8_t clampVolt)
{ 
  uint8_t temp_data = 0;
  
  // Configure feedback register
  temp_data = readRegister8(DRV2605L_REG_FEEDBACK);
  temp_data &= 0x03;
  temp_data |= 0x10;
  temp_data |= 0x04;
  writeRegister8(DRV2605L_REG_FEEDBACK, temp_data);

  // Set overdrive clamp voltage
  temp_data = clampVolt;
  writeRegister8(DRV2605L_REG_CLAMPV, temp_data);

  // Configure control registers for calibration
  temp_data = readRegister8(DRV2605L_REG_CONTROL4);
  temp_data &= 0x0F;
  temp_data |= 0x10;
  temp_data |= 0x40;
  writeRegister8(DRV2605L_REG_CONTROL4, temp_data);
 
  temp_data = readRegister8(DRV2605L_REG_CONTROL1);
  temp_data &= 0xE0;
  temp_data |= 0x10;
  writeRegister8(DRV2605L_REG_CONTROL1, temp_data);
 
  temp_data = readRegister8(DRV2605L_REG_CONTROL2);
  temp_data &= 0xCF;
  temp_data |= 0x10;
  temp_data |= 0x08;
  temp_data |= 0x02;
  writeRegister8(DRV2605L_REG_CONTROL2, temp_data);

  temp_data = readRegister8(DRV2605L_REG_CONTROL5);
  temp_data &= 0xF0;
  writeRegister8(DRV2605L_REG_CONTROL5, temp_data);

  // Set the device to auto-calibration mode
  setMode(DRV2605L_MODE_AUTOCAL);

  // Read status register
  uint8_t status = readRegister8(DRV2605L_REG_STATUS);
  bool diagFail = 1;
  Serial.println(status);

  // Start calibration
  go();
  delay(1000);

  // Check if calibration is still running
  uint8_t goCheck = readRegister8(DRV2605L_REG_GO);
  if (goCheck & 0x01) {
    delay(500);
    goCheck = readRegister8(DRV2605L_REG_GO);
    if(goCheck & 0x01) {
      return false;
    }
  }

  // Read final status and check for calibration failure
  status = readRegister8(DRV2605L_REG_STATUS);
  diagFail = (status & 0x08) ? true : false;

  // Set back to internal trigger mode
  setMode(DRV2605L_MODE_INTTRIG);

  return (!diagFail);
}