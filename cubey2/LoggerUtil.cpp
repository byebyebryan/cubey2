#include "LoggerUtil.h"

#include <time.h>

namespace cubey2 {

	std::string LoggerUtil::GetPrefix() {
		time_t rawtime;
		struct tm timeinfo;

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		char buffer[80];
		strftime(buffer, 80, "%Y/%b/%d %X - ", &timeinfo);

		return std::string(buffer);
	}
}