#include "SessionManager.h"
#include "ThreadPool.h"
#include "Acceptor.h"
#include "Session.h"

extern CriticalSection cs;

SessionManager::SessionManager()
{
}


SessionManager::~SessionManager()
{
}


void SessionManager::run()
{

	Acceptor *acceptor = new Acceptor("9000");
	ThreadPool::getInstance()->createThread();

	while (1) {
		Session *s = acceptor->accept();
		ThreadPool::getInstance()->addSession(s);
		ThreadPool::getInstance()->setEvent();
	}

	ThreadPool::getInstance()->release();
	delete acceptor;
}