#include "mbed.h"
#include "lib/panel_controller.h"
#include "RgbPanel.h"
#include "lib/receivers/tcp_receiver.h"
#include "EthernetInterface.h"

DigitalOut alive(LED1);

using namespace DevBit;

EthernetInterface network;
RgbPanel panel(D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D10, D11);
PanelController panelController(&panel);
Receivers::TcpReceiver receiver(&panelController);

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

int main() {
  printf("Starting RGB Panel Controller\n");

  benchmark_panel_draw();
  setup_network();

  panelController.start();      // Starts a refresh thread !
  receiver.listen(&network);    // Starts a receiver thread !

  while(true) {
    alive = !alive;
    ThisThread::sleep_for(1s);
  }

  return 0;
}