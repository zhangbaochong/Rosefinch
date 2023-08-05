#include "Log.h"

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Rosefinch
{
	Log::Log()
	{
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);
        console_sink->set_pattern("[%Y-%m-%d %T] [%^%l%$] (%s %#) %v");

        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Editor.log", true);
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("[%Y-%m-%d %T] [%^%l%$] (%s %#) %v");

        const spdlog::sinks_init_list sink_list = { console_sink, file_sink };

        spdlog::init_thread_pool(8192, 1);

        m_Logger = std::make_shared<spdlog::async_logger>("muggle_logger",
            sink_list.begin(),
            sink_list.end(),
            spdlog::thread_pool(),
            spdlog::async_overflow_policy::block);
        m_Logger->set_level(spdlog::level::trace);

        spdlog::register_logger(m_Logger);
	}

	Log::~Log()
	{
		m_Logger->flush();
		spdlog::drop_all();
	}
}