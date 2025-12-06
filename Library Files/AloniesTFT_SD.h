#ifndef ALONIESTFT_SD_H
#define ALONIESTFT_SD_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define DEBUG_PRINTLN(x) do { if (_debug_enabled) { Serial.println(x); } } while (0)

// Define the Chip Select pin for the SD card
// Based on the provided examples, pin 10 is used for Arduino Uno/Mega.
#define SD_CS_PIN 10

class AloniesTFT_SD {
public:
    /**
     * @brief Construct a new AloniesTFT_SD object with a specific CS pin.
     * @param cs_pin The Chip Select pin for the SD card.
     */
    AloniesTFT_SD(uint8_t cs_pin);
    
    /**
     * @brief Construct a new AloniesTFT_SD object with the default CS pin (10).
     */
    AloniesTFT_SD();

    /**
     * @brief Initializes the SD card module.
     * @return True if initialization is successful, false otherwise.
     */
    bool begin();

    /**
     * @brief Enables or disables debug mode.
     * @param enabled Set to true to enable debug output to Serial.
     */
    void setDebug(bool enabled);

    /**
     * @brief Lists all files and directories in the root of the SD card.
     */
    void listFilesInRoot();

    /**
     * @brief Reads the content of a specified file and prints it to Serial.
     * @param filename The name of the file to read.
     */
    void readFile(const char* filename);

    /**
     * @brief Writes content to a specified file on the SD card.
     *        If the file does not exist, it will be created.
     *        If the file exists, its content will be overwritten.
     * @param filename The name of the file to write to.
     * @param content The string content to write into the file.
     */
    void writeFile(const char* filename, const char* content);

private:
    bool _debug_enabled = false;
    uint8_t _cs_pin;
    bool _card_initialized = false;
};

#endif // ALONIESTFT_SD_H
