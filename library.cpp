
#include "library.h"
#include "TreeAvl.h"
#include "NodeAvl.h"
#include <stdexcept>
#include <iostream>

typedef void* element;
typedef bool (*CompareFun)(element, element);

void *Init(){
try{
     TreeAvl *DS=new TreeAvl();
     return (void*) DS;
}
catch (std::bad_alloc &e){
        return nullptr;
    }
}


StatusType Add(void *DS, int key, void* value, void** node){
    if(DS== nullptr)
        return INVALID_INPUT;
    try {
        ((TreeAvl*) DS)->Add(key, value, node);
    }
    catch (dataStructure::INVALID_INPUT& e) {
        return INVALID_INPUT;
    }
    catch (dataStructure::ALLOCATION_ERROR& e) {
        return ALLOCATION_ERROR;
    }
    catch (dataStructure::SUCCESS& e) {
        return SUCCESS;
    }
    return SUCCESS;
}


StatusType Size(void *DS, int *n){
    if(DS== nullptr)
        return INVALID_INPUT;
    try {
        ((TreeAvl*) DS)->Size(n);
    }
    catch (dataStructure::INVALID_INPUT& e) {
        return INVALID_INPUT;
    }
    catch (dataStructure::SUCCESS& e) {
        return SUCCESS;
    }
    return SUCCESS;
}


StatusType DeleteByPointer(void *DS, void* p){
    if(DS== nullptr)
        return INVALID_INPUT;
    try {
        ((TreeAvl *) DS)->DeleteByPointer(p);
    }
    catch (dataStructure::INVALID_INPUT& e) {
        return INVALID_INPUT;
    }
    catch (dataStructure::SUCCESS& e) {
        return SUCCESS;
    }
    return SUCCESS;
}


StatusType Find(void *DS, int key, void** value){
    if(DS== nullptr)
        return INVALID_INPUT;
    try {
       ((TreeAvl*) DS)->Find(key,value);
    }
    catch (dataStructure::INVALID_INPUT& e) {
        return INVALID_INPUT;
    }
    catch (dataStructure::ALLOCATION_ERROR& e) {
        return ALLOCATION_ERROR;
    }
    catch (dataStructure::FAILURE& e) {
        return FAILURE;
    }
    return SUCCESS;
}




StatusType Delete(void *DS, int key){
    if(DS== nullptr)
        return INVALID_INPUT;
    int key_copy=key;
    try {
        ((TreeAvl *) DS)->Delete(key_copy);
    }
    catch (dataStructure::INVALID_INPUT& e) {
        return INVALID_INPUT;
    }
    catch (dataStructure::ALLOCATION_ERROR& e) {
        return ALLOCATION_ERROR;
    }
    catch (dataStructure::FAILURE& e) {
        return FAILURE;
    }
    catch (dataStructure::SUCCESS& e) {
        return SUCCESS;
    }
    return SUCCESS;
}




void Quit(void** DS){
    if(*DS==NULL)
        return;
    TreeAvl* TreeAvl = (TreeAvl*) *DS;
    TreeAvl->Quit(TreeAvl->TreeAvlRoot());
    delete TreeAvl;
    *DS=NULL;

}