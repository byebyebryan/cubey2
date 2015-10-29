#pragma once

#include <queue>

#include "ILogger.h"
#include "IService.h"
#include "LoggerUtil.h"
#include "DuoBufferMTB.h"

namespace cubey2 {
	class ConsoleLoggerMT : public ILogger, public IService<ILogger, ConsoleLoggerMT> {
	public:
		void Init() override;
		void Log(const std::string& message) override;

		struct LogEntryMT {
			std::thread::id thread_id;
			time_t time_stamp;
			std::string message;

			LogEntryMT(const std::string& _message) :
				thread_id(std::this_thread::get_id()),
				time_stamp(time(NULL)),
				message(_message) {}
		};
	private:
		DuoBufferMTB<std::queue<LogEntryMT>> buffer_;
	};
}