#include "client/client.hpp"

int main()
{
	Client* helloworld;

	helloworld = new Client();

	helloworld->fillerFunction();

    phoenix::Logger::logMessage( "main.cpp", 11, "Testing the logger", 0);
    phoenix::Logger::logMessage( "main.cpp", 12, "Testing the logger", "INFO");
    phoenix::Logger::logMessage( "main.cpp", 13, "Testing the logger", "DEBUG");

}
Also