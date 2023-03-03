import { SerialPort } from 'serialport'
import process, { exit } from 'process';
import * as bmp from 'bmp-js'
import fs from 'fs'

console.log("Welcome to Pixy PixelArt by DevBit (VIVES College University)");

// Create a port
const port = new SerialPort({ path: '/dev/ttyACM0', baudRate: 115200 }, function (err) {
  if (err) {
    return console.log('Failed to open port: ', err.message)
  }
})

function sleep(ms) {
  return new Promise((resolve) => {
    setTimeout(resolve, ms);
  });
}

// Crude but we need to finish this fast !
const colors = {
  red: { r: 255, g: 0, b: 0 },
  green: { r: 0, g: 255, b: 0 },
  blue: { r: 0, g: 0, b: 255 },
  white: { r: 255, g: 255, b: 255 }
}

const pixelArt = {
  x: 0,
  y: 0,
  drag: false,      // keep drawing while moving
  iColor: 0,       // red
  color: function() { return Object.values(colors)[this.iColor] }
};

function write_pixel(x, y, color) { port.write(`PIXEL=${x},${y},${color.r},${color.g},${color.b}\n`); }
function render() { port.write('RENDER!\n'); }
function clear() { port.write('CLEAR!\n'); }
function reset() { port.write('RESET!\n'); }

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
  render();
}

clear_drawing();
write_pixel(pixelArt.x, pixelArt.y, pixelArt.color());
render();

process.stdin.on('keypress', async (character, key) => {
  console.log(key)

  switch (key.name) {
    case 'c':
      if (key.ctrl) exit(0);

      pixelArt.iColor = (pixelArt.iColor+1)%(Object.keys(colors).length);
      write_pixel(pixelArt.x, pixelArt.y, pixelArt.color());
      render();
      break;

    case 'escape':
      pixelArt.drag = false;
      clear_drawing();
      clear();
      write_pixel(pixelArt.x, pixelArt.y, pixelArt.color());
      render();
      break;

    case 'down':
      write_pixel(pixelArt.x, pixelArt.y, drawing[pixelArt.x][pixelArt.y]);
      pixelArt.y = (pixelArt.y + 1) & 0x1F;
      write_pixel(pixelArt.x, pixelArt.y, pixelArt.color());
      if (pixelArt.drag) drawing[pixelArt.x][pixelArt.y] = pixelArt.color()
      render();
      break;

    case 'up':
      write_pixel(pixelArt.x, pixelArt.y, drawing[pixelArt.x][pixelArt.y]);
      pixelArt.y = (pixelArt.y - 1) & 0x1F;
      write_pixel(pixelArt.x, pixelArt.y, pixelArt.color());
      if (pixelArt.drag) drawing[pixelArt.x][pixelArt.y] = pixelArt.color()
      render();
      break;

    case 'right':
      write_pixel(pixelArt.x, pixelArt.y, drawing[pixelArt.x][pixelArt.y]);
      pixelArt.x = (pixelArt.x + 1) & 0x1F;
      write_pixel(pixelArt.x, pixelArt.y, pixelArt.color());
      if (pixelArt.drag) drawing[pixelArt.x][pixelArt.y] = pixelArt.color()
      render();
      break;

    case 'left':
      write_pixel(pixelArt.x, pixelArt.y, drawing[pixelArt.x][pixelArt.y]);
      pixelArt.x = (pixelArt.x - 1) & 0x1F;
      write_pixel(pixelArt.x, pixelArt.y, pixelArt.color());
      if (pixelArt.drag) drawing[pixelArt.x][pixelArt.y] = pixelArt.color()
      render();
      break;

    case 'space':
      pixelArt.drag = false;
      drawing[pixelArt.x][pixelArt.y] = pixelArt.color()
      write_pixel(pixelArt.x, pixelArt.y, pixelArt.color());
      render();
      break;
    
    case 'backspace':
    case 'delete':
      pixelArt.drag = false;
      drawing[pixelArt.x][pixelArt.y] = { r: 0, g: 0, b: 0 }
      write_pixel(pixelArt.x, pixelArt.y, pixelArt.color());
      render();
      break;
  
    case 'd':
      pixelArt.drag = !pixelArt.drag;
      break;

    case 's': {
      const filename = `./images/${Date.now()}.bmp`
      console.log(`Saving image ${filename}`);

      const dataArray = []
      for (let y = 0; y < 32; y++) {
        for(let x = 0; x < 32; x++) {
          dataArray.push(0);                  // A
          dataArray.push(drawing[x][y].g);
          dataArray.push(drawing[x][y].b);
          dataArray.push(drawing[x][y].r);
        }
      }

      const bmpData = {
        data: Buffer.from(dataArray), //Buffer of AGBR,AGBR,...
        width: 32, //Number
        height: 32 //Number
      };

      const rawData = bmp.encode(bmpData);        //defaults to no compression
      fs.writeFileSync(filename, rawData.data);
      break;
    }

    // case 'l': {
    //   const filename = `./images/1669487907495.bmp`;
    //   console.log(`Loading image ${filename}`)
    //   const bmpBuffer = fs.readFileSync(filename);
    //   const bmpData = bmp.decode(bmpBuffer);

    //   if (bmpData.height != 32 || bmpData.width != 32) {
    //     console.log("Dimensions dont match");
    //     break;
    //   }
      
    //   for (let y = 0; y < 32; y++) {
    //     for(let x = 0; x < 32; x++) {
    //       drawing[x][y] = {
    //         g: bmpData.data[4*32*y+4*x+1],
    //         b: bmpData.data[4*32*y+4*x+2],
    //         r: bmpData.data[4*32*y+4*x+3]
    //       }
    //       write_pixel(x, y, drawing[x][y]);
    //       await sleep(5);
    //       render();
    //       await sleep(5);
    //     }
    //   }

    //   render();
    //   break;
    // }

    case 'r':
      reset();
      await sleep(200);
      clear_drawing();
      write_pixel(pixelArt.x, pixelArt.y, colors.white);
      render();
      break;

    default:
      break;
  }

})

