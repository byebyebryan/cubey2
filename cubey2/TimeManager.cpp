#include "TimeManager.h"

#include <time.h>

namespace cubey2 {
	void TimeManager::Init() {
		start_time_point_ = GetCurrentTime();
	}

	TimePoint TimeManager::GetCurrentTime() {
		return std::chrono::high_resolution_clock::now();
	}

	std::string TimeManager::GetTimeString(const std::string& _format) {
		time_t rawtime;
		struct tm timeinfo;

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		char buffer[80];
		strftime(buffer, 80, _format.c_str(), &timeinfo);

		return std::string(buffer);
	}

	
}