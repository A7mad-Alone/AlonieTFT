#include <AloniesTFT.h>
#include <AloniesTFT_SD.h>
#include <AloniesTFT_Touch.h>
#include <Adafruit_GFX.h> // needed for GFXfont

AloniesTFT tft;
AloniesTFT_SD sdCard;
AloniesTFT_Touch touch;

void setup() {
    Serial.begin(9600);
    tft.setDebug(true);
    sdCard.setDebug(true);
    touch.setDebug(true);

    tft.begin();
    tft.clearScreen();
    
    // Get screen dimensions
    int16_t width = tft.width();
    int16_t height = tft.height();

    // --- Text ---
    tft.drawText(10, 10, "Kitchen Sink Demo", WHITE, 2);
    tft.drawText(10, 30, "Default Font", YELLOW, 1);

    // --- Shapes ---
    // Rectangles
    tft.drawRect(10, 80, 50, 30, RED);
    tft.fillRect(70, 80, 50, 30, RED);
    
    // Rounded Rectangles
    tft.drawRoundRect(10, 120, 50, 30, 5, BLUE);
    tft.fillRoundRect(70, 120, 50, 30, 5, BLUE);

    // Circles
    tft.drawCircle(35, 170, 15, MAGENTA);
    tft.fillCircle(95, 170, 15, MAGENTA);

    // Triangles
    tft.drawTriangle(10, 200, 35, 230, 60, 200, CYAN);
    tft.fillTriangle(70, 200, 95, 230, 120, 200, CYAN);

    // Lines
    tft.drawLine(150, 80, 200, 110, GREEN);
    
    tft.drawText(10, height - 20, "Demo Complete!", WHITE, 1);
}

void loop() {
    // Nothing to do here
}
