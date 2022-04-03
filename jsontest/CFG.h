#pragma once

#include "json.hpp"

using json = nlohmann::basic_json<std::map, std::vector, std::string, bool, std::int64_t, std::uint64_t, float>;
using value_t = json::value_t;

namespace SystemFF {
	bool CreateFolder(std::string path, std::string folderName);
	bool CreateNewFile(std::string path, std::string fileName);
	bool FolderAlreadyExists(std::string path, std::string folderName);

	std::string GetFileExtension(std::string fileName);
	std::vector<std::string> GetAllFilesInDirectory(std::string path);
};

namespace CFG {
	void InitCFG();
	bool GetCFG(std::string path, json& JSON);
	bool SaveCFG(std::string path, json JSON);
};