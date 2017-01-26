/**
 * @file Utils.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "../../idl/Account.hh"

#include <ctime>
#include <map>
#include <vector>

namespace utils {
	class Utils {
	public:

		/**
		 * Define the type of possible account operations
		 */
		enum class OperationType {ADD=1, WITHDRAW=2};

		/**
		 * Trim a string
		 * @param[in/out] s String to be trimmed
		 */
		static void trim(std::string &s);

		/**
		 * Split string into words
		 * @return List of words in the string (considering spaces as the separator)
		 */
		static std::vector<std::string> tokenize(const std::string &s);

		/**
		 * Extract the properties from a property file and put them in a map
		 * @param[in] fileName		Name of the file to be parsed
		 * @param[out]	properties	Map of properties in the form <property_name, value>
		 */
		static void parseFile(const std::string fileName, std::map<std::string, std::string> &properties);

		/**
		 * Converts an operation of type Utils::OperationType to corbaAccount::operationType
		 * @param[in] opType	Operation type to be converted
		 * @return	Returns the equivalent corbaAccount::operationType
		 */
		static corbaAccount::operationType convertType(OperationType opType);

		/**
		 * Converts an operation of type Utils::OperationType to corbaAccount::operationType
		 * @param[in] opType	Operation type to be converted
		 * @return	Returns the equivalent Utils::OperationType
		 */
		static Utils::OperationType convertType(corbaAccount::operationType opType);

		/**
		 * Converts a date/time to a string
		 * @param[in] date	Date/Time to be converted
		 * @return	Date string
		 */
		static std::string convertDate(const time_t& date);

	};
}
