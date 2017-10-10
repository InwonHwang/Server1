#pragma once

class Session;
class Connector;

class SessionManager
{
public:	
	~SessionManager(void);

	static Connector *connector;
	static Session *s;
	
	static void connect();
	static void send(const char * str);
	static char * recv();
	static void destroy();

private:
	static bool doesConnect;
private:
	SessionManager(void);
};

