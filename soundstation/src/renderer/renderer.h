#pragma once

#include "renderer/rendercommand.h"
#include "renderer/textrenderer.h"

namespace SoundStation
{
    class Renderer
    {
    public:
        static void init();
        static void shutdown();
    };
}