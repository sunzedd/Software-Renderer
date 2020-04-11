#include "Timer.h"

namespace core {

Timer* Timer::s_instance = nullptr;

void Timer::restart()
{
    m_timeStep = m_clock.restart();
}

Timer* Timer::getInstance()
{
    if (!s_instance)
        s_instance = new Timer();

    return s_instance;
}

unsigned int Timer::deltaTimeSeconds()
{
    return m_timeStep.asSeconds();
}

unsigned int Timer::deltaTimeMiliseconds()
{
    return m_timeStep.asMilliseconds();
}

unsigned int Timer::deltaTimeMicroseconds()
{
    return m_timeStep.asMicroseconds();
}

Timer::Timer()
{}

Timer::~Timer()
{}

} // namespace core
