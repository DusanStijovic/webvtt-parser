#include "logger/Logger.h"
#include "utf8.h"

#define DILOGE(message)                      \
    do                                        \
    {                                         \
        CPlusPlusLogging::Logger::getLogger() \
            ->error(message);                  \
     } while (0)                           

#define DILOGI(message)                           \
    do                                        \
    {                                         \
        CPlusPlusLogging::Logger::getLogger() \
            ->info(message);              \
    } while (0)
