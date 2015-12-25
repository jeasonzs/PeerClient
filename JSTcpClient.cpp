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
}

JSTcpClient::~JSTcpClient() {
	// TODO Auto-generated destructor stub
    close();
}



int JSTcpClient::connect(char* ip,int port)
{
    struct sockaddr_in s_add;
    int fd = -1;
    int ret = 0;
    
    close();
    fd= socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        cout<<"Listen()>>socket error!!!!"<<endl;
        return -1;
    }
    
    bzero(&s_add,sizeof(struct sockaddr_in));
    
    s_add.sin_family=AF_INET;
    s_add.sin_addr.s_addr= inet_addr(ip);
    s_add.sin_port=htons(port);
    
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
    _fd = fd;
    start();
    return 0;
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
void JSTcpClient::run()
{
    char dat[2048] = {0};
	while(!needExit()) {
        size_t len = recv(_fd, dat, sizeof(dat), 0);
        if(len > 0) {
            handlePkg(dat, len);
        }
	}
}


