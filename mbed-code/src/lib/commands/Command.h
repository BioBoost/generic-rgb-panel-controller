#pragma once
#include "mbed.h"
#include "string.h"

class Command {
    public: 
        Command(const char* command);
        Command(Command &command);
        bool execute(char* command);

        virtual std::string get();
        virtual std::string set(std::string argument);
        virtual std::string action();
    
        static const char ERROR_MESSAGE[];
        static const char SUCCESS_MESSAGE[];
    private:
        char command[20];

};