#pragma once
#pragma comment ( lib, "ws2_32.lib" )

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <process.h>
#include <string.h>
#include <queue>
#include <list>
#include <time.h>
#include <stdio.h>

#define BUFSIZE 256
#define NUM_OF_CLIENT 10

#include "protocol.h"
#include "Time.h"
#include "LockList.h"

void printSync(const char *str);

class CriticalSection
{
	CRITICAL_SECTION cs;
public:
	CriticalSection(void){ InitializeCriticalSection(&cs); }
	~CriticalSection(void){ DeleteCriticalSection(&cs); }

	void Enter(){ EnterCriticalSection(&cs); }
	void Leave(){ LeaveCriticalSection(&cs); }
};
