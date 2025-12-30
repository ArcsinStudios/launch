#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace launch {
	std::vector<std::string> split(const std::string& orig, char delim);

	std::string concat(const std::vector<std::string>& list, const std::string& sep = "");

	std::string replace(std::string orig, const std::string& from, const std::string& to);

	void replace_inplace(std::string& orig, const std::string& from, const std::string& to);

	std::string trim(const std::string& orig);

	std::string ltrim(const std::string& orig);

	std::string rtrim(const std::string& orig);

	void trim_inplace(std::string& orig);

	void ltrim_inplace(std::string& orig);

	void rtrim_inplace(std::string& orig);
}