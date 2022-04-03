#include "CFG.h"

#include <fstream>
#include <iostream>

#include "dirent.h"
#include <sys/types.h>
#include <direct.h>
#include <Windows.h>
#include <shlobj.h>

const std::string backslash = "\\";

bool SystemFF::CreateFolder(std::string path, std::string folderName) {
	std::string folder = path + folderName;

	int status = _mkdir(folder.c_str());

	return status == -1 ? false : true;
}

bool SystemFF::FolderAlreadyExists(std::string path, std::string folderName) {
	DIR* directory;
	struct dirent* en;

	directory = opendir(path.c_str()); //open all or present directory

	int attemps = 0;
	bool found = false;

	if (directory) {
		while (((en = readdir(directory)) != NULL) && !found) {

			if (attemps >= 5000) break; // 5000 attemps e nao achou a pasta? wtf

			if (SystemFF::GetFileExtension(en->d_name) == "") continue;

			if (!strcmp(en->d_name, folderName.c_str())) {
				found = true;
				break;
			}

			attemps++;
		}
		closedir(directory); //close all directory
	}

	return found;
}

bool SystemFF::CreateNewFile(std::string path, std::string fileName) {

	std::string pathName = path + "/" + fileName;

	std::ofstream file(pathName.c_str());

	return file.good();
}

std::string SystemFF::GetFileExtension(std::string fileName) {
	std::string extension;
	int count = fileName.length();

	while (count > 0) {
		char actualLetter = fileName.at(count - 1);

		if (actualLetter == '.') {
			std::reverse(extension.begin(), extension.end());

			if (extension != "json") extension = "";			
			break;
		}

		extension += actualLetter;

		count--;
	}


	return extension;
}

std::vector<std::string> SystemFF::GetAllFilesInDirectory(std::string path) {
	DIR* directory;
	struct dirent* en;

	directory = opendir(path.c_str()); //open all or present directory
	
	std::vector<std::string> files{};

	int attemps = 0;

	if (directory) {
		while ((en = readdir(directory)) != NULL) {

			if (attemps >= 5000) break; // 5000 attemps e nao achou arquivo? wtf

			if (SystemFF::GetFileExtension(en->d_name) == "") continue;
		
			files.push_back(en->d_name);

			attemps++;
		}
		closedir(directory); //close all directory
	}

	return files;
};

bool CFG::GetCFG(std::string path, json& JSON) {
	std::ifstream in{ path };

	if (in.good()) {
		JSON = json::parse(in, nullptr, false);
	
		return true;
	}

	return false;
}

bool CFG::SaveCFG(std::string path, json JSON) {
	std::ofstream file(path);

	if (file.good()) {
		file << JSON;
		return true;
	}

	return false;
}

void CFG::InitCFG() {

	char path[MAX_PATH];

	const std::string cfgFolderName = "test";
	SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path);

	if (!SystemFF::FolderAlreadyExists(path, cfgFolderName)) {
		SystemFF::CreateFolder(path, cfgFolderName);
	}

	std::string cfgPath = path + backslash + cfgFolderName;


	std::vector<std::string> cfgs = SystemFF::GetAllFilesInDirectory(cfgPath);

	if (cfgs.size() == 0) {
		SystemFF::CreateNewFile(cfgPath, "cfg_example_1.json");
	}

	// should list all files in cfgPath
	for (int i = 0; i < cfgs.size(); i++) {
		std::cout << "val = " << cfgs[i] << "\n";
	}
}