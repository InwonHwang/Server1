#include "Time.h"

Time::Time()
{
	(void)time(&mStartTime);	
}


Time::~Time()
{
}


char *Time::getCurrentTime()
{
	(void)time(&mCurTime);
	localtime_s(&mCurTm, &mCurTime);

	sprintf_s(mBuf, "%d�� %d�� %d�� %d�� %d�� %d��\n",
		mCurTm.tm_year + 1900, mCurTm.tm_mon + 1, mCurTm.tm_mday,
		mCurTm.tm_hour, mCurTm.tm_min, mCurTm.tm_sec);

	mBuf[strlen(mBuf) - 1] = 0;

	return mBuf;
}

char * Time::getStayTime()
{
	(void)time(&mCurTime);
	time_t stayTime = mCurTime - mStartTime;
	struct tm stayTm;
	localtime_s(&stayTm, &stayTime);

	sprintf_s(mBuf, "%d�� %d�� %d��\n", stayTm.tm_hour - 9, stayTm.tm_min, stayTm.tm_sec);

	mBuf[strlen(mBuf) - 1] = 0;


	return mBuf;
}

