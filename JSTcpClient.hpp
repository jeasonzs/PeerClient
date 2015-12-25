/*
 * JSTcpClient.h
 *
 *  Created on: 2015Äê12ÔÂ21ÈÕ
 *      Author: Administrator
 */

#ifndef JSTCPCLIENT_HPP_
#define JSTCPCLIENT_HPP_

#include "JSThread.hpp"


class JSTcpClient : public JSThread{
public:
	JSTcpClient();
	virtual ~JSTcpClient();

public:
	int connect(char* ip,int port,int reConnectms);
	void close();
    bool isAlive();
    int send(char* dat,size_t len);

private:
    virtual void run();
    int connect();

protected:
    virtual int handlePkg(char* data,size_t len) = 0;

private:
    int _fd;
    char _ip[64];
    int _port;
    int _reConnectms;

};

#endif /* JSTCPCLIENT_HPP_ */
