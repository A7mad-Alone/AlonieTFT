#include "MyTFT.h"
#include <Arduino.h>
#include <string.h>


// ------------------ Constructor ------------------
MyTFT::MyTFT(uint16_t id, uint8_t rotation) : _id(id), _rotation(rotation) {}

// ------------------ Initialization ------------------
void MyTFT::begin() {
    tft.begin(_id);
    tft.setRotation(_rotation);
    tft.WriteCmdData(0x36, 0x08); // fix mirroring/orientation
    tft.fillScreen(BLACK);
}

// ------------------ ID ------------------
uint16_t MyTFT::getID() {
    return tft.readID();
}

// ------------------ Text ------------------
void MyTFT::drawCenteredText(const char* txt, uint16_t color, uint8_t size) {
    tft.setTextColor(color);
    tft.setTextSize(size);
    int16_t x = (tft.width() - (6 * size * strlen(txt))) / 2;
    int16_t y = (tft.height() - (8 * size)) / 2;
    tft.setCursor(x, y);
    tft.print(txt);
}

void MyTFT::showText(const char* txt, uint16_t color, uint8_t size) {
    tft.fillScreen(BLACK);
    drawCenteredText(txt, color, size);
}

void MyTFT::showMessage(const char* txt) {
    showText(txt); // simple alias
}

// ------------------ Rainbow ------------------
void MyTFT::showRainbow() {
    uint16_t colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA, WHITE};
    for (uint8_t i = 0; i < sizeof(colors)/sizeof(colors[0]); i++) {
        tft.fillScreen(colors[i]);
        drawCenteredText("Hello World!", BLACK, 2);
        delay(500);
    }
}

// ------------------ Shapes ------------------
void MyTFT::drawTestLines(uint16_t color) {
    int w = tft.width(), h = tft.height();
    tft.fillScreen(BLACK);
    for (int x2 = 0; x2 < w; x2 += 6) tft.drawLine(0, 0, x2, h - 1, color);
    for (int y2 = 0; y2 < h; y2 += 6) tft.drawLine(0, 0, w - 1, y2, color);
}

void MyTFT::drawTestRects(uint16_t color) {
    tft.fillScreen(BLACK);
    int cx = tft.width() / 2;
    int cy = tft.height() / 2;
    int n = min(tft.width(), tft.height());
    for (int i = 2; i < n; i += 6) {
        int i2 = i / 2;
        tft.drawRect(cx - i2, cy - i2, i, i, color);
    }
}

void MyTFT::drawFilledRects(uint16_t color1, uint16_t color2) {
    tft.fillScreen(BLACK);
    int cx = tft.width() / 2 - 1;
    int cy = tft.height() / 2 - 1;
    int n = min(tft.width(), tft.height());
    for (int i = n; i > 0; i -= 6) {
        int i2 = i / 2;
        tft.fillRect(cx - i2, cy - i2, i, i, color1);
        tft.drawRect(cx - i2, cy - i2, i, i, color2);
    }
}

void MyTFT::drawCirclesTest(uint16_t color) {
    tft.fillScreen(BLACK);
    int radius = 10;
    int w = tft.width(), h = tft.height();
    int r2 = radius * 2;
    for (int x = radius; x < w; x += r2) {
        for (int y = radius; y < h; y += r2) {
            tft.fillCircle(x, y, radius, color);
        }
    }
}

void MyTFT::drawTrianglesTest(uint16_t color) {
    tft.fillScreen(BLACK);
    int cx = tft.width() / 2;
    int cy = tft.height() / 2;
    int n = min(cx, cy);
    for (int i = 0; i < n; i += 10) {
        tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, color);
    }
}

void MyTFT::showShapes() {
    drawTestLines(CYAN);
    delay(500);
    drawTestRects(RED);
    delay(500);
    drawFilledRects(GREEN, WHITE);
    delay(500);
    drawCirclesTest(MAGENTA);
    delay(500);
    drawTrianglesTest(YELLOW);
    delay(500);
}
