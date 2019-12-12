

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

/**
 * the cimplexity is O(1)
 * @return
 */
StatusType AddImage(void *DS, int imageID){
    if(DS== nullptr )
        return INVALID_INPUT;
    try {
        ((StaticEye *) DS)->AddImage(imageID);
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


StatusType DeleteImage(void *DS, int imageID){
    if(DS== nullptr )
        return INVALID_INPUT;
    try {
        ((StaticEye *) DS)->DeleteImage(imageID);
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

StatusType AddLabel(void *DS, int imageID, int segmentID, int label){
    if(DS== nullptr)
        return INVALID_INPUT;
    try {
        ((StaticEye*) DS)->AddLabel(imageID,segmentID, label);
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


StatusType DeleteLabel(void *DS, int imageID, int segmentID){
    if(DS== nullptr)
        return INVALID_INPUT;
    try {
        ((StaticEye*) DS)->DeleteLabel(imageID,segmentID);
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

StatusType GetLabel(void *DS, int imageID, int segmentID, int *label){
    if(DS== nullptr )
        return INVALID_INPUT;
    try {
        ((StaticEye *) DS)->GetLabel(imageID,segmentID,label);
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

StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments,int* numOfSegments){
    if(DS== nullptr )
        return INVALID_INPUT;
    try {
        ((StaticEye *) DS)->GetAllUnLabeledSegments(imageID,segments,numOfSegments);
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



StatusType GetAllSegmentsByLabel(void *DS, int label, int **images, int **segments, int *numOfSegments){
    if(DS== nullptr )
        return INVALID_INPUT;
    try {
        ((StaticEye *) DS)->GetAllSegmentsByLabel(label,images,segments,numOfSegments);
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
    if (*DS == nullptr)
        return;
    StaticEye* static_eye = (StaticEye*) *DS;
    //static_eye->
    //tree_avl->Quit(tree_avl->TreeAvlRoot());
    delete (StaticEye*)*DS;
    *DS = nullptr;
}
