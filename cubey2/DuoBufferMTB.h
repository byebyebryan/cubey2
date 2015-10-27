#pragma once

#include <thread>
#include <mutex>

#include "DuoBuffer.h"
#include "OrderedConditionVar.h"

namespace cubey2 {
	template<typename BufferT>
	class DuoBufferMTB : public DuoBuffer<BufferT> {
	public:
		std::unique_lock<std::mutex> GetFrontBufferLock() {
			return front_buffer_condition_var_.GetLock();
		}

		void LockFrontBuffer(std::unique_lock<std::mutex>& lock) {
			if (swap_requested_) {
				WaitForSwap();
			}
			front_buffer_condition_var_.Wait(lock);
		}

		void UnlockFrontBuffer(std::unique_lock<std::mutex>& lock) {
			front_buffer_condition_var_.NotifyNext(lock);
		}

		void WaitForSwap() {
			auto lock = swap_condition_var_.GetLock();
			swap_condition_var_.Wait(lock);
			swap_condition_var_.NotifyNext(lock);
		}

		void SwapMTB() {
			if(!swap_requested_) {
				swap_requested_ = true;

				auto f_lock = front_buffer_condition_var_.GetLock();
				auto b_lock = back_buffer_condition_var_.GetLock();
				front_buffer_condition_var_.Wait(f_lock);
				back_buffer_condition_var_.Wait(b_lock);

				DuoBuffer<BufferT>::Swap();

				swap_condition_var_.Start();
			}
			else {
				WaitForSwap();
			}
		}

	protected:
		OrderedConditionVar front_buffer_condition_var_;
		OrderedConditionVar back_buffer_condition_var_;
		OrderedConditionVar swap_condition_var_;

		std::atomic_bool swap_requested_;
		std::atomic_bool swap_finished_;
	};
}