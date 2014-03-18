#ifndef utils_h__
#define utils_h__

class Utils
{
public:
	static std::string getExtensionFromFile(const char *path);

	static glm::vec4 rgbColorToVec4(unsigned char color[3]);
};

#endif // utils_h__
