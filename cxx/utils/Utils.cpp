/**
 * @file Utils.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "Utils.h"

namespace utils {

void Utils::trim(std::string &s) {
	s.erase(s.begin(),  std::find_if(s.begin(),  s.end(),  std::not1(std::ptr_fun<int,int>(std::isspace))));
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int,int>(std::isspace))).base(), s.end());
};


std::vector<std::string> Utils::tokenize(const std::string &s) {
	std::vector<std::string> tokens;
	std::string::const_iterator it = s.begin();
	while (it != s.end()) {
		std::string::const_iterator it2 = std::find(it, s.end(), '=');
		std::string tmp = std::string(it, it2);
		trim(tmp);
		if (!tmp.empty()) {
			tokens.push_back(tmp);
		}
		it = (it2 == s.end()) ? it2 : it2 + 1;
	}
	return tokens;
}


void Utils::parseFile(const std::string fileName, std::map<std::string, std::string> &properties) {
	std::ifstream *ifs = new std::ifstream(fileName, std::ios::in);
	std::string line;
	std::vector<std::string> tokens;
	while (std::getline(*ifs, line)) {
		trim(line);
		tokens = tokenize(line);
		if (tokens.size() < 2) {
			std::cerr << "Wrong file format. It must contain lines with <key> <value>" << std::endl;
			throw std::exception();
		} else {
			properties.insert(std::make_pair(tokens.at(0), tokens.at(1)));
		}
		tokens.clear();
	}
	ifs->close();
}

corbaAccount::operationType Utils::convertType(OperationType opType) {
	switch (opType) {
	case OperationType::ADD:
		return corbaAccount::operationType::ADD;
	case OperationType::WITHDRAW:
		return corbaAccount::operationType::WITHDRAW;
	}
}

Utils::OperationType Utils::convertType(corbaAccount::operationType opType) {
	switch (opType) {
	case corbaAccount::operationType::ADD:
		return OperationType::ADD;
	case corbaAccount::operationType::WITHDRAW:
		return OperationType::WITHDRAW;
	}
}

std::string Utils::convertDate(const time_t& date) {
	std::tm * ptm = std::localtime(&date);
	char buffer[32];
	std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);
	return std::string(buffer);
}

}
