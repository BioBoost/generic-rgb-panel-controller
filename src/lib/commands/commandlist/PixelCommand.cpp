#include "PixelCommand.h"
#include "../../color.h"

PixelCommand::PixelCommand(const char* command, DevBit::Canvas * canvas)
  : Command(command), _canvas(canvas) {
}

//PIXEL=x,y,R,G,B
std::string PixelCommand::set(std::string argument) {
  std::array<uint8_t,5> argValues;

    size_t iSeperator = 0;    
    for(unsigned int i = 0; i < argValues.size(); i++) {
      iSeperator = argument.find_first_of(",");
      argValues.at(i) = strtoul(argument.data(), NULL, 10);
      argument.erase(0, iSeperator + 1);
    }

    _canvas->pixel({ argValues[0], argValues[1] }, DevBit::Color(argValues[2], argValues[3], argValues[4]));

    return Command::SUCCESS_MESSAGE;
} 