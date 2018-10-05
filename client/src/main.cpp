#include "engine/common.hpp"

#include "client/client.hpp"

int main()
{
#   ifdef PHEONIX_OS_WINDOWS
    std::cout << "Hey Windows!" << std::endl;
#   elif defined(PHEONIX_OS_LINUX)
    std::cout << "Hey Linux!" << std::endl;
#   endif
}
