#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>

using namespace std;
bool mainStopFlg = false;

void SigintCb(int iSigNum)
{
    mainStopFlg=true;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    signal(SIGINT,SigintCb);
    signal(SIGALRM,SigintCb);
    std::cout << "start peerClient!\n"<<endl;

    while (!mainStopFlg) {
        usleep(100*1000);
    }


    return 0;
}

