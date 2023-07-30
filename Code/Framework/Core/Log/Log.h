#pragma once

#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/common.h>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#define LOG_DEBUG(...) SPDLOG_LOGGER_CALL(Log::GetInstance().GetLogger().get(), spdlog::level::debug, __VA_ARGS__)
#define LOG_INFO(...) SPDLOG_LOGGER_CALL(Log::GetInstance().GetLogger().get(), spdlog::level::info, __VA_ARGS__)
#define LOG_WARN(...) SPDLOG_LOGGER_CALL(Log::GetInstance().GetLogger().get(), spdlog::level::warn, __VA_ARGS___)
#define LOG_ERROR(...) SPDLOG_LOGGER_CALL(Log::GetInstance().GetLogger().get(), spdlog::level::error, __VA_ARGS__)
#define LOG_CRITICAL(...) SPDLOG_LOGGER_CALL(Log::GetInstance().GetLogger().get(), spdlog::level::critical, __VA_ARGS__)


namespace Rosefinch 
{
    class Log final
    {
    public:
        static Log& GetInstance()
        {
            static Log instance;
            return instance;
        }

        std::shared_ptr<spdlog::logger> GetLogger()
        {
            return m_logger;
        } 

    private:
        Log();
        ~Log();

        std::shared_ptr<spdlog::logger> m_logger;
    };
}