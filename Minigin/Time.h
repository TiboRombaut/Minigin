#pragma once
#include "Singleton.h"
#include <chrono>

class Time  final : public dae::Singleton<Time>
{
public:
	Time() = default;
	~Time() = default;

	void Update();

	float GetDeltaTime() const;
	std::chrono::steady_clock::time_point GetPreviousTime() const;
	int GetFPS() const;
	int GetMsPerFrame() const;
	void SetMsPerFrame(const int& msPerFrame);

private:
	std::chrono::steady_clock::time_point m_PreviousTime = std::chrono::high_resolution_clock::now();
	float m_DeltaTime{};
	int m_MsPerFrame = 16; //16 = 60fps, 33 = 30 fps
};
