#pragma once

#include <thread>
#include <unordered_map>

#include "IService.h"
#include "Thread.h"

namespace cubey2 {
	class ThreadManager : public IService<ThreadManager> {
	public:
		template<class ThreadF, class... ArgTs>
		void LaunchThread(const std::string& _name, ThreadF&& _f, ArgTs... _args) {
			std::thread new_thread(_f, _args...);
			
			new_thread.detach();
		}

		void AddThread(const Thread& _new_thread) {
			threads_[std::this_thread::get_id()] = _new_thread;
		}

		const Thread& GetThread() {
			return threads_[std::this_thread::get_id()];
		}
	private:
		std::unordered_map<std::thread::id, Thread> threads_;
	};
}