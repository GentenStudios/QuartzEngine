#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/utils/IO.hpp>

using namespace qz;

std::string File::readFile(const std::string& filePath)
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