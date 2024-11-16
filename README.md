# SensAir - Matter-Enabled Sensor

**SensAir** is a Matter-enabled environmental sensor device that provides real-time measurements of temperature, humidity, and atmospheric pressure. Built using the ESP32 platform, SensAir is designed to seamlessly integrate into smart home ecosystems supporting the Matter protocol, offering robust and secure connectivity.

## Features

- **Temperature Measurement**: Provides accurate temperature readings using a built-in sensor.
- **Humidity Measurement**: Monitors and reports relative humidity in the environment.
- **Pressure Measurement**: Tracks atmospheric pressure changes.
- **Matter Protocol Support**: Ensures interoperability with other Matter-compatible devices for seamless integration.
- **Secure Commissioning**: Supports secure setup and commissioning through BLE and Thread.

## Hardware Requirements

- **ESP32 Development Board**
- **BMX280 Sensor** (for temperature, humidity, and pressure readings)
- **Power Supply** (USB or battery)

## Getting Started

### Prerequisites

- ESP-IDF v5.2.3 installed and configured
- Matter SDK setup on your development environment

Ensure you have the following tools installed:

```bash
brew install cmake ninja dfu-util
```

#### Setup ESP-IDF and ESP-Matter

```bash
# Create working directory
mkdir esp && cd esp

# Clone ESP-IDF and checkout version v5.2.3
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf; git checkout v5.2.3; ./install.sh; source ./export.sh; cd ..

# Clone ESP-Matter
git clone --depth 1 https://github.com/espressif/esp-matter.git
cd esp-matter; git submodule update --init --depth 1

# Initialize Matter SDK submodules
cd connectedhomeip/connectedhomeip; ./scripts/checkout_submodules.py --platform esp32 darwin --shallow; cd ../..

# Install Matter dependencies
./install.sh; cd ..
```


### Build and Flash

1. **Initialize NVS Flash**:
   ```bash
   idf.py set-target esp32
   idf.py menuconfig
   ```

2. **Build the firmware**:
   ```bash
   idf.py build
   ```

3. **Flash the firmware to the ESP32**:
   ```bash
   idf.py flash monitor
   ```

### Commissioning

1. **Power on the device** and open a Matter-supported app (e.g., Apple Home, Google Home) to start the onboarding process.
2. **Scan the QR code** displayed on the serial monitor or device label to begin commissioning.

## Usage

Once commissioned, SensAir will automatically start reporting temperature, humidity, and pressure measurements to your Matter-enabled smart home controller. You can monitor real-time sensor data and configure alerts or automation rules using any Matter-compatible app.

## Troubleshooting

- If the device fails to commission, **check your Wi-Fi connection** and **reset the device** by holding the reset button for 10 seconds.
