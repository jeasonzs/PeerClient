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

void heartCb(void* ptr)
{
    cout<<"heartCb cb"<<endl;
	JSPeerClient* client = (JSPeerClient*)ptr;
	if(client) {
		client->close();
	}
	mainStopFlg=true;
}

void registCb(void* ptr)
{
    cout<<"registCb cb"<<endl;
	JSPeerClient* client = (JSPeerClient*)ptr;
	if(client) {
		client->heart(heartCb,ptr);
	}
}

void connectCb(void* ptr)
{
    cout<<"connectCb cb"<<endl;
	JSPeerClient* client = (JSPeerClient*)ptr;
	if(client) {
		client->regist(registCb,ptr);
	}
}






#if 1
int main(int argc, const char * argv[]) {
    // insert code here...
    signal(SIGINT,SigintCb);
    signal(SIGALRM,SigintCb);
    std::cout << "start peerClient!\n"<<endl;
    srand( (unsigned)time( NULL ) );
    JSPeerClient* client = new JSPeerClient(rand()%1000000+1);
    client->connect("192.168.10.158", 60000 ,1000*2,connectCb,client);
    while (!mainStopFlg) {
        usleep(1000*1000);
//        client->regist(registCb,NULL);
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


