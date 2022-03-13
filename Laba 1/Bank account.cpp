#include"Bank account.h"

bool operator>(tm t1, tm t2)
{
	if (t1.tm_year != t2.tm_year) return t1.tm_year > t2.tm_year;
	if (t1.tm_mon != t2.tm_mon) return t1.tm_mon > t2.tm_mon;
	if (t1.tm_mday != t2.tm_mday) return t1.tm_mday > t2.tm_mday;
	if (t1.tm_hour != t2.tm_hour) return t1.tm_hour > t2.tm_hour;
	if (t1.tm_min != t2.tm_min) return t1.tm_min > t2.tm_min;
	return t1.tm_sec > t2.tm_sec;
}

bool operator<(tm t1, tm t2)
{
	if (t1.tm_year != t2.tm_year) return t1.tm_year < t2.tm_year;
	if (t1.tm_mon != t2.tm_mon) return t1.tm_mon < t2.tm_mon;
	if (t1.tm_mday != t2.tm_mday) return t1.tm_mday < t2.tm_mday;
	if (t1.tm_hour != t2.tm_hour) return t1.tm_hour < t2.tm_hour;
	if (t1.tm_min != t2.tm_min) return t1.tm_min < t2.tm_min;
	return t1.tm_sec < t2.tm_sec;
}

bool operator==(tm t1, tm t2)
{
	return t1.tm_year == t2.tm_year && t1.tm_mon == t2.tm_mon 
		&& t1.tm_mday == t2.tm_mday && t1.tm_hour == t2.tm_hour 
		&& t1.tm_min == t2.tm_min && t1.tm_sec == t2.tm_sec;
}

tm BankAccount::SetOpenDate(std::string date)
{
	tm openDate;
	std::vector<std::string> data = Split(date, ".");
	if (data.size() != 3 || !TryParse(data[1], openDate.tm_mon) || !TryParse(data[2], openDate.tm_year) || !TryParse(data[0], openDate.tm_mday))
		throw std::exception("Uncorrect date");
	return openDate;
}

std::string BankAccount::GetOpenDate()
{
	return ToString(openDate.tm_mday) + '.' + ToString(openDate.tm_mon) + '.' + ToString(openDate.tm_year);
}

bool BankAccount::CheckField(std::string fieldName, std::string value)
{
	return GetField(fieldName) == value;
}

void BankAccount::Print(std::ostream& stream)
{
	stream << "Account Number: " << number;
	stream << "\nAccount Code: " << code;
	stream << "\nLast Name: " << lastName;
	stream << "\nDeposit: " << sum;
	stream << "\nPercent: " << percent << '%';
	stream << "\nOpen Date: " << GetOpenDate();
	stream << "\n------------------------------------------\n";
}

bool BankAccount::Read(std::istream& stream)
{
	std::string data;
	std::getline(stream, data, '\n');
	if (data == "") return false;
	std::vector<std::string> strs = Split(data, " ");
	if (!TryParse(strs[strs.size() - 1], number))
		throw std::exception("Uncorrect number");

	std::getline(stream, data, '\n');
	if (data == "") return false;
	strs = Split(data, " ");
	if (!TryParse(strs[strs.size() - 1], code))
		throw std::exception("Uncorrect code");

	std::getline(stream, data, '\n');
	if (data == "") return false;
	strs = Split(data, " ");
	lastName = strs[strs.size() - 1];

	std::getline(stream, data, '\n');
	if (data == "") return false;
	strs = Split(data, " ");
	if (!TryParse(strs[strs.size() - 1], sum) && sum > 0)
		throw std::exception("Uncorrect Deposit");

	std::getline(stream, data, '\n');
	if (data == "") return false;
	strs = Split(data, " ");
	std::string str = Trim(strs[strs.size() - 1], "%");
	if (!TryParse(str, percent) && percent > 0)
		throw std::exception("Uncorrect Percent");

	std::getline(stream, data, '\n');
	if (data == "") return false;
	strs = Split(data, " ");
	openDate = SetOpenDate(strs[strs.size() - 1]);

	std::getline(stream, data, '\n');
	return true;
}

bool BankAccount::SetField(std::string fieldName, std::string value)
{
	if (fieldName == "number") 
	{
		return TryParse(value, number);
	}
	if (fieldName == "code")
	{
		return TryParse(value, code);
	}
	if (fieldName == "lastname")
	{
		lastName = value;
		return true;
	}
	if (fieldName == "sum")
	{
		return TryParse(value, sum);
	}
	if (fieldName == "percent")
	{
		return TryParse(value, percent);
	}
	if (fieldName == "opendate")
	{
		openDate = SetOpenDate(value);
		return true;
	}
	return false;
}

std::string BankAccount::GetField(std::string fieldName)
{
	if (fieldName == "number")
		return ToString(number);
	if (fieldName == "code")
		return ToString(code);
	if (fieldName == "lastname")
		return lastName;
	if (fieldName == "sum")
		return ToString(sum);
	if (fieldName == "percent")
		return ToString(percent);
	if (fieldName == "opendate")
		return GetOpenDate();
	return "";
}

int BankAccount::CompareField(std::string fieldName, std::string value)
{
	if (fieldName == "number")
	{
		int number;
		return TryParse(value, number) ?  this->number - number:false;
	}
	if (fieldName == "code")
	{
		int code;
		return TryParse(value, code) ? this->code - code:false;
	}
	if (fieldName == "lastname")
	{
		if (lastName > value)
			return 1;
		if (lastName < value)
			return -1;
		else
			return 0;
	}
	if (fieldName == "sum")
	{
		double sum;
		return TryParse(value, sum) ? this->sum - sum:false;
	}
	if (fieldName == "percent")
	{
		double percent;
		return TryParse(value, percent) ? this->percent - percent:false;
	}
	if (fieldName == "opendate")
	{
		tm openDate = SetOpenDate(value);
		bool res;
		if (this->openDate > openDate)
			return 1;
		if (this->openDate < openDate)
			return -1;
		else
			return 0;
	}
	return false;
}

void BankAccount::ReadFromConsole()
{
	std::string date;

	std::cout << "Account Number: ";
	std::cin >> number;
	std::cout << "Account Code: ";
	std::cin >> code;
	std::cout << "Last Name: ";
	std::cin >> lastName;
	std::cout << "Deposit: ";
	std::cin >> sum;
	std::cout << "Percent: ";
	std::cin >> percent;
	std::cout << "Open Date [DD.MM.YYYY]: ";
	std::cin >> date;
	openDate = SetOpenDate(date);
}

std::string ToString(int n)
{
	std::stringstream stream;
	stream << n;
	std::string date;
	stream >> date;
	return date;
}

std::string ToString(double n)
{
	std::istringstream stream(n);
	std::string date;
	stream >> date;
	return date;
}