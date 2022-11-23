#include "tcp_receiver.h"

namespace DevBit::Receivers {

  TcpReceiver::TcpReceiver(PanelController * controller)
    : controller(controller) {
  }

  void TcpReceiver::listen(EthernetInterface * network, unsigned int port) {

    // Open a TCP Socket
    socket.open(network);        // Open socket on ethernet stack
    socket.bind(1337);            // Bind socket to port
    printf("Listening for incoming connections\n");
    socket.listen();              // Listen for incoming connections

    printf("Starting TCP Thread\n");
    thread.start(callback(this, &TcpReceiver::receive));
  }

  void TcpReceiver::receive(void) {
    while(listening) {
      nsapi_error_t clientError = 0;
      printf("Waiting for client to connect\n");
      TCPSocket * client = socket.accept(&clientError);     // Blocking ! (Can be set to non-blocking)

      if (clientError == 0) {
        printf("Client connected\n");

        while (nsapi_size_or_error_t status = client->recv(buffer, sizeof(buffer)) > 0) {
          // Can do that here as buffer is protected using mutex
          controller->write_buffer(buffer, BUFFER_SIZE);
          clear_buffer();
        }

        printf("Client disconnected\n");
      }
    }
  }

  void TcpReceiver::close(void) {
    listening = false;
    socket.close();
    thread.join();
  }

  void TcpReceiver::clear_buffer(void) {
    memset(buffer, 0, BUFFER_SIZE*sizeof(buffer[0]));
  }

};