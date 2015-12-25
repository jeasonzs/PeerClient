//
//  JSPeerClient.hpp
//  PeerClient
//
//  Created by jeason on 15/12/25.
//  Copyright © 2015年 letv. All rights reserved.
//

#ifndef JSPeerClient_hpp
#define JSPeerClient_hpp

#include "JSTcpClient.hpp"
#include "JSPeerProtocol.hpp"


typedef void (*RegistCallback)();
typedef void (*HeartCallback)();

class JSPeerClient : public JSTcpClient
{
public:
    JSPeerClient(int clientId);
    ~JSPeerClient();
    
public:
    void regist(RegistCallback cb);
    void heart(HeartCallback cb);
    
    
protected:
    virtual int handlePkg(char* data,size_t len);
    
    
private:
    RegistCallback _registCb;
    HeartCallback _heartCb;
    int _clientId;
};



#endif /* JSPeerClient_hpp */
