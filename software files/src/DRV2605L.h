#ifndef DRV2605L_H
#define DRV2605L_H

#include <Arduino.h>
#include <Wire.h>

// Default I2C address (usually 0x5A according to the datasheet,
// but it can also be 0x5B, 0x5C, or 0x59 depending on your board)
#define DRV2605L_I2C_ADDR  0x5A  

// --- BASIC REGISTER ADDRESSES TO BE USED ---
#define DRV2605L_REG_STATUS         0x00
#define DRV2605L_REG_MODE           0x01
#define DRV2605L_REG_RTP_IN         0x02
#define DRV2605L_REG_LIBRARY        0x03
#define DRV2605L_REG_WAVESEQ1       0x04
#define DRV2605L_REG_WAVESEQ2       0x05
// ... additional wave sequence registers can be added here as needed (0x06, 0x07 etc.)
#define DRV2605L_REG_GO             0x0C
#define DRV2605L_REG_FEEDBACK       0x1A
#define DRV2605L_REG_CONTROL1       0x1B
#define DRV2605L_REG_CONTROL2       0x1C
#define DRV2605L_REG_CONTROL3       0x1D
#define DRV2605L_REG_CONTROL4       0x1E
#define DRV2605L_REG_CONTROL5       0x1F
#define DRV2605L_REG_CONTROL6       0x20
#define DRV2605L_REG_CONTROL7       0x21
#define DRV2605L_REG_CONTROL8       0x22
#define DRV2605L_REG_RATEDV         0x16
#define DRV2605L_REG_CLAMPV         0x17

// --- MODE REGISTER VALUES (0x01) ---
#define DRV2605L_MODE_INTTRIG       0x00  // Internal Trigger (Waveform Sequencer)
#define DRV2605L_MODE_EXTTRIGEDGE   0x01  // External Trigger (Edge)
#define DRV2605L_MODE_EXTTRIGLVL    0x02  // External Trigger (Level)
#define DRV2605L_MODE_ANALOG_PWM    0x03  // Analog/PWM Mode
#define DRV2605L_MODE_AUDIOVIBE     0x04  // Audio-to-Vibe Mode
#define DRV2605L_MODE_REALTIME      0x05  // Real-Time Playback (RTP) Mode
#define DRV2605L_MODE_DIAGNOSTICS   0x06  // Diagnostics Mode
#define DRV2605L_MODE_AUTOCAL       0x07  // Auto-Calibration Mode

class DRV2605L {
public:
  DRV2605L();

  bool begin(TwoWire &wirePort = Wire, uint8_t i2cAddr = DRV2605L_I2C_ADDR);
  void setMode(uint8_t mode);

  // Basic register read/write functions
  void writeRegister8(uint8_t reg, uint8_t val);
  uint8_t readRegister8(uint8_t reg);

  // Waveform definition
  // e.g., setWaveform(1, 47);  // Put ROM ID 47 into waveform slot 1
  void setWaveform(uint8_t slot, uint8_t waveform);

  // Start/stop playing waveforms from memory (ROM)
  void go(void);
  void stop(void);

  // Send real-time amplitude in RTP mode
  void setRealtimeValue(uint8_t rtpVal);

  // Typical parameter settings (e.g., rated voltage, overdrive clamp, etc.)
  void setRatedVoltage(uint8_t val);
  void setOverdriveClampVoltage(uint8_t val);

  // Our own simple auto-cal function (optional, can be customized according to the datasheet)
  bool autoCalibrate(uint8_t ratedVolt, uint8_t clampVolt);

private:
  TwoWire *_i2c;
  uint8_t  _i2cAddr;
};

#endif
