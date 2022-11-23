#include "canvas.h"

namespace DevBit {

  void Canvas::clear(void) {
    for (uint8_t y = 0; y < HEIGHT; y++) {
      for (uint8_t x = 0; x < WIDTH; x++) {
        pixel({ x, y }, Color::BLACK);
      }
    }
  }

  void Canvas::pixel(Point location, Color color) {
    if (location.x >= WIDTH || location.y >= HEIGHT) return;

    _pixels[HEIGHT*location.y + location.x] = color;
  }

  void Canvas::rectangle(Point origin, uint8_t width, uint8_t height, Color color) {
    if ((origin.x + width) >= WIDTH || (origin.y + height) >= HEIGHT) return;
    
    for (uint8_t y = 0; y < height; y++) {
      for (uint8_t x = 0; x < width; x++) {
        pixel({ origin.x + x, origin.y + y }, color);
      }
    }
  }

  Color * Canvas::pixels(void) {
    return _pixels;
  }

  size_t Canvas::size(void) {
    return TOTAL_SIZE;
  }

};