import { SerialPort } from 'serialport'
import process, { exit } from 'process';

console.log("Welcome to Pixy PixelArt by DevBit (VIVES College University)");

// Create a port
const port = new SerialPort({ path: '/dev/ttyACM0', baudRate: 115200 }, function (err) {
  if (err) {
    return console.log('Failed to open port: ', err.message)
  }
})

// Crude but we need to finish this fast !
const colors = {
  red: { r: 255, g: 0, b: 0 },
  green: { r: 0, g: 255, b: 0 },
  blue: { r: 0, g: 0, b: 255 },
}

const white = { r: 255, g: 255, b: 255 }

const pixelArt = {
  x: 0,
  y: 0,
  iColor: 0,       // red
  color: function() { return Object.values(colors)[this.iColor] }
};

function write_pixel(x, y, color) { port.write(`PIXEL=${x},${y},${color.r},${color.g},${color.b}\n`); }
function render() { port.write('RENDER!\n'); }
function clear() { port.write('CLEAR!\n'); }

console.log("Capturing keyboard input");

import * as readlineModule from 'readline';
import { write } from 'fs';

readlineModule.emitKeypressEvents(process.stdin);
process.stdin.setRawMode(true);

const drawing = [];
function clear_drawing() {
  for(let x = 0; x < 32; x++) {
    drawing[x] = []
    for (let y = 0; y < 32; y++) {
      drawing[x][y] = { r: 0, g: 0, b: 0 }
    }
  }
  clear();
  render();
}
clear_drawing();

write_pixel(pixelArt.x, pixelArt.y, white);
render();

process.stdin.on('keypress', (character, key) => {
  console.log(key)

  switch (key.name) {
    case 'c':
      if (key.ctrl) exit(0);

      pixelArt.iColor = (pixelArt.iColor+1)%(Object.keys(colors).length);
      write_pixel(pixelArt.x, pixelArt.y, pixelArt.color());
      render();
      break;

    case 'escape':
      clear_drawing();
      break;

    case 'down':
      write_pixel(pixelArt.x, pixelArt.y, drawing[pixelArt.x][pixelArt.y]);
      pixelArt.y = (pixelArt.y + 1) & 0x1F;
      write_pixel(pixelArt.x, pixelArt.y, white);
      render();
      break;

    case 'up':
      write_pixel(pixelArt.x, pixelArt.y, drawing[pixelArt.x][pixelArt.y]);
      pixelArt.y = (pixelArt.y - 1) & 0x1F;
      write_pixel(pixelArt.x, pixelArt.y, white);
      render();
      break;

    case 'right':
      write_pixel(pixelArt.x, pixelArt.y, drawing[pixelArt.x][pixelArt.y]);
      pixelArt.x = (pixelArt.x + 1) & 0x1F;
      write_pixel(pixelArt.x, pixelArt.y, white);
      render();
      break;

    case 'left':
      write_pixel(pixelArt.x, pixelArt.y, drawing[pixelArt.x][pixelArt.y]);
      pixelArt.x = (pixelArt.x - 1) & 0x1F;
      write_pixel(pixelArt.x, pixelArt.y, white);
      render();
      break;

    case 'space':
      drawing[pixelArt.x][pixelArt.y] = pixelArt.color()
      write_pixel(pixelArt.x, pixelArt.y, white);
      render();
      break;
    
    case 'backspace':
    case 'delete':
      drawing[pixelArt.x][pixelArt.y] = { r: 0, g: 0, b: 0 }
      write_pixel(pixelArt.x, pixelArt.y, white);
      render();
      break;

    default:
      break;
  }

})

