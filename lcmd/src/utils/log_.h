#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "spdlog/fmt/bin_to_hex.h"
#include "oal/time_tick.h"

class MarsLog
{
    std::shared_ptr<spdlog::logger> logger;

public:
    enum
    {
        LOG_VERBOSE,
        LOG_DEBUG,
        LOG_WARN,
        LOG_ERROR,
        LOG_CRITICAL,
        LOG_OFF
    };

    MarsLog(bool enableConsole, bool enableFile)
    {
        logger = std::make_shared<spdlog::logger>("log");
        // spdlog::register_logger(logger);
        if (enableConsole)
        {
            auto console = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
            logger->sinks().push_back(console);
        }
        if (enableFile)
        {
            //auto file = std::make_shared<spdlog::sinks::rotating_file_sink_mt>();
        }

        logger->flush_on(spdlog::level::warn);
        logger->set_pattern("[%Y-%m-%d %H:%M%S.%e] %^[%L]%$ %v");

        SetLevel(LOG_VERBOSE);
    }
    void SetLevel(int level)
    {
        switch (level)
        {
        case LOG_VERBOSE:
            logger->set_level(spdlog::level::trace);
            break;
        case LOG_DEBUG:
            logger->set_level(spdlog::level::debug);
        case LOG_WARN:
            logger->set_level(spdlog::level::warn);
            break;
        case LOG_ERROR:
            logger->set_level(spdlog::level::err);
            break;
        case LOG_CRITICAL:
            logger->set_level(spdlog::level::critical);
            break;
        case LOG_OFF: // pass through
            logger->set_level(spdlog::level::off);
        default:
            break;
        }
    }
    static MarsLog* LoggerInstance()
    {
        static MarsLog log(true, false);
        return &log;
    }
    std::shared_ptr<spdlog::logger> Logger()
    {
        return logger;
    }
};

extern MarsLog _gLog;

#define LOGV(TAG, ...) MarsLog::LoggerInstance()->Logger()->trace("(" TAG ") " __VA_ARGS__)
#define LOGD(TAG, ...) MarsLog::LoggerInstance()->Logger()->debug("(" TAG ") " __VA_ARGS__)
#define LOGW(TAG, ...) MarsLog::LoggerInstance()->Logger()->warn("(" TAG ") " __VA_ARGS__)
#define LOGE(TAG, ...) MarsLog::LoggerInstance()->Logger()->error("(" TAG ") " __VA_ARGS__)
#define LOGC(TAG, ...) MarsLog::LoggerInstance()->Logger()->critical("(" TAG ") " __VA_ARGS__)

class MarsFunStopWatch
{
    uint64_t startTime_;
    uint64_t timeThreshold_;
    std::string fnName_;
    std::string fileName_;

public:
    MarsFunStopWatch(const char *fileName, const char *funName, uint64_t timeThreshold)
    {
        startTime_ = TimeTick::Ms();
        fnName_ = funName;
        fileName_ = fileName;
        timeThreshold_ = timeThreshold;
        if (timeThreshold_ == 0)
        {
            LOGV("FUN", "{0}-{1} IN\t\t++++++++++", fileName_, fnName_);
        }
    }
    void Tick(int duration)
    {
        auto d = TimeTick::Ms() - startTime_;
        if(d > duration)
        {
            LOGV("FUN", "{0}-{1} TICK @{}\t\t++++++++++", fileName_, fnName_, d);
        }
    }
    ~MarsFunStopWatch()
    {
        auto d = TimeTick::Ms() - startTime_;
        if (timeThreshold_ != 0 && d > timeThreshold_)
        {
            LOGW("FUN", "{0}-{1} OUT @{2}\t----------", fileName_, fnName_, d);
        }
        else if (timeThreshold_ == 0)
        {
            LOGV("FUN", "{0}-{1} OUT @{2}\t----------", fileName_, fnName_, d);
        }
    }
};

#define FUN_STOP_WATCHER(t) MarsFunStopWatch mfst(__FILE__, __FUNCTION__, t)