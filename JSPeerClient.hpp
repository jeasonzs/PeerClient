//
//  JSPeerClient.hpp
//  PeerClient
//
//  Created by jeason on 15/12/25.
//  Copyright 漏 2015骞� letv. All rights reserved.
//

#ifndef JSPeerClient_hpp
#define JSPeerClient_hpp

#include "JSTcpClient.hpp"
#include "JSPeerProtocol.hpp"


typedef void (*RegistResponseCB)(void* context);
typedef void (*HeartResponseCB)(void* context);
typedef void (*ConnectPeerResponseCB)(void* context,int status,int remoteId,char* iceInfoRemote);
typedef void (*IncomeConnectPeerCB)(void* context,int remoteId,char* iceInfoRemote);

class JSPeerClient : public JSTcpClient
{
public:
    JSPeerClient(int clientId);
    ~JSPeerClient();
    
public:
    void setRegistResponseCb(RegistResponseCB cb,void* context);
    void setHeartResponseCb(HeartResponseCB cb,void* context);
    void setConnectPeerResponseCb(ConnectPeerResponseCB cb,void* context);
    void setIncomeConnectPeerCb(IncomeConnectPeerCB cb,void* context);

public:
    void regist();
    void heart();
    void connectPeer(int remoteId,char* iceInfoLocal);
    void incomeConnectPeerResponse(int remoteId,char* iceInfoLocal);
    
protected:
    virtual int handlePkg(char* data,size_t len);
    
private:
    RegistResponseCB _registResponseCb;
    void* _registResponseCbContext;
    HeartResponseCB _heartResponseCb;
    void* _heartResponseCbContext;
    ConnectPeerResponseCB _connectPeerResponseCb;
    void* _connectPeerResponseCbContext;
    IncomeConnectPeerCB _incomeConnectPeerCb;
    void* _incomeConnectPeerCbContext;

    int _clientId;
};



#endif /* JSPeerClient_hpp */
