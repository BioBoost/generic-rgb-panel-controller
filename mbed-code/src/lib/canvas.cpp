#include "canvas.h"
#include <cmath>

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
    if ((origin.x + width) > WIDTH || (origin.y + height) > HEIGHT) return;
    
    for (uint8_t y = 0; y < height; y++) {
      for (uint8_t x = 0; x < width; x++) {
        if (y == 0 || x == 0 || x == width-1 || y == height-1) {
          pixel({ origin.x + x, origin.y + y }, color);
        }
      }
    }
  }

  void Canvas::rectangle_filled(Point origin, uint8_t width, uint8_t height, Color color) {
    if ((origin.x + width) > WIDTH || (origin.y + height) > HEIGHT) return;
    
    for (uint8_t y = 0; y < height; y++) {
      for (uint8_t x = 0; x < width; x++) {
        pixel({ origin.x + x, origin.y + y }, color);
      }
    }
  }

  void Canvas::circle(Point origin, uint8_t radius, Color color) {
    // calculates the minimum angle between two pixels in a diagonal.
    // you can multiply minAngle by a security factor like 0.9 just to be sure you wont have empty pixels in the circle
    double minAngle = 0.9 * acos(1 - 1.0/(radius));

    for(double angle = 0; angle <= 360; angle += minAngle) {
      double dx = radius * cos(angle);
      double dy = radius * sin(angle);
      pixel({ round(origin.x + dx), round(origin.y + dy) }, color);
    }
  }

  void Canvas::circle_filled(Point origin, uint8_t radius, Color color) {
    for (uint8_t r = radius; r >= 1; r--) {
      circle(origin, r, color);
    }
    pixel(origin, color);
  }

  Color * Canvas::pixels(void) {
    return _pixels;
  }

  size_t Canvas::size(void) {
    return TOTAL_SIZE;
  }

};