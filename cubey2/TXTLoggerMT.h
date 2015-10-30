#pragma once

#include <thread>
#include <mutex>

#include "ILogger.h"

namespace cubey2 {
	class TXTLoggerMT: public ILogger {
	public:
		void Init() override;
		void Destroy() override;

		void Log(const std::string& message) override;

	private:
		std::mutex mutex_;

		size_t log_file_key_;
	};
}
