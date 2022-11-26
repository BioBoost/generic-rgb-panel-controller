# RGB Led Panel Controller

Control a 32x32 AdaFruit LED panel from the following interfaces:

- [ ] TCP Socket
- [ ] UDP Socket
- [ ] I2C Interface
- [ ] Serial Port
- [ ] SPI Interface

These interfaces allow 2 modes of control.

1. RAW RGB data frame mode where one can just send a full RGB buffer to the interface, which is then transfered to the panel buffer and displayed.
2. A canvas mode where it is possible to draw on a canvas and then transfer that to the panel.

The canvas mode supports a number of actions:

1. clear: clearing the canvas
2. pixel: setting the color of a single pixel at coordinates x,y
3. h-line: horizontal line in a specific color
4. v-line: vertical line in a specific color

A possible future enhancement could be a `static` action that allows you to draw a static pixel map and save that. After which each clear would clear the canvas except for the static image.

## Command Parser

Command parser is copy of Sille's command parser for DUST. Maybe later it could become a library :). Thx mate. Works as a charm.
