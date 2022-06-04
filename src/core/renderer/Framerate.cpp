#include "core/include.hpp"
#include <unistd.h>

namespace Framerate {
void Sleep(unsigned int fps, unsigned long frameTime)
{
    int sleepLength = (1000.0f / fps) * 1000 - frameTime;

    if (sleepLength > 0) usleep(sleepLength);
}
} // namespace Framerate