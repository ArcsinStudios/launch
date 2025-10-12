#pragma once

#include <algorithm>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace launch {
	class clap {
	private:
		std::unordered_map<std::string, std::string> aliases;
		std::unordered_map<std::string, std::string> opts;
		std::vector<std::string> flags;

	public:
		clap(int argc, char* argv[], std::unordered_map<std::string, std::string> _aliases = {});

		std::optional<std::string> get_opt(std::string opt) const;

		bool get_flag(std::string flag) const;
	};
}