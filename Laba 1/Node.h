#pragma once
#include <string>


struct Node
{
	virtual bool CheckField(std::string fieldName, std::string value) { return false; }
	virtual int CompareField(std::string fieldName, std::string value) { return false; }
	virtual void Print(std::ostream& stream) {}
	virtual bool Read(std::istream& stream) { return false; }
	virtual std::string GetField(std::string fieldName) { return ""; }
	virtual bool SetField(std::string fieldName, std::string value) { return false; }
};