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
	int connect(char* ip,int port);
	void close();

private:
    virtual void run();

protected:
    virtual int handlePkg(char*data,size_t len) = 0;

private:
    int _fd;

};

#endif /* JSTCPCLIENT_HPP_ */
