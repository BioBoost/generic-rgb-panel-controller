#pragma once

#include "../canvas.h"
#include "CommandParser.h"
#include "../panel_controller.h"

class CommandManager {
    public:
        CommandManager(FileHandle* stdioFileHandle, DevBit::Canvas * canvas, DevBit::PanelController * panelController);
        void dispatch();
    private:
        CommandParser parser;
};