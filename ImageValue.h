#ifndef PLEASE_IMAGEVALUE_H
#define PLEASE_IMAGEVALUE_H

#include "TreeAvl.h"
#include "NodeAvl.h"
#include "Map.h"
#include "StaticEye.h"

class ImageValue {
    int image_segments;
    Map *missingLable;
    int *labels;

public:


    ImageValue(int image_segments) :image_segments(image_segments){
        labels=new int[image_segments];
        missingLable = new Map();
            void* value=0;
            void* node;
            for (int i=0;i<image_segments;i++){
                labels[i] = 0;
            }
            for (int j=0; j<image_segments; j++){
                try {
                    missingLable->Add(j, value, &node);
                }
                catch (dataStructure::ALLOCATION_ERROR &e) {
                    throw dataStructure::ALLOCATION_ERROR();
                }
                catch (dataStructure::INVALID_INPUT &e) {
                    throw dataStructure::INVALID_INPUT();
                }
                catch (dataStructure::SUCCESS &e) {
                    continue;
                }

            }
    }


};


#endif //PLEASE_IMAGEVALUE_H
