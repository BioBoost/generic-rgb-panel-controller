#pragma once

#include "../Command.h"
#include "../canvas.h"
#include "../panel_controller.h"

class RenderCommand : public Command {
    public:
        RenderCommand(const char* command, DevBit::Canvas * canvas, DevBit::PanelController * panelController);
        std::string action() override;

    private:
        DevBit::Canvas * _canvas;
        DevBit::PanelController * _panelController;
};
