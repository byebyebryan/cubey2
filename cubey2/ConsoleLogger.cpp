#include "ConsoleLogger.h"

namespace cubey2 {
	void ConsoleLogger::Log(const std::string & message) {
		auto ss = LoggerUtil::GetPrefix();
		std::cout << ss << message.c_str() << std::endl;
	}
}

