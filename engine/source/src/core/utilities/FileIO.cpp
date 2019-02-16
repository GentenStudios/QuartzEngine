#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/utilities/FileIO.hpp>

using namespace qz::utils;

std::string FileIO::readAllFile(const std::string& filepath)
{
	std::fstream fileHandle;
	fileHandle.open(filepath.c_str());

	std::string fileString;
	fileString.assign(
		(std::istreambuf_iterator<char>(fileHandle)),
		(std::istreambuf_iterator<char>())
	);

	fileHandle.close();

	return fileString;
}
