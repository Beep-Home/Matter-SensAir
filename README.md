# SensAir

**SensAir** is a Matter-enabled environmental sensor device designed for real-time measurement of temperature, humidity, and atmospheric pressure. Built on the ESP32 platform, SensAir integrates seamlessly into Matter-compatible smart home ecosystems, offering robust and secure connectivity. Depending on the ESP32 module used, SensAir supports Matter over Thread or Wi-Fi. Currently, the following ESP32 modules are supported: **H2**, **C6**, and **S3**.

## Features
- **Temperature Measurement**: Provides accurate temperature readings.
- **Humidity Measurement**: Monitors and reports relative humidity levels.
- **Pressure Measurement**: Tracks atmospheric pressure changes.
- **Matter Protocol Support**: Enables interoperability with other Matter-compatible devices for seamless integration.

## Hardware Requirements
- **ESP32 H2, C6, or S3 Development Board**:
    - H2 or C6 for Thread-based connectivity
    - C6 or S3 for Wi-Fi connectivity
- **BME280 Sensor**: For temperature, humidity, and pressure readings
- **Power Supply**: 5V (USB-C or direct wiring to pins)

## Getting Started

### Hardware Wiring
Follow the wiring instructions below for your ESP32 module and the BME280 sensor:

#### ESP32-H2
```
ESP32-H2     BME280
  3.3V <-----> VCC
  22   <-----> SDA
  12   <-----> SCL
  GND  <-----> GND
```

#### ESP32-C6
```
ESP32-C6     BME280
  3.3V <-----> VCC
  6    <-----> SDA
  7    <-----> SCL
  GND  <-----> GND
```

#### ESP32-S3
```
ESP32-S3     BME280
  3.3V <-----> VCC
  35   <-----> SDA
  36   <-----> SCL
  GND  <-----> GND
```

### Flashing Your ESP Module with SensAir

Flashing your ESP module is straightforward using the **Beep-Home ESP Flashing Tool**. Follow these steps:

1. **Connect the Module**
    - Connect your ESP32 module to your computer.
    - If your board has two USB ports, use the one labeled **USB**.

2. **Select the Binary**
    - Select the appropriate binary file for your module and protocol (**Thread** or **Wi-Fi**).

3. **Enter Download Mode** (if required for your ESP32 module):
    - Hold the **Boot** button for 2 seconds.
    - After 5 seconds, while still holding the **Boot** button, press and hold the **Reset** button for 2 seconds.
    - Release the **Reset** button while continuing to hold the **Boot** button for another 2 seconds.
    - Finally, release the **Boot** button.

4. **Flash the Device**
    - In the Beep-Home ESP Flashing Tool, click **Flash** and select the appropriate serial port for your module.

5. **Exit Download Mode**
    - Once flashing is complete, press the **Reset** button on your ESP module to exit download mode.

Your device is now ready to use with **SensAir**.

### Using SensAir

1. **Power on SensAir**:
    - Use a 5V power supply connected to a USB-C port or directly to the 5V(+) and GND(-) pins.

2. **Add SensAir to Your Home Automation Platform**:
    - Open a Matter-compatible app (e.g., Apple Home or Home Assistant) and select the option to add a new device.

3. **Scan the QR Code**:
    - Use the QR code provided in the SensAir repository. Note that your app may notify you that the device is uncertified. This is expected and should be accepted for SensAir to function properly.

4. **Start Using SensAir**:
    - Once added, SensAir will begin reporting temperature, humidity, and pressure measurements every 30 seconds. Configure alerts or automation rules in your home automation platform to leverage SensAir's data.

<img src="https://github.com/Beep-Home/SensAir/blob/main/matter-qr-code.png?raw=true" width=200 alt="QR Code for SensAir">

## Troubleshooting

- **Commissioning Issues**:
    - Ensure your Wi-Fi or Thread network is functioning correctly.
    - Reset the device by holding the **Boot** button for 10 second.

## Confirmed Compatibility

### Home Assistant
- **Supported Values**: Temperature, humidity, and pressure
- **Thread** (Home Assistant Skyconnect ZBT-1):
    - **ESP32-H2 (4MB)**: ESP32-H2 DevKit
    - **ESP32-C6 (8MB)**: ESP32-C6 DevKit
- **Wi-Fi**:
    - **ESP32-C6 (8MB)**: ESP32-C6 DevKit
    - **ESP32-S3 (4MB)**: Wemos S3 MINI

### Apple Home
- **Supported Values**: Temperature sensor only
- **Thread** (HomePod or Apple TV as Thread Border Router):
    - **ESP32-H2 (4MB)**: ESP32-H2 DevKit
    - **ESP32-C6 (8MB)**: ESP32-C6 DevKit
- **Wi-Fi**:
    - **ESP32-C6 (8MB)**: ESP32-C6 DevKit
    - **ESP32-S3 (4MB)**: Wemos S3 MINI
