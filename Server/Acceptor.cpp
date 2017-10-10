#include "Acceptor.h"
#include "Session.h"


Acceptor::Acceptor(char *PORT) : mListening(false)
{
	WSAStartup(MAKEWORD(2, 2), &mWsa);
	set(PORT);
}

Acceptor::~Acceptor()
{	
	closesocket(mSock);
	WSACleanup();
}

void Acceptor::set(char *PORT)
{	
	if (mListening) return;

	try {
		mSock = socket(AF_INET, SOCK_STREAM, 0);
		if (mSock == INVALID_SOCKET) throw;
	}
	catch (const std::exception &e) {
		printf("%s \n", e.what());		
	}

	ZeroMemory(&mAddr, sizeof(mAddr));
	mAddr.sin_family = AF_INET;
	mAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	mAddr.sin_port = htons(atoi(PORT));

	try {
		if(bind(mSock, (SOCKADDR *)&mAddr, sizeof(mAddr)) == SOCKET_ERROR) throw;
		if(listen(mSock, NUM_OF_CLIENT) == SOCKET_ERROR) throw;
		
	}
	catch (const std::exception &e) {
		
		printf("%s \n", e.what());
	}

	int nOptVal;
	int nOptLen = sizeof(nOptVal);
	
	setsockopt(mSock, SOL_SOCKET, SO_REUSEADDR, (char *)&nOptVal, (int)sizeof(nOptVal));

	mListening = true;
}

Session *Acceptor::accept()
{
	if (!mListening) return nullptr;

	SOCKET clientSock;
	SOCKADDR_IN clientAddr;
	int addrlen = sizeof(clientAddr);

	try {
		clientSock = ::accept(mSock, (SOCKADDR *)&clientAddr, &addrlen);
		if (clientSock == INVALID_SOCKET) throw;
	}
	catch (const std::exception &e) {
		e.what();
	}

	return new Session(clientSock, clientAddr);
}


