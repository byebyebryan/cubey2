#pragma once

#include "ILogger.h"

namespace cubey2 {
	class ConsoleLogger : public ILogger {
	public:
		void Log(const std::string& message) override;

	protected:
		static std::string GetPrefix();
	};
}