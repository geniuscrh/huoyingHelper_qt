#include "jibanthread.h"

JibanThread::JibanThread()
{

}

void JibanThread::run(){

    for(int i=0;i<1000;i++){
         emit send(QString::number(i+1));
         Sleep(30*1000);
    }

}
