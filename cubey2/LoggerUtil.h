#pragma once

#include <iostream>

#include "ServiceLocator.h"
#include "ILogger.h"

namespace cubey2 {

	inline void Log(const std::string& message) {
		ServiceLocator<ILogger>::service()->Log(message);
	}

	class LoggerUtil {
	public:
		static std::string GetPrefix();

		template<typename LoggerT>
		static void InitLoggerService() {
			ServiceLocator<ILogger>::set_service(new LoggerT());
		}
	};

}
