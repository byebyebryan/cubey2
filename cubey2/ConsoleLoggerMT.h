#pragma once

#include <thread>
#include <mutex>

#include "ConsoleLogger.h"
#include "ThreadManager.h"

namespace cubey2 {
	class ConsoleLoggerMT : public ConsoleLogger {
	public:
		void Log(const std::string& message) override;

	private:
		static std::string GetPrefixMT();

		std::mutex mutex_;
	};
}