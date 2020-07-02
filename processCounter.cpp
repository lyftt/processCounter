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
        std::cout<<this->processName<<"is already running..."<<std::endl;
    return result;
}


