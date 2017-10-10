#pragma once
#include "stdafx.h"

class Time
{
private:
	struct tm mCurTm;
	time_t mCurTime;
	time_t mStartTime;
	char mBuf[BUFSIZE];

public:
	char * getCurrentTime();
	char * getStayTime();

public:
	Time();
	~Time();
};

