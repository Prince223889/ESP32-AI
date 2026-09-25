#pragma once
#include <Arduino.h>

struct ESP32AIResult {
  uint16_t classIndex = 0;
  float score = 0.0f;
  char label[48] = {};
};

class IESP32AIBackend {
public:
  virtual ~IESP32AIBackend() = default;
  virtual bool begin(size_t inputBytes) = 0;
  virtual size_t infer(const uint8_t *input, size_t inputBytes,
                       ESP32AIResult *results, size_t resultCapacity) = 0;
};

class ESP32AI {
public:
  explicit ESP32AI(IESP32AIBackend *backend = nullptr) : backend_(backend) {}
  void setBackend(IESP32AIBackend *backend) { backend_ = backend; }

  bool begin(size_t inputBytes) { return backend_ && backend_->begin(inputBytes); }
  size_t infer(const uint8_t *input, size_t inputBytes,
               ESP32AIResult *results, size_t resultCapacity) {
    return backend_ ? backend_->infer(input, inputBytes, results, resultCapacity) : 0;
  }

  static uint8_t rgb565ToGray(uint16_t px);
  static bool resizeRGB565ToGray(const uint8_t *src, uint32_t srcW, uint32_t srcH,
                                 uint8_t *dst, uint32_t dstW, uint32_t dstH);
  static void normalizeUint8ToFloat(const uint8_t *src, float *dst, size_t count);

private:
  IESP32AIBackend *backend_ = nullptr;
};
