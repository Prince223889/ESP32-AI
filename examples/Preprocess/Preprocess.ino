#include <ESP32AI.h>

void setup() {
  Serial.begin(115200);
  delay(300);

  uint8_t src[2 * 4 * 4] = {};
  uint8_t gray[2 * 2] = {};
  float normalized[4] = {};

  Serial.println("ESP32-AI preprocessing example");
  Serial.println(ESP32AI::resizeRGB565ToGray(src, 4, 4, gray, 2, 2) ? "resize: OK" : "resize: FAIL");
  ESP32AI::normalizeUint8ToFloat(gray, normalized, 4);
  Serial.printf("first normalized value: %.3f\n", normalized[0]);
}

void loop() { delay(5000); }
