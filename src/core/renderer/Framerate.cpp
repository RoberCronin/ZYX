#include "core/include.hpp"
#include <unistd.h>

namespace Framerate
{
    void Sleep(unsigned int fps, unsigned long frameTime)
    {
        usleep((int)((1000.0f / fps) * 1000 - frameTime));
        // std::cout << (int)((1000.0f / fps) * 1000 - frameTime) << std::endl;
    }
}