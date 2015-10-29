#include "ConsoleLogger.h"

#include <time.h>

namespace cubey2 {
	void ConsoleLogger::Log(const std::string & message) {
		auto ss = GetPrefix();
		std::cout << ss + message << std::endl;
	}

	std::string ConsoleLogger::GetPrefix() {
		time_t rawtime;
		struct tm timeinfo;

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		char buffer[80];
		strftime(buffer, 80, "%Y/%b/%d %X - ", &timeinfo);

		return std::string(buffer);
	}
}

