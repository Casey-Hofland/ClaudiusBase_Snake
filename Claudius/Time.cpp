#include "Time.h"

void Time::Update() noexcept
{
	m_last = m_now;
	m_now = SDL_GetPerformanceCounter();

	m_frameCount++;

	m_unscaledDeltaTime = ((m_now - m_last) * 1000.0f / SDL_GetPerformanceFrequency()) * 0.01f;
	m_unscaledTime += m_unscaledDeltaTime;

	m_deltaTime = m_unscaledDeltaTime * m_timeScale;
	m_time += m_deltaTime;
}

unsigned int Time::GetFrameCount() const noexcept
{
	return m_frameCount;
}

float Time::GetTimeScale() const noexcept
{
	return m_timeScale;
}

void Time::SetTimeScale(float timeScale) noexcept
{
	this->m_timeScale = timeScale;
}

float Time::GetTime() const noexcept
{
	return m_time;
}

float Time::GetDeltaTime() const noexcept
{
	return m_deltaTime;
}

float Time::GetUnscaledTime() const noexcept
{
	return m_unscaledTime;
}

float Time::GetUnscaledDeltaTime() const noexcept
{
	return m_unscaledDeltaTime;
}
