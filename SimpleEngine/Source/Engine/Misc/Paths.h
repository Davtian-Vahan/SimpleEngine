#pragma once

#include <filesystem>
#include <iostream>

class Paths
{
public:
	static std::string solution_dir()
	{
		std::filesystem::path p = std::filesystem::current_path();
		return p.string();
	}

	static std::string source_dir()
	{
		std::string abs_dir = solution_dir();
		return abs_dir + "\\Source";
	}

	static std::string engine_source_dir()
	{
		std::string src_dir = source_dir();
		return src_dir + "\\Engine";
	}

	static std::string engine_resource_dir()
	{
		std::string eng_src_dir = engine_source_dir();
		return eng_src_dir + "\\Resources";
	}
};