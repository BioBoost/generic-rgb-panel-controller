#pragma once

#include "../Command.h"
#include "../canvas.h"
#include "../panel_controller.h"

class ClearCommand : public Command {
    public:
        ClearCommand(const char* command, DevBit::Canvas * canvas);
        std::string action() override;

    private:
        DevBit::Canvas * _canvas;
};
