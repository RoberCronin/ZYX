#pragma once

#include <chrono>
#include <sys/types.h>

class Time
{
public:
    static inline long GetTime() { return s_Instance->GetTimeImpl(); }

    static inline long GetEpochTime() { return s_Instance->GetEpochTimeImpl(); }

protected:
    virtual long GetTimeImpl();
    virtual long GetEpochTimeImpl();

private:
    Time() {}
    Time(Time& time) {}

    u_int64_t m_StartTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();

    static Time* s_Instance;
};
