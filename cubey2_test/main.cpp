
#include "queue"
#include "vector"

#include "Cubey2.h"

using namespace cubey2;

DuoBufferMTB<std::queue<std::string>> logging_buffer;

void LoggingTest() {
	/*static int g_id = 0;
	int t_id = ++g_id;
	for (int i = 0; i < 100;i++) {
		auto lock = logging_buffer.LockFrontBuffer();
		logging_buffer.front_buffer()->push("thread " + std::to_string(t_id) + " count " + std::to_string(i) + "\n");
	}*/

	for (int i = 0; i < 10;i++) {
		Logger::GetInstance()->Log("count " + std::to_string(i));
	}
}

int main(void) {
	TimeManager::InitService();
	ThreadManager::InitService();
	FileManager::InitService();
	//Logger::InitService<ConsoleLoggerMT>();
	TaskScheduler::InitService();
	Logger::InitService<TXTLoggerMT>();

	/*for (int i = 0; i < 10; i++ ) {
		ThreadManager::GetInstance()->LaunchThread("thread"+std::to_string(i), LoggingTest);
	}*/

	/*TimePoint start = TimeManager::GetInstance()->GetCurrentTime();

	std::cout << FileManager::GetInstance()->GetOutputFile("test.log")->file_size() << std::endl;

	Logger::GetInstance()->Log("cores : [" + std::to_string(std::thread::hardware_concurrency()) + "]");

	FileManager::GetInstance()->GetOutputFile("test.log")->WriteToDisk();

	std::cout << FileManager::GetInstance()->GetOutputFile("test.log")->file_size() << std::endl;*/

	TaskScheduler::GetInstance()->ScheduleRepeatingTask(2000, LoggingTest);

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	
	TaskScheduler::GetInstance()->UnscheduleAllTask();

	ServiceLocator<Logger>::ShutDownService();
	ServiceLocator<TaskScheduler>::ShutDownService();
	ServiceLocator<FileManager>::ShutDownService();
	ServiceLocator<ThreadManager>::ShutDownService();
	ServiceLocator<TimeManager>::ShutDownService();
	
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	/*logging_buffer.SwapMTB();

	auto lock = logging_buffer.LockBackBuffer();
	while(!logging_buffer.back_buffer()->empty()) {
		std::string str = logging_buffer.back_buffer()->front();
		std::cout << str;
		logging_buffer.back_buffer()->pop();
	}*/
}