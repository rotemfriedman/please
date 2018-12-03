#ifndef HW2_TREE_NODEAVL_H
#define HW2_TREE_NODEAVL_H

#include "TreeAvl.h"

template<class TKey, class TValue>
class NodeAvl {
    int height;
    int balance_factor;
    TKey key;
    TValue value;
    NodeAvl<TKey, TValue> *parent;
    NodeAvl<TKey, TValue> *left_tree;
    NodeAvl<TKey, TValue> *right_tree;

public:
    NodeAvl(int height, int balance_factor, TKey key, TValue value,
            NodeAvl<TKey, TValue> *parent,
            NodeAvl<TKey, TValue> *left_tree, NodeAvl<TKey, TValue> *right_tree)
            : height(height), balance_factor(balance_factor), key(key),
              value(value), parent(parent),
              left_tree(left_tree), right_tree(right_tree) {
    }

    ~NodeAvl() = default;

    NodeAvl(const NodeAvl &nodeavl) = default;

    NodeAvl &operator=(const NodeAvl &nodeavl) = default;

    NodeAvl *nodeAvlGetParent() {
        return this->parent;
    }

    NodeAvl *nodeAvlGetRightChild() {
        return this->right_tree;
    }

    NodeAvl *nodeAvlGetLeftChild() {
        return this->left_tree;
    }

    int nodeAvlGetHeight() {
        return this->height;
    }

    int nodeAvlGetBalanceFactor() {
        return this->balance_factor;
    }


    TValue nodeAvlGetValue() {
        return this->value;
    }

    TKey nodeAvlGetKey() {
        return this->key;
    }

    void nodeAvlSetparent(NodeAvl *nodeavl) {
        this->parent = nodeavl;
    }

    void nodeAvlSetLeftChild(NodeAvl *nodeavl) {
        this->left_tree = nodeavl;
    }

    void nodeAvlSetRightChild(NodeAvl *nodeavl) {
        this->right_tree = nodeavl;
    }

    void nodeAvlSetHight(int height) {
        this->height = height;
    }

    void nodeAvlSetBalanceFactor(int balance_factor) {
        this->balance_factor = balance_factor;
    }


    NodeAvl *getFollowingNode() {
        NodeAvl *following_node = this;
        if (following_node->nodeAvlGetRightChild() == nullptr)
            return nullptr;
        else
            following_node = following_node->nodeAvlGetRightChild();
        while (following_node->nodeAvlGetLeftChild() != nullptr) {
            //like the algoritem go right and then left until null
            following_node = following_node->nodeAvlGetLeftChild();
        }
        return following_node;
    }


};



#endif //HW2_TREE_NODEAVL_H
