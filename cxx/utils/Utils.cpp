/**
 * \file Utils.cpp
 * \author Ronald T. Fernandez
 * \mail ronaldtfernandez@gmail.com
 * \version 1.0
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
		std::string::const_iterator it2 = std::find(it, s.end(), ' ');
		if (it2 != s.end()) {
			tokens.push_back(std::string(it + 1, it2 - 1));
			it = it2 + 1;
		}
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
		}
		properties.insert(std::make_pair(tokens.at(0), tokens.at(1)));
	}
	ifs->close();
}

void Utils::convertMapToArray(std::map<std::string, std::string> m, char**** arr) {
	unsigned int pos = 0;
	for (std::map<std::string, std::string>::iterator it = m.begin(); it != m.end(); ++it) {
		(*arr)[pos][0] = const_cast<char*>(it->first.c_str());
		(*arr)[pos++][1] = const_cast<char*>(it->second.c_str());
	}
}
}


