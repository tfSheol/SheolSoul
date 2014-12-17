#ifndef MYSOCKET_H_
#define MYSOCKET_H_

#include <string>
#include <iostream>
#include <winsock2.h>

#define		SIZE 512

class MySocket
{
private:
    WSADATA		_WSAData;
    SOCKET		_sock;
    fd_set 		_readfds;
    struct timeval	_tv;
    char		_buffer[SIZE + 1]; // std::string _buffer.c_str();
    std::string 	_reply;
	 
public:
    MySocket();
    ~MySocket();
    bool 		connex(std::string, int);
    bool 		sendData(std::string data);
    std::string		recvData();
};

#endif /* MYSOCKET_H_ */