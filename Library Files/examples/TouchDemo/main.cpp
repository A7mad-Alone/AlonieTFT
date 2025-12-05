#include <AloniesTFT.h>
#include <AloniesTFT_Touch.h>

AloniesTFT tft;

// For ESP32, you need to use ADC1 pins for analog input when using Wi-Fi.
// These are example pins, please change to match your wiring:
// XP=25, YP=32(ADC1_CH4), XM=33(ADC1_CH5), YM=26
AloniesTFT_Touch touch(25, 32, 33, 26, 300);

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.clearScreen();
  tft.drawText(10, 10, "Touch Demo", WHITE, 2);
  tft.drawText(10, 30, "Touch the screen!", YELLOW, 1);
}

void loop() {
  TSPoint p = touch.getPoint();

  // Only if pressure is detected
  if (p.z > 10 && p.z < 1000) {
    // Calibrate the point to TFT coordinates
    TSPoint calibratedP = touch.getCalibratedPoint(tft.width(), tft.height(), tft.Get_Rotation());

    // Draw a small circle at the touched location
    tft.fillCircle(calibratedP.x, calibratedP.y, 2, CYAN);

    // Print raw and calibrated data to Serial Monitor
    Serial.print("Raw X = "); Serial.print(p.x);
    Serial.print("\tRaw Y = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.print(p.z);
    Serial.print("\tCalibrated X = "); Serial.print(calibratedP.x);
    Serial.print("\tCalibrated Y = "); Serial.println(calibratedP.y);
  }
  delay(20); // Small delay to prevent too many readings
}

