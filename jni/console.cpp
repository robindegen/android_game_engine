#include "aeon.h"
#include "console.h"

#include <android/log.h>

char Console::OutputBuffer[CONSOLE_LINE_BUFFSIZE];

//TODO: Crappy print implementation... this should be reworked...
void Console::Print(LogLevel level, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	vsprintf(OutputBuffer, format, args);

	std::string logLevelString;
	switch(level)
	{
		case Info:		{ logLevelString = "INF"; } break;
		case Debug:		{ logLevelString = "DBG"; } break;
		case Warning:	{ logLevelString = "WRN"; } break;
		case Error:		{ logLevelString = "ERR"; } break;
	};

	//This looks horrible, but it's a lot faster.
	std::string logMessage;
	logMessage += '[';
	logMessage += logLevelString;
	logMessage += ']';
	logMessage += ' ';
	logMessage += OutputBuffer;

	__android_log_print(ANDROID_LOG_INFO, "aeon", "%s", logMessage.c_str());

	va_end(args);
}
