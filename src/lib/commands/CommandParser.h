#pragma once 

#include "mbed.h"
#include "Command.h"
#include <vector>

class CommandParser {
    public:
        CommandParser(mbed::FileHandle* uart);
        ~CommandParser();
        void dispatch();
        void addCommand(Command* command);
        void parse(char* commandString);

    private:
        std::vector<Command*> commandList;
        mbed::FileHandle* uart;
        char buffer[100];
        int buffer_index = 0; 
};

