#include "AloniesTFT_SD.h"
#include <SPI.h>
#include <SD.h>

AloniesTFT_SD::AloniesTFT_SD(uint8_t cs_pin) {
    _cs_pin = cs_pin;
}

AloniesTFT_SD::AloniesTFT_SD() {
    _cs_pin = 10; // Default CS pin
}

void AloniesTFT_SD::setDebug(bool enabled) {
    _debug_enabled = enabled;
}

bool AloniesTFT_SD::begin() {
    DEBUG_PRINTLN("Initializing SD card...");
    pinMode(_cs_pin, OUTPUT);

    _card_initialized = SD.begin(_cs_pin);
    if (!_card_initialized) {
        DEBUG_PRINTLN("SD Card initialization failed!");
        return false;
    }
    DEBUG_PRINTLN("SD Card initialized.");
    return true;
}

void AloniesTFT_SD::listFilesInRoot() {
    DEBUG_PRINTLN("Listing files in root directory...");
    if (!_card_initialized) {
        DEBUG_PRINTLN("SD Card not initialized. Cannot list files.");
        return;
    }

    File root = SD.open("/");
    if (!root) {
        DEBUG_PRINTLN("Failed to open root directory.");
        return;
    }

    DEBUG_PRINTLN("Files on SD Card:");
    while (true) {
        File entry = root.openNextFile();
        if (!entry) {
            break;
        }
        if (entry.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(entry.name());
        } else {
            Serial.print("  FILE: ");
            Serial.print(entry.name());
            Serial.print("\tSIZE: ");
            Serial.println(entry.size());
        }
        entry.close();
    }
    root.close();
}

void AloniesTFT_SD::readFile(const char* filename) {
    DEBUG_PRINTLN("Reading file...");
    if (!_card_initialized) {
        DEBUG_PRINTLN("SD Card not initialized. Cannot read file.");
        return;
    }

    File dataFile = SD.open(filename);
    if (dataFile) {
        Serial.print("Content of ");
        Serial.print(filename);
        Serial.println(":");
        while (dataFile.available()) {
            Serial.write(dataFile.read());
        }
        dataFile.close();
        Serial.println("\n--- End of file ---");
    } else {
        Serial.print("Error opening ");
        Serial.println(filename);
    }
}

void AloniesTFT_SD::writeFile(const char* filename, const char* content) {
    DEBUG_PRINTLN("Writing to file...");
    if (!_card_initialized) {
        DEBUG_PRINTLN("SD Card not initialized. Cannot write file.");
        return;
    }

    File dataFile = SD.open(filename, FILE_WRITE);
    if (dataFile) {
        dataFile.println(content);
        dataFile.close();
        Serial.print("Successfully wrote to ");
        Serial.println(filename);
    } else {
        Serial.print("Error writing to ");
        Serial.println(filename);
    }
}
