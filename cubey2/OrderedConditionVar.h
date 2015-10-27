#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace cubey2 {
	//
	//	Helper around std::condition_variable to provide ordered execution.
	//	Waiting instances will be waken up and unblocked one at a time based on the order
	//	they entered the wait.
	//
	class OrderedConditionVar {
	public:
		std::mutex mutex_;

		OrderedConditionVar() {
			queue_end_index_ = 0;
			queue_current_index_ = 0;
		}

		std::unique_lock<std::mutex> GetLock() {
			return std::unique_lock<std::mutex>(mutex_);
		}

		void Wait(std::unique_lock<std::mutex>& lock) {
			int queued_index = ++queue_end_index_;
			condition_variable_.wait(lock, [&]() {return queue_current_index_ == queued_index; });
		}

		/*void Wait() {
			auto lock = GetLock();
			Wait(lock);
		}*/

		/*template<class PredicateF>
		void Wait(std::unique_lock<std::mutex>& lock, PredicateF predicate) {
			int queued_index = ++queue_end_index_;
			condition_variable_.wait(lock, [&]() {return (queue_current_index_ == queued_index) && predicate(); });
		}*/

		void NotifyNext(std::unique_lock<std::mutex>& lock) {
			++queue_current_index_;
			condition_variable_.notify_all();
			lock.unlock();
		}

		void Reset() {
			queue_end_index_ = 0;
			queue_current_index_ = 0;
		}

		void Start() {
			++queue_current_index_;
		}

	private:
		std::condition_variable condition_variable_;
		std::atomic_int queue_end_index_;
		std::atomic_int queue_current_index_;
	};
}