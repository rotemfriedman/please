
#include "library.h"
#include "TreeAvl.h"
#include "NodeAvl.h"
#include <stdexcept>
#include <iostream>



void *Init(){
try{
     TreeAvl<int,int,void*> *DS=new TreeAvl<int,int,void*>(nullptr, nullptr,comparefun,0);
     return (void*) DS;
}
catch (std::bad_alloc &e){
        return NULL;
    }
}

int comparefun(int x,int y){
    if(x-y<0)
        return -1;
    if(x-y>0)
        return 1;
    return 0;
}