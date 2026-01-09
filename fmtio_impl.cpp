#include "launch_config.h"

#include "fmtio_impl.h"

#if !defined(LAUNCH_NO_HEDGEHOG)

namespace launch {
	void fmtout(const std::string& fmt, const hedgehog& captures, std::ostream& out) {
		std::regex pattern("\\{(\\d+)\\}");

		std::sregex_iterator specifiers_begin(fmt.begin(), fmt.end(), pattern);
		std::sregex_iterator specifiers_end;
		std::vector<int> indices;

		std::sregex_token_iterator split_begin(fmt.begin(), fmt.end(), pattern, -1);
		std::sregex_token_iterator split_end;
		std::vector<std::string> split;

		for (std::sregex_iterator i = specifiers_begin; i != specifiers_end; ++i) {
			std::smatch match = *i;
			try {
				indices.push_back(std::stoi(match[1].str()));
			}
			catch (const std::out_of_range&) {
				indices.push_back(-1);
			}
		}
		for (std::sregex_token_iterator i = split_begin; i != split_end; ++i) {
			split.push_back(i->str());
		}

		for (size_t i = 0; i < indices.size(); ++i) {
			out << split[i];
			try {
				out << captures[indices.at(i)];
			}
			catch (const std::out_of_range&) {
				out << "[BAD_IDX]";
			}
		}
		if (!split.empty() && !fmt.ends_with("}")) {
			out << split.back();
		}
	}
}

#endif