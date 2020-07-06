#include <iostream>
#include "processCounter.h"



int main()
{
    processCounter pc("vim");

    pc.killProcess();

    int c = pc.counter();
    std::cout<<"count="<<c<<std::endl;
    return 0;
}

