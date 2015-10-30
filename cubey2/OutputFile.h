#pragma once

#include <fstream>
#include <string>

#include "DuoBufferMTB.h"

namespace cubey2 {
	

	class OutputFile {
	public:
		OutputFile() :
			file_name_(""),
			file_path_("") {
		}

		OutputFile(const std::string& _file_name, const std::string& _file_path, size_t _buffer_size) :
				file_name_(_file_name),
				file_path_(_file_path) {
			auto f_lock = buffer_.LockFrontBuffer();
			auto b_lock = buffer_.LockBackBuffer();
			buffer_.front_buffer()->reserve(_buffer_size);
			buffer_.back_buffer()->reserve(_buffer_size);
		}

		void Append(const std::string& text) {
			auto f_lock = buffer_.LockFrontBuffer();
			buffer_.front_buffer()->append(text);
		}

		bool WriteToDisk() {
			buffer_.SwapMTB();
			if (Open()) {
				auto b_lock = buffer_.LockBackBuffer();
				ofstream_.write(buffer_.back_buffer()->c_str(), buffer_.back_buffer()->size());
				ofstream_.close();
				buffer_.back_buffer()->clear();

				return true;
			}
			return false;
		}

	private:
		std::ofstream ofstream_;
		DuoBufferMTB<std::string> buffer_;
		std::string file_name_;
		std::string file_path_;

		bool Open() {
			if (!ofstream_.is_open()) {
				ofstream_.open(file_path_ + file_name_, std::ofstream::app);
			}

			return ofstream_.is_open();
		}
	};
}