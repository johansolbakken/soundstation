#pragma once

#include "core/log.h"

#ifdef __APPLE__ 
    #define DEBUG_BREAK __builtin_trap()
#elif __linux__
    #define DEBUG_BREAK __builtin_trap()
#elif _WIN32
    #define DEBUG_BREAK __debugbreak()
#endif

#define SS_ASSERT(condition, message) \
    if (!(condition)) \
    { \
        SS_LOG_ERROR(fmt::format("[ASSERTION FAILED]: {}",message)); \
        DEBUG_BREAK; \
    }