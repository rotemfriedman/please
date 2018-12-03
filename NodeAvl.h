#ifndef HW2_TREE_NODEAVL_H
#define HW2_TREE_NODEAVL_H

#include "TreeAvl.h"

template<class TKey, class TValue>
class NodeAvl{
    int hight;
    int balance_factor;
    TKey key;
    TValue value;
    NodeAvl< TKey , TValue >* parent;
    NodeAvl< TKey , TValue >* left_tree;
    NodeAvl< TKey , TValue >* right_tree;

public:
    NodeAvl(int hight,int balance_factor, TKey key, TValue value, NodeAvl< TKey , TValue >* parent,
            NodeAvl< TKey , TValue >* left_tree,NodeAvl< TKey , TValue >* right_tree)
            : hight(hight),balance_factor(balance_factor),key(key),value(value),parent(parent),
              left_tree(left_tree),right_tree(right_tree){

    }

    ~NodeAvl()= default;
    NodeAvl (const NodeAvl &nodeavl)= default;
    NodeAvl &operator=(const NodeAvl &nodeavl)= default;

    NodeAvl* nodeAvlGetParent(){
        return this->parent;
    }

    NodeAvl* nodeAvlGetRightChild(){
        return this->right_tree;
    }

    NodeAvl* nodeAvlGetLeftChild(){
        return this->left_tree;
    }

    int nodeAvlGetHight(){
        return this->hight;
    }

    TValue nodeAvlGetValue(){
        return this->value;
    }

    TKey nodeAvlGetKey(){
        return this->key;
    }

    void nodeAvlSetparent(NodeAvl* nodeavl){
        this->parent=nodeavl;
    }

    void nodeAvlSetLeftChild(NodeAvl* nodeavl){
        this->left_tree=nodeavl;
    }

    void nodeAvlSetRightChild(NodeAvl* nodeavl){
        this->right_tree=nodeavl;
    }





};





#endif //HW2_TREE_NODEAVL_H
