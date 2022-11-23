#pragma once

#include "mbed.h"
#include "EthernetInterface.h"
#include "../panel_controller.h"

namespace DevBit::Receivers {

  class TcpReceiver {

    public:
      TcpReceiver(PanelController * controller);

    public:
      void listen(EthernetInterface * network, unsigned int port=1337);
      void close(void);

    private:
      void receive(void);

    private:
      void clear_buffer(void);

    private:
      PanelController * controller = nullptr;
      Thread thread;
      bool listening = true;
      TCPSocket socket;

      static const size_t BUFFER_SIZE = 3 * 1024;
      char buffer[BUFFER_SIZE];
  };

};