#include "mbed.h"
#include "lib/panel_controller.h"
#include "RgbPanel.h"

DigitalOut alive(LED1);

using namespace DevBit;

RgbPanel panel(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D10, D11);
PanelController panelController(&panel);

int main() {
  printf("Starting RGB Panel Controller\n");

  panelController.start();    // Starts a refresh thread !

  uint32_t buffer[] = { 10, 20, 30, 40, 50 };
  while(true) {
    alive = !alive;
    ThisThread::sleep_for(1s);

    panelController.write_buffer(buffer, 5);
  }

  return 0;
}