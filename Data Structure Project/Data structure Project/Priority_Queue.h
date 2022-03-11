#pragma once
#include"Mission.h"

template<class T>
class NNode
{
private:
	T data;
	int Key;
public:
	NNode(T d, int k) { data = d; Key = k; }
	NNode() {}
	void Set_Key(int k) { Key = k; }
	int Get_key() { return Key; }
	void Set_data(T d) { data = d; }
	T Get_data() { return data; }
};

template<class T>
class PQueue
{
private:
	NNode<T>* array[100];
	int count;
public:
	PQueue()
	{
		count = 0;
	}
	PQueue(PQueue& q)
	{
		count = q.count;
		for (int i = 0; i < count; i++)
		{
			array[i] = q.array[i];
		}
	}

	void enqueue(T msn, int Key)
	{
		NNode<T>* nd = new NNode<T>(msn, Key);
		int i;
		for (i = 0; i < count; i++)
		{
			if (Key >= array[i]->Get_key())
			{
				break;
			}
		}
		for (int j = count; j > i; j--)
		{
			array[j] = array[j - 1];
		}
		array[i] = nd;
		count++;
	}

	bool dequeue(T &msn)
	{
		if (count == 0)
			return false;
		msn = array[--count]->Get_data();
		return true;
	}

	bool peak(T& msn)
	{
		if (count == 0)
			return false;
		msn = array[count - 1]->Get_data();
		return true;
	}

	bool IsEmpty()
	{
		if (count == 0)
			return true;
		return false;
	}

};