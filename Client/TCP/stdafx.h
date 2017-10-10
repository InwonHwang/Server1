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
#define NUM_OF_CLIENT 5

#include "protocol.h"

