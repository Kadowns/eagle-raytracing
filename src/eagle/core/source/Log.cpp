
#include "../Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>


_EAGLE_BEGIN

std::shared_ptr<spdlog::logger> Log::s_coreLogger;
std::shared_ptr<spdlog::logger> Log::s_clientLogger;

void Log::init(Log::LOG_LEVEL coreLogLevel, Log::LOG_LEVEL clientLogLevel) {

    spdlog::set_pattern("%^%n: %v%$");
    s_coreLogger = spdlog::stdout_color_mt("Eagle");
    s_coreLogger->set_level((spdlog::level::level_enum)coreLogLevel);
    s_clientLogger = spdlog::stdout_color_mt(EAGLE_GET_INFO(EAGLE_APP_NAME));
    s_clientLogger->set_level((spdlog::level::level_enum)clientLogLevel);
}

_EAGLE_END


