#include <Arduino.h>
#include "AloniesTFT.h"

AloniesTFT tft;

void setup() {
    tft.begin();
    tft.showText("Hello TFT Library!");
}

void loop() {
    // Nothing to do here; static text
}
