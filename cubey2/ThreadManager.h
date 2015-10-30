#pragma once

#include <thread>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "IService.h"
#include "ThreadInfo.h"

namespace cubey2 {
	const std::string kMainThreadName = "Main Thread";

	class ThreadManager : public IService<ThreadManager> {
	public:
		void Init() override;
		void Destroy() override;

		template<class ThreadF, class... ArgTs>
		void LaunchThread(const std::string& _name, ThreadF&& _f, ArgTs... _args) {
			std::lock_guard<std::mutex> lock(mutex_);
			threads_.emplace_back(_f, _args...);
			auto it = threads_.rbegin();
			threads_info_[(*it).get_id()] = ThreadInfo {_name};
		}

		const ThreadInfo& GetThreadInfo();

		size_t GetThreadCount() {
			return threads_.size() + 1;
		}

		size_t GetHardwareThreadCount() {
			return std::thread::hardware_concurrency();
		}
	private:
		std::vector<std::thread> threads_;
		std::unordered_map<std::thread::id, ThreadInfo> threads_info_;

		std::mutex mutex_;
	};
}