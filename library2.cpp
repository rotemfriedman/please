

#include "library2.h"
#include "TreeAvl.h"
#include "NodeAvl.h"
#include "StaticEye.h"
#include "ImageValue.h"
#include "Map.h"
#include <stdexcept>
#include <iostream>




void * Init(int segments){


    try{
        StaticEye *DS=new StaticEye(segments);
        return (void*) DS;
    }
    catch (std::bad_alloc &e){
        throw dataStructure:: ALLOCATION_ERROR();;
    }
}



