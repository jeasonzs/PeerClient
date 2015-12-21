/*
 * JSTcpClient.cpp
 *
 *  Created on: 2015Äê12ÔÂ21ÈÕ
 *      Author: Administrator
 */

#include "JSTcpClient.hpp"

JSTcpClient::JSTcpClient() {
	// TODO Auto-generated constructor stub
	_fd = -1;
}

JSTcpClient::~JSTcpClient() {
	// TODO Auto-generated destructor stub
}


void JSTcpClient::connect(char* ip,int port)
{
	fd = socket()
}
void JSTcpClient::close()
{
	close(_fd);
}
virtual void JSTcpClient::run()
{
	while(!needExit()) {

	}
}
virtual int JSTcpClient::handlePkg(char*data,int len)
{

	return 0;
}

