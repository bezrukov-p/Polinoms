#pragma once
#include <iostream>

const int MAXSIZE = 1000;
using namespace std;

template<class TType>
class TList
{
private:
	template<class TType>
	struct Node
	{
		TType key;
		Node *pNext;
		Node *pPrev;
		Node(TType val = {})
		{
			pNext = nullptr;
			key = val;
		}
	};
	int size;
	Node<TType> *pFirst;
public:

	class Iterator
	{
	private:
		Node<TType> *pointer;
	public:
		Iterator()
		{
			pointer = new Node<TType>;
		}

		Iterator(const Iterator &i)
		{
			pointer = i.pointer;
		}

		Iterator& operator=(const Iterator &i)
		{
			pointer = i.pointer;
			return *this;
		}

		Node<TType>* operator->() const
		{
			return pointer;
		}

		bool operator==(const Iterator &i)
		{
			if (pointer == i.pointer)
				return true;
			else
				return false;
		}

		bool operator!=(const Iterator &i)
		{
			if (pointer != i.pointer)
				return true;
			else
				return false;
		}

		TType operator*()const
		{
			if (pointer == nullptr)
				throw("error");
			else
				return pointer->key;
		}

		Iterator& operator ++()
		{
			this->pointer = this->pointer->pNext;
			return *this;
		}

		friend TList;
	};

	Iterator Begin()
	{
		Iterator i;
		i.pointer = pFirst;
		return i;
	}

	Iterator End()
	{
		Iterator i;
		Node<TType> * tmp = pFirst;
		if (IsEmpty())
		{
			i.pointer = pFirst;
			return i;
		}
		else
		{
			while (tmp->pNext != nullptr)
			{
				tmp = tmp->pNext;
			}
			i.pointer = tmp->pNext;
			return i;
		}
	}

	TList()
	{
		size = 0;
		pFirst = nullptr;
	}

	TList(const TList<TType> &l)
	{
		pFirst = nullptr;
		size = l.size;
		Node<TType> * tmp = l.pFirst;
		while (tmp != nullptr)
		{
			AddNodeEnd(tmp->key);
			tmp = tmp->pNext;
		}

	}

	TList<TType>& operator=(const TList<TType> &l)
	{
		DelAllNode();
		Node<TType> * tmp = l.pFirst;
		while (tmp != nullptr)
		{
			AddNodeEnd(tmp->key);
			tmp = tmp->pNext;
		}
		return *this;
	}

	bool operator==(const TList<TType> &l)
	{
		if (size != l.size)
			return false;
		Node<TType> * tmp1 = pFirst;
		Node<TType> * tmp2 = l.pFirst;
		while (tmp2 != nullptr)
		{
			if (tmp1->key != tmp2->key)
				return false;
			tmp1 = tmp1->pNext;
			tmp2 = tmp2->pNext;
		}
		return true;
	}

	bool operator!=(const TList<TType> &l)
	{
		return !(*this == l);
	}

	int GetSize()
	{
		return size;
	}

	bool IsEmpty()
	{
		return pFirst == nullptr;
	}

	/*void AddNodeBegin(TType _key)
	{
		Node<TType> *tmp = new Node<TType>;
		tmp->key = _key;
		tmp->pNext = pFirst;
		pFirst->pPrev = tmp;
		pFirst = pFirst->pPrev;
		size++;
	}*/

	void AddNodeEnd(TType _key)
	{
		if (!IsEmpty())
		{
			if (size >= MAXSIZE)
				throw "full";
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

	void Erase(Iterator i)
	{
		Node<TType> *tmp = pFirst;
		Node<TType> *prev;
		int pos = 0;
		while (tmp != i.pointer)
		{
			prev = tmp;
			tmp = tmp->pNext;
			pos++;
		}
		if (pos == 0)
		{
			pFirst = pFirst->pNext;
			delete tmp;
			size--;
		}
		else
		{
			prev->pNext = tmp->pNext;
			delete tmp;
			size--;
		}
	}

	void Insert(Iterator i, TType val)
	{
		Node<TType> *tmp = pFirst;
		Node<TType> *prev;
		Node<TType> *insert = new Node<TType>(val);
		int pos = 0;
		while (tmp != i.pointer)
		{
			prev = tmp;
			tmp = tmp->pNext;
			pos++;
		}
		if (pos == 0)
		{
			insert->pNext = tmp;
			pFirst = insert;
			size++;
		}
		else
		{
			insert->pNext = tmp;
			prev->pNext = insert;
			size++;
		}
	}

	void DelAllNode()
	{
		while (pFirst != nullptr)
		{
			Node<TType> *tmp = pFirst;
			pFirst = pFirst->pNext;
			delete tmp;
		}
	}

	~TList()
	{
		DelAllNode();
	}

	friend class Iterator;
};