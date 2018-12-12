#ifndef PLEASE_STATICEYE_H
#define PLEASE_STATICEYE_H

#include "TreeAvl.h"
#include "NodeAvl.h"
#include "Map.h"
#include "ImageValue.h"
#include <stdlib.h>
#include <stdio.h>

class StaticEye {
    TreeAvl<int, ImageValue> *Pictures;
    int segments;
    int count_for_array;

public:

    StaticEye(int segments) : segments(segments), count_for_array(0) {
        this->Pictures = new TreeAvl<int, ImageValue>();
    }

    ~StaticEye() {
        Pictures->Quit(Pictures->TreeAvlRoot());
        delete Pictures;
    }


    StaticEye(const StaticEye &static_eye) : segments(static_eye.segments), Pictures(static_eye.Pictures),
                                             count_for_array(count_for_array) {
    }

    StaticEye &operator=(const StaticEye &static_eye) {
        if (this == &static_eye)
            return *this;
        this->Pictures = static_eye.Pictures;
        this->segments = static_eye.segments;
        this->count_for_array=static_eye.count_for_array;

        return *this;
    }


    void AddImage(int imageID) {
        if (imageID <= 0) {
            throw dataStructure::INVALID_INPUT();
        }
        //ImageValue temp(segments);
        // ImageValue pointer_ImageValue=Pictures->TreeAvlRoot()->nodeAvlGetValue();
        ImageValue *new_value = new ImageValue(segments);
        NodeAvl<int, ImageValue> *save_node;
        NodeAvl<int, ImageValue> *node_that_found;
        try {
            node_that_found = (this->Pictures)->Find(imageID);
            if (node_that_found != nullptr) //the key exist
                throw dataStructure::SUCCESS();
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
                (this->Pictures)->Add(imageID, (ImageValue *) new_value, (void **) &save_node);
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
            NodeAvl<int, ImageValue> *new_node = Pictures->Find(imageID);
            for (int i = 0; i < segments; i++) {

                new_node->nodeAvlGetValue().ImageValueGetMap()->Delete(i);
            }
            delete[] new_node->nodeAvlGetValue().ImageValueGetLabels();

            this->Pictures->Delete(imageID);

            throw dataStructure::SUCCESS();
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
    }


    void AddLabel(int imageID, int segmentID, int label) {
        if (segmentID < 0 || segmentID >= this->segments ||
            label <= 0 || imageID <= 0)
            throw dataStructure::INVALID_INPUT();

        NodeAvl<int, ImageValue> *found_image;
        // ImageValue *pointer_ImageValue;
        try {
            found_image = (this->Pictures)->Find(imageID);

            if (((found_image->nodeAvlGetValue()).ImageValueGetLabels()[segmentID] != 0)) {//there is a lable
                throw dataStructure::FAILURE();
            }//finish if

            (found_image->nodeAvlGetValue()).ImageValueGetLabels()[segmentID] = label;

            //now we need to remove the node from the list missingLable

            (found_image->nodeAvlGetValue()).ImageValueGetMap()->Delete(segmentID);

            //}//finish catch- SUCCESS
            throw dataStructure::SUCCESS();


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
        //catch (dataStructure::SUCCESS &e) { //the key exist


    }//finish func

    void GetLabel(int imageID, int segmentID, int *label) {

        if (segmentID < 0 || segmentID >= this->segments ||
            label <= 0 || imageID <= 0)
            throw dataStructure::INVALID_INPUT();

        NodeAvl<int, ImageValue> *found_image;
        //ImageValue *pointer_ImageValue;
        try {
            found_image = (this->Pictures)->Find(imageID);

            if (((found_image->nodeAvlGetValue()).ImageValueGetLabels()[segmentID] == 0)) {//there is a lable
                throw dataStructure::FAILURE();
            }//finish if
            *label = (found_image->nodeAvlGetValue().ImageValueGetLabels()[segmentID]);
            throw dataStructure::SUCCESS();
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

    }//finish function

    void DeleteLabel(int imageID, int segmentID) {
        if (segmentID < 0 || segmentID >= segments || imageID <= 0)
            throw dataStructure::INVALID_INPUT();
        void *node;

        //ImageValue *pointer_ImageValue;
        NodeAvl<int, ImageValue> *found_image;
        try {
            found_image = (this->Pictures)->Find(imageID);

            if ((found_image->nodeAvlGetValue()).ImageValueGetLabels()[segmentID] == 0) { //there is no lable
                throw dataStructure::FAILURE();
            }//finish if

            (found_image->nodeAvlGetValue()).ImageValueGetLabels()[segmentID] = 0;

            (found_image->nodeAvlGetValue()).ImageValueGetMap()->Add(segmentID, 0, &node);

            //finish catch-success
            throw dataStructure::SUCCESS();

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
    }


    void GetAllUnLabeledSegments(int imageID, int **segments, int *numOfSegments) {
        if (imageID <= 0 || segments == nullptr || numOfSegments == nullptr)
            throw dataStructure::INVALID_INPUT();
        *numOfSegments = 0;
        // ImageValue *pointer_ImageValue;
        NodeAvl<int, ImageValue> *found_image;
        try {
            found_image = (this->Pictures)->Find(imageID);

            if (found_image->nodeAvlGetValue().ImageValueGetMap()->MapSize() == 0)
                throw dataStructure::FAILURE();

            int size_array = found_image->nodeAvlGetValue().ImageValueGetMap()->MapSize();
            int *temp_segments = (int *) malloc(sizeof(int) * size_array);
            if (temp_segments == nullptr)
                throw dataStructure::ALLOCATION_ERROR();
            int counter = 0;
            for (Map::Node<int> *itr = found_image->nodeAvlGetValue().ImageValueGetMap()->returnHead();
                 itr != nullptr;
                 itr = itr->nodeGetNext()) {
                temp_segments[counter] = itr->getKey();
                counter++;
                (*numOfSegments)++;
            }
            *segments = temp_segments;
            throw dataStructure::SUCCESS();
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
    }


    void inorder_count(NodeAvl<int,ImageValue> *p,int label){
        if(p==nullptr)
            return;
        inorder_count(p->nodeAvlGetLeftChild(),label);
        for(int i=0; i<segments;i++) {
            if (p->nodeAvlGetValue().ImageValueGetLabels()[i] == label)
                this->count_for_array++;
        }
        inorder_count(p->nodeAvlGetRightChild(),label);
    }

    void write_inorder(NodeAvl<int, ImageValue> *p, int label, int *images, int *segments) {
        if (p == nullptr)
            return;
        write_inorder(p->nodeAvlGetLeftChild(), label, images, segments);

        for (int i = 0; i < this->segments; i++) {
            if (p->nodeAvlGetValue().ImageValueGetLabels()[i] == label) {
                images[i] = p->nodeAvlGetKey();
                segments[i] = i;
            }
        }

        write_inorder(p->nodeAvlGetRightChild(), label, images, segments);
    }


    void GetAllSegmentsByLabel(int label, int **images, int **segments, int *numOfSegments) {
        if (images == nullptr || segments == nullptr || numOfSegments == nullptr || label <= 0)
            throw dataStructure::INVALID_INPUT();
        //count how much area we have with the same lable
        inorder_count(Pictures->TreeAvlRoot(),label);
       int *temp_segments = (int *) malloc(count_for_array * sizeof(int));
        if (temp_segments == nullptr)
            throw dataStructure::ALLOCATION_ERROR();
        int *temp_images = (int *) malloc(count_for_array * sizeof(int));
        if (temp_images == nullptr)
            throw dataStructure::ALLOCATION_ERROR();

        write_inorder(Pictures->TreeAvlRoot(), label,temp_images, temp_segments);
        *numOfSegments = count_for_array;
        for(int i=0;i<this->segments;i++) {
            *segments[i] = temp_segments[i];
            *images[i] = temp_images[i];
        }
        throw dataStructure::SUCCESS();
    }


};


#endif //PLEASE_STATICEYE_H