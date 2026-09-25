#include <ESP32AI.h>

uint8_t source[16] = {
  0x00,0xF8, 0x00,0xF8, 0xE0,0x07, 0xE0,0x07,
  0x1F,0x00, 0x1F,0x00, 0xFF,0xFF, 0xFF,0xFF
};
uint8_t gray[4];

void setup() {
  Serial.begin(115200);
  if (!ESP32AI::resizeRGB565ToGray(source, 4, 2, gray, 2, 2)) return;
  Serial.printf("gray=%u,%u,%u,%u\n", gray[0],gray[1],gray[2],gray[3]);
  Serial.println("Next step: connect an Edge Impulse, TFLite Micro or ESP-DL backend through IESP32AIBackend.");
}
void loop() {}
