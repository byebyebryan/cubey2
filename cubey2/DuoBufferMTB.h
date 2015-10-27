#pragma once

#include <thread>
#include <mutex>

#include "DuoBuffer.h"

namespace cubey2 {
	template<typename BufferT>
	class DuoBufferMTB : public DuoBuffer<BufferT> {
	public:
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
		std::mutex front_buffer_mutex_;
		std::mutex back_buffer_mutex_;
	};
}