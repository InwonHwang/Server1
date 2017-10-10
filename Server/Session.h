#pragma once
#include "stdafx.h"

class Packet;

class Session
{
private:
	SOCKET mClientSock;
	SOCKADDR_IN mClientAddr;

public:
	Session(const SOCKET &sock, const SOCKADDR_IN &addr);
	~Session();

	void send(const  Packet *p);
	Packet *recv();
	char *getPeerIP();
	int getPeerPort();
	
};

