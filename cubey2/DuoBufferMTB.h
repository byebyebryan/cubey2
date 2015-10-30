#pragma once

#include <thread>
#include <mutex>

#include "DuoBuffer.h"

namespace cubey2 {
	template<typename BufferT>
	class DuoBufferMTB : public DuoBuffer<BufferT> {
	public:
		DuoBufferMTB () : DuoBuffer() {
		}

		DuoBufferMTB (const DuoBufferMTB<BufferT>& _other) {
			std::lock_guard<std::mutex> f_lock(_other.front_buffer_mutex_);
			std::lock_guard<std::mutex> b_lock(_other.back_buffer_mutex_);
			ping_ = _other.ping_;
			pong_ = _other.pong_;
			flip_ = _other.flip_;
		}

		DuoBufferMTB(DuoBufferMTB<BufferT>&& _other) {
			std::lock_guard<std::mutex> f_lock(_other.front_buffer_mutex_);
			std::lock_guard<std::mutex> b_lock(_other.back_buffer_mutex_);
			ping_ = std::move(_other.ping_);
			pong_ = std::move(_other.pong_);
			flip_ = std::move(_other.flip_);
		}

		void SwapMTB() {
			auto f_lock = LockFrontBuffer();
			auto b_lock = LockBackBuffer();
			Swap();
		}

		std::unique_lock<std::mutex> LockFrontBuffer() {
			return std::unique_lock<std::mutex>(front_buffer_mutex_);
		}

		std::unique_lock<std::mutex> LockBackBuffer() {
			return std::unique_lock<std::mutex>(back_buffer_mutex_);
		}
	protected:
		mutable std::mutex front_buffer_mutex_;
		mutable std::mutex back_buffer_mutex_;
	};
}