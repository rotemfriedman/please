#ifndef PLEASE_STATICEYE_H
#define PLEASE_STATICEYE_H

#include "TreeAvl.h"
#include "NodeAvl.h"
#include "Map.h"
#include "ImageValue.h"

class StaticEye {
    TreeAvl<int, ImageValue>* Pictures;
    int segments;

public:

    StaticEye(int segments) {
        this->Pictures = new TreeAvl<int, ImageValue>();
        this->segments = segments;
    }

    ~StaticEye() {
        Pictures->Quit(Pictures->TreeAvlRoot());
        delete Pictures;
    }


    StaticEye(const StaticEye &static_eye) : segments(static_eye.segments), Pictures(static_eye.Pictures) {
    }

    StaticEye &operator=(const StaticEye &static_eye) {
        if (this == &static_eye)
            return *this;
        this->Pictures = static_eye.Pictures;
        this->segments = static_eye.segments;

        return *this;
    }


    void AddImage(int imageID) {
        if (imageID <= 0) {
            throw dataStructure::INVALID_INPUT();
        }
        //ImageValue temp(segments);
       // ImageValue pointer_ImageValue=Pictures->TreeAvlRoot()->nodeAvlGetValue();
        ImageValue* new_value = new ImageValue(segments);
        NodeAvl<int,ImageValue>* save_node;
        NodeAvl<int, ImageValue>* node_that_found;
        try {
            node_that_found = (this->Pictures)->Find(imageID);
        }
        catch (dataStructure::ALLOCATION_ERROR &e) {
            throw dataStructure::ALLOCATION_ERROR();
        }
        catch (dataStructure::INVALID_INPUT &e) {
            throw dataStructure::INVALID_INPUT();
        }
        catch (dataStructure::SUCCESS &e) { //the key exist
            throw dataStructure::FAILURE();
        }
        catch (dataStructure::FAILURE &e) { //the key not exist
            try {
                (this->Pictures)->Add(imageID,new_value,(void**) &save_node);
                //(ImageID, &new_value, &save_node);
            }
            catch (dataStructure::ALLOCATION_ERROR &e) {
                throw dataStructure::ALLOCATION_ERROR();
            }
            catch (dataStructure::INVALID_INPUT &e) {
                throw dataStructure::INVALID_INPUT();
            }
            catch (dataStructure::SUCCESS &e) {
                    throw dataStructure::SUCCESS();
            }
        }
    }


    void DeleteImage(int imageID) {
        if (imageID <= 0) {
            throw dataStructure::INVALID_INPUT();
        }
        try {
            this->Pictures->Delete(imageID);
        }
        catch (dataStructure::INVALID_INPUT &e) {
            throw dataStructure::INVALID_INPUT();
        }
        catch (dataStructure::ALLOCATION_ERROR &e) {
            throw dataStructure::ALLOCATION_ERROR();
        }
        catch (dataStructure::FAILURE &e) {
            throw dataStructure::FAILURE();
        }
        catch (dataStructure::SUCCESS &e) {
            // destroy the connected list missing_lable
            //void *value;
            NodeAvl<int, ImageValue> *new_node = Pictures->Find(imageID);

            for (int i = 0; i < segments; i++) {

                new_node->nodeAvlGetValue().ImageValueGetMap()->Delete(i);
            }
            delete[] new_node->nodeAvlGetValue().ImageValueGetLabels();

            throw dataStructure::SUCCESS();
        }
    }


    void AddLabel(int imageID, int segmentID, int label) {
        if (segmentID < 0 || segmentID >= this->segments ||
            label <= 0 || imageID <= 0)
            throw dataStructure::INVALID_INPUT();

        NodeAvl<int, ImageValue> *found_image;
       // ImageValue *pointer_ImageValue;
        try {
            found_image = (this->Pictures)->Find(imageID);
        }
        catch (dataStructure::ALLOCATION_ERROR &e) {
            throw dataStructure::ALLOCATION_ERROR();
        }
        catch (dataStructure::INVALID_INPUT &e) {
            throw dataStructure::INVALID_INPUT();
        }
        catch (dataStructure::FAILURE &e) { //the imageID not exist
            throw dataStructure::FAILURE();
        }
        catch (dataStructure::SUCCESS &e) { //the key exist
            if (((found_image->nodeAvlGetValue()).ImageValueGetLabels()[segmentID] != 0)) {//there is a lable
                throw dataStructure::FAILURE();
            }//finish if

            (found_image->nodeAvlGetValue()).ImageValueGetLabels()[segmentID] = label;

            //now we need to remove the node from the list missingLable

            (found_image->nodeAvlGetValue()).ImageValueGetMap()->Delete(segmentID);

        }//finish catch- SUCCESS
        throw dataStructure::SUCCESS();

    }//finish func

