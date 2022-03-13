#include "Bank account.h"
#include "Collection.h"
#include<Windows.h>

//Арутюнян Артур Артуровияч
//1
//Счет в банке представляет собой структуру с полями:
//номер счета, код счета, фамилия владельца, сумма на счете, дата открытия счета, годовой процент начисления. 
//Поиск по номеру счета, дате открытия и владельцу.

void Interface();
void Menu(int command, Bank<BankAccount>& bank);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Bank<BankAccount> bank;
	int command = 0;
	while (command != 7)
	{
		Interface();
		std::cin >> command;
		Menu(command, bank);
		std::cin.ignore();
		std::cin.get();
		system("cls");
	}
	return 0;
}

void Interface()
{
	std::cout << "Выберите комманду:\n";
	std::cout << "1. Прочитать файл\n";
	std::cout << "2. Добавить из консоли\n";
	std::cout << "3. Выбрать по фильтру\n";
	std::cout << "4. Сортировать\n";
	std::cout << "5. Обновить\n";
	std::cout << "6. Напечатать\n";
	std::cout << "7. Выход\n";
}

void Read(Bank<BankAccount>& bank)
{
	std::cout << "Введите имя файла\n";
	std::string fileName;
	std::cin >> fileName;
	std::fstream file(fileName);
	if (file.is_open())
	{
		bank.Read(file);
		file.close();
	}
	else
	{
		std::cout << "Не удалось открыть файл\n";
	}
}

void ReadFromConsole(Bank<BankAccount>& bank)
{
	BankAccount* account = new BankAccount();
	account->ReadFromConsole();
	bank.Add(account);
}

void Select(Bank<BankAccount>& bank)
{
	int command;
	std::cout << "1. Фильтровать по номеру счета\n";
	std::cout << "2. Фильтровать по дате открытия\n";
	std::cout << "3. Фильтровать по владельцу\n";
	std::cin >> command;
	std::string param = "";
	std::string value = "";
	switch (command)
	{
	case 1:
		std::cout << "Введите номер счета: ";
		std::cin >> value;
		param = "number";
		break;
	case 2:
		std::cout << "Введите дату открытия счета: ";
		std::cin >> value;
		param = "opendate";
		break;
	case 3:
		std::cout << "Введите фамилию владельца счета: ";
		std::cin >> value;
		param = "lastname";
		break;
	default:
		std::cout << "Неизвестная комманда\n";
		break;
	}
	if (command > 0 && command < 4)
	{
		bank.Select(param + '=' + value);
	}
}

void Sort(Bank<BankAccount>& bank)
{
	int command;
	std::cout << "1. Сортировать по номеру счета\n";
	std::cout << "2. Сортировать по дате открытия\n";
	std::cout << "3. Сортировать по владельцу\n";
	std::cin >> command;
	std::string param = "";
	switch (command)
	{
	case 1:
		param = "number";
		break;
	case 2:
		param = "opendate";
		break;
	case 3:
		param = "lastname";
		break;
	default:
		std::cout << "Неизвестная комманда\n";
		break;
	}
	if (command > 0 && command < 4)
		bank.Sort(param);
}

void UpdateInterface()
{
	std::cout << "1. Номер счета\n";
	std::cout << "2. Код счета\n";
	std::cout << "3. Фамилия\n";
	std::cout << "4. Депозит\n";
	std::cout << "5. Процент\n";
	std::cout << "6. Дата открытия счета\n";
	std::cout << "7. Выход\n";
}

void Update(Bank<BankAccount>& bank)
{
	int command = 0;
	std::string param ="";
	while (command!=7)
	{
		UpdateInterface();
		std::cin >> command;

		switch (command)
		{
		case 1:
			param = "number";
			break;
		case 2:
			param = "code";
			break;
		case 3:
			param = "lastname";
			break;
		case 4:
			param = "sum";
			break;
		case 5:
			param = "percent";
			break;
		case 6:
			param = "opendate";
			break;
		case 7:
			return;
		default:
			std::cout << "Неизвестная комманда\n";
			break;
		}

		std::cout << "Введите новое значение поля\n";
		std::string value;
		std::cin >> value;
		bank.Update(param + '=' + value);
	}
}

void Print(Bank<BankAccount>& bank, std::ostream& stream)
{
	int command;
	std::cout << "1. Печать всех элементов\n";
	std::cout << "2. Печать выбранных элементов\n";
	std::cin >> command;

	if (command == 1)
	{
		bank.Print(stream);
	}
	else if (command == 2)
	{
		bank.PrintSelected(stream);
	}
	else
	{
		std::cout << "Неизвестная комманда\n";
	}

}

void Print(Bank<BankAccount>& bank)
{
	int command;
	std::cout << "1. Печать в файл\n";
	std::cout << "2. Печать на консоль\n";
	std::cin >> command;

	if (command == 1)
	{
		std::cout << "Введите имя файла\n";
		std::string filName;
		std::cin >> filName;
		std::ofstream file(filName);
		Print(bank, file);
		file.close();
	}
	else if (command == 2)
	{
		Print(bank, std::cout);
	}
	else
	{
		std::cout << "Неизвестная комманда\n";
	}

}

void Menu(int command, Bank<BankAccount>& bank)
{
	if (command == 1)
		Read(bank);
	else if (command == 2)
		ReadFromConsole(bank);
	else if (command == 3)
		Select(bank);
	else if (command == 4)
		Sort(bank);
	else if (command == 5)
		Update(bank);
	else if (command == 6)
		Print(bank);
}

