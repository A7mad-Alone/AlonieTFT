#include <Arduino.h>
#include "AloniesTFT.h"

AloniesTFT tft;

void setup() {
    tft.begin();
    tft.showText("Graphics Playground");
    delay(1500);
}

void loop() {
    tft.showRainbow();
    delay(1000);

    tft.showShapes();
    delay(2000);

    tft.showText("TFT Demo Complete!");
    delay(1500);
}
