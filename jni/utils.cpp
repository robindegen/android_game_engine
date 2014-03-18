#include "aeon.h"
#include "utils.h"

std::string Utils::getExtensionFromFile(const char *path)
{
	std::string filepath = path;

	//Find the last . (this is the file extension)
	size_t offset = filepath.find_last_of('.');

	if(offset == std::string::npos)
	{
		Console::Print(Console::Warning, "Could not find file extension for %s.", path);
		return "";
	}

	return filepath.substr(offset + 1);
}

glm::vec4 Utils::rgbColorToVec4(unsigned char color[3])
{
	float r = ((float) color[0]) / 256.0f;
	float g = ((float) color[1]) / 256.0f;
	float b = ((float) color[2]) / 256.0f;

	return glm::vec4(r, g, b, 1.0f);
}
