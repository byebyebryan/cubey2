#pragma once

#include <functional>

#include "IDGenerator.h"
#include "TimeManager.h"

namespace cubey2 {
	struct RepeatingTask {
		UID id_;
		std::chrono::milliseconds interval_;
		TimePoint last_run_time_;
		TimePoint next_run_time_;

		std::function<void()> process_fn_;
		std::function<bool()> override_trigger_fn_;

		void Update() {
			TimePoint now = TimeManager::GetInstance()->GetCurrentTime();
			if (now > next_run_time_ || override_trigger_fn_()) {
				process_fn_();
				last_run_time_ = now;
				next_run_time_ = now + interval_;
			}
		}
	};
}