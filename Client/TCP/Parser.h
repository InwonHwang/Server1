#pragma once
#include "stdafx.h"

class Packet;

class Parser
{
private:
	Parser();

	static char ** split(const char *data);
	static int getLength(const char *data);

public:
	
	static char *serialize(const Packet *p);
	static Packet *deserialize(const char *data);

public:	
	~Parser();
};