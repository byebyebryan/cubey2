#include "TXTLoggerMT.h"

#include "TimeManager.h"
#include "ThreadManager.h"
#include "FileManager.h"
#include "TaskScheduler.h"

namespace cubey2 {

	void TXTLoggerMT::Init() {
		log_file_key_ = FileManager::GetInstance()->AddOutputFile(kDefaultLogFileName);

		disk_write_task_id_ = TaskScheduler::GetInstance()->ScheduleRepeatingTask(kDefaultLogFileWriteInterval, [=]() {
			FileManager::GetInstance()->GetOutputFile(log_file_key_)->WriteToDisk();
		});
	}

	void TXTLoggerMT::Destroy() {
		TaskScheduler::GetInstance()->UnscheduleRepeatingTask(disk_write_task_id_);
	}

	void TXTLoggerMT::Log(const std::string & _message) {
		std::lock_guard<std::mutex> lock(mutex_);
		std::string msg = TimeManager::GetInstance()->GetTimeString() + " - " + ThreadManager::GetInstance()->GetThreadInfo().name_ + " - " + _message + "\n";
		FileManager::GetInstance()->GetOutputFile(log_file_key_)->Append(msg);
	}
}