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

	private:
		DuoBufferMTB<std::queue<std::string>> buffer_;
	};
}