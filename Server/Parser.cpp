#include "Parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

int Parser::getLength(const char *data)
{
	char *pch = (char*)memchr(data, 0xFFFF, BUFSIZE);

	return pch - data + 3;
}

char ** Parser::split(const char *data)
{
	int len = getLength(data);

	int cur = 0;

	char ** ret = new char*[4];

	int j = 0;
	for (int i = 0; i < len; i++) {

		if (data[i] == ',' || i == len - 1) {
			ret[j] = new char[i - cur + 1];
			memcpy(ret[j], data + cur, i - cur + 1);

			ret[j][i - cur] = '\0';
			cur = i + 1;
			j++;
		}
	}

	return ret;
}

char *Parser::serialize(const Packet *p)
{
	char tocken = ',';
	int sizeOfPacket = sizeof(*p) + strlen(p->mData);

	char *str = new char[sizeOfPacket];

	memcpy(str, &p->mFront, sizeof(unsigned short));
	memcpy(str + 2, &tocken, sizeof(char));
	memcpy(str + 3, &p->mLengthOfData, sizeof(size_t));
	memcpy(str + 7, &tocken, sizeof(char));
	memcpy(str + 8, p->mData, strlen(p->mData));
	memcpy(str + (sizeOfPacket - 4), &tocken, sizeof(char));
	memcpy(str + (sizeOfPacket - 3), &p->mBack, sizeof(unsigned short));

	return str;
}


Packet *Parser::deserialize(const char *data)
{
	Packet * ret = new Packet();

	char ** str = split(data);

	memcpy(&ret->mFront, str[0], sizeof(unsigned short));
	memcpy(&ret->mLengthOfData, str[1], sizeof(int));
	memcpy(&ret->mBack, str[3], sizeof(unsigned short));
	ret->mData = new char[ret->mLengthOfData + 1];
	strcpy_s(ret->mData, strlen(str[2]) + 1, str[2]);
	ret->mData[ret->mLengthOfData - 1] = 0;
	

	for (int i = 0; i < 4; i++)
		delete[] str[i];

	delete[] str;

	return ret;
}