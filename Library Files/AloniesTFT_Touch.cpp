#include "AloniesTFT_Touch.h"

AloniesTFT_Touch::AloniesTFT_Touch(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rxplate) {
    _xp = xp;
    _yp = yp;
    _xm = xm;
    _ym = ym;
    _rxplate = rxplate;
    ts = new TouchScreen(_xp, _yp, _xm, _ym, _rxplate);
}

void AloniesTFT_Touch::setDebug(bool enabled) {
    _debug_enabled = enabled;
}

bool AloniesTFT_Touch::isTouching(int16_t minPressure, int16_t maxPressure) {
    DEBUG_PRINTLN("Checking for touch...");
    TSPoint p = ts->getPoint();
    bool touched = (p.z > minPressure && p.z < maxPressure);
    if(touched) {
        DEBUG_PRINTLN("Touch detected.");
    }
    return touched;
}

TSPoint AloniesTFT_Touch::getPoint() {
    DEBUG_PRINTLN("Getting raw touch point...");
    return ts->getPoint();
}

TSPoint AloniesTFT_Touch::getCalibratedPoint(int16_t tftWidth, int16_t tftHeight, uint8_t rotation) {
    DEBUG_PRINTLN("Getting calibrated touch point...");
    TSPoint p = ts->getPoint();

    // if pressure is invalid, return an invalid point (z=0)
    if (p.z < 10 || p.z > 1000) {
        return TSPoint(0, 0, 0);
    }

    DEBUG_PRINTLN("Raw point: X=" + String(p.x) + " Y=" + String(p.y) + " Z=" + String(p.z));

    // Apply calibration and map to screen dimensions
    int16_t x = 0, y = 0;

    // Use the hardcoded calibration values for now
    // In a real application, these should be calibrated
    #define TS_MINX 124
    #define TS_MAXX 906
    #define TS_MINY 83
    #define TS_MAXY 893

    switch (rotation) {
        case 0: // Portrait
        case 2: // Portrait inverted
            x = map(p.x, TS_MINX, TS_MAXX, 0, tftWidth);
            y = map(p.y, TS_MINY, TS_MAXY, 0, tftHeight);
            break;
        case 1: // Landscape
        case 3: // Landscape inverted
            x = map(p.y, TS_MINY, TS_MAXY, 0, tftWidth);
            y = map(p.x, TS_MINX, TS_MAXX, 0, tftHeight);
            break;
    }

    // Ensure coordinates are within bounds
    x = constrain(x, 0, tftWidth - 1);
    y = constrain(y, 0, tftHeight - 1);

    DEBUG_PRINTLN("Calibrated point: X=" + String(x) + " Y=" + String(y));

    return TSPoint(x, y, p.z);
}
