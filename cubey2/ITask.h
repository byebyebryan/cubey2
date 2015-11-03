#pragma once

#include <functional>

#include "IDGenerator.h"
#include "TimeManager.h"

namespace cubey2 {
	template <typename TaskT>
	class ITask {
	public:
		ITask() : 
				id_(IDGenerator<TaskT>::NextID()),
				is_marked_for_deletion_(false) {}

		ITask(const std::function<void()>& _process_fn) :
				id_(IDGenerator<TaskT>::NextID()),
				process_fn_(_process_fn),
				is_marked_for_deletion_(false) {}

		virtual ~ITask() {}

		virtual void Start(const TimePoint& _now) = 0;
		virtual void Update(const TimePoint& _now) = 0;

		UID id_;
		std::function<void()> process_fn_;
		bool is_marked_for_deletion_;
	};
}