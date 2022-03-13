#pragma once

#include <vector>
#include <string>
#include <sstream>

#define LShift 32;

std::vector<std::string> Split(std::string s, std::string seperator);
std::string Trim(std::string s, std::string subString);
std::string ToLower(std::string s);
std::string ToUpper(std::string s);

bool TryParse(std::string str, int& res);
bool TryParse(std::string str, double& res);