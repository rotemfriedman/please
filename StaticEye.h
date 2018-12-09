#ifndef PLEASE_STATICEYE_H
#define PLEASE_STATICEYE_H

#include "TreeAvl.h"
#include "NodeAvl.h"
#include "Map.h"
#include "ImageValue.h"

class StaticEye {
    TreeAvl<int, ImageValue *> *Pictures;
    int segments;

public:

    StaticEye(int segments) {
        this->Pictures = new TreeAvl<int, ImageValue *>();
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
        ImageValue *real_value;
        ImageValue *pointer_ImageValue;
        int temp=0;
        void *save_node;
        void *new_value;
        NodeAvl<int, ImageValue *> *node_that_found;
        try {
            node_that_found = (this->Pictures)->Find(imageID, (void **) &pointer_ImageValue);
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
                (this->Pictures)->Add(imageID,(void **) &new_value, &save_node);
                //(ImageID, &new_value, &save_node);
            }
            catch (dataStructure::ALLOCATION_ERROR &e) {
                throw dataStructure::ALLOCATION_ERROR();
            }
            catch (dataStructure::INVALID_INPUT &e) {
                throw dataStructure::INVALID_INPUT();
            }
            catch (dataStructure::SUCCESS &e) {

                try {
                    real_value = new ImageValue(this->segments);
                }
                catch (dataStructure::ALLOCATION_ERROR &e) {
                    throw dataStructure::ALLOCATION_ERROR();
                }
                catch (dataStructure::INVALID_INPUT &e) {
                    throw dataStructure::INVALID_INPUT();
                }
                catch (dataStructure::SUCCESS &e) {
                    node_that_found->nodeAvlSetValue(real_value);

                    throw dataStructure::SUCCESS();


                } //finish catch
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
            void *value;
            NodeAvl<int, ImageValue *> *new_node = Pictures->Find(imageID, &value);

            for (int i = 0; i < segments; i++) {

                new_node->nodeAvlGetValue()->ImageValueGetMap()->Delete(i);
            }
            delete[] new_node->nodeAvlGetValue()->ImageValueGetLabels();

            throw dataStructure::SUCCESS();
        }
    }


    void AddLabel(int imageID, int segmentID, int label) {
        if (segmentID < 0 || segmentID >= this->segments ||
            label <= 0 || imageID <= 0)
            throw dataStructure::INVALID_INPUT();

        NodeAvl<int, ImageValue *> *found_image;
        ImageValue *pointer_ImageValue;
        try {
            found_image = (this->Pictures)->Find(imageID, (void **) &pointer_ImageValue);
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
            if (((found_image->nodeAvlGetValue())->ImageValueGetLabels()[segmentID] != 0)) {//there is a lable
                throw dataStructure::FAILURE();
            }//finish if

            (found_image->nodeAvlGetValue())->ImageValueGetLabels()[segmentID] = label;

            //now we need to remove the node from the list missingLable

            (found_image->nodeAvlGetValue())->ImageValueGetMap()->Delete(segmentID);

        }//finish catch- SUCCESS
        throw dataStructure::SUCCESS();

    }//finish func

    void GetLabel(int imageID, int segmentID, int *label) {

        if (segmentID < 0 || segmentID >= this->segments ||
            label <= 0 || imageID <= 0)
            throw dataStructure::INVALID_INPUT();


        NodeAvl<int, ImageValue *> *found_image = 0;
        ImageValue *pointer_ImageValue;
        try {
            found_image = (this->Pictures)->Find(imageID, (void **) &pointer_ImageValue);
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
            if (((found_image->nodeAvlGetValue())->ImageValueGetLabels()[segmentID] != 0)) {//there is a lable
                throw dataStructure::FAILURE();
            }//finish if
            *label = (found_image->nodeAvlGetValue()->ImageValueGetLabels()[segmentID]);

        }//finish the catch-SUCCESS

        throw dataStructure::SUCCESS();

    }//finish function

    void DeleteLabel(int imageID, int segmentID) {
        if (segmentID < 0 || segmentID >= segments || imageID <= 0)
            throw dataStructure::INVALID_INPUT();
        void *node;

        ImageValue *pointer_ImageValue;
        NodeAvl<int, ImageValue *> *found_image;
        try {
            found_image = (this->Pictures)->Find(imageID, (void **) &pointer_ImageValue);
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

            if ((found_image->nodeAvlGetValue())->ImageValueGetLabels()[segmentID] == 0) { //there is no lable
                throw dataStructure::FAILURE();
            }//finish if

            (found_image->nodeAvlGetValue())->ImageValueGetLabels()[segmentID] = 0;

            (found_image->nodeAvlGetValue())->ImageValueGetMap()->Add(segmentID, 0, &node);

            //finish catch-success
            throw dataStructure::SUCCESS();

        }//finish func





    }
};


#endif //PLEASE_STATICEYE_H
