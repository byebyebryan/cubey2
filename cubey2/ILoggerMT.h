#pragma once

#include <queue>

#include "ILogger.h"
#include "DuoBufferMTB.h"

namespace cubey2 {
	class ILoggerMT : public ILogger {
	public:
		void Log(const std::string& message) override;

	protected:
		struct LogEntryMT {
			std::thread::id thread_id;
			time_t time_stamp;
			std::string message;

			LogEntryMT(const std::string& _message) :
				thread_id(std::this_thread::get_id()),
				time_stamp(time(NULL)),
				message(_message) {}
		};

		void ProcessBackBuffer();

		DuoBufferMTB<std::queue<LogEntryMT>> buffer_;
	};
}