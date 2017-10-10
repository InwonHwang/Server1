#include "stdafx.h"
#include "Session.h"

CriticalSection cs;

void printSync(const char *str)
{
	cs.Enter();
	printf_s("%s", str);
	cs.Leave();
}