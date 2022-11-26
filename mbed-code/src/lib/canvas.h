#pragma once

#include "mbed.h"
#include "point.h"
#include "color.h"

namespace DevBit {

  class Canvas {

    public:
      void clear(void);
    
    public:
      void pixel(Point location, Color color);
      void rectangle(Point origin, uint8_t width, uint8_t height, Color color);
      void rectangle_filled(Point origin, uint8_t width, uint8_t height, Color color);
      void circle(Point origin, uint8_t radius, Color color);
      void circle_filled(Point origin, uint8_t radius, Color color);

    public:
      Color * pixels(void);
      size_t size(void);

    private:
      static const size_t WIDTH = 32;
      static const size_t HEIGHT = 32;
      static const size_t TOTAL_SIZE = WIDTH * HEIGHT;
      Color _pixels[TOTAL_SIZE];

  };

};