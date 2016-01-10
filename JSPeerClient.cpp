//
//  JSPeerClient.cpp
//  PeerClient
//
//  Created by jeason on 15/12/25.
//  Copyright 漏 2015骞� letv. All rights reserved.
//
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <sys/time.h>
#include <iostream>
#include <string.h>
#include "JSPeerClient.hpp"

using namespace std;
JSPeerClient::JSPeerClient(int clientId)
{
    _clientId = clientId;
    cout<<"clientId="<<clientId<<endl;
}

JSPeerClient::~JSPeerClient()
{

}


void JSPeerClient::setRegistResponseCb(RegistResponseCB cb,void* context)
{
	_registResponseCb = cb;
	_registResponseCbContext = context;
}
void JSPeerClient::setHeartResponseCb(HeartResponseCB cb,void* context)
{
	_heartResponseCb = cb;
	_heartResponseCbContext = context;
}
void JSPeerClient::setConnectPeerResponseCb(ConnectPeerResponseCB cb,void* context)
{
	_connectPeerResponseCb = cb;
	_connectPeerResponseCbContext = context;
}
void JSPeerClient::setIncomeConnectPeerCb(IncomeConnectPeerCB cb,void* context)
{
	_incomeConnectPeerCb = cb;
	_incomeConnectPeerCbContext = context;
}


void JSPeerClient::regist()
{
    JSPeerProtocolRegist regist(_clientId, JS_PEER_ID_SERVER);
    send((char*)&regist, sizeof(regist));
}
void JSPeerClient::heart()
{
    JSPeerProtocolHeart heart(_clientId, JS_PEER_ID_SERVER);
    send((char*)&heart, sizeof(heart));
}

void JSPeerClient::connectPeer(int remoteId,char* iceInfoLocal)
{
	JSPeerProtocolConnect connect(_clientId,remoteId);
	strcpy(connect.iceInfo,iceInfoLocal);
	send((char*)&connect, sizeof(connect));
}
void JSPeerClient::incomeConnectPeerResponse(int remoteId,char* iceInfoLocal)
{
	JSPeerProtocolConnectResponse connectResponse(_clientId,remoteId);
	strcpy(connectResponse.iceInfo,iceInfoLocal);
	send((char*)&connectResponse, sizeof(connectResponse));
}




int JSPeerClient::handlePkg(char* data, size_t len)
{
    cout<<"handle pkg len="<<len<<",dat="<<data;
    JSPeerProtocolHeader* header = NULL;
    int pos = 0;
    header = JSPeerProtocolHeader::mapPkg(data, len, pos);
    if(header) {
        switch (header->type) {
            case JS_PEER_MSG_REGIST_RESPONSE:
                cout<<"regist response msg"<<endl;
                _registResponseCb(_registResponseCbContext);
                break;
                
            case JS_PEER_MSG_HEART_RESPONSE:
                cout<<"heart response msg"<<endl;
                _heartResponseCb(_heartResponseCbContext);
                break;
                
            case JS_PEER_MSG_CONNECT_RESPONSE:{
            	cout<<"Connect response msg"<<endl;
            	JSPeerProtocolConnectResponse* connectResponse = (JSPeerProtocolConnectResponse*)(header);
				_connectPeerResponseCb(_connectPeerResponseCbContext,connectResponse->status,connectResponse->fromId,connectResponse->iceInfo);
				break;
            }

            case JS_PEER_MSG_CONNECT:{
				cout<<"Connect msg"<<endl;
				JSPeerProtocolConnect* connect = (JSPeerProtocolConnect*)header;
				_incomeConnectPeerCb(_incomeConnectPeerCbContext,connect->fromId,connect->iceInfo);
				break;
            }
            default:
                break;
        }
    }
    return 0;
}
