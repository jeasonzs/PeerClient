//
//  JSPeerClient.cpp
//  PeerClient
//
//  Created by jeason on 15/12/25.
//  Copyright © 2015年 letv. All rights reserved.
//

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


void JSPeerClient::regist(RegistCallback cb)
{
    _registCb = cb;
    JSPeerProtocolRegist regist(_clientId, JS_PEER_ID_SERVER);
    send((char*)&regist, sizeof(regist));
}
void JSPeerClient::heart(HeartCallback cb)
{
    _heartCb = cb;
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
                _registCb();
                break;
                
            case JS_PEER_MSG_HEART_RESPONSE:
                cout<<"heart response msg"<<endl;
                _heartCb();
                break;
                
            default:
                break;
        }
    }
    return 0;
}