    void GetLabel(int imageID, int segmentID, int *label) {

        if (segmentID < 0 || segmentID >= this->segments ||
            label <= 0 || imageID <= 0)
            throw dataStructure::INVALID_INPUT();


        NodeAvl<int, ImageValue> *found_image;
        //ImageValue *pointer_ImageValue;
        try {
            found_image = (this->Pictures)->Find(imageID);
        }

        catch (dataStructure::ALLOCATION_ERROR &e) {
            throw dataStructure::ALLOCATION_ERROR();
        }
        catch (dataStructure::INVALID_INPUT &e) {
            throw dataStructure::INVALID_INPUT();
        }
        catch (dataStructure::FAILURE &e) { //the IMAGEid not exist
            throw dataStructure::FAILURE();
        }
        catch (dataStructure::SUCCESS &e) { //the key exist
            if (((found_image->nodeAvlGetValue()).ImageValueGetLabels()[segmentID] != 0)) {//there is a lable
                throw dataStructure::FAILURE();
            }//finish if
            *label = (found_image->nodeAvlGetValue().ImageValueGetLabels()[segmentID]);

        }//finish the catch-SUCCESS

        throw dataStructure::SUCCESS();

    }//finish function

    void DeleteLabel(int imageID, int segmentID) {
        if (segmentID < 0 || segmentID >= segments || imageID <= 0)
            throw dataStructure::INVALID_INPUT();
        void *node;

        //ImageValue *pointer_ImageValue;
        NodeAvl<int, ImageValue> *found_image;
        try {
            found_image = (this->Pictures)->Find(imageID);
        }
        catch (dataStructure::ALLOCATION_ERROR &e) {
            throw dataStructure::ALLOCATION_ERROR();
        }
        catch (dataStructure::INVALID_INPUT &e) {
            throw dataStructure::INVALID_INPUT();
        }
        catch (dataStructure::FAILURE &e) { //the imageID NOT EXIST
            throw dataStructure::FAILURE();
        }
        catch (dataStructure::SUCCESS &e) { //the key exist

            if ((found_image->nodeAvlGetValue()).ImageValueGetLabels()[segmentID] == 0) { //there is no lable
                throw dataStructure::FAILURE();
            }//finish if

            (found_image->nodeAvlGetValue()).ImageValueGetLabels()[segmentID] = 0;

            (found_image->nodeAvlGetValue()).ImageValueGetMap()->Add(segmentID, 0, &node);

            //finish catch-success
            throw dataStructure::SUCCESS();

        }//finish func
        }


        void GetAllUnLabeledSegments(int imageID, int **segments, int* numOfSegments){
            if(imageID<=0 || segments== nullptr || numOfSegments== nullptr)
                throw dataStructure::INVALID_INPUT();
            *numOfSegments=0;
           // ImageValue *pointer_ImageValue;
            NodeAvl<int,ImageValue>* found_image;
            try {
                found_image = (this->Pictures)->Find(imageID);
            }
            catch (dataStructure::ALLOCATION_ERROR &e) {
                throw dataStructure::ALLOCATION_ERROR();
            }
            catch (dataStructure::INVALID_INPUT &e) {
                throw dataStructure::INVALID_INPUT();
            }
            catch (dataStructure::FAILURE &e) { //the imageID NOT EXIST
                throw dataStructure::FAILURE();
            }
            catch (dataStructure::SUCCESS &e) { //the key exist and we continue the function
                if(found_image->nodeAvlGetValue().ImageValueGetMap()->MapSize()==0)
                    throw dataStructure::FAILURE();

                int size_arry=found_image->nodeAvlGetValue().ImageValueGetMap()->MapSize();
                *segments = (int*) malloc(size_arry*sizeof(int));
                if(*segments== nullptr)
                    throw dataStructure::ALLOCATION_ERROR();
                int counter=0;
                for(Map::Node<int>* itr=found_image->nodeAvlGetValue().ImageValueGetMap()->returnHead();
                    itr!= nullptr;
                    itr=itr->nodeGetNext()){
                    *segments[counter]=itr->getKey();
                    counter++;
                    *numOfSegments++;
                }
                throw dataStructure::SUCCESS();
            }
        }


        int inorder_count(NodeAvl<int,ImageValue> *p,int count,int label){
            if(p==nullptr)
                return count;
            inorder_count(p->nodeAvlGetLeftChild(),count,label);
            for(int i=0; i<segments;i++) {
                if (p->nodeAvlGetValue().ImageValueGetLabels()[i] == label)
                    count++;
            }
            inorder_count(p->nodeAvlGetRightChild(),count,label);
        }

        void write_inorder(NodeAvl<int,ImageValue> *p,int label,int **images, int **segments){
            if(p== nullptr)
                return;
            write_inorder(p->nodeAvlGetLeftChild(),label,images, segments);

            for(int i=0; i<this->segments; i++){
                if(p->nodeAvlGetValue().ImageValueGetLabels()[i] == label){
                    *images[i]=p->nodeAvlGetKey();
                    *segments[i]=i;
                }
            }

            write_inorder(p->nodeAvlGetRightChild(),label,images, segments);
        }




        void GetAllSegmentsByLabel(int label, int **images, int **segments, int *numOfSegments){
            if(images== nullptr || segments== nullptr || numOfSegments== nullptr || label<=0)
                throw dataStructure::INVALID_INPUT();
            //count how much area we have with the same lable
            int count=inorder_count(Pictures->TreeAvlRoot(),0,label);
            *segments = (int*) malloc(count*sizeof(int));
            if(*segments== nullptr)
                throw dataStructure::ALLOCATION_ERROR();
            *images = (int*) malloc(count*sizeof(int));
            if(*images== nullptr)
                throw dataStructure::ALLOCATION_ERROR();

            write_inorder(Pictures->TreeAvlRoot(),label,images,segments);
            *numOfSegments=count;

            throw dataStructure::SUCCESS();
        }



};


#endif //PLEASE_STATICEYE_H
