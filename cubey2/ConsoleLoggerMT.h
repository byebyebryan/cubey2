#pragma once

#include <thread>
#include <mutex>

#include "ILogger.h"

namespace cubey2 {
	class ConsoleLoggerMT : public ILogger {
	public:
		void Log(const std::string& _message) override;

	private:
		std::mutex mutex_;
	};
}