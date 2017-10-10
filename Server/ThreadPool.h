#pragma once
#include "stdafx.h"

class Session;
class WorkerThread;
template <typename T> class LockList;

class ThreadPool
{
	friend class WorkerThread;
private:
	static ThreadPool *mInstance;

	std::list<Session *> mListOfSession;
	WorkerThread *mListOfThread[NUM_OF_CLIENT];
	HANDLE mListOfEvent[NUM_OF_CLIENT];	

private:
	ThreadPool();
	

public:
	~ThreadPool();

	static ThreadPool *getInstance();
	void setEvent();
	void addSession(Session *s);
	void createThread();
	void release();
};

