#pragma once

class Packet {
public:
	Packet() : mFront(0x0000), mBack(0xFFFF) {}
	~Packet() { if (mData) delete[] mData; }

	unsigned short mFront;
	unsigned short mBack;
	size_t mLengthOfData;
	char *mData;
};