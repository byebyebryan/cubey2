#include "ThreadManager.h"

namespace cubey2 {
	void ThreadManager::Init() {
		std::lock_guard<std::mutex> lock(mutex_);
		threads_info_[std::this_thread::get_id()] = ThreadInfo{ kMainThreadName };
	}

	void ThreadManager::Destroy() {
		for (auto& thread : threads_) {
			thread.join();
		}
	}

	const ThreadInfo& ThreadManager::GetThreadInfo() {
		std::lock_guard<std::mutex> lock(mutex_);
		return threads_info_[std::this_thread::get_id()];
	}
}