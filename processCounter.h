#pragma once
#ifndef __PROCESS_COUNTER_H__
#define __PROCESS_COUNTER_H__

#include <iostream>
#include <string>

class processCounter
{
public:
    processCounter(std::string pn):processName(pn) {}
    ~processCounter() {}

    int counter();   //return count of process
    
    //int startProcess();  //start the process

    bool killProcess();  //kill the process
private:
    std::string processName;
};

#endif
