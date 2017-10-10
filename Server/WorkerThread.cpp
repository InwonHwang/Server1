#include "WorkerThread.h"
#include "Session.h"
#include "ThreadPool.h"

extern CriticalSection cs;

WorkerThread::WorkerThread()
{
}


WorkerThread::~WorkerThread()
{
	CloseHandle(mThreadHandle);
}


void WorkerThread::createThread(int index)
{	
	mThreadHandle = (HANDLE)_beginthreadex(NULL, 0, work, (LPVOID)index, 0, &mThreadId);	
}

unsigned int WINAPI WorkerThread::work(LPVOID arg)
{
	int index = (int)arg;	

	while (1) {		
		Session *s = nullptr;

		cs.Enter();
		if (!ThreadPool::getInstance()->mListOfSession.empty()) {
			s = ThreadPool::getInstance()->mListOfSession.front();
			ThreadPool::getInstance()->mListOfSession.pop_front();
		}
		cs.Leave();

		if (!s) {
			WaitForSingleObject(ThreadPool::getInstance()->mListOfEvent[index], INFINITE);
			continue;
		}

		Time t;

		char buf[BUFSIZE];

		sprintf_s(buf, "\n[IP: %s / PORT: %d] 접속\n", s->getPeerIP(), s->getPeerPort());
		printSync("=========================================\n");
		printSync(t.getCurrentTime());
		printSync(buf);
		printSync("=========================================\n\n");

		while (1) {

			Packet *p = s->recv();

			if (!p) break;

			printSync(t.getCurrentTime());
			sprintf_s(buf, "\n[IP: %s / PORT: %d] 받은 데이터: %s / 길이: %d \n\n", s->getPeerIP(), s->getPeerPort(), p->mData, p->mLengthOfData);
			printSync(buf);

			s->send(p);

			delete p;
		}

		sprintf_s(buf, "\n[IP: %s / PORT: %d] 종료\n", s->getPeerIP(), s->getPeerPort());
		printSync("=========================================\n");
		printSync(t.getCurrentTime());
		printSync(buf);
		printSync("접속 시간:");
		printSync(t.getStayTime());
		printSync("\n=========================================\n\n");
		
		if(s) delete s;
	}
	
	return 0;
}