#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <sys/time.h>

#include "JSPeerClient.hpp"
#include <pjnath.h>
#include "JSIceClient.hpp"

using namespace std;
bool mainStopFlg = false;

void SigintCb(int iSigNum)
{
    mainStopFlg=true;

}
void connectCb(void* context)
{
    cout<<"connectCb cb"<<endl;
	JSPeerClient* client = (JSPeerClient*)context;
	if(client) {
		client->regist();
	}
}

void registResponseCb(void* context)
{
    cout<<"registCb cb"<<endl;
	JSPeerClient* client = (JSPeerClient*)context;
	if(client) {
		client->heart();
	}
}

void heartResponseCb(void* context)
{
    cout<<"heartCb cb"<<endl;
//	JSPeerClient* client = (JSPeerClient*)context;
//	if(client) {
//		client->connectPeer(0x12345678,"iceinfo");
//	}
}


void connectPeerResponseCb(void* context,int status,int remoteId,char* iceInfoRemote)
{
    cout<<"connectPeerResponseCb cb"<<endl;
	JSPeerClient* client = (JSPeerClient*)context;
	if(client) {
		cout<<"status="<<status<<"remoteId="<<remoteId<<"iceInfoRemote="<<iceInfoRemote<<endl;
	}
}

void incomeConnectPeerCb(void* context,int remoteId,char* iceInfoRemote)
{
    cout<<"incomeConnectPeerCb cb"<<endl;
	JSPeerClient* client = (JSPeerClient*)context;
	if(client) {
		cout<<"remoteId="<<remoteId<<"iceInfoRemote="<<iceInfoRemote<<endl;
		client->incomeConnectPeerResponse(remoteId,"iceinfo");
	}
}










#if 1
extern int iceDemo(int argc, char *argv[]);

int main(int argc, char * argv[]) {
    JSIceClient iceClient;
    iceClient.setStun("127.0.0.1");
    iceClient.icedemo_console();
    // insert code here...
    //return iceDemo(argc,argv);
//    signal(SIGINT,SigintCb);
//    signal(SIGALRM,SigintCb);
//    std::cout << "start peerClient!\n"<<endl;
//    srand( (unsigned)time( NULL ) );
//    JSPeerClient* client = new JSPeerClient(21/*rand()%1000000+1*/);
//    client->setRegistResponseCb(registResponseCb,client);
//    client->setHeartResponseCb(heartResponseCb,client);
//    client->setConnectPeerResponseCb(connectPeerResponseCb,client);
//    client->setIncomeConnectPeerCb(incomeConnectPeerCb,client);
//
//    client->connect("127.0.0.1", 60000 ,1000*2,connectCb,client);
    
//    while (!mainStopFlg) {
////    	client->heart();
////        usleep(1000*1000*5);
////        client->connectPeer(0x12345678,"iceinfo");
////        client->regist(registCb,NULL);
//    }
//
//    client->close();
//    delete client;
//
//
//    return 0;
}
#else

class parent
{
	int a[16];
public:
	parent(){;};
    
	inline int sizse(){return sizeof(*this)-sizeof(parent);};
};

class sub: public parent
{
	int b[16];
public:
	sub(){;};

};
int main(int argc, const char * argv[]) {
    // insert code here...
	sub s;
	cout<<"size="<<s.sizse()<<endl;

    return 0;
}
#endif


