#include "ConsoleLoggerMT.h"

#include "TimeManager.h"
#include "ThreadManager.h"

namespace cubey2 {

	void ConsoleLoggerMT::Log(const std::string & _message) {
		std::lock_guard<std::mutex> lock(mutex_);
		std::cout << TimeManager::GetInstance()->GetTimePrefix() + " - " + ThreadManager::GetInstance()->GetThreadInfo().name_ + " - " + _message << std::endl;
	}
}