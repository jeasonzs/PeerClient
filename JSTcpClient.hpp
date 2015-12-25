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
	void connect(char* ip,int port);
	void close();

private:
    virtual void run();

protected:
    virtual int handlePkg(char*data,int len);

private:
    int _fd;

};

#endif /* JSTCPCLIENT_HPP_ */
