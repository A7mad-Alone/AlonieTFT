#ifndef MYTFT_H
#define MYTFT_H

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

// Color definitions
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

class MyTFT {
  public:
    MyTFT(uint16_t id = 0x9341, uint8_t rotation = 0);

    void begin();  // initialize TFT
    uint16_t getID(); // read TFT ID

    // Super simple plug-and-play functions
    void showText(const char* txt, uint16_t color = 0xFFE0, uint8_t size = 2); // yellow default
    void showRainbow();
    void showShapes();
    void showMessage(const char* txt); // alias for showText

  private:
    MCUFRIEND_kbv tft;
    uint16_t _id;
    uint8_t _rotation;

    // Internal helpers
    void drawCenteredText(const char* txt, uint16_t color, uint8_t size);
    void drawTestLines(uint16_t color);
    void drawTestRects(uint16_t color);
    void drawFilledRects(uint16_t color1, uint16_t color2);
    void drawCirclesTest(uint16_t color);
    void drawTrianglesTest(uint16_t color);
};

#endif
