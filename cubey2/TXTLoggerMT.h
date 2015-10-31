#pragma once

#include <thread>
#include <mutex>

#include "ILogger.h"
#include "IDGenerator.h"

namespace cubey2 {
	const std::string kDefaultLogFileName = "cubey2.log";
	const size_t kDefaultLogFileWriteInterval = 3000;

	class TXTLoggerMT: public ILogger {
	public:
		void Init() override;
		void Destroy() override;

		void Log(const std::string& message) override;

	private:
		std::mutex mutex_;

		size_t log_file_key_;
		UID disk_write_task_id_;
	};
}
