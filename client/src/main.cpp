#include "client/client.hpp"

#include "util/logging.hpp"


int main()
{
	Client* helloworld;

	helloworld = new Client();

	helloworld->fillerFunction();

    ERROR("Yo, something went really wrong!");
    WARNING("Yo, something went really wrong!");
    INFO("Yo, something went really wrong!");
    DEBUG("Yo, something went really wrong!");
}
