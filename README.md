# Boardoza DRV2605L Haptic Motor Driver Breakout Board

The **Boardoza DRV2605L Haptic Driver Breakout Board** is based on the **Texas Instruments DRV2605L**, a powerful and intelligent haptic motor driver designed specifically for **ERM (Eccentric Rotating Mass)** and **LRA (Linear Resonant Actuator)** vibration motors. Unlike simple on/off motor drivers, the DRV2605L integrates a built-in waveform library and smart-loop control engine to generate advanced vibration effects such as clicks, double-clicks, ramps, buzz patterns, and audio-synchronized feedback.

Unlike standard motor drivers for DC or stepper motors, the DRV2605 is optimized for **ERM (Eccentric Rotating Mass)** and **LRA (Linear Resonant Actuator)** motors. It communicates via **I²C**, allowing you to configure, chain, and trigger complex vibration patterns directly from your microcontroller. This breakout board is ideal for **wearables, game controllers, touch interfaces, mobile devices, assistive systems, and any project that requires professional-grade haptic feedback**.

## [Click here to purchase!](https://www.ozdisan.com/ureticiler/boardoza)

| Front Side | Back Side |
|:---:|:---:|
| ![DRV2605L Front](./assets/DRV2605L%20Front.png) | ![DRV2605L Back](./assets/DRV2605L%20Back.png) |

---

## Key Features
 
- **I²C-Controlled Digital Playback Engine:** Includes a waveform sequencer for flexible haptic pattern generation.  
- **Real-Time Playback Options:** Supports control via I²C, PWM, or analog input.  
- **Dual Drive Modes:** Operates in open-loop (ERM) and closed-loop (LRA) configurations.  
- **Smart-Loop™ Control:** Provides automatic overdrive and braking for optimized performance.  
- **Automatic Resonance Tracking:** Includes actuator diagnostics for LRA operation.  
- **Automatic Level Calibration:** Ensures consistent output performance.  
- **Battery Voltage Compensation:** Maintains stable operation under varying supply conditions.  
- **Differential H-Bridge Output:** Features OUT+ and OUT− for driving actuators.    


---

## Technical Specifications

**Model:** DRV2605L  
**Manufacturer:** Boardoza  
**Manufacturer IC:** Texas Instruments  
**Device Type:** Haptic Driver IC  
**Functions:** Smart Haptic Motor Driver    
**Input Voltage (VDD):** 2.0V – 5.2V  
**Interface:** I²C (Standard & Fast Mode, up to 400kHz)  
**Control Input (IN/TRIG):** PWM / Analog / External Trigger (Selectable)  
**Supported Actuators:**  
- ERM (Eccentric Rotating Mass) – Open-Loop Drive  
- LRA (Linear Resonant Actuator) – Closed-Loop with Auto Resonance Tracking  

**Playback Modes:**  
- Internal ROM Waveform Library  
- RAM-Based Custom Waveform Sequencing  
- Real-Time Playback (RTP) Mode  
- Audio-to-Vibe Mode  

**Drive Output:** Differential H-Bridge (OUT+, OUT−)  
**Auto Features:**  
- Automatic Overdrive & Braking  
- Automatic Resonance Tracking (LRA)  
- Automatic Level Calibration  
- Actuator Diagnostics  

**Operating Temperature:** -40°C to +150°C  
**Board Dimensions:** 20mm x 20mm   

---

## Board Pinout

### ( J1 ) Control & Power Connector

| Pin Number | Pin Name | Description |
|:---:|:---:|---|
| 1 | VCC | Supply Input (2.0V – 5.2V DC) |
| 2 | IN | Multi-mode Input (PWM / Analog / Trigger). Connect to GND if unused |
| 3 | SCL | I²C Serial Clock |
| 4 | SDA | I²C Serial Data |
| 5 | GND | Ground |

### ( J2 ) Haptic Motor Output

| Pin Number | Pin Name | Description |
|:---:|:---:|---|
| 1 | OUT+ | Positive Differential Output |
| 2 | OUT− | Negative Differential Output |

---

## Board Dimensions

<img src="./assets/DRV2605L Dimensions.png" alt="DRV2605L Board Dimension" width="450"/>

---

## Step Files

[Boardoza DRV2605L.step](./assets/DRV2605L%20Step.step)

---

## Datasheet

[DRV2605L Datasheet.pdf](./assets/DRV2605L%20Datasheet.pdf)

---

## Version History

- V1.0.0 - Initial Release  

---

## Support

- If you have any questions or need support, please contact **support@boardoza.com**

---

## **License**

This repository contains both hardware and software components:

### **Hardware Design**

[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

All hardware design files are licensed under [Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

### **Software/Firmware**

[![BSD-3-Clause][bsd-shield]][bsd]

All software and firmware are licensed under [BSD 3-Clause License][bsd].

[bsd]: https://opensource.org/licenses/BSD-3-Clause
[bsd-shield]: https://img.shields.io/badge/License-BSD%203--Clause-blue.svg
