# ESP32-AI

A small backend-neutral AI adapter layer for ESP32 projects. It does **not** replace TensorFlow Lite Micro, ESP-DL or Edge Impulse. Instead it standardizes the part that repeatedly appears between a camera and an inference engine: image conversion, resizing and backend dispatch.

## Why this design

Current ESP32-P4 projects already have mature runtimes such as Espressif's `esp-tflite-micro` and `esp-dl`. Copying another runtime into an Arduino library would create a large, fragile dependency. This library stays lightweight and lets an application provide its own backend.

## Pipeline

```text
Camera RGB565
    -> resizeRGB565ToGray()/your own preprocessor
    -> model input
    -> IESP32AIBackend::infer()
    -> ESP32AIResult[]
```

## Example backend shape

```cpp
class MyBackend : public IESP32AIBackend {
  bool begin(size_t inputBytes) override { /* load model */ return true; }
  size_t infer(const uint8_t *input, size_t bytes,
               ESP32AIResult *results, size_t cap) override {
    /* call your chosen runtime */
    return 0;
  }
};
```

This makes the same application architecture usable with Edge Impulse SDK output, TFLite Micro or ESP-DL without forcing any one vendor into the library.
