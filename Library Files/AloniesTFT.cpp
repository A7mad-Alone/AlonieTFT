#include "AloniesTFT.h"
#include <Arduino.h>
#include <string.h>


// ------------------ Constructor ------------------
AloniesTFT::AloniesTFT(uint16_t id, uint8_t rotation) : _id(id), _rotation(rotation) {}

// ------------------ Initialization ------------------
void AloniesTFT::begin() {
    DEBUG_PRINTLN("Initializing TFT...");
    tft.begin(_id);
    tft.setRotation(_rotation);
    tft.WriteCmdData(0x36, 0x08); // fix mirroring/orientation
    tft.fillScreen(BLACK);
}

// ------------------ ID ------------------
uint16_t AloniesTFT::getID() {
    DEBUG_PRINTLN("Getting TFT ID");
    return tft.readID();
}

void AloniesTFT::setDebug(bool enabled) {
    _debug_enabled = enabled;
}

uint8_t AloniesTFT::Get_Rotation() {
    return tft.getRotation();
}

// ------------------ Text ------------------
void AloniesTFT::drawCenteredText(const char* txt, uint16_t color, uint8_t size) {
    tft.setTextColor(color);
    tft.setTextSize(size);
    int16_t x = (tft.width() - (6 * size * strlen(txt))) / 2;
    int16_t y = (tft.height() - (8 * size)) / 2;
    tft.setCursor(x, y);
    tft.print(txt);
}

void AloniesTFT::showText(const char* txt, uint16_t color, uint8_t size) {
    tft.fillScreen(BLACK);
    drawCenteredText(txt, color, size);
}

void AloniesTFT::showMessage(const char* txt) {
    showText(txt); // simple alias
}

// ------------------ Rainbow ------------------
void AloniesTFT::showRainbow() {
    uint16_t colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA, WHITE};
    for (uint8_t i = 0; i < sizeof(colors)/sizeof(colors[0]); i++) {
        tft.fillScreen(colors[i]);
        drawCenteredText("Hello World!", BLACK, 2);
        delay(500);
    }
}

// ------------------ Shapes ------------------
void AloniesTFT::drawTestLines(uint16_t color) {
    int w = tft.width(), h = tft.height();
    tft.fillScreen(BLACK);
    for (int x2 = 0; x2 < w; x2 += 6) tft.drawLine(0, 0, x2, h - 1, color);
    for (int y2 = 0; y2 < h; y2 += 6) tft.drawLine(0, 0, w - 1, y2, color);
}

void AloniesTFT::drawTestRects(uint16_t color) {
    tft.fillScreen(BLACK);
    int cx = tft.width() / 2;
    int cy = tft.height() / 2;
    int n = min(tft.width(), tft.height());
    for (int i = 2; i < n; i += 6) {
        int i2 = i / 2;
        tft.drawRect(cx - i2, cy - i2, i, i, color);
    }
}

void AloniesTFT::drawFilledRects(uint16_t color1, uint16_t color2) {
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

void AloniesTFT::drawCirclesTest(uint16_t color) {
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

void AloniesTFT::drawTrianglesTest(uint16_t color) {
    tft.fillScreen(BLACK);
    int cx = tft.width() / 2;
    int cy = tft.height() / 2;
    int n = min(cx, cy);
    for (int i = 0; i < n; i += 10) {
        tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, color);
    }
}

void AloniesTFT::showShapes() {
    drawTestLines(CYAN);
    delay(500);
    drawTestRects(RED);
    delay(500);
    drawFilledRects(GREEN, WHITE);
    delay(500);
    drawCirclesTest(MAGENTA);
    delay(500);
    drawTrianglesTest(YELLOW);
}

// ------------------ Drawing Functions ------------------
void AloniesTFT::clearScreen() {
    DEBUG_PRINTLN("Clearing screen");
    tft.fillScreen(BLACK);
}

void AloniesTFT::drawText(int16_t x, int16_t y, const char* text, uint16_t color, uint8_t size) {
    DEBUG_PRINTLN("Drawing text");
    tft.setCursor(x, y);
    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.print(text);
}

void AloniesTFT::setFont(const GFXfont *f) {
    DEBUG_PRINTLN("Setting font");
    tft.setFont(f);
}

void AloniesTFT::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    DEBUG_PRINTLN("Drawing line");
    tft.drawLine(x0, y0, x1, y1, color);
}

void AloniesTFT::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    DEBUG_PRINTLN("Drawing rectangle");
    tft.drawRect(x, y, w, h, color);
}

void AloniesTFT::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    DEBUG_PRINTLN("Drawing filled rectangle");
    tft.fillRect(x, y, w, h, color);
}

void AloniesTFT::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
    DEBUG_PRINTLN("Drawing rounded rectangle");
    tft.drawRoundRect(x, y, w, h, r, color);
}

void AloniesTFT::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
    DEBUG_PRINTLN("Drawing filled rounded rectangle");
    tft.fillRoundRect(x, y, w, h, r, color);
}

void AloniesTFT::drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    DEBUG_PRINTLN("Drawing XBitmap");
    tft.drawXBitmap(x, y, bitmap, w, h, color);
}

void AloniesTFT::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    DEBUG_PRINTLN("Drawing circle");
    tft.drawCircle(x0, y0, r, color);
}

void AloniesTFT::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    DEBUG_PRINTLN("Drawing filled circle");
    tft.fillCircle(x0, y0, r, color);
}

void AloniesTFT::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    DEBUG_PRINTLN("Drawing triangle");
    tft.drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

void AloniesTFT::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    DEBUG_PRINTLN("Drawing filled triangle");
    tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

int16_t AloniesTFT::width() {
    return tft.width();
}

int16_t AloniesTFT::height() {
    return tft.height();
}

void AloniesTFT::drawPixel(int16_t x, int16_t y, uint16_t color) {
    DEBUG_PRINTLN("Drawing pixel");
    tft.drawPixel(x, y, color);
}
