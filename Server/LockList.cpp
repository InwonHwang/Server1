#include "LockList.h"

extern CriticalSection cs;

template <typename T>
void LockList<T>::push_front(const T &data)
{
	cs.Enter();
	mList.push_front(data);
	cs.Leave();
}

template <typename T>
void LockList<T>::push_back(const T &data)
{
	cs.Enter();
	mList.push_back(data);
	cs.Leave();
}

template <typename T>
void LockList<T>::pop_front()
{
	cs.Enter();
	mList.pop_front();
	cs.Leave();
}

template <typename T>
void LockList<T>::pop_back()
{
	cs.Enter();
	mList.pop_back();
	cs.Leave();
}

template <typename T>
T LockList<T>::front()
{
	cs.Enter();
	T ret = mList.front();
	cs.Leave();

	return ret;
}

template <typename T>
bool LockList<T>::empty()
{
	cs.Enter();
	bool ret = mList.empty();
	cs.Leave();

	return ret;
}