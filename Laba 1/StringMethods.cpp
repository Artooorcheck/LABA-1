#include "StringMethods.h"

std::vector<std::string> Split(std::string s, std::string seperator)
{
	std::vector<std::string> output;

	std::string::size_type prev_pos = 0, pos = 0;

	while ((pos = s.find(seperator, pos)) != std::string::npos)
	{
		std::string substring(s.substr(prev_pos, pos - prev_pos));

		output.push_back(substring);

		pos += seperator.size();

		prev_pos = pos;
	}

	output.push_back(s.substr(prev_pos, pos - prev_pos));

	return output;
}

std::string Trim(std::string s, std::string subString)
{
	std::vector<std::string> strs = Split(s, subString);

	std::string res;

	for (std::string str : strs)
		res = res + str;
	return res;
}

std::string ToLower(std::string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += LShift;
	}
	return s;
}

std::string ToUpper(std::string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= LShift;
	}
	return s;
}

bool TryParse(std::string str, int& res)
{
	std::istringstream stream(str);
	try
	{
		stream >> res;
	}
	catch (std::exception e)
	{
		return false;
	}
	return true;
}

bool TryParse(std::string str, double& res)
{
	std::istringstream stream(str);
	try
	{
		stream >> res;
	}
	catch (std::exception e)
	{
		return false;
	}
	return true;
}
