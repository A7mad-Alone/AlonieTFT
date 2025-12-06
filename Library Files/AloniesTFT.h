#ifndef ALONIESTFT_H
#define ALONIESTFT_H

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

#define DEBUG_PRINTLN(x) do { if (_debug_enabled) { Serial.println(x); } } while (0)

class AloniesTFT {
  public:
    /**
     * @brief Construct a new AloniesTFT object
     * @param id The ID of the TFT display. Default is 0x9341.
     * @param rotation The rotation of the screen. Default is 0.
     */
    AloniesTFT(uint16_t id = 0x9341, uint8_t rotation = 0);

    /**
     * @brief Initializes the TFT display.
     */
    void begin();

    /**
     * @brief Reads the TFT display's ID.
     * @return The ID of the TFT display.
     */
    uint16_t getID();

    /**
     * @brief Enables or disables debug mode.
     * @param enabled Set to true to enable debug output to Serial.
     */
    void setDebug(bool enabled);

    /**
     * @brief Gets the current screen rotation.
     * @return The current rotation value (0-3).
     */
    uint8_t Get_Rotation();

    // Super simple plug-and-play functions
    /**
     * @brief Displays centered text on the screen.
     * @param txt The text to display.
     * @param color The color of the text. Default is YELLOW.
     * @param size The size of the text. Default is 2.
     */
    void showText(const char* txt, uint16_t color = 0xFFE0, uint8_t size = 2);

    /**
     * @brief Displays a rainbow pattern on the screen.
     */
    void showRainbow();

    /**
     * @brief Displays a sequence of shapes on the screen.
     */
    void showShapes();

    /**
     * @brief Alias for showText.
     * @param txt The text to display.
     */
    void showMessage(const char* txt);

    // Drawing Functions
    /**
     * @brief Clears the screen to black.
     */
    void clearScreen();

    /**
     * @brief Draws text at a specific location.
     * @param x The x-coordinate of the top-left corner.
     * @param y The y-coordinate of the top-left corner.
     * @param text The text to draw.
     * @param color The color of the text.
     * @param size The size of the text.
     */
    void drawText(int16_t x, int16_t y, const char* text, uint16_t color, uint8_t size);

    /**
     * @brief Sets the font for the text.
     * @param f A pointer to the GFXfont object.
     */
    void setFont(const GFXfont *f = NULL);

    /**
     * @brief Draws a line between two points.
     * @param x0 The x-coordinate of the first point.
     * @param y0 The y-coordinate of the first point.
     * @param x1 The x-coordinate of the second point.
     * @param y1 The y-coordinate of the second point.
     * @param color The color of the line.
     */
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

    /**
     * @brief Draws a rectangle outline.
     * @param x The x-coordinate of the top-left corner.
     * @param y The y-coordinate of the top-left corner.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     * @param color The color of the rectangle.
     */
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

    /**
     * @brief Draws a filled rectangle.
     * @param x The x-coordinate of the top-left corner.
     * @param y The y-coordinate of the top-left corner.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     * @param color The color of the rectangle.
     */
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

    /**
     * @brief Draws a rounded rectangle outline.
     * @param x The x-coordinate of the top-left corner.
     * @param y The y-coordinate of the top-left corner.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     * @param r The corner radius.
     * @param color The color of the rectangle.
     */
    void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);

    /**
     * @brief Draws a filled rounded rectangle.
     * @param x The x-coordinate of the top-left corner.
     * @param y The y-coordinate of the top-left corner.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     * @param r The corner radius.
     * @param color The color of the rectangle.
     */
    void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);

    /**
     * @brief Draws a monochrome bitmap.
     * @param x The x-coordinate of the top-left corner.
     * @param y The y-coordinate of the top-left corner.
     * @param bitmap A pointer to the bitmap data.
     * @param w The width of the bitmap.
     * @param h The height of the bitmap.
     * @param color The color of the bitmap.
     */
    void drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);

    /**
     * @brief Draws a circle outline.
     * @param x0 The x-coordinate of the center.
     * @param y0 The y-coordinate of the center.
     * @param r The radius of the circle.
     * @param color The color of the circle.
     */
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

    /**
     * @brief Draws a filled circle.
     * @param x0 The x-coordinate of the center.
     * @param y0 The y-coordinate of the center.
     * @param r The radius of the circle.
     * @param color The color of the circle.
     */
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

    /**
     * @brief Draws a triangle outline.
     * @param x0 The x-coordinate of the first point.
     * @param y0 The y-coordinate of the first point.
     * @param x1 The x-coordinate of the second point.
     * @param y1 The y-coordinate of the second point.
     * @param x2 The x-coordinate of the third point.
     * @param y2 The y-coordinate of the third point.
     * @param color The color of the triangle.
     */
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

    /**
     * @brief Draws a filled triangle.
     * @param x0 The x-coordinate of the first point.
     * @param y0 The y-coordinate of the first point.
     * @param x1 The x-coordinate of the second point.
     * @param y1 The y-coordinate of the second point.
     * @param x2 The x-coordinate of the third point.
     * @param y2 The y-coordinate of the third point.
     * @param color The color of the triangle.
     */
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

    /**
     * @brief Draws a single pixel.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param color The color of the pixel.
     */
    void drawPixel(int16_t x, int16_t y, uint16_t color);

    // Screen Dimensions
    /**
     * @brief Gets the width of the screen.
     * @return The width of the screen in pixels.
     */
    int16_t width();

    /**
     * @brief Gets the height of the screen.
     * @return The height of the screen in pixels.
     */
    int16_t height();

  private:
    MCUFRIEND_kbv tft;
    uint16_t _id;
    uint8_t _rotation;
    bool _debug_enabled = false;

    // Internal helpers
    void drawCenteredText(const char* txt, uint16_t color, uint8_t size);
    void drawTestLines(uint16_t color);
    void drawTestRects(uint16_t color);
    void drawFilledRects(uint16_t color1, uint16_t color2);
    void drawCirclesTest(uint16_t color);
    void drawTrianglesTest(uint16_t color);
};

#endif
