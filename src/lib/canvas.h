#pragma once

#include "mbed.h"
#include "point.h"
#include "color.h"

namespace DevBit {

  class Canvas {

    public:
      void clear(void);
      void pixel(Point location, Color color);
      void rectangle(Point origin, uint8_t width, uint8_t height, Color color);

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