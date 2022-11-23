#pragma once

#include "mbed.h"

namespace DevBit {

  class PanelController {

    public:
      PanelController(void);    // TODO: Inject Panel ?

    public:
      void start(void);
      void stop(void);

    public:
      void write_buffer(const uint32_t * buffer, size_t size);
      void clear_buffer(void);

    private:
      void refresh_panel(void);

    private:
      Thread _refreshThread;
      volatile bool _keepRefreshing = true;
      Mutex mutex;

      // For the moment internal buffer, later buffer of panel
      const static size_t BUFFER_SIZE = 64;
      uint32_t _buffer[BUFFER_SIZE] = { 0 };

  };

};