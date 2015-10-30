#pragma once

#include <unordered_map>

#include "IService.h"
#include "OutputFile.h"

namespace cubey2 {
	const int kDefaultOutputFileBufferSize = 4096;
	const std::string kDefaultOutputFilePath = "./";

	class FileManager : public IService<FileManager> {
	public:
		size_t AddOutputFile(const std::string& _file_name, const std::string& _file_path = kDefaultOutputFilePath, size_t _buffer_size = kDefaultOutputFileBufferSize) {
			size_t key = std::hash<std::string>()(_file_path + _file_name);
			output_files_.emplace(std::make_pair(key, OutputFile(_file_name, _file_path, _buffer_size)));
			return key;
		}

		OutputFile* GetOutputFile(size_t _key) {
			return &output_files_[_key];
		}

	private:
		std::unordered_map<size_t, OutputFile> output_files_;
	};
}


