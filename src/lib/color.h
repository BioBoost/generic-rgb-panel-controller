#pragma once

#include "mbed.h"

namespace DevBit {

  class Color {

    public:
      Color(void);
      Color(uint8_t red, uint8_t green, uint8_t blue);
      Color(const Color &color);
      Color(uint32_t rgb);
    
    public:
      void red(uint8_t red);
      void green(uint8_t green);
      void blue(uint8_t blue);
      void rgb(uint32_t rgb);

    public:
      uint8_t red(void) const;
      uint8_t green(void) const;
      uint8_t blue(void) const;
      uint32_t rgb(void) const;

    public:
      void dim(uint8_t percentage);

    public:
      bool operator==(const Color& other);
      bool operator!=(const Color& other);
      uint8_t& operator[](size_t index);

    public:
      static const Color BLACK;
      static const Color WHITE;
      static const Color RED;
      static const Color GREEN;
      static const Color BLUE;

    private:
      uint8_t _red = 0;
      uint8_t _green = 0;
      uint8_t _blue = 0;

  };

};
