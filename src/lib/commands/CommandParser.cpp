#include "CommandParser.h"

CommandParser::CommandParser(mbed::FileHandle* uart) {
    this->uart = uart;
}

CommandParser::~CommandParser() {
    for (Command* command : commandList) {
        delete command;
    }
}

void CommandParser::dispatch() {
    while(uart->readable()) {
        char received;
        uart->read(&received, 1);
        buffer[buffer_index] = received;
        buffer[buffer_index+1] = '\0';
        buffer_index++;

        if(received != '\r' && received != '\n') {
            continue;
        }

        buffer_index = 0;
        buffer[strcspn(buffer, "\r\n")] = 0; // clear newline or carriage return characters
        parse(buffer);
    }
}

void CommandParser::addCommand(Command* command) {
    commandList.push_back(command);
}

void CommandParser::parse(char* commandString) {
    bool success = false;

    // printf("Got: %s\n", commandString);

    for (Command* command : commandList) {
        success |= command->execute(commandString);
    }

    if(!success) {
        printf("%s\n", Command::ERROR_MESSAGE);
    }
}