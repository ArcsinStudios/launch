export module goodstr:impl;

import std;

namespace launch {
	export std::vector<std::string> split(const std::string& orig, const std::string& delim);

	export std::string concat(const std::vector<std::string>& list, const std::string& sep = "");

	export std::string replace(std::string orig, const std::string& from, const std::string& to);

	export void replace_inplace(std::string& orig, const std::string& from, const std::string& to);

	export std::string ltrim(const std::string& orig);

	export std::string rtrim(const std::string& orig);

	export std::string trim(const std::string& orig);

	export void ltrim_inplace(std::string& orig);

	export void rtrim_inplace(std::string& orig);

	export void trim_inplace(std::string& orig);
}