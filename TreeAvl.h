#ifndef HW2_TREE_TREEAVL_H
#define HW2_TREE_TREEAVL_H

#include "NodeAvl.h"
#include "Exception.h"

template< class CompareFun ,class TKey, class TValue>
class TreeAvl {
    NodeAvl<TKey, TValue> *root;
    NodeAvl<TKey, TValue> *itr;
    CompareFun compare;
    int tree_size;

public:

    //לבדוק האם צריך לאתחל את הcompare
    //constractor of the class TreeAvl
    TreeAvl() :root(nullptr), itr(nullptr), tree_size(0){};

    ~TreeAvl()= default;

    TreeAvl (const TreeAvl &tree_avl)= default;

    TreeAvl &operator=(const TreeAvl &tree_avl)= default;


    //לבדוק לגבי הקצאת זיכרון
    /* Description:   Finds an item in the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The item to find.
 * Output:        value - a pointer to a variable which will contain the value of the element.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item does not exist in the DS.
 *                SUCCESS - If the item is found in the DS.
 */

    /*
     *
    void Find(int key, void** value) {
        if (*value == nullptr) {
            throw dataStructure::INVALID_INPUT();
        }

        NodeAvl<TKey, TValue> new_node=new NodeAvl<TKey, TValue>
                (0,0,key, nullptr, nullptr, nullptr, nullptr);
        this->itr=this->root;
        while(itr!= nullptr){
            int result=compare(itr, new_node);
            if(result<0)
                itr=itr->nodeAvlGetRightChild();
            else if( result>0)
                itr=itr->nodeAvlGetLeftChild();
            else{       //in this case result=0, and we found the //node
                *value=itr->getdata;
                delete new_node;
                throw dataStructure::SUCCESS();
            }/// if we here the key not in the tree
            delete new_node;
            *value= nullptr;
            throw dataStructure::FAILURE();
        }
    }



*/

};

#endif //HW2_TREE_TREEAVL_H
