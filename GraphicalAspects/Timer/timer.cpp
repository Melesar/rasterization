//
// Created by serge on 22.01.2019.
//

#include "timer.h"
#include <iostream>
#include <iomanip>

void Timer::startSample(const std::string &name)
{
    TimeSample sample;
    sample.startTime = std::clock();
    sample.sampleName = name;

    samples.push(sample);
}

void Timer::finishSample()
{
    if (samples.empty())
    {
        std::cout << "No startSample call before finishSample";
        return;
    }

    auto lastSample = samples.top(); samples.pop();
    auto seconds = (double) (std::clock() - lastSample.startTime) / CLOCKS_PER_SEC;

    std::cout << std::setprecision(2) << std::setw(2)
        << lastSample.sampleName << " finished in " << seconds << " seconds" << std::endl;
}
