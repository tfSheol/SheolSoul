#include "MySocket.h"

MySocket::MySocket() : _sock(-1)
{
}

MySocket::~MySocket()
{
    closesocket(_sock);
    WSACleanup();
}

bool                    MySocket::connex(std::string addr, int port)
{
    SOCKADDR_IN		sin;

    if (_sock)
    {
        WSAStartup(MAKEWORD(2,0), &_WSAData);
        if (!(_sock = socket(AF_INET, SOCK_STREAM, 0)))
                std::cerr << "Error: socket." << std::endl;
        sin.sin_addr.s_addr = inet_addr(addr.c_str());
        sin.sin_family = AF_INET;
        sin.sin_port = htons(port);
        if (connect(_sock, (sockaddr*)&sin, sizeof(sin)) < 0)
        {
            std::cerr << "Error: connect." << std::endl;
            closesocket(_sock);
            return (true);
        }
    }
    std::cout << "Connected !" << std::endl;
    return (false);
}

bool 			MySocket::sendData(std::string data)
{
    if(send(_sock, data.c_str(), data.size(), 0) < 0)
    {
        std::cerr << "Error: send." << std::endl;
        return (true);
    }
    std::cout << ">> " << data << std::endl;
    
    return (false);
}

std::string			MySocket::recvData()
{
    _reply.resize(0);
    FD_ZERO(&_readfds);
    FD_SET(_sock, &_readfds);
    _tv.tv_sec = 0;
    _tv.tv_usec = 9;
    if (select(0, &_readfds, NULL, NULL, &_tv) == SOCKET_ERROR)
    {
        std::cerr << "Error : Select" << std::endl;
        return (NULL);
    }
    else
    {
        if (FD_ISSET(_sock, &_readfds))
        {
            while (_reply[(_reply.length() - 1)] != '\n' && _reply[(_reply.length() - 2)] != '\r')
            {
                memset(_buffer, '\0', SIZE);
                if(recv(_sock, _buffer, SIZE, 0) == SOCKET_ERROR)
                {
                   std::cerr << "Error: recv." << std::endl;
                   return (NULL);
                }
                else
                    _reply += _buffer;
            }
        }
    }
    return (_reply);
}