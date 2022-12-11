#pragma once

#include <filesystem>
#include <iostream>

class Paths
{
public:
	static std::string engine_absolute_path()
	{
		std::filesystem::path p = std::filesystem::current_path();
		return p.string();
	}

	static std::string source_dir()
	{
		std::string abs_path = engine_absolute_path();
		return abs_path + "\\Source";
	}
};