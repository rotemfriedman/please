#ifndef HW2_TREE_TREEAVL_H
#define HW2_TREE_TREEAVL_H

#include "NodeAvl.h"
#include "Exception.h"
#include <stdexcept>

template< class CompareFun ,class TKey, class TValue>
class TreeAvl {
    NodeAvl<TKey, TValue> *root;
    NodeAvl<TKey, TValue> *itr;
    CompareFun compare;
    int tree_size;

public:

    //לבדוק האם צריך לאתחל את הcompare
    //constractor of the class TreeAvl
    TreeAvl(CompareFun compare) :root(nullptr),itr(nullptr),compare(compare),
                                 tree_size(0){};

    ~TreeAvl()= default;

    TreeAvl (const TreeAvl &tree_avl)= default;

    TreeAvl &operator=(const TreeAvl &tree_avl)= default;


/**
 * the function get a node and fix his balce factor
 * @param node_avl - from type pointer to NodeAvl
 */
    void fixFactor(NodeAvl<TKey, TValue>* node_avl)
    {
        int right_height, left_height;
        if((node_avl->nodeAvlGetRightChild())->nodeAvlGetHeight()==NULL)
            right_height=-1;
        else{
            right_height=(node_avl->nodeAvlGetRightChild())->nodeAvlGetHeight();
        }
        if((node_avl->nodeAvlGetLeftChild())->nodeAvlGetHeight()==NULL)
            left_height=-1;
        else{
            left_height=(node_avl->nodeAvlGetLeftChild())->nodeAvlGetHeight();
        }
        //update the balnce factor
        node_avl->nodeAvlSetBalanceFactor(left_height-right_height);
    }

/**
 * the function get a node_avl and fix his height
 * @param node_avl - from type pointer to NodeAvl
 */
    void fixHeight(NodeAvl<TKey, TValue>* node_avl){
        if(node_avl->nodeAvlGetLeftChild()==nullptr && node_avl->
                nodeAvlGetRightChild()==nullptr){
            node_avl->nodeAvlSetHeight(0);
            return;
        }
        if(node_avl->nodeAvlGetLeftChild()==nullptr && node_avl->
                nodeAvlGetRightChild()!=nullptr){
            node_avl->nodeAvlSetHeight(1+((node_avl->nodeAvlGetRightChild())->nodeAvlGetHeight()));
        }
        else if (node_avl->nodeAvlGetLeftChild()!=nullptr && node_avl->nodeAvlGetRightChild()==nullptr){
            node_avl->nodeAvlSetHeight(1+((node_avl->nodeAvlGetLeftChild())->nodeAvlGetHeight()));
        }
        else{  //both of the child trees are not NULL
                if(((node_avl->nodeAvlGetLeftChild())->nodeAvlGetHeight())>=
                        ((node_avl->nodeAvlGetRightChild())->nodeAvlGetHeight())){
                    node_avl->nodeAvlSetHeight(1+((node_avl->nodeAvlGetLeftChild())
                            ->nodeAvlGetHeight()));
                }
                else{
                    node_avl->nodeAvlSetHeight(1+((node_avl->nodeAvlGetRightChild())
                            ->nodeAvlGetHeight()));
                }
        }
    }


    /* Description:   Finds an item in the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The item to find.
 * Output:        value - a pointer to a variable which will contain the value of the element.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item does not exist in the DS.
 *                SUCCESS - If the item is found in the DS.
 */
    void Find(int key, void** value) {
        if (*value == nullptr) {
            throw dataStructure::INVALID_INPUT();
        }
        NodeAvl<TKey, TValue>* new_node;
        try{
            new_node=new NodeAvl<TKey, TValue>
                    (0,0,key, nullptr, nullptr, nullptr, nullptr);
        }
        catch (std::bad_alloc& e){
            throw dataStructure::ALLOCATION_ERROR();
        }
        if(new_node==NULL)                         //maybe we don't need this
            throw dataStructure::ALLOCATION_ERROR();
        this->itr=this->root;
        while(itr!= nullptr){
            int result=this->compare(itr, new_node);
            if(result<0)                           //itr->key < new_node->key
                itr=itr->nodeAvlGetRightChild();
            else if( result>0)                      //itr->key > new_node->key
                itr=itr->nodeAvlGetLeftChild();
            else{         //in this case result=0, and we found the node
                *value=itr->nodeAvlGetValue();
                delete new_node;
                throw dataStructure::SUCCESS();
            }/// if we here the key is not in the tree
            delete new_node;
            *value= nullptr;
            throw dataStructure::FAILURE();
        }
    }



};

#endif //HW2_TREE_TREEAVL_H
