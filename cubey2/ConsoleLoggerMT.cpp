#include "ConsoleLoggerMT.h"

namespace cubey2 {
	void ConsoleLoggerMT::Init() {

	}
	void ConsoleLoggerMT::Log(const std::string & message) {
		auto f_lock = buffer_.LockFrontBuffer();
		buffer_.front_buffer()->push(LogEntryMT(message));
	}
}