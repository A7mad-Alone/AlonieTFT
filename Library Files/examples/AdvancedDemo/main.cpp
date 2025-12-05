#include <AloniesTFT.h>

AloniesTFT myTFT;

void setup() {
  myTFT.begin();
  myTFT.clearScreen();

  // Use the new high-level drawing functions
  myTFT.drawText(10, 10, "Advanced Demo", WHITE, 2);
  
  myTFT.drawRect(10, 40, 100, 50, RED);
  myTFT.drawLine(10, 100, 110, 100, BLUE);

  myTFT.drawText(10, 120, "Using the new AloniesTFT API!", GREEN, 1);
}

void loop() {
  // Nothing to do here
}
