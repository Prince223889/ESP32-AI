#include "ESP32AI.h"

uint8_t ESP32AI::rgb565ToGray(uint16_t px) {
  uint8_t r = (uint8_t)(((px >> 11) & 0x1F) * 255 / 31);
  uint8_t g = (uint8_t)(((px >> 5) & 0x3F) * 255 / 63);
  uint8_t b = (uint8_t)((px & 0x1F) * 255 / 31);
  return (uint8_t)((77u*r + 150u*g + 29u*b) >> 8);
}

bool ESP32AI::resizeRGB565ToGray(const uint8_t *src, uint32_t srcW, uint32_t srcH,
                                  uint8_t *dst, uint32_t dstW, uint32_t dstH) {
  if (!src || !dst || !srcW || !srcH || !dstW || !dstH) return false;
  for (uint32_t y=0; y<dstH; ++y) {
    uint32_t sy = (uint32_t)((uint64_t)y * srcH / dstH);
    for (uint32_t x=0; x<dstW; ++x) {
      uint32_t sx = (uint32_t)((uint64_t)x * srcW / dstW);
      size_t si = ((size_t)sy * srcW + sx) * 2u;
      uint16_t px = (uint16_t)src[si] | ((uint16_t)src[si+1] << 8);
      dst[(size_t)y * dstW + x] = rgb565ToGray(px);
    }
  }
  return true;
}

void ESP32AI::normalizeUint8ToFloat(const uint8_t *src, float *dst, size_t count) {
  if (!src || !dst) return;
  for (size_t i=0; i<count; ++i) dst[i] = src[i] / 255.0f;
}
