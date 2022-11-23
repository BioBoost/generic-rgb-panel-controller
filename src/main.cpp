#include "mbed.h"
#include "lib/panel_controller.h"

DigitalOut alive(LED1);

using namespace DevBit;

PanelController panelController;

int main() {
  printf("Starting RGB Panel Controller\n");

  panelController.start();

  uint32_t buffer[] = { 10, 20, 30, 40, 50 };
  while(true) {
    alive = !alive;
    ThisThread::sleep_for(1s);

    panelController.write_buffer(buffer, 5);
  }

  return 0;
}