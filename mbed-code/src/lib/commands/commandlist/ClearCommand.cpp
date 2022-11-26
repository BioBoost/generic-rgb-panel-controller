#include "ClearCommand.h"

ClearCommand::ClearCommand(const char* command, DevBit::Canvas * canvas)
  : Command(command), _canvas(canvas) {
}

std::string ClearCommand::action() {
  printf("Clearing canvas\n");
  _canvas->clear();

  return Command::SUCCESS_MESSAGE;
}