#include "Poll.h"

namespace Custom
{
    Poll::Poll(uint32_t duration) : duration(duration){};

    bool Poll::shouldExecute()
    {
        return millis() > _last_executed_at + duration;
    }

    void Poll::setExecuted()
    {
        _last_executed_at = millis();
    }
}