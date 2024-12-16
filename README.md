# SensAir - Matter-Enabled Sensor

**SensAir** is a Matter-enabled environmental sensor device that provides real-time measurements of temperature, humidity, and atmospheric pressure. Built using the ESP32 platform, SensAir is designed to seamlessly integrate into smart home ecosystems supporting the Matter protocol, offering robust and secure connectivity. SensAir supports running Matter over Thread as well as Matter over WiFi depending on the ESP32 module used. At the moment three different ESP32 modules are supported these are the H2, C6 and S3.

## Features

- **Temperature Measurement**: Provides accurate temperature readings using a built-in sensor.
- **Humidity Measurement**: Monitors and reports relative humidity in the environment.
- **Pressure Measurement**: Tracks atmospheric pressure changes.
- **Matter Protocol Support**: Ensures interoperability with other Matter-compatible devices for seamless integration.

## Hardware Requirements

- **ESP32 H2, C6 or S3 Development Board** (H2 or C6 when using Thread, C6 or S3 when using Wi-Fi)
- **BME280 Sensor** (for temperature, humidity, and pressure readings)
- **Power Supply** (5V)



## Getting Started

### Hardware Wiring
Depending on your chosen ESP32 module the wiring may be different below we listed all default wirings for the ESP32 modules that we support.

#### ESP32H2
```
ESP32H2       BME280
  3.3v <----->  VCC
  22   <----->  SDA
  12   <----->  SCL
  gnd  <----->  GND
```

#### ESP32C6
```
ESP32C6       BME280
  3.3v <----->  VCC
  6    <----->  SDA
  7    <----->  SCL
  gnd  <----->  GND
```

#### ESP32S3
```
ESP32S3       BME280
  3.3v <----->  VCC
  35   <----->  SDA
  36   <----->  SCL
  gnd  <----->  GND
```


### Flashing Your ESP Module with SensAir

Flashing your ESP module is straightforward using our **ESP Flashing Tool**. Follow these steps:

1. **Connect the Module**  
   - Connect your ESP32 module to your computer.  
   - If your board has two USB ports, use the one labeled **USB**.

2. **Select the Binary**  
   - Choose the appropriate binary for your board, ensuring it matches your preferred protocol (**Thread** or **Wi-Fi**).

3. **Enter Download Mode** (if required for your ESP32 module):  
   - Hold the **Boot** button for 2 seconds.  
   - After 5 seconds, while still holding the **Boot** button, press and hold the **Reset** button for 2 seconds.  
   - Release the **Reset** button but continue holding the **Boot** button for another 2 seconds.  
   - Finally, release the **Boot** button.  

4. **Flash the Device**  
   - In the web tool, press **Flash** and select the correct serial port for your module.

5. **Exit Download Mode**  
   - After flashing is complete, press the **Reset** button on your ESP module once to exit download mode.

Your device is now ready to use with **SensAir**!


### Using SensAir

1. **Power on the SensAir** by connecting a 5v power supply to one of the usb c ports or directly to the 5v(+) and GND(-) pin. 
2. **Add SensAir** to your home automation platform by opening the corresponding Matter-supported app (e.g., Apple Home or HomeAssistant). Select the option to add a new device to start the onboarding process. The app should request to scan a QR code.
3. **Scan the QR code** provided in the SensAir repository to begin commissioning. After scanning the QR code your app may notify you that the device you are trying to add is uncertified, this is normal and must be accepted for SensAir to function.

4. **SensAir is ready for use**. Once commissioned, SensAir will automatically start reporting temperature, humidity, and pressure measurements to your Matter-enabled smart home hub. The sensor data will be updated every 30 seconds. You can now configure alerts or automation rules using the readings of SensAir.

<img src="https://github.com/Beep-Home/SensAir/blob/main/matter-qr-code.png?raw=true" width=250>


## Troubleshooting

- If the device fails to commission, **check your Wi-Fi connection** and **reset the device** Resetting the device is done by holding the boot button on your developer board for one second.

## Confirmed Compatibility

### Home Assistant
- **Displayed Values**: Temperature, humidity, and pressure 
- **Thread** (using HomeAssistant Skyconnect ZBT-1)
  - **ESP32-H2 (4MB)**: ESP32H2 DevKit
  - **ESP32-C6 (8MB)**: ESP32C6 DevKit
- **Wi-Fi**
  - **ESP32-C6 (8MB)**: ESP32C6 DevKit
  - **ESP32-S3 (4MB)**: Wemos S3 Mini

### Apple Home
- **Displayed Values**: Recognizes only the temperature sensor
- **Thread** (HomePod or Apple TV as Thread Border Router)
  - **ESP32-H2 (4MB)**: ESP32H2 DevKit
  - **ESP32-C6 (8MB)**: ESP32C6 DevKit
- **Wi-Fi**
  - **ESP32-C6 (8MB)**: ESP32C6 DevKit
  - **ESP32-S3 (4MB)**: Wemos S3 Mini
