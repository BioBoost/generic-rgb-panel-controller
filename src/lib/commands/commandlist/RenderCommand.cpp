#include "RenderCommand.h"

RenderCommand::RenderCommand(const char* command, DevBit::Canvas * canvas, DevBit::PanelController * panelController)
  : Command(command), _canvas(canvas), _panelController(panelController) {
}

std::string RenderCommand::action() {
  printf("Rendering canvas on display\n");
  _panelController->write_buffer(_canvas->pixels(), _canvas->size());
  return Command::SUCCESS_MESSAGE;
}