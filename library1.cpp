#include "library1.h"
#include "Map.h"
#include <stdexcept>
#include <iostream>
#include "Exception.h"

/**
 * the cimplexity is O(1)
 * @return
 */
void *Init(){
    Map* DS= new Map;
    if (DS==NULL){
        return NULL;
    }
    return (void*)DS;
}



/**
 * the cimplexity is O(1)
 * @return
 */
StatusType Add(void *DS, int key, void* value, void** node){
    if(DS==NULL)
        return INVALID_INPUT;
    try {
    ((Map *) DS)->Add(key, value, node);
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

/**
 * the cimplexity is O(1)
 * @return
 */
StatusType DeleteByPointer(void *DS, void* p){
    if(DS==NULL)
        return INVALID_INPUT;
    try {
        ((Map*) DS)->DeleteByPointer(p);
    }
    catch (dataStructure::INVALID_INPUT& e) {
        return INVALID_INPUT;
    }
    catch (dataStructure::SUCCESS& e) {
        return SUCCESS;
    }
    return SUCCESS;
}

/**
 * the cimplexity is O(1)
 * @return
 */
StatusType Size(void *DS, int *n){
    if(DS==NULL)
        return INVALID_INPUT;
    try {
        ((Map*) DS)->Size(n);
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
    if(DS==NULL)
        return INVALID_INPUT;
    try {
        ((Map *) DS)->Find(key, value);
    }
    catch (dataStructure::INVALID_INPUT& e) {
        return INVALID_INPUT;
    }
    catch (dataStructure::FAILURE& e) {
        return FAILURE;
    }
    catch (dataStructure::SUCCESS& e) {
        return SUCCESS;
    }
    return SUCCESS;
}


StatusType Delete(void *DS, int key){
    if(DS==NULL)
        return INVALID_INPUT;
    int key_copy=key;
    try {
        ((Map *) DS)->Delete(key_copy);
    }
    catch (dataStructure::INVALID_INPUT& e) {
        return INVALID_INPUT;
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
    Map* dictionary = (Map*) *DS;
    dictionary->Quit(DS);
    delete dictionary;
    *DS=NULL;

}