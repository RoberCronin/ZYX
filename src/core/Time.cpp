#include "core/include.hpp"

#include <chrono>

Time* Time::s_Instance = new Time();

long Time::GetTimeImpl()
{
    return std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() - m_StartTime;
}

long Time::GetEpochTimeImpl()
{
    return std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
}
