#pragma once
#include "Node.h"
#include <list>
#include<functional>
#include<algorithm>

struct Filter
{
	std::string param;
	std::string value;
	Filter(std::string param, std::string value)
	{
		this->param = param;
		this->value = value;
	}
};

template<typename T, typename = std::enable_if_t<std::is_base_of_v<Node, T>>>
class Bank
{
	std::vector<Node*> accounts;
	std::vector<std::vector<Node*>::iterator> selected;
	std::string sortField;

	std::vector<Filter> ParsReq(std::string req)
	{
		std::vector<std::string> coef = Split(req, " AND ");

		std::vector<Filter> filters;
		for (auto i : coef)
		{
			std::vector<std::string> coe = Split(i, "=");
			filters.push_back(Filter(Trim(ToLower(coe[0]), " "), Trim(coe[1], " ")));
		}
		return filters;
	}

	static bool CheckParams(Node* elem, std::vector<Filter>& filters)
	{
		for (Filter f : filters)
		{
			if (!elem->CheckField(f.param, f.value))
				return false;
		}
		return true;
	}

	void SetField(std::vector<Node*>::iterator elem, std::vector<Filter>& newData)
	{
		for (Filter f : newData)
		{
			(*elem)->SetField(f.param, f.value);
			if (f.param == sortField)
				sortField = "";
		}
	}

	void Print(std::ostream& stream, std::vector<std::vector<Node*>::iterator>::iterator begin, std::vector<std::vector<Node*>::iterator>::iterator end)
	{
		for (auto i = begin; i != end; i++)
		{
			(**i)->Print(stream);
		}
	}

	void Print(std::ostream& stream, std::vector<Node*>::iterator begin, std::vector<Node*>::iterator end)
	{
		for (auto i = begin; i != end; i++)
		{
			i->Print(stream);
		}
	}

	void Search(std::vector<Filter> filters)
	{
		for (auto i = accounts.begin(); i != accounts.end(); i++)
		{
			if (CheckParams(*i, filters))
				selected.push_back(i);
		}
	}

	int BinarySearchFirst(Filter filter)
	{

		int left = 0, midd = 0, right = accounts.size() - 1;
		while (true)
		{
			midd = (left + right) / 2;

			if (accounts[midd]->CompareField(filter.param, filter.value) > 0)
				right = midd - 1;
			else if (accounts[midd]->CompareField(filter.param, filter.value) < 0)
				left = midd + 1;
			else
				return midd;

			if (left > right)
				return midd;
		}

	}

	void BinarySearch(Filter filter)
	{
		std::vector<Node*>::iterator res = accounts.begin();

		int index = BinarySearchFirst(filter);

		if (accounts[index]->GetField(filter.param) == filter.value)
		{
			std::advance(res, index);
		}
		else return;

		while ((*res)->CheckField(filter.param, filter.value))res--;
		res++;
		do
		{
			selected.push_back(res);
			res++;
		} while ((*res)->CheckField(filter.param, filter.value));
	}

public:

	void Read(std::istream& stream)
	{
		while (stream)
		{
			T* account = new T();
			if (!stream.fail() && account->Read(stream))
				accounts.push_back(account);
		}
	}

	void Print(std::ostream& stream)
	{
		for (Node* elem : accounts)
		{
			elem->Print(stream);
		}
	}

	void PrintSelected(std::ostream& stream)
	{
		Print(stream, selected.begin(), selected.end());
	}

	void Add(T* elem)
	{
		if (sortField == "")
		{
			accounts.push_back(elem);
		}
		else
		{
			int index = BinarySearchFirst(Filter(sortField, elem->GetField(sortField)));
			if(index>=accounts.size()-1)
				accounts.push_back(elem);
			else if (accounts[index]->CompareField(sortField, elem->GetField(sortField)) > 0)
			{
				std::vector<Node*>::iterator res = accounts.begin();
				std::advance(res, index);
				accounts.insert(res, elem);
			}
			else
			{
				std::vector<Node*>::iterator res = accounts.begin();
				std::advance(res, index+1);
				accounts.insert(res, elem);
			}
			selected.clear();
		}
	}

	void Remove()
	{
		for (auto i = selected.begin(); i != selected.end(); i++)
		{
			accounts.erase(i);
		}
	}

	std::vector<T> Select(std::string req)
	{
		std::vector<Filter> filters = ParsReq(req);
		selected.clear();
		if (filters.size() == 1 && sortField == filters[0].param)
		{
			BinarySearch(filters[0]);
		}
		else
		{
			Search(filters);
		}
		return GetSelected();
	}

	void Update(std::string req)
	{
		std::vector<Filter> newData = ParsReq(req);
		for (auto i = selected.begin(); i != selected.end(); i++)
		{
			SetField(*i, newData);
		}
	}

	void Sort(std::string field)
	{
		sortField = field;
		selected.clear();
		std::sort(accounts.begin(), accounts.end(), [&field](Node* a, Node* b) {return a->CompareField(field, b->GetField(field))<0; });
	}

	std::vector<T> GetSelected()
	{
		std::vector<T> res;
		for (auto i : selected)
		{
			T* e = dynamic_cast<T*>(*i);
			res.push_back(*e);
		}
		return res;
	}

	~Bank()
	{
		for(auto elem : accounts)
		{
			delete elem;
		}
	}
};
