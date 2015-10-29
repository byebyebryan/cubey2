#pragma once

#include <thread>
#include <unordered_map>

namespace cubey2 {
	struct Thread {
		std::string name_;
	};

	class ThreadManager {
	public:
		template<class ThreadF>
		static void LaunchThread(const std::string& _name, ThreadF&& _f) {
			std::thread new_thread(_f);
			threads_[new_thread.get_id()] = _name;
			new_thread.detach();
		}
	private:
		static std::unordered_map<std::thread::id, Thread> threads_;
	};
}