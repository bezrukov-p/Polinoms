#pragma once
#include <iostream>

using namespace std;

template<class TType>
struct Node
{
	TType key;
	Node *pNext;
	Node *pPrev;
	Node()
	{
		pNext = nullptr;
		pPrev = nullptr;
		key = {};
	}
};

template<class TType>
class TList
{
	int size;
	Node<TType> *pFirst;
public:
	TList()
	{
		size = 0;
		pFirst = nullptr;
	}

	int GetSize()
	{
		return size;
	}

	bool IsEmpty()
	{
		return pFirst == nullptr;
	}

	void AddNodeBegin(TType _key)
	{
		Node<TType> *tmp = new Node<TType>;
		tmp->key = _key;
		tmp->pNext = pFirst;
		pFirst->pPrev = tmp;
		pFirst = pFirst->pPrev;
		size++;
	}

	void AddNodeEnd(TType _key)
	{
		if (pFirst != nullptr)
		{
			Node<TType> *tmp = pFirst;
			while (tmp->pNext != nullptr)
			{
				tmp = tmp->pNext;
			}
			Node<TType> *tmp1 = new Node<TType>;
			tmp1->key = _key;
			tmp1->pPrev = tmp;
			tmp->pNext = tmp1;
		}
		else
		{
			Node<TType> *tmp = new Node<TType>;
			tmp->key = _key;
			pFirst = tmp;
		}
		size++;
	}

	/*void DelNode(int i)
	{
		if (i < size)
		{

		}
		else
			throw "invalid index";
	}*/

	void DelAllNode()
	{
		while (pFirst != nullptr)
		{
			Node<TType> *tmp = pFirst;
			pFirst = pFirst->pNext;
			delete tmp;
		}
		
	}

	TList& operator=(TList& l)
	{
		DelAllNode();
		size = l.size;
		Node<TType> *tmp1 = pFirst;
		Node<TType> *tmp2 = l.pFirst;
		while (tmp2 != nullptr)
		{
			Node<TType> *tmp = new Node;
			////////////////////////////////////////
			tmp2 = tmp2->pNext;
		}
	}

	~TList()
	{
		DelAllNode();
	}
};