#include <Arduino.h>
#include "AloniesTFT.h"

AloniesTFT tft;

void setup() {
    tft.begin();
}

void loop() {
    // Rainbow animation
    tft.showRainbow();
    delay(1000);
}
