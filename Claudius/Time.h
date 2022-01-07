#pragma once

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "SDL.h"
#pragma warning(pop)

class Time
{
    unsigned int m_frameCount{};

    float m_timeScale{ 1.0f };

    float m_time{};
    float m_deltaTime{};

    float m_unscaledTime{};
    float m_unscaledDeltaTime{};

    Uint64 m_now{ SDL_GetPerformanceCounter() };
    Uint64 m_last{};

public:
    void Update() noexcept;

    unsigned int GetFrameCount() const noexcept;

    float GetTimeScale() const noexcept;
    void SetTimeScale(float timeScale) noexcept;

    float GetTime() const noexcept;
    float GetDeltaTime() const noexcept;

    float GetUnscaledTime() const noexcept;
    float GetUnscaledDeltaTime() const noexcept;
};
