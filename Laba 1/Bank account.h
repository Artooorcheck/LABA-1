#pragma once
#include <string>
#include <list>
#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include "StringMethods.h"
#include "Node.h"
#include<cmath>

std::string ToString(int n);
std::string ToString(double n);

struct BankAccount: Node
{
private:
	int number;
	int code;
	std::string lastName;
	double sum;
	double percent;
	tm openDate;

	tm SetOpenDate(std::string date);
	std::string GetOpenDate();
public:
	void ReadFromConsole();
	virtual bool CheckField(std::string fieldName, std::string value) override;
	virtual void Print(std::ostream& stream) override;
	virtual bool Read(std::istream& stream) override;
	virtual bool SetField(std::string fieldName, std::string value) override;
	virtual std::string GetField(std::string fieldName) override;
	virtual int CompareField(std::string fieldName, std::string value) override;
};