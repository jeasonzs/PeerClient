#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <sys/time.h>

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


#if 1
int main(int argc, const char * argv[]) {
    // insert code here...
    signal(SIGINT,SigintCb);
    signal(SIGALRM,SigintCb);
    std::cout << "start peerClient!\n"<<endl;
    JSPeerClient* client = new JSPeerClient(0x123456);
    client->connect("192.168.10.158", 60000 ,1000*2);
    srand( (unsigned)time( NULL ) );
    while (!mainStopFlg) {
        usleep(10*1000);
//        if(client->send("hello server!!!\n", sizeof("hello server!!!\n")) <= 0) {
//            cout<<"send error !!!!!!"<<endl;
//        }
//        client->heart(heartCb);
//        client->regist(registCb);
        JSPeerClient* client = new JSPeerClient(rand()%1000000+1);
        client->connect("192.168.10.158", 60000 ,1000*2);
        client->regist(registCb);
    }

    client->close();
    delete client;


    return 0;
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


