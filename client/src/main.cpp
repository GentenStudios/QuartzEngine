#include "client/client.hpp"

#include "util/logging.hpp"

int main()
{
    INITLOGGER( "pheonix.log", pheonix::LogVerbosity::INFO );
    ERROR("Yo, something went really wrong! ERROR");
    WARNING("Yo, something went really wrong! WARNING");
    INFO("Yo, something went really wrong! INFO");
    DEBUG("Yo, something went really wrong! DEBUG");
    DESTROYLOGGER();
}
