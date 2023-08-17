#include "core/log.h"

#include <fmt/format.h>

int main()
{
    SS_LOG_DEBUG("Hello, world!");
    SS_LOG_INFO("Hello, world!");
    SS_LOG_WARN("Hello, world!");
    SS_LOG_ERROR("Hello, world!");
    return 0;
}
