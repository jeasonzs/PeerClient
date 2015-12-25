#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>


#include "JSPeerClient.hpp"


using namespace std;
bool mainStopFlg = false;

void SigintCb(int iSigNum)
{
    mainStopFlg=true;
}

void registCb()
{
    cout<<"registCb cb"<<endl;
}

void heartCb()
{
    cout<<"heartCb cb"<<endl;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    signal(SIGINT,SigintCb);
    signal(SIGALRM,SigintCb);
    std::cout << "start peerClient!\n"<<endl;
    JSPeerClient* client = new JSPeerClient(0x123456);
    client->connect("192.168.131.131", 60000 ,1000*2);
    
    while (!mainStopFlg) {
        usleep(1000*1000);
//        if(client->send("hello server!!!\n", sizeof("hello server!!!\n")) <= 0) {
//            cout<<"send error !!!!!!"<<endl;
//        }
        client->heart(heartCb);
        client->regist(registCb);
    }
    
    client->close();
    delete client;


    return 0;
}

