#pragma once

#include <iostream>
#include <sstream>

#include "IService.h"

namespace cubey2 {
	class ILogger : public IService<ILogger> {
	public:
		virtual ~ILogger() {}
		virtual void Log(const std::string& message) = 0;
	};
}