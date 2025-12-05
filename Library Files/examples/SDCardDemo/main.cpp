#include <AloniesTFT.h>
#include <AloniesTFT_SD.h>

AloniesTFT tft;
// For ESP32, the default VSPI CS pin is 5. Change this to match your wiring.
AloniesTFT_SD sdCard(5);

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.clearScreen();
  tft.drawText(10, 10, "SD Card Demo", WHITE, 2);

  // Initialize SD Card
  if (!sdCard.begin()) {
    tft.drawText(10, 40, "SD Init Failed!", RED, 1);
    while (true); // Halt if SD card fails
  }
  tft.drawText(10, 40, "SD Init OK!", GREEN, 1);

  // Write a test file
  sdCard.writeFile("test.txt", "Hello from AloniesTFT_SD!");
  
  // List files
  sdCard.listFilesInRoot();

  // Read the test file
  sdCard.readFile("test.txt");

  tft.drawText(10, 60, "Check Serial Monitor", YELLOW, 1);
}

void loop() {
  // Nothing to do here
}
