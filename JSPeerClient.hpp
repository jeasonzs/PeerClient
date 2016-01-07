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


typedef void (*RegistCallback)(void*);
typedef void (*HeartCallback)(void*);

class JSPeerClient : public JSTcpClient
{
public:
    JSPeerClient(int clientId);
    ~JSPeerClient();
    
public:
    void regist(RegistCallback cb,void* ptr);
    void heart(HeartCallback cb,void* ptr);
    
    
protected:
    virtual int handlePkg(char* data,size_t len);
    
private:
    RegistCallback _registCb;
    void* _registCbPtr;
    HeartCallback _heartCb;
    void* _heartCbPtr;
    int _clientId;
};



#endif /* JSPeerClient_hpp */
