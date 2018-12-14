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
bool IsXYZ(char xyz)
{
	if (xyz == 'x' || xyz == 'y' || xyz == 'z')
		return true;
	else 
		return false;
}

int ConvertCoeff(string _k)
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
	return atoi(_k.c_str());
}

class Monom
{
	int coeff;
	int exp; //0-999 xyz
public:
	Monom(int c = 0, int e = 0,string _monom = "")
	{
		coeff = c;
		exp = e;
	}

	Monom operator+(const Monom &m)
	{
		if (exp != m.exp)
			throw "not equal coeffs";
		Monom tmp;
		tmp.coeff = coeff + m.coeff;
		tmp.exp = exp;
		return tmp;
	}

	Monom operator-(const Monom &m)
	{
		if (exp != m.exp)
			throw "not equal coeffs";
		Monom tmp;
		tmp.coeff = coeff - m.coeff;
		tmp.exp = exp;
		return tmp;
	}

	bool operator==(const Monom &m)
	{
		if (coeff == m.coeff && exp == m.exp)
			return true;
		else
			return false;
	}

	bool operator!=(const Monom &m)
	{
		return !(*this == m);
	}

	int GetCoeff()
	{
		return coeff;
	}

	int GetExp()
	{
		return exp;
	}

	bool IsEqualPow(Monom m)
	{
		if (GetExp() == m.GetExp())
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
		monoms.DelAllNode();
		vector<string> monoms_str;
		int i = 0;
		do
		{
			string monom;
			do
			{
				monom += polinom[i];
				i++;
			} while (!IsOperator(polinom[i]) && i != polinom.size());  // + or -

			monoms_str.push_back(monom);
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
				for (j; j < monoms_str[i].size(); j++)          
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
									_exp += (int)(monoms_str[i][j] - '0') * 100; // -48
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
		polinom = p.polinom;
		monoms = p.monoms;
		return *this;
	}

	bool operator==(const TPolinom &p)
	{
		if (monoms == p.monoms)
			return true;
		else
			return false;
	}

	bool operator!=(const TPolinom &p)
	{
		return !(*this == p);
	}

	TPolinom operator+(TPolinom& p)
	{
		TPolinom result, main, side;
		TList<Monom>::Iterator it1, it2;
		if (monoms.GetSize() >= p.monoms.GetSize())
		{
			main = *this;
			side = p;
			it1 = monoms.Begin();
			it2 = p.monoms.Begin();
		}
		else
		{
			main = p;
			side = *this;
			it2 = monoms.Begin();
			it1 = p.monoms.Begin();
		}
		for (it1; it1 != main.monoms.End();)
		{
			if (it1->key.GetExp() == it2->key.GetExp())
			{
				if ((it1->key.GetCoeff() + it2->key.GetCoeff()) != 0)
					result.monoms.AddNodeEnd(*(it1)+*(it2));
				++it1; ++it2;
			}
			else if (it1->key.GetExp() > it2->key.GetExp())
			{
				result.monoms.AddNodeEnd(*it1);
				++it1;
			}
			else 
			{
				result.monoms.AddNodeEnd(*it2);
				++it2;
			}
		}
		while (it2 != side.monoms.End())
		{
			result.monoms.AddNodeEnd(*it2);
			++it2;
		}
		return result;
	}

	friend ostream & operator<<(ostream &os, TPolinom &pl);
	friend istream & operator>>(istream &is, TPolinom &pl);
};

ostream & operator<<(ostream & os, TPolinom & p)
{
	string pl;
	for (auto it = p.monoms.Begin(); it != p.monoms.End(); ++it)
	{
		int deg = it->key.GetExp();
		if (it != p.monoms.Begin() && it->key.GetCoeff() > 0)
			os << "+";
		if (it->key.GetCoeff() != 1)
			os << to_string(it->key.GetCoeff());
		if ((int)(deg * 0.01) % 10 != 0)
		{
			if ((int)(deg * 0.01) % 10 == 1)
				os << "x";
			else
				os << "x^" << (int)(deg * 0.01) % 10;
		}
		if ((int)(deg * 0.1) % 10 != 0)
		{
			if ((int)(deg * 0.1) % 10 == 1)
				os << "y";
			else
				os << "y^" << (int)(deg * 0.1) % 10;
		}
		if (deg % 10 != 0)
		{
			if (deg % 10 == 1)
				os << "z";
			else
				os << "z^" << deg % 10;
		}
	}
	return os;
}

istream & operator>>(istream & is, TPolinom & p)
{
	is >> p.polinom;
	p.FillMonoms();
	return is;
}