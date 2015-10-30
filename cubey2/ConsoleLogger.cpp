#include "ConsoleLogger.h"

#include "TimeManager.h"

namespace cubey2 {
	void ConsoleLogger::Log(const std::string & _message) {
		std::cout << TimeManager::GetInstance()->GetTimePrefix() + " - " + _message << std::endl;
	}
}

