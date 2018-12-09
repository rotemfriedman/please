#ifndef PLEASE_STATICEYE_H
#define PLEASE_STATICEYE_H

#include "TreeAvl.h"
#include "NodeAvl.h"
#include "Map.h"
#include "ImageValue.h"

class StaticEye {
    TreeAvl<int, ImageValue*> *Pictures;
    int segments;

public:

    StaticEye(int segments):segments(segments),Pictures(new TreeAvl<int, ImageValue *>()){
    }

    ~StaticEye() = default;

    StaticEye(const StaticEye &static_eye) = default;

    StaticEye &operator=(const StaticEye &static_eye) = default;

};



#endif //PLEASE_STATICEYE_H
