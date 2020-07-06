#include <iostream>
#include "processCounter.h"
#include <string.h>
#include <stdio.h>

int processCounter::counter()
{
    std::string cmdTemplate = "ps -eaf | grep -v \"sh -c\" | awk '{print $8}' | grep -w %s$ | grep -c %s";

    char cmd[256];
    memset(cmd,0,sizeof(cmd));
    sprintf(cmd,cmdTemplate.c_str(),this->processName.c_str(),this->processName.c_str());

    FILE *f = popen(cmd,"r");
    if(NULL == f)
    {
        std::cout<<"popen error"<<std::endl;
        return 0;
    }

    int result = 0;
    fscanf(f,"%d",&result);

    if(pclose(f) == -1)
    {
        perror("pclose");
        std::cout<<"pclose error"<<std::endl;
    }


    if(result > 0)
        std::cout<<this->processName<<" is already running..."<<std::endl;
    return result;
}

bool processCounter::killProcess()
{
    if(counter() >= 1)
    {
        std::string queryCmd = "ps -eaf | grep -v \"sh -c\" | awk '{if($8~\"" + this->processName + "\"" +")print $2}'";
        FILE *f1 = popen(queryCmd.c_str(),"r");
        if(NULL == f1)
        {
            std::cout<<"popen error"<<std::endl;
            return false;
        }

        int pid = 0;
        fscanf(f1,"%d",&pid);
        std::cout<<processName<<" pid = "<<pid<<std::endl;

        std::string killCmd = "kill -9 " + std::to_string(pid);

        FILE *f2 = popen(killCmd.c_str(),"r");
        if(NULL == f2)
        {
            std::cout<<"popen error, killCmd error"<<std::endl;
            return false;
        }
        
    }else
    {    
        std::cout<<processName<<" is not running, no need to kill"<<std::endl;
        return false;
    }

    return true;
}
