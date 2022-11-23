#pragma once

#include "mbed.h"
#include "RgbPanel.h"

namespace DevBit {

  class PanelController {

    public:
      PanelController(RgbPanel * panel);

    public:
      void start(void);
      void stop(void);

    public:
      void write_buffer(const uint32_t * buffer, size_t size);
      void write_buffer(const char * buffer, size_t size);
      void clear_buffer(void);

    private:
      void refresh_panel(void);

    private:
      Thread _refreshThread;
      volatile bool _keepRefreshing = true;
      Mutex mutex;
      RgbPanel * _panel;
  };

};