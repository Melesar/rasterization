#pragma once

#include <string>
#include <stack>
#include <chrono>

class Timer
{
public:

    void startSample(const std::string& name);
    void finishSample();

private:

    struct TimeSample
    {
        std::clock_t startTime;
        std::string sampleName;
    };

    std::stack<TimeSample> samples;
};
