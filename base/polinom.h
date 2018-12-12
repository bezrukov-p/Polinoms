#pragma once
#include "list.h"
#include <string>
#include <vector>

bool IsOperator(char op)
{
	if (op == '+' || op == '-')
		return true;
	else
		return false;
}
bool IsXYZ(char x)
{
	if (x == 'x' || x == 'y' || x == 'z')
		return true;
	else 
		return false;
}

double ConvertCoeff(string _k)
{
	if (_k.empty())
		return 1;
	if (_k.size() == 1)
	{
		if (_k[0] == '+')
			return 1;
		else
			if (_k[0] == '-')
				return -1;
	}
	return atof(_k.c_str());
}
class Monom
{
	double coeff;
	int exp; //0-999
public:
	Monom(double c = 0, int e = 0)
	{
		coeff = c;
		exp = e;
	}

	double GetCoeff()
	{
		return coeff;
	}

	int GetExp()
	{
		return exp;
	}

	bool IsEqualPow(Monom m1, Monom m2)
	{
		if (m1.GetExp() == m2.GetExp())
			return true;
		else
			return false;
	}

	void ChangeCoeff(int c)
	{
		coeff = c;
	}

	void ChangeExp(int e)
	{
		exp = e;
	}
};

class TPolinom
{
	string polinom;
	TList<Monom> monoms;
public:
	void FillMonoms()
	{
		vector<string> monoms_str;
		int i = 0;
		do
		{
			if (IsOperator(polinom[i])) // -1xxx+2yyyy-3z
			{
				string monom;
				do
				{
					monom += polinom[i];
					i++;
				} while (!IsOperator(polinom[i]) && i != polinom.size());  // + or -

				monoms_str.push_back(monom);
			}
			else
				i++;
		} while (i < polinom.size());

		for (int i = 0; i < monoms_str.size(); i++)
		{
			string coeff;
			int j = 0;
			while (!IsXYZ(monoms_str[i][j]) && j != monoms_str[i].size())
			{
				coeff += monoms_str[i][j];
				j++;
			}
			if (j == monoms_str[i].size())
			{
				Monom tmp(ConvertCoeff(coeff),0);
				monoms.AddNodeEnd(tmp);
			}
			else
			{
				int _exp = 0; //0-999
				for (j; j < monoms_str[i].size(); j++)          //-2x^2y^3z +2
				{
					if (monoms_str[i][j] == 'z')
					{
						if (j + 1 == monoms_str[i].size() || monoms_str[i][j + 1] != '^')
						{
							_exp += 1;
						}
						else
						{
							j = j + 2;
							_exp += monoms_str[i][j] - '0'; // -48
						}
					}
					else
						if (monoms_str[i][j] == 'y')
						{
							if (j + 1 == monoms_str[i].size() || monoms_str[i][j + 1] != '^')
							{
								_exp += 10;
							}
							else
							{
								j = j + 2;
								_exp += monoms_str[i][j] - '0' * 10; // -48
							}
						}
						else
							if (monoms_str[i][j] == 'x')
							{
								if (j + 1 == monoms_str[i].size() || monoms_str[i][j + 1] != '^')
								{
									_exp += 100;
								}
								else
								{
									j = j + 2;
									_exp += monoms_str[i][j] - '0' * 100; // -48
								}
							}
				}
				Monom tmp(ConvertCoeff(coeff), _exp);
				monoms.AddNodeEnd(tmp);
			}
		}
	}

	TPolinom(string _polinom = "")
	{
		polinom = _polinom;
		if (polinom != "")
			FillMonoms();
	}

	TPolinom& operator=(TPolinom& p)
	{

	}

	TPolinom operator+(TPolinom& p)
	{
		TPolinom tmp;
		return tmp;
	}
};