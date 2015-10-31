#pragma once

#include <stdint.h>

namespace cubey2 {
	using UID = uint64_t;

	template <typename T>
	class IDGenerator {
	public:
		static UID NextID() {
			return ++current_id_;
		}

	private:
		static UID current_id_;
	};

	template <typename T>
	UID IDGenerator<T>::current_id_ = 0;
}