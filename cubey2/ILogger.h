#pragma once

#include <iostream>
#include <sstream>

namespace cubey2 {
	
	class ILogger {
	public:
		virtual ~ILogger() {}
		virtual void Log(const std::string& message) = 0;
	};
}