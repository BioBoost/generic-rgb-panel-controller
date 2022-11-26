#include "Command.h"
#include "string.h"

const char Command::ERROR_MESSAGE[] = "ERROR";
const char Command::SUCCESS_MESSAGE[] = "OK";

Command::Command(const char* command){
    strcpy(this->command, command);
}

bool Command::execute(char* command) {

    size_t command_size = strlen(this->command);
    if( strncmp(command, this->command, command_size) != 0){
        return false;   // command starts with wrong characters
    }

    if( strlen(command) == command_size ) {
        std::string result = get();
        printf("%s\n", result.c_str());
        return true;
    }

    if( command[command_size] == '!') {
        std::string result = action();
        printf("%s\n", result.c_str());
        return true;
    }
    
    if( command[command_size] == '=') {
        char argument[100] = { 0 };
        strcpy(argument, command + command_size + 1);
        std::string result = set(argument);
        printf("%s\n", result.c_str());
        return true;
    }

    return false;
}

std::string Command::get() {
    return "NotImplemented";
}

std::string Command::set(std::string argument) {
    return "NotImplemented";
}

std::string Command::action() {
    return "NotImplemented";
}
