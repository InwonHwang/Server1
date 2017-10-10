#pragma once
#include "stdafx.h"

class Session;

class Acceptor
{
private:
	WSADATA	mWsa;
	SOCKADDR_IN mAddr;
	SOCKET mSock;
	bool mListening;

private:
	void set(char *PORT);

public:
	Session *accept();

public:
	Acceptor(char *PORT);
	~Acceptor();

};