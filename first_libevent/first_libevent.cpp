// first_libevent.cpp: 定义控制台应用程序的入口点。
//

#include <iostream>
#include <event2/event.h>


int main()
{
	// std::cout << "hello world" << std::endl;
#ifdef _WIN32
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

	event_base * base = event_base_new();
	if(base){
		std::cout << "event_base_new()执行成功！" << std::endl;
	}

    return 0;
}

