#pragma once

#include <chrono>

#include "IService.h"

namespace cubey2 {
	const std::string kDefaultTimeFormat = "%Y/%m/%d_%X";

	using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

	class TimeManager : public IService<TimeManager> {
	public:
		void Init() override;

		TimePoint GetCurrentTime();
		std::string GetTimeString(const std::string& _format = kDefaultTimeFormat);

	private:
		TimePoint start_time_point_;
	};
}


