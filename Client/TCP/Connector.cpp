#include "Connector.h"
#include "Session.h"


Connector::Connector()
{
	try {
		if(WSAStartup(MAKEWORD(2, 2), &mWsa) != 0) throw;
	}
	catch (const std::exception &e){
		e.what();
	}
	set();
}

Connector::~Connector()
{
	WSACleanup();
}

void Connector::set()
{
	try {
		mSock = socket(AF_INET, SOCK_STREAM, 0);
		if (mSock == INVALID_SOCKET) throw;
	}
	catch (const std::exception &e) {
		e.what();
	}
}

Session * Connector::connect(char *IP, char *PORT)
{	
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = htons(atoi(PORT));

	try {		
		int ret = ::connect(mSock, (SOCKADDR *)&addr, sizeof(addr));
		if (ret == SOCKET_ERROR) throw;
	}
	catch (const std::exception &e) {		
		e.what();
	}

	return new Session(mSock, addr);
}
