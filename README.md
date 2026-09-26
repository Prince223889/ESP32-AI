# ESP32-AI

Repository: https://github.com/Prince223889/ESP32-AI

Small backend-neutral preprocessing and inference adapter for Arduino-ESP32.

## Why this library does not ship an AI runtime

Espressif already provides substantial runtimes such as TensorFlow Lite Micro and ESP-DL. Repacking those runtimes inside a tiny Arduino library would create large and fragile dependencies. `ESP32-AI` therefore provides the glue layer instead:

```text
camera/frame buffer
      ↓
resize / grayscale / RGB conversion
      ↓
normalization
      ↓
user-selected AI backend
      ↓
ESP32AIResult[]
```

## Included helpers

- RGB565 → grayscale
- RGB565 resize + grayscale
- RGB565 resize + RGB888
- uint8 → float normalization
- uint8 → int8 normalization
- top-result selection
- backend interface for your own TFLite Micro / ESP-DL / Edge Impulse adapter

## No hidden model

The library does not contain a chicken-disease model, credentials or cloud API. Your application supplies its own backend and model.

## Minimal example

See `examples/Preprocess/Preprocess.ino`.

## License

MIT.
