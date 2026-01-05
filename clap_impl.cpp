#include "launch_config.h"

#include "clap_impl.h"

namespace launch {
	clap::clap(int argc, char* argv[], std::unordered_map<std::string, std::string> _aliases) {
		aliases = _aliases;
		for (int i = 1; i < argc; ++i) {
			std::string opt = argv[i];
			std::string next_opt;
			if (i + 1 != argc) {
				next_opt = argv[i + 1];
			}
			if (opt.starts_with("--")) {
				size_t eq_pos = opt.find("=");
				std::string raw = opt.substr(2, eq_pos - 2);
				if (eq_pos != std::string::npos) {
					opts[raw] = opt.substr(eq_pos + 1);
				}
				else if (!next_opt.empty() && !next_opt.starts_with("-")) {
					opts[raw] = next_opt;
					++i;
				}
				else {
					flags.push_back(raw);
				}
			}
			else if (opt.starts_with("-")) {
				std::string alias = opt.substr(1);
				std::string temp;
				for (char ch : alias) {
					std::string raw;
					std::unordered_map<std::string, std::string>::iterator raw_it = aliases.find(std::string(1, ch));
					if (raw_it != aliases.end()) {
						raw = raw_it->second;
					}
					else {
						raw = ch;
					}
					flags.push_back(raw);
					temp = raw;
				}
				if (!next_opt.empty() && !next_opt.starts_with("-")) {
					opts[temp] = next_opt;
					++i;
				}
			}
		}
	}

	std::optional<std::string> clap::get_opt(std::string opt) const {
		std::unordered_map<std::string, std::string>::const_iterator it = opts.find(opt);
		if (it == opts.end()) {
			return std::nullopt;
		}
		return it->second;
	}

	bool clap::get_flag(std::string flag) const {
		std::vector<std::string>::const_iterator it = std::find(flags.begin(), flags.end(), flag);
		return it != flags.end();
	}
}