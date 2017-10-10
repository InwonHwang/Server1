#include "Session.h"
#include "Parser.h"

extern CriticalSection cs;

Session::Session(const SOCKET &sock, const SOCKADDR_IN &addr) : mClientSock(sock), mClientAddr(addr)
{
	int len = sizeof(mClientAddr);
	getpeername(mClientSock, (struct sockaddr *)&mClientAddr, &len);
}

Session::~Session()
{
}

void Session::send(const Packet *p)
{
	char *toBeSend = Parser::serialize(p);
	cs.Enter();
	::send(mClientSock, toBeSend, BUFSIZE, 0);
	cs.Leave();
	delete[] toBeSend;
}

Packet * Session::recv()
{
	
	char buf[BUFSIZE];
	cs.Enter();
	int r = ::recv(mClientSock, buf, BUFSIZE, 0);
	cs.Leave();

	if (r == -1) return nullptr;

	Packet *ret = Parser::deserialize(buf);

	return ret;	
}

char *Session::getPeerIP()
{	
	return inet_ntoa(mClientAddr.sin_addr);
}

int Session::getPeerPort()
{
	return ntohs(mClientAddr.sin_port);
}