#include <iostream>
#include "Map.h"
#include "StaticEye.h"
#include "ImageValue.h"
#include "library2.h"
#include "TreeAvl.h"
#include "NodeAvl.h"
//#include "library1.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {


    std::cout << "Hello, World!" << std::endl;
    void* new_DS = Init(3);
     AddImage(new_DS,10);
     AddImage(new_DS,11);
    AddImage(new_DS,12);
   //  AddImage(new_DS,13);
 //   AddImage(new_DS,14);
    AddLabel(new_DS,10,0,999);
    AddLabel(new_DS,10,1,94);
    AddLabel(new_DS,10,2,999);
    AddLabel(new_DS,11,0,999);
    AddLabel(new_DS,12,0,4545);
    AddLabel(new_DS,12,1,999);
    AddLabel(new_DS,12,2,555);

    //AddLabel(new_DS,10,2,95);
    int courseID=999;
    int numOfLabels;
    int *images, *segments;
    StatusType res = GetAllSegmentsByLabel(new_DS, courseID, &images, &segments, &numOfLabels);

    for (int i = 0; i < numOfLabels; i++)
    {
        printf("%d\t||\t%d\n", images[i], segments[i]);
    }





//    DeleteImage(new_DS,12);
  //  DeleteImage(new_DS,11);
   //  AddImage(new_DS,10);
   // AddImage(new_DS,11);
   // StatusType status8 = DeleteLabel(new_DS,10,0);
 //   StatusType status11 = DeleteLabel(new_DS,11,0);


    /* StatusType status6=AddLabel(new_DS,10,1,96);
    int lable94;
    int lable95;
    int lable96;
    StatusType status7=GetLabel(new_DS,10,0,&lable94);
    StatusType status8=GetLabel(new_DS,10,2,&lable95);
    StatusType status9=GetLabel(new_DS,10,1,&lable96);

*/

    return 0;

}