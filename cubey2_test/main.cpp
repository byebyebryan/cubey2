
#include "queue"
#include "vector"

#include "Cubey2.h"

using namespace cubey2;

DuoBufferMTB<std::queue<std::string>> logging_buffer;

void LoggingTest() {
	static int g_id = 0;
	int t_id = ++g_id;
	for (int i = 0; i < 100;i++) {
		auto lock = logging_buffer.LockFrontBuffer();
		logging_buffer.front_buffer()->push("thread " + std::to_string(t_id) + " count " + std::to_string(i) + "\n");
	}
}

int main(void) {
	ConsoleLogger::InitService();

	for (int i = 0; i < 10; i++ ) {
		std::thread t_thread(LoggingTest);
		t_thread.detach();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	logging_buffer.SwapMTB();

	auto lock = logging_buffer.LockBackBuffer();
	while(!logging_buffer.back_buffer()->empty()) {
		std::string str = logging_buffer.back_buffer()->front();
		std::cout << str;
		logging_buffer.back_buffer()->pop();
	}
}