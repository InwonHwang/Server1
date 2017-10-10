#include "SessionManager.h"

#include "TCP/Connector.h"
#include "TCP/Session.h"
#include "TCP/Parser.h"

Connector *SessionManager::connector = nullptr;
Session *SessionManager::s = nullptr;
bool SessionManager::doesConnect = false;

SessionManager::SessionManager(void)
{
}


SessionManager::~SessionManager(void)
{
}

void SessionManager::connect()
{
	if(doesConnect) return;

	connector = new Connector();
	
	s = connector->connect("127.0.0.1", "9000");

	doesConnect = true;
}

void SessionManager::send(const char * str)
{
	Packet *p = new Packet();
	p->mData = new char[BUFSIZE];

	strcpy(p->mData, str);

	p->mLengthOfData = strlen(p->mData);
	p->mData[strlen(p->mData) - 1] = 0;		

	s->send(p);
	delete p;
}

char * SessionManager::recv()
{
	Packet *p = s->recv();
	char *ret = new char[BUFSIZE];
	strcpy(ret, p->mData);

	delete p;

	return ret;
}

void SessionManager::destroy()
{
	if(connector) delete connector;
	if(s) delete s;
}
