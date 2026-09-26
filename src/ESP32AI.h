#pragma once
#include <Arduino.h>

/** Result item returned by a user-supplied AI backend. */
/** Result item returned by a user-supplied AI backend. */
struct ESP32AIResult {
  uint16_t classIndex = 0;
  float score = 0.0f;
  char label[48] = {};
};

/** Backend contract implemented by the application/runtime adapter. */
/** Backend contract implemented by the application/runtime adapter. */
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

  /** Set a user-owned backend implementation; the library does not own it. */
  void setBackend(IESP32AIBackend *backend) { backend_ = backend; }
  bool hasBackend() const { return backend_ != nullptr; }

  /** Initialize the selected backend for an expected input size in bytes. */
  /** Initialize the selected backend for an expected input size in bytes. */
  bool begin(size_t inputBytes);
  /** Run the selected backend and fill caller-owned result storage. */
  /** Run the selected backend and fill caller-owned result storage. */
  size_t infer(const uint8_t *input, size_t inputBytes,
               ESP32AIResult *results, size_t resultCapacity);

  /** Convert one RGB565 pixel to 8-bit grayscale. */
  static uint8_t rgb565ToGray(uint16_t px);
  static bool resizeRGB565ToGray(const uint8_t *src, uint32_t srcW, uint32_t srcH,
                                 uint8_t *dst, uint32_t dstW, uint32_t dstH);
  static bool resizeRGB565ToRGB888(const uint8_t *src, uint32_t srcW, uint32_t srcH,
                                   uint8_t *dst, uint32_t dstW, uint32_t dstH);
  static void normalizeUint8ToFloat(const uint8_t *src, float *dst, size_t count);
  static void normalizeUint8ToInt8(const uint8_t *src, int8_t *dst, size_t count);
  static bool topResult(const ESP32AIResult *results, size_t count, ESP32AIResult &out);

private:
  IESP32AIBackend *backend_ = nullptr;
};
