#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

class Timer
{
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_times.push_back(static_cast<unsigned int>(elapsedSeconds()));
        m_bRunning = false;
    }

    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if (m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }
    inline void eraseTimers()
    {
        m_times.erase(m_times.end());
    }
    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }
    std::vector<unsigned int> getTimes() const
    {
        return m_times;
    }
private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
    std::vector<unsigned int> m_times;
};