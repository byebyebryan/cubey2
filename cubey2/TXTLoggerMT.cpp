#include "TXTLoggerMT.h"

#include "TimeManager.h"
#include "ThreadManager.h"
#include "FileManager.h"

namespace cubey2 {

	void TXTLoggerMT::Init() {
		log_file_key_ = FileManager::GetInstance()->AddOutputFile("test.log");
	}

	void TXTLoggerMT::Destroy() {
		FileManager::GetInstance()->GetOutputFile(log_file_key_)->WriteToDisk();
	}

	void TXTLoggerMT::Log(const std::string & _message) {
		std::lock_guard<std::mutex> lock(mutex_);
		std::string msg = TimeManager::GetInstance()->GetTimePrefix() + " - " + ThreadManager::GetInstance()->GetThreadInfo().name_ + " - " + _message + "\n";
		FileManager::GetInstance()->GetOutputFile(log_file_key_)->Append(msg);
	}
}