# AloniesTFT Library

A user-friendly Arduino library for TFT displays, designed to provide a powerful and easy-to-use API for your graphics and UI needs. This library is a high-level wrapper around the popular `MCUFRIEND_kbv` and `Adafruit_GFX` libraries, simplifying the process of drawing shapes, text, and images on your TFT screen.

---

## Table of Contents

1.  [Overview](#overview)
2.  [Features](#features)
3.  [SD Card Support](#sd-card-support)
4.  [Touchscreen Support](#touchscreen-support)
5.  [Debug Mode](#debug-mode)
6.  [Requirements](#requirements)
7.  [Setup Instructions](#setup-instructions)
8.  [Usage](#usage)
9.  [API](#api)
10. [Examples](#examples)
11. [Contributing](#contributing)
12. [License](#license)

---

## Overview

The `AloniesTFT` library is designed to make working with TFT displays as simple as possible. By providing a clean and intuitive API, it abstracts away the complexities of the underlying `MCUFRIEND_kbv` and `Adafruit_GFX` libraries. Whether you're a beginner looking to display sensor data or an experienced developer building a complex user interface, `AloniesTFT` provides the tools you need to get the job done quickly and efficiently.

---

## Features

-   **Easy Initialization**: Get your TFT display up and running with a single `begin()` command.
-   **Rich Drawing API**: A comprehensive set of functions for drawing shapes, lines, and text.
-   **Bitmap Support**: Display icons and images with the `drawXBitmap` function.
-   **SD Card Integration**: Easily read and write files to an SD card for storing assets or data.
-   **Touchscreen Interaction**: Implement interactive user interfaces by reading touch input.
-   **Debug Mode**: Enable serial output to monitor library functions for easier debugging.
-   **Clean and Simple**: A high-level API that is easy to learn and use.
-   **Well-Documented**: The library is well-documented with clear examples.

---

## SD Card Support

The library provides a dedicated `AloniesTFT_SD` class to handle SD card operations. It simplifies initialization, file listing, reading, and writing. The Chip Select (CS) pin is configurable via the constructor.

**Default Pins for Arduino Uno/Mega**:
- **SD_SS (CS)**: Pin 10
- **SD_DI (MOSI)**: Pin 11
- **SD_DO (MISO)**: Pin 12
- **SD_SCK (SCK)**: Pin 13

**Constructor**:
```cpp
AloniesTFT_SD sdCard; // Uses default CS pin 10
AloniesTFT_SD sdCard(uint8_t cs_pin); // Specify the CS pin
```

---

## Touchscreen Support

The library includes an `AloniesTFT_Touch` class for interacting with the display's resistive touchscreen. The touch pins are configurable via the constructor.

**Default Pins for Arduino Uno/Mega (Common Configuration)**:
- **YP**: A3 (Analog)
- **XM**: A2 (Analog)
- **YM**: 9 (Digital)
- **XP**: 8 (Digital)

**Constructor**:
```cpp
AloniesTFT_Touch touch; // Uses default pins
AloniesTFT_Touch touch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rxplate); // Specify all pins
```

---

## Debug Mode

The library includes a debug mode that provides detailed output to the Serial Monitor about the functions being called. This can be very useful for debugging your application.

To enable debug mode, you need to call the `setDebug()` function on your `AloniesTFT`, `AloniesTFT_SD`, or `AloniesTFT_Touch` object.

**Example**:
```cpp
#include <AloniesTFT.h>

AloniesTFT tft;

void setup() {
  Serial.begin(9600); // Serial monitor must be started for debug output

  tft.setDebug(true); // Enable debug mode for the TFT object
  
tft.begin();
  tft.drawText(10, 10, "Debug Mode On", WHITE, 2);
}
```

---

## Requirements

### Hardware
-   A TFT display compatible with the `MCUFRIEND_kbv` library.
-   An SD card module (integrated with the display shield).
-   A resistive touchscreen (integrated with the display shield).

### Software
-   [Arduino IDE](https://www.arduino.cc/en/software)
-   The following Arduino libraries must be installed:
    -   [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
    -   [MCUFRIEND_kbv](https://github.com/prenticedavid/MCUFRIEND_kbv)
    -   [SD Library](https://www.arduino.cc/reference/en/libraries/sd/) (usually built-in with Arduino IDE)
    -   [TouchScreen Library](https://github.com/adafruit/Adafruit_TouchScreen) (by Adafruit)

You can install these dependencies via the Arduino Library Manager.

---

## Setup Instructions

1.  Download the latest version of the `AloniesTFT` library from the [releases page](https://github.com/your-username/AloniesTFT/releases).
2.  In the Arduino IDE, navigate to `Sketch` > `Include Library` > `Add .ZIP Library...` and select the downloaded ZIP file.
3.  Alternatively, you can clone this repository into your Arduino `libraries` folder.
4.  **Install Dependencies**: Ensure all required libraries (listed above) are installed via the Arduino Library Manager.

---

## Usage

Here is a simple example of how to use the `AloniesTFT` library with an Arduino Uno/Mega:

```cpp
#include <AloniesTFT.h>
#include <AloniesTFT_SD.h>
#include <AloniesTFT_Touch.h>

// Create instances of the classes
AloniesTFT tft;
AloniesTFT_SD sdCard; // Uses default CS pin 10
AloniesTFT_Touch touch; // Uses default touch pins

void setup() {
  Serial.begin(9600); // Initialize serial for debugging
  
  // Initialize the display
  tft.begin();
  tft.clearScreen();
  tft.drawText(10, 10, "Welcome to AloniesTFT!", WHITE, 2);

  // Initialize SD Card (optional)
  if (sdCard.begin()) {
    tft.drawText(10, 40, "SD Card OK!", GREEN, 1);
    sdCard.listFilesInRoot(); // Example: list files
  } else {
    tft.drawText(10, 40, "SD Card Failed!", RED, 1);
  }
}

void loop() {
  // Check for touch input (optional)
  TSPoint p = touch.getCalibratedPoint(tft.width(), tft.height(), tft.Get_Rotation());
  if (p.z > 10 && p.z < 1000) {
    tft.fillCircle(p.x, p.y, 3, BLUE); // Draw a point where touched
  }
  delay(50); // Small delay for responsiveness
}
```

---

## ESP32 Usage

When using this library with an ESP32, you will need to specify the pins for the SD card and touchscreen in the constructor of the respective classes.

**Default SPI Pins for ESP32 (VSPI)**:
- **MOSI**: GPIO 23
- **MISO**: GPIO 19
- **SCK**: GPIO 18
- **SS/CS**: GPIO 5

Here is an example of how to instantiate the classes for an ESP32:

```cpp
#include <AloniesTFT.h>
#include <AloniesTFT_SD.h>
#include <AloniesTFT_Touch.h>

// TFT display object
AloniesTFT tft;

// SD card object with ESP32's default VSPI CS pin
AloniesTFT_SD sdCard(5); 

// Touchscreen object with example ESP32 pins
// Make sure to use ADC1 pins for YP and XM if you are using Wi-Fi
AloniesTFT_Touch touch(25, 32, 33, 26, 300);

void setup() {
  // Your setup code here
}

void loop() {
  // Your loop code here
}
```

---

## API

The `AloniesTFT` library provides several classes for different functionalities:

### `AloniesTFT` Class (Display Functions)
-   `void begin()`: Initializes the display.
-   `uint16_t getID()`: Reads the TFT display's ID.
-   `void setDebug(bool enabled)`: Enables or disables debug output.
-   ... (and all the drawing functions) ...

### `AloniesTFT_SD` Class (SD Card Functions)
-   `AloniesTFT_SD(uint8_t cs_pin)`: Constructor to specify the CS pin.
-   `bool begin()`: Initializes the SD card module.
-   `void setDebug(bool enabled)`: Enables or disables debug output.
-   `void listFilesInRoot()`: Lists all files and directories in the root.
-   `void readFile(const char* filename)`: Reads and prints file content.
-   `void writeFile(const char* filename, const char* content)`: Writes content to a file.

### `AloniesTFT_Touch` Class (Touchscreen Functions)
-   `AloniesTFT_Touch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rxplate)`: Constructor to specify touch pins.
-   `void setDebug(bool enabled)`: Enables or disables debug output.
-   `bool isTouching(int16_t minPressure = 10, int16_t maxPressure = 1000)`: Checks for touch within pressure thresholds.
-   `TSPoint getPoint()`: Gets raw touch data (`x`, `y`, `z`).
-   `TSPoint getCalibratedPoint(int16_t tftWidth, int16_t tftHeight, uint8_t rotation = 0)`: Gets calibrated touch data mapped to TFT coordinates.

---

## Examples

The library includes a variety of examples in the `Library Files/examples` directory. These are a great way to learn the different features of the library.

-   **CombinedDemo**: A demo showing various features.
-   **RainbowDemo**: A demo of different colors.
-   **ShapesDemo**: A demo of different shapes.
-   **TextDemo**: A demo of text rendering.
-   **AdvancedDemo**: A demo of the advanced drawing functions.
-   **KitchenSinkDemo**: A comprehensive demo showcasing all library features.
-   **SDCardDemo**: Demonstrates SD card initialization, file listing, reading, and writing.
-   **TouchDemo**: Shows how to read touch input and draw on the screen.

---

## Contributing

Contributions are welcome! If you have ideas for new features or improvements, feel free to fork the repository and submit a pull request.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.