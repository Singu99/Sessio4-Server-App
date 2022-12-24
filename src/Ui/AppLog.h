#pragma once
#include "imgui.h"
#include <mutex>

// Usage:
//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");
class AppLog
{
public:
    AppLog();
    ~AppLog() = default;

    void Clear();
    void AddLog(const char* fmt, va_list args) IM_FMTARGS(2);
    void Draw(const char* title, bool* p_open = NULL);

private:
    ImGuiTextBuffer     m_buf;
    ImGuiTextFilter     m_filter;
    ImVector<int>       m_lineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool                m_autoScroll;  // Keep scrolling if already at the bottom.
    
    std::mutex m_data;                  // Mutex for thread safety
};