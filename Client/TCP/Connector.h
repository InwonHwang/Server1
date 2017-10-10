#pragma once

#include "stdafx.h"

class Session;

class Connector
{
private:
	SOCKADDR_IN mAddr;
	SOCKET mSock;
	WSADATA	mWsa;

private:
	void set();

public:
	Session *connect(char *IP, char *PORT);

public:
	Connector();
	~Connector();

	
};

