#include "engine/utils/io.hpp"

using namespace phx;

std::string File::readFile(std::string& filePath)
{
	std::fstream fileIn;
	fileIn.open(filePath.c_str());

	std::string content;
	content.assign(
		(std::istreambuf_iterator<char>(fileIn)),
		(std::istreambuf_iterator<char>())
	);

	fileIn.close();

	return content;
}