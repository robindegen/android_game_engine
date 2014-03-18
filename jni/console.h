#ifndef console_h__
#define console_h__

class Console
{
public:
	enum LogLevel
	{
		Debug,
		Info,
		Warning,
		Error
	};

	static void Print(LogLevel level, const char *format, ...);

private:
	static char OutputBuffer[CONSOLE_LINE_BUFFSIZE];
};

#ifdef SHOW_DEBUG_MESSAGES
#  define DEBUGPRINT(format, ... )		Console::Print(Console::Debug, format, __VA_ARGS__);
#else
#  define DEBUGPRINT(format, ... )
#endif

#endif // console_h__
