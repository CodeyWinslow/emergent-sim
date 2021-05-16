#pragma once
#include "UIComponentFloodPanel.h"

namespace EmergentGraphics
{
    class ToolsPanel :
        public UIComponentFloodPanel
    {
    public:
        ToolsPanel(SDL_Renderer* renderer, SDL_Point position = { 10,10 },
            SDL_Point padding = { 20,20 }, SDL_Point buttonMargin = { 5,0 },
            SDL_Color backColor = { 214, 161, 107, 220 });
    };
}

