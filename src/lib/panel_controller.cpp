#include "panel_controller.h"

namespace DevBit {

  PanelController::PanelController(void) {
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
      for(size_t i = 0; i < BUFFER_SIZE; i++) printf("%d ", _buffer[i]);
      printf("\n");

      ThisThread::sleep_for(1000ms);      // TODO: property !
    }
  }

  void PanelController::write_buffer(const uint32_t * buffer, size_t size) {
    if (size > BUFFER_SIZE) size = BUFFER_SIZE;

    size_t byteSize = size*sizeof(_buffer[0]);
    size_t bytesLeft = (BUFFER_SIZE-size)*sizeof(_buffer[0]);

    mutex.lock();
    memcpy(_buffer, buffer, byteSize);
    memset(_buffer+byteSize, 0, bytesLeft);
    mutex.unlock();
  }

  void PanelController::clear_buffer(void) {
    size_t byteSize = BUFFER_SIZE*sizeof(_buffer[0]);
    memset(_buffer, 0, byteSize);
  }

};