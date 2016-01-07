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
#include "JSPeerClient.hpp"

using namespace std;
JSPeerClient::JSPeerClient(int clientId)
{
    _clientId = clientId;
}

JSPeerClient::~JSPeerClient()
{

}

void JSPeerClient::regist(RegistCallback cb,void* ptr)
{
    _registCb = cb;
    _registCbPtr = ptr;
    JSPeerProtocolRegist regist(_clientId, JS_PEER_ID_SERVER);
    send((char*)&regist, sizeof(regist));
}
void JSPeerClient::heart(HeartCallback cb,void* ptr)
{
    _heartCb = cb;
    _heartCbPtr = ptr;
    JSPeerProtocolHeart heart(_clientId, JS_PEER_ID_SERVER);
    send((char*)&heart, sizeof(heart));
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
                _registCb(_registCbPtr);
                break;
                
            case JS_PEER_MSG_HEART_RESPONSE:
                cout<<"heart response msg"<<endl;
                _heartCb(_heartCbPtr);
                break;
                
            default:
                break;
        }
    }
    return 0;
}
