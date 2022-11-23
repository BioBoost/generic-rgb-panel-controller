#include "panel_controller.h"
#include "mbed_assert.h"

namespace DevBit {

  PanelController::PanelController(RgbPanel * panel)
    : _panel(panel) {

    clear_buffer();
  }

  void PanelController::start(void) {
    _keepRefreshing = true;
    _refreshThread.start(callback(this, &PanelController::refresh_panel));
  }

  void PanelController::stop(void) {
    _keepRefreshing = false;
    _refreshThread.join();
  }

  void PanelController::refresh_panel(void) {
    while (_keepRefreshing) {
      _panel->draw();
      ThisThread::sleep_for(25ms);      // TODO: property !
    }
  }

  void PanelController::write_buffer(const uint32_t * buffer, size_t size) {
    MBED_ASSERT(size == RgbPanel::BUFFER_SIZE);

    size_t byteSize = size*sizeof(_panel->buffer[0]);
    mutex.lock();
    memcpy(_panel->buffer, buffer, byteSize);
    mutex.unlock();
  }

  void PanelController::write_buffer(const char * buffer, size_t size) {
    MBED_ASSERT(size == 3*RgbPanel::BUFFER_SIZE);

    mutex.lock();
    // Can't just memcpy here because RgbPanel encodes colors using 4 bytes
    for (size_t i = 0; i < RgbPanel::BUFFER_SIZE; i++) {
      size_t c = 3 * i;
      _panel->buffer[i] = ((uint32_t)buffer[c] << 16) + ((uint32_t)buffer[c+1] << 8) + ((uint32_t)buffer[c+2]);
    }
    mutex.unlock();
  }

  void PanelController::clear_buffer(void) {
    mutex.lock();
    _panel->clear();
    mutex.unlock();
  }

};