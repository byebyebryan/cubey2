#pragma once

#include "ILogger.h"
#include "IService.h"
#include "LoggerUtil.h"

namespace cubey2 {
	class ConsoleLogger : public ILogger, public IService<ILogger, ConsoleLogger> {
		void Log(const std::string& message) override;
	};
}