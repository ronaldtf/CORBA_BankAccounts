/**
 * \file Utils.hpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
 */

#include <map>
#include <vector>

namespace utils {
	class Utils {
	public:
		static void trim(std::string &s);

		static std::vector<std::string> tokenize(const std::string &s);

		static void parseFile(const std::string fileName, std::map<std::string, std::string> &properties);

		static void convertMapToArray(std::map<std::string, std::string> m, char**** arr);

	};
}
