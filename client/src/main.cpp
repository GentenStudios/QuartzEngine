#include "engine/common.hpp"

#include "client/client.hpp"

#include "engine/utils/logging.hpp"

int main()
{
#   ifdef PHEONIX_OS_WINDOWS
    std::cout << "Hey Windows!" << std::endl;
#   elif defined(PHEONIX_OS_LINUX)
    std::cout << "Hey Linux!" << std::endl;
#   endif
    INITLOGGER( "pheonix.log", pheonix::LogVerbosity::INFO );
    ERROR("Yo, something went really wrong! ERROR");
    WARNING("Yo, something went really wrong! WARNING");
    INFO("Yo, something went really wrong! INFO");
    DEBUG("Yo, something went really wrong! DEBUG");
    DESTROYLOGGER();
}
