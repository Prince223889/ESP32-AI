#include "ESP32AI.h"

bool ESP32AI::begin(size_t inputBytes) {
  return backend_ && inputBytes > 0 && backend_->begin(inputBytes);
}

size_t ESP32AI::infer(const uint8_t *input, size_t inputBytes,
                      ESP32AIResult *results, size_t resultCapacity) {
  if (!backend_ || !input || inputBytes == 0 || !results || resultCapacity == 0) return 0;
  return backend_->infer(input, inputBytes, results, resultCapacity);
}

uint8_t ESP32AI::rgb565ToGray(uint16_t px) {
  const uint8_t r = static_cast<uint8_t>(((px >> 11) & 0x1F) * 255u / 31u);
  const uint8_t g = static_cast<uint8_t>(((px >> 5) & 0x3F) * 255u / 63u);
  const uint8_t b = static_cast<uint8_t>((px & 0x1F) * 255u / 31u);
  return static_cast<uint8_t>((77u * r + 150u * g + 29u * b) >> 8);
}

bool ESP32AI::resizeRGB565ToGray(const uint8_t *src, uint32_t srcW, uint32_t srcH,
                                  uint8_t *dst, uint32_t dstW, uint32_t dstH) {
  if (!src || !dst || !srcW || !srcH || !dstW || !dstH) return false;
  for (uint32_t y = 0; y < dstH; ++y) {
    const uint32_t sy = static_cast<uint32_t>(static_cast<uint64_t>(y) * srcH / dstH);
    for (uint32_t x = 0; x < dstW; ++x) {
      const uint32_t sx = static_cast<uint32_t>(static_cast<uint64_t>(x) * srcW / dstW);
      const size_t si = (static_cast<size_t>(sy) * srcW + sx) * 2u;
      const uint16_t px = static_cast<uint16_t>(src[si]) | (static_cast<uint16_t>(src[si + 1]) << 8);
      dst[static_cast<size_t>(y) * dstW + x] = rgb565ToGray(px);
    }
  }
  return true;
}

bool ESP32AI::resizeRGB565ToRGB888(const uint8_t *src, uint32_t srcW, uint32_t srcH,
                                    uint8_t *dst, uint32_t dstW, uint32_t dstH) {
  if (!src || !dst || !srcW || !srcH || !dstW || !dstH) return false;
  for (uint32_t y = 0; y < dstH; ++y) {
    const uint32_t sy = static_cast<uint32_t>(static_cast<uint64_t>(y) * srcH / dstH);
    for (uint32_t x = 0; x < dstW; ++x) {
      const uint32_t sx = static_cast<uint32_t>(static_cast<uint64_t>(x) * srcW / dstW);
      const size_t si = (static_cast<size_t>(sy) * srcW + sx) * 2u;
      const uint16_t px = static_cast<uint16_t>(src[si]) | (static_cast<uint16_t>(src[si + 1]) << 8);
      const size_t di = (static_cast<size_t>(y) * dstW + x) * 3u;
      dst[di + 0] = static_cast<uint8_t>(((px >> 11) & 0x1F) * 255u / 31u);
      dst[di + 1] = static_cast<uint8_t>(((px >> 5) & 0x3F) * 255u / 63u);
      dst[di + 2] = static_cast<uint8_t>((px & 0x1F) * 255u / 31u);
    }
  }
  return true;
}

void ESP32AI::normalizeUint8ToFloat(const uint8_t *src, float *dst, size_t count) {
  if (!src || !dst) return;
  for (size_t i = 0; i < count; ++i) dst[i] = src[i] / 255.0f;
}

void ESP32AI::normalizeUint8ToInt8(const uint8_t *src, int8_t *dst, size_t count) {
  if (!src || !dst) return;
  for (size_t i = 0; i < count; ++i) {
    dst[i] = static_cast<int8_t>(static_cast<int>(src[i]) - 128);
  }
}

bool ESP32AI::topResult(const ESP32AIResult *results, size_t count, ESP32AIResult &out) {
  if (!results || count == 0) return false;
  size_t best = 0;
  for (size_t i = 1; i < count; ++i) {
    if (results[i].score > results[best].score) best = i;
  }
  out = results[best];
  return true;
}
