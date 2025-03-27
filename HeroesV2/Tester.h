#pragma once
#include <vector>
#include "ResultsLib.h"
class Tester
{
public:
	const char* file;
	Tester() : file("HeroesV2.log")
	{
		std::vector<std::string> codeFiles{ "HeroesDB.h", "HeroesDB.cpp", "HeroesV2.cpp" };
		results::Log(file, codeFiles);
	}
};

