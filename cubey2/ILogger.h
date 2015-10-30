#pragma once

#include "IService.h"

namespace cubey2 {
	class ILogger : public IService<ILogger> {
	public:
		virtual ~ILogger() {}
		virtual void Log(const std::string& message) = 0;
	};

	using Logger = ILogger;
}