#ifndef PLEASE_IMAGEVALUE_H
#define PLEASE_IMAGEVALUE_H

#include "TreeAvl.h"
#include "NodeAvl.h"
#include "Map.h"
#include "StaticEye.h"

class ImageValue{
        int image_segments;
        Map* MissingLable; //המפתח ברשימה המקושרת יהיה ה segment_id
        int Labels[image_segments]; //כל הלייבלים יאותחלו ל0 בפונקציית איתחול
};

#endif //PLEASE_IMAGEVALUE_H
