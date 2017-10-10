#pragma once
#include "stdafx.h"

class Session;

class WorkerThread
{
private:
	HANDLE				mThreadHandle;
	unsigned			mThreadId;

public:
	WorkerThread();
	~WorkerThread();
	
	void createThread(int index);
	static unsigned int WINAPI work(LPVOID arg);
};

