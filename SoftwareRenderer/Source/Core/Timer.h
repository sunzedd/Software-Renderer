#pragma once
#include  <SFML/System/Clock.hpp>

namespace core {

class Timer
{
public:
    static Timer* getInstance();
    ~Timer();
    
    void restart();
    unsigned int deltaTimeSeconds();
    unsigned int deltaTimeMiliseconds();
    unsigned int deltaTimeMicroseconds();

private:
    Timer();

private:
    sf::Clock m_clock;
    sf::Time m_timeStep;
    static Timer* s_instance;
};

} // namespace core
