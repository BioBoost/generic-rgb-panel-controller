#include "mbed.h"
#include "lib/panel_controller.h"
#include "RgbPanel.h"
#include "lib/receivers/tcp_receiver.h"
#include "EthernetInterface.h"
#include "lib/canvas.h"
#include "commands/CommandManager.h"

DigitalOut alive(LED1);

using namespace DevBit;

EthernetInterface network;
RgbPanel panel(PTC10, D3, PTC11, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14);
PanelController panelController(&panel);
Receivers::TcpReceiver receiver(&panelController);
Canvas canvas;
CommandManager commandManager(mbed_file_handle(STDIN_FILENO), &canvas, &panelController);

void benchmark_panel_draw(void) {
  printf("Benchmarking time it takes to draw the panel ...\n");
  Timer timer;
  timer.start();
  panel.draw();
  timer.stop();
  printf(
    "The time taken was %llu milliseconds\n",
    std::chrono::duration_cast<std::chrono::milliseconds>(timer.elapsed_time()).count()
  );
}

bool setup_network(void) {
  // Bring up the ethernet interface
  printf("Acquiring an IP Address\n");
  nsapi_error_t status = network.connect();

  if (status != 0) {
    printf("Failed to acquire IP address\n");
    return false;
  }

  SocketAddress ipAddress;
  network.get_ip_address(&ipAddress);
  printf("IP address: %s\n", ipAddress.get_ip_address());

  return true;
}

void canvas_demo(void) {
  canvas.clear();
  canvas.rectangle({0, 0}, 32, 32, Color::GREEN);
  // canvas.rectangle_filled({1, 1}, 30, 30, Color::BLUE);
  // canvas.pixel({0, 0}, Color::RED);
  // canvas.pixel({13, 0}, Color::GREEN);
  // canvas.pixel({0, 23}, Color::BLUE);
  // canvas.pixel({0, 8}, Color::WHITE);

  // canvas.circle({ 12, 12 }, 4, Color::RED);
  canvas.circle_filled({ 24, 24 }, 4, Color::WHITE);

  panelController.write_buffer(canvas.pixels(), canvas.size());
}


int main() {
  printf("Starting RGB Panel Controller\n");

  // benchmark_panel_draw();       // Damn drawing a panel costs us 17ms, which would allow for maximum refresh rate of 58Hz
                                // So if we set interval between draws to 8ms we get total of 25ms giving us 40Hz
  canvas_demo();
  // setup_network();

  // receiver.listen(&network);    // Starts a receiver thread !

  // // panel.buffer[0] = 0xFF0000;
  // // panel.buffer[1] = 0x00FF00;
  // // panel.buffer[2] = 0x0000FF;
  // // panel.buffer[256] = 0xFF0000;
  // // panel.buffer[257] = 0x00FF00;
  // // panel.buffer[258] = 0x0000FF;
  // // panel.buffer[486] = 0xFF0000;
  // // panel.buffer[487] = 0x00FF00;
  // // panel.buffer[488] = 0x0000FF;


  // for (int y = 0; y < 32; y++) {
  //   for (int x = 0; x < 32; x++) {
  //     if (y == 0 || x == 0 || x == 31 || y == 31) {
  //       panel.buffer[x + y*32] = 0xFF0000;
  //     }
  //   }
  // }

  panelController.start();      // Starts a refresh thread !
  printf("Please enter command ?\n");

  while(true) {
    commandManager.dispatch();
    alive = !alive;
    ThisThread::sleep_for(100ms);
  }

  return 0;
}