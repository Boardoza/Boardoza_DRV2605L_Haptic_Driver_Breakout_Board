#ifndef DRV2605L_H
#define DRV2605L_H

#include <Arduino.h>
#include <Wire.h>

// Varsayılan I2C adresi (datasheet'e göre genelde 0x5A kullanılır,
// ancak kartınıza göre 0x5B, 0x5C veya 0x59 da olabilir)
#define DRV2605L_I2C_ADDR  0x5A  

// --- KULLANILACAK TEMEL REGISTER ADRESLERİ ---
#define DRV2605L_REG_STATUS         0x00
#define DRV2605L_REG_MODE           0x01
#define DRV2605L_REG_RTP_IN         0x02
#define DRV2605L_REG_LIBRARY        0x03
#define DRV2605L_REG_WAVESEQ1       0x04
#define DRV2605L_REG_WAVESEQ2       0x05
// ... buraya ihtiyaca göre ek wave sekans registerları eklenebilir (0x06, 0x07 vb.)
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

// --- MODE REGISTER DEĞERLERİ (0x01) ---
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
  // Kurucu
  DRV2605L();

  // Başlatma fonksiyonu
  bool begin(TwoWire &wirePort = Wire, uint8_t i2cAddr = DRV2605L_I2C_ADDR);

  // Mode ayarlama (MODE registerine yazar)
  void setMode(uint8_t mode);

  // Basit register yazma/okuma fonksiyonları
  void writeRegister8(uint8_t reg, uint8_t val);
  uint8_t readRegister8(uint8_t reg);

  // Dalgaformu (Waveform) tanımlama
  // örn: setWaveform(1, 47);  // 1. dalgaform slotuna ROM ID 47'yi koy
  void setWaveform(uint8_t slot, uint8_t waveform);

  // Hafızadaki (ROM) dalgaformlarını çalma başlatma/durdurma
  void go(void);
  void stop(void);

  // RTP modunda anlık genlik gönderme
  void setRealtimeValue(uint8_t rtpVal);

  // Tipik parametre ayarları (örn. rated voltage, overdrive clamp vb.)
  void setRatedVoltage(uint8_t val);
  void setOverdriveClampVoltage(uint8_t val);

  // Kendi basit auto-cal fonksiyonumuz (opsiyonel, datasheet'e göre özelleştirilebilir)
  bool autoCalibrate(uint8_t ratedVolt, uint8_t clampVolt);

private:
  TwoWire *_i2c;
  uint8_t  _i2cAddr;
};

#endif
