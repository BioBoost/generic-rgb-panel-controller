#include "ResetCommand.h"

ResetCommand::ResetCommand(const char* command)
  : Command(command) {
}

std::string ResetCommand::action() {
    printf("Resetting....\r\n");
    ThisThread::sleep_for(500ms);
    NVIC_SystemReset();
    return Command::SUCCESS_MESSAGE;
}