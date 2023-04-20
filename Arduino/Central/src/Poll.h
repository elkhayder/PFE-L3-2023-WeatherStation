#ifndef _POLL_H
#define _POLL_H

#include <Arduino.h>

namespace Custom
{

    class Poll
    {
    public:
        uint32_t duration;

        Poll(uint32_t duration);

        bool shouldExecute();

        void setExecuted();

    private:
        uint32_t _last_executed_at = 0;
    };

}
#endif