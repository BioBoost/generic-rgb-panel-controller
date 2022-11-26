#pragma once

#include "../Command.h"
#include "../canvas.h"
#include "../panel_controller.h"

class PixelCommand : public Command {
    public:
        PixelCommand(const char* command, DevBit::Canvas * canvas);
        std::string set(std::string argument) override;

    private:
        DevBit::Canvas * _canvas;
};
