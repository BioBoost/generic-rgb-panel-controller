#include "color.h"

namespace DevBit {

  Color::Color(void) { }

  Color::Color(uint8_t red, uint8_t green, uint8_t blue) {
    this->red(red);
    this->green(green);
    this->blue(blue);
  }

  Color::Color(const Color &color) {
    _red = color._red;
    _green = color._green;
    _blue = color._blue;
  }

  Color::Color(uint32_t rgb) {
    this->rgb(rgb);
  }

  void Color::red(uint8_t red) {
    _red = red;
  }

  void Color::green(uint8_t green) {
    _green = green;
  }

  void Color::blue(uint8_t blue) {
    _blue = blue;
  }

  void Color::rgb(uint32_t rgb) {
    red((rgb >> 16) & 0xFF);
    green((rgb >> 8) & 0xFF);
    blue((rgb) & 0xFF);
  }

  uint8_t Color::red(void) const {
    return _red;
  }

  uint8_t Color::green(void) const {
    return _green;
  }

  uint8_t Color::blue(void) const {
    return _blue;
  }

  uint32_t Color::rgb(void) const {
    return ((uint32_t)red() << 16) + ((uint32_t)green() << 8) + ((uint32_t)blue());
  }

  void Color::dim(uint8_t percentage) {
    if (percentage > 100) percentage = 100;
    
    red(red() - round((red() * 1.0 * percentage / 100)));
    green(green() - round((green() * 1.0 * percentage / 100)));
    blue(blue() - round((blue() * 1.0 * percentage / 100)));
  }

  bool Color::operator==(const Color& other) {
    return rgb() == other.rgb();
  }

  bool Color::operator!=(const Color& other) {
    return !(*this == other);
  }

  uint8_t& Color::operator[](size_t index) {
    //if (index > 2) throw out_of_range("Index is out of range for Color");

    // No other option here because we need to return reference
    if (index == 0) return _red;
    else if (index == 1) return _green;

    return _blue;
  }

  // TODO: Add more colors
  const Color Color::BLACK = Color(0, 0, 0);
  const Color Color::WHITE = Color(255, 255, 255);
  const Color Color::RED = Color(255, 0, 0);
  const Color Color::GREEN = Color(0, 255, 0);
  const Color Color::BLUE = Color(0, 0, 255);

};