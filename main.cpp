
#include <iostream>

#include "library.h"
#include "TreeAvl.h"
#include "NodeAvl.h"
#include <stdexcept>
#include <iostream>



int main() {
    std::cout << "Hello, World!" << std::endl;


     void* new_DS = Init();
    void* node;
   // int n;


     StatusType status = Add(new_DS ,5, (void *) 2, &node);
    StatusType status2 = Add(new_DS, 3, (void *) 4, &node);
    StatusType status3 = Add(new_DS, 1, (void *) 6, &node);
   // StatusType status3=Find(new_DS, 9, &s);
    //StatusType status5=Delete(new_DS,1);
    //StatusType status7= Size(new_DS, &n);
   std::cout << status <<status2<<status3<< std::endl;
    //   Quit(&new_DS);
     //*/

    return 0;

}


