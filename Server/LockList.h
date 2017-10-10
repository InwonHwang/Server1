#pragma once
#include "stdafx.h"

template <typename T>
class LockList : std::list<T>
{
private:
	std::list<T> mList;

public:
	LockList() {}
	~LockList() { mList.clear(); }

	void push_front(const T &data);
	void push_back(const T &data);
	void pop_front();
	void pop_back();
	T front();
	bool empty();
};

