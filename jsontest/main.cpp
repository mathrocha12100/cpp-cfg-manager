#include <iostream>

#include "CFG.h"

int main() {

	std::string cfgPath = "./cfgs/cfg1.json";


	json JSON;

	CFG::GetCFG(cfgPath, JSON);

	std::cout << JSON["fov"] << std::endl;

	JSON["fov"] = 3424;
	JSON["aimbot"]["smooth"] = 1.3;

	CFG::SaveCFG(cfgPath, JSON);

	std::cout << JSON["fov"];

	return 0;
}
