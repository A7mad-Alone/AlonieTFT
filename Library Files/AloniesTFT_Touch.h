#ifndef ALONIESTFT_TOUCH_H
#define ALONIESTFT_TOUCH_H

#include <Arduino.h>
#include <TouchScreen.h>

#define DEBUG_PRINTLN(x) do { if (_debug_enabled) { Serial.println(x); } } while (0)

// Define the touchscreen pins based on the provided examples
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

// Touch sensitivity calibration values from the provided examples
#define TS_MINX 124
#define TS_MAXX 906
#define TS_MINY 83
#define TS_MAXY 893

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
#define RX_PLATE 300

class AloniesTFT_Touch {
public:
    /**
     * @brief Construct a new AloniesTFT_Touch object with specific pins.
     * @param xp The X+ pin.
     * @param yp The Y+ pin.
     * @param xm The X- pin.
     * @param ym The Y- pin.
     * @param rxplate The resistance of the screen.
     */
    AloniesTFT_Touch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rxplate);

    /**
     * @brief Construct a new AloniesTFT_Touch object with default pins.
     */
    AloniesTFT_Touch();

    /**
     * @brief Enables or disables debug mode.
     * @param enabled Set to true to enable debug output to Serial.
     */
    void setDebug(bool enabled);

    /**
     * @brief Checks if the touchscreen is currently being pressed.
     * @param minPressure Minimum pressure threshold for a valid touch.
     * @param maxPressure Maximum pressure threshold for a valid touch.
     * @return True if the screen is being touched within the pressure thresholds, false otherwise.
     */
    bool isTouching(int16_t minPressure = 10, int16_t maxPressure = 1000);

    /**
     * @brief Gets the raw touch point data from the touchscreen.
     * @return A TSPoint object containing raw x, y, and z (pressure) values.
     */
    TSPoint getPoint();

    /**
     * @brief Gets the calibrated touch point data, mapped to TFT coordinates.
     * @param tftWidth The width of the TFT display.
     * @param tftHeight The height of the TFT display.
     * @param rotation The current rotation of the TFT display (0-3).
     * @return A TSPoint object with calibrated x, y, and raw z (pressure) values.
     */
    TSPoint getCalibratedPoint(int16_t tftWidth, int16_t tftHeight, uint8_t rotation = 0);

private:
    bool _debug_enabled = false;
    uint8_t _xp, _yp, _xm, _ym;
    uint16_t _rxplate;
    TouchScreen* ts;
};

#endif // ALONIESTFT_TOUCH_H
