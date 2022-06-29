#pragma once
#include "Timer.h"

Timer::Timer()
{
    GetCurrentTimeMilliseconds();
    lastTime = currentTime;
}

// Destructor
Timer::~Timer()
{
}

float Timer::RecordNewTime()
{
    // Get the current time
    GetCurrentTimeMilliseconds();
    // Get difference between last recorded time and new time
    std::chrono::duration<float> difference = currentTime - lastTime;

    // Calculate the difference in seconds for deltatime
    DeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(difference).count();

    // Keep track of this time until next method call
    lastTime = currentTime;

    // Keep track of total run time
    totalRunTimeSeconds += DeltaTime;

    // Calculate fps
    CalculateFrames(DeltaTime);

    return DeltaTime;
}

void Timer::CalculateFrames(float DeltaTime)
{
    frameTimer += DeltaTime;
    // Count to one second
    if (frameTimer >= 1) {
        // Fps is equal to the amount of frames counted before this call
        fps = frames;
        // Reset frames and timer
        frames = 0;
        frameTimer = 0;
    }

    // Add frame to count
    frames++;
}


void Timer::GetCurrentTimeMilliseconds()
{
    // Get current clock time
    currentTime = std::chrono::system_clock::now();
}

