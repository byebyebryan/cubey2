#include "ConsoleLoggerMT.h"

namespace cubey2 {

	void ConsoleLoggerMT::Log(const std::string & message) {
		std::lock_guard<std::mutex> lock(mutex_);
		auto ss = GetPrefixMT();
		std::cout << ss + message << std::endl;
	}
	std::string ConsoleLoggerMT::GetPrefixMT()
	{
		return ConsoleLogger::GetPrefix() + ThreadManager::GetInstance()->GetThread().name_;
	}
}