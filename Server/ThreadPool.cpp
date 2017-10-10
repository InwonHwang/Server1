#include "ThreadPool.h"
#include "WorkerThread.h"

extern CriticalSection cs;

ThreadPool *ThreadPool::mInstance;

ThreadPool::ThreadPool()
{
}


ThreadPool::~ThreadPool()
{
	for (int i = 0; i < NUM_OF_CLIENT; i++)
		if (mListOfThread[i]) delete mListOfThread[i];
}

ThreadPool *ThreadPool::getInstance()
{
	if (!mInstance) mInstance = new ThreadPool();

	return mInstance;
}

void ThreadPool::addSession(Session *s)
{
	cs.Enter();
	mListOfSession.push_back(s);
	cs.Leave();
}

void ThreadPool::setEvent()
{
	for (int i = 0; i < NUM_OF_CLIENT; i++) {
		SetEvent(mListOfEvent[i]);
	}
}

void ThreadPool::createThread()
{
	for (int i = 0; i < NUM_OF_CLIENT; i++) {
		WorkerThread *newThread = new WorkerThread();

		newThread->createThread(i);
		mListOfThread[i] = newThread;

		HANDLE newEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		mListOfEvent[i] = newEvent;
	}
}

void ThreadPool::release()
{
	if (mInstance) delete mInstance;
}