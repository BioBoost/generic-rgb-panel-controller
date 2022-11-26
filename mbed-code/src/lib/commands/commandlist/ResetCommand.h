#pragma once

#include "../Command.h"

class ResetCommand : public Command {
  public:
    ResetCommand(const char* command);
    std::string action() override;
};