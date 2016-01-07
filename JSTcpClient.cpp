/*
 * JSTcpClient.cpp
 *
 *  Created on: 2015Äê12ÔÂ21ÈÕ
 *      Author: Administrator
 */
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include "JSTcpClient.hpp"

using namespace std;

JSTcpClient::JSTcpClient() {
	// TODO Auto-generated constructor stub
	_fd = -1;
    _ip[0] = '\0';
    _port = 0;
    _reConnectms = 0;
}

JSTcpClient::~JSTcpClient() {
	// TODO Auto-generated destructor stub
    close();
    _fd = -1;
    _ip[0] = '\0';
    _port = 0;
    _reConnectms = 0;
}



void JSTcpClient::connect(char* ip,int port,int reConnectms,ConnectCallback cb,void* ptr)
{
    strcpy(_ip,ip);
    _port = port;
    _reConnectms = reConnectms;
    _connectCb = cb;
    _connectCbPtr = ptr;
    
    close();
    _fd = -1;
    start();
}
int JSTcpClient::connect()
{
    struct sockaddr_in s_add;
    int fd = -1;
    int ret = 0;

    fd= socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        cout<<"Listen()>>socket error!!!!"<<endl;
        return -1;
    }
    
    bzero(&s_add,sizeof(struct sockaddr_in));
    
    s_add.sin_family=AF_INET;
    s_add.sin_addr.s_addr= inet_addr(_ip);
    s_add.sin_port=htons(_port);
    
    struct timeval timeout={0,500*1000};//500ms
    ret = setsockopt(fd,SOL_SOCKET,SO_SNDTIMEO,(const char*)&timeout,sizeof(timeout));
    ret |= setsockopt(fd,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout));
    if(ret) {
        ::close(fd);
        return -1;
    }
    
    if(::connect(fd, (struct sockaddr *)&s_add, sizeof(s_add))) {
        ::close(fd);
        return -1;
    }
    return fd;
}

void JSTcpClient::close()
{
    if(isRuning()) {
        stop();
    }
    if (_fd >= 0) {
        ::close(_fd);
    }
    _fd = -1;
}

bool JSTcpClient::isAlive()
{
    return _fd>=0?true:false;
}

int JSTcpClient::send(char *dat, size_t len)
{
    return ::send(_fd, dat, len, 0);
}

void JSTcpClient::run()
{
    char dat[2048] = {0};
    _fd = connect();
    if(_fd >= 0) {
    	_connectCb(_connectCbPtr);
    }
	while(!needExit() && (_fd >= 0 || _reConnectms)) {
        if (_fd < 0 ) {
            usleep(1000*_reConnectms);
            _fd = connect();
            if(_fd >= 0) {
				_connectCb(_connectCbPtr);
			}
            continue;
        }
        ssize_t len = recv(_fd, dat, sizeof(dat), 0);
        if(len > 0) {
            handlePkg(dat, len);
        }
        else if(len == 0){
            ::close(_fd);
            _fd = -1;
        }
	}
}


