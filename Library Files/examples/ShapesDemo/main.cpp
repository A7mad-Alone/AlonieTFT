#include <Arduino.h>
#include "AloniesTFT.h"

AloniesTFT tft;

void setup() {
    tft.begin();
}

void loop() {
    // Draw all shapes
    tft.showShapes();
    delay(2000);
}
