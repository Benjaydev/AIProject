#pragma once
#include <chrono>
using namespace std;
class Timer
{

public:

	Timer();
	~Timer();

	// FPS
	int fps = 0;
	int frames = 0;
	float frameTimer = 0;

	float totalRunTimeSeconds = 0;

	// Timer
	std::chrono::time_point<std::chrono::system_clock> lastTime;
	std::chrono::time_point<std::chrono::system_clock> currentTime;
	float DeltaTime = 0;


	float RecordNewTime();

protected:
	void GetCurrentTimeMilliseconds();


private:
	void CalculateFrames(float DeltaTime);
};

