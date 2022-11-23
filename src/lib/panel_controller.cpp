#include "panel_controller.h"

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
      printf("Refreshing panel\n");   // TODO: Refresh actual panel
      for(size_t i = 0; i < RgbPanel::BUFFER_SIZE; i++) printf("%d ", _panel->buffer[i]);
      printf("\n");

      ThisThread::sleep_for(1000ms);      // TODO: property !
    }
  }

  void PanelController::write_buffer(const uint32_t * buffer, size_t size) {
    if (size > RgbPanel::BUFFER_SIZE) size = RgbPanel::BUFFER_SIZE;

    size_t byteSize = size*sizeof(_panel->buffer[0]);
    size_t bytesLeft = (RgbPanel::BUFFER_SIZE-size)*sizeof(_panel->buffer[0]);

    mutex.lock();
    memcpy(_panel->buffer, buffer, byteSize);
    memset(_panel->buffer+byteSize, 0, bytesLeft);
    mutex.unlock();
  }

  void PanelController::clear_buffer(void) {
    mutex.lock();
    _panel->clear();
    mutex.unlock();
  }

};