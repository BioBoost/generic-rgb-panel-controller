#include "CommandManager.h"

#include "ClearCommand.h"
#include "PixelCommand.h"
#include "RenderCommand.h"

CommandManager::CommandManager(FileHandle* stdioFileHandle, DevBit::Canvas * canvas, DevBit::PanelController * panelController)
  : parser(stdioFileHandle) {

  parser.addCommand(new ClearCommand("CLEAR", canvas));
  parser.addCommand(new PixelCommand("PIXEL", canvas));
  parser.addCommand(new RenderCommand("RENDER", canvas, panelController));
}

void CommandManager::dispatch() {
  parser.dispatch();
}