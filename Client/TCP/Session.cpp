#include "Session.h"
#include "Parser.h"

Session::Session(const SOCKET &sock, const SOCKADDR_IN &addr) : mClientSock(sock), mClientAddr(addr)
{
}

Session::~Session()
{
}

void Session::send(const Packet *p)
{
	char *toBeSend = Parser::serialize(p);
	::send(mClientSock, toBeSend, BUFSIZE, 0);
	delete[] toBeSend;
}

Packet * Session::recv()
{	
	char buf[BUFSIZE];

	int r = ::recv(mClientSock, buf, BUFSIZE, 0);

	if (r == -1) return nullptr;

	Packet *ret = Parser::deserialize(buf);

	return ret;	
}