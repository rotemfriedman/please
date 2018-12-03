#ifndef HW2_TREE_TREEAVL_H
#define HW2_TREE_TREEAVL_H

#include "NodeAvl.h"
#include "Exception.h"
#include <stdexcept>

template<class CompareFun, class TKey, class TValue>
class TreeAvl {
    NodeAvl<TKey, TValue> *root;
    NodeAvl<TKey, TValue> *itr;
    CompareFun compare;
    int tree_size;

public:

    //constractor of the class TreeAvl
    TreeAvl(CompareFun compare) : root(nullptr), itr(nullptr), compare(compare),
                                  tree_size(0) {};

    ~TreeAvl() = default;

    TreeAvl(const TreeAvl &tree_avl) = default;

    TreeAvl &operator=(const TreeAvl &tree_avl) = default;


/**
 * the function get a node and fix his balce factor
 * @param node_avl - from type pointer to NodeAvl
 */
    void setFactorBalance(NodeAvl<TKey, TValue> *node_avl) {
        int right_height, left_height;
        if ((node_avl->nodeAvlGetRightChild())->nodeAvlGetHeight() == NULL)
            right_height = -1;
        else {
            right_height = (node_avl->nodeAvlGetRightChild())->nodeAvlGetHeight();
        }
        if ((node_avl->nodeAvlGetLeftChild())->nodeAvlGetHeight() == NULL)
            left_height = -1;
        else {
            left_height = (node_avl->nodeAvlGetLeftChild())->nodeAvlGetHeight();
        }
        //update the balnce factor
        node_avl->nodeAvlSetBalanceFactor(left_height - right_height);
    }

/**
 * the function get a node_avl and fix his height
 * @param node_avl - from type pointer to NodeAvl
 */
    void fixHeight(NodeAvl<TKey, TValue> *node_avl) {
        if (node_avl->nodeAvlGetLeftChild() == nullptr && node_avl->
                nodeAvlGetRightChild() == nullptr) {
            node_avl->nodeAvlSetHeight(0);
            return;
        }
        if (node_avl->nodeAvlGetLeftChild() == nullptr && node_avl->
                nodeAvlGetRightChild() != nullptr) {
            node_avl->nodeAvlSetHeight(1 +
                                       ((node_avl->nodeAvlGetRightChild())->nodeAvlGetHeight()));
        } else if (node_avl->nodeAvlGetLeftChild() != nullptr &&
                   node_avl->nodeAvlGetRightChild() == nullptr) {
            node_avl->nodeAvlSetHeight(1 +
                                       ((node_avl->nodeAvlGetLeftChild())->nodeAvlGetHeight()));
        } else {  //both of the child trees are not NULL
            if (((node_avl->nodeAvlGetLeftChild())->nodeAvlGetHeight()) >=
                ((node_avl->nodeAvlGetRightChild())->nodeAvlGetHeight())) {
                node_avl->nodeAvlSetHeight(
                        1 + ((node_avl->nodeAvlGetLeftChild())
                                ->nodeAvlGetHeight()));
            } else {
                node_avl->nodeAvlSetHeight(
                        1 + ((node_avl->nodeAvlGetRightChild())
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
    void Find(int key, void **value) {
        if (*value == nullptr) {
            throw dataStructure::INVALID_INPUT();
        }
        NodeAvl<TKey, TValue> *new_node;
        try {
            new_node = new NodeAvl<TKey, TValue>
                    (0, 0, key, nullptr, nullptr, nullptr, nullptr);
        }
        catch (std::bad_alloc &e) {
            throw dataStructure::ALLOCATION_ERROR();
        }
        if (new_node ==
            nullptr)                         //maybe we don't need this
            throw dataStructure::ALLOCATION_ERROR();
        this->itr = this->root;
        while (itr != nullptr) {
            int result = this->compare(itr, new_node);
            if (result < 0)                           //itr->key < new_node->key
                itr = itr->nodeAvlGetRightChild();
            else if (result > 0)                      //itr->key > new_node->key
                itr = itr->nodeAvlGetLeftChild();
            else {         //in this case result=0, and we found the node
                *value = itr->nodeAvlGetValue();
                delete new_node;
                throw dataStructure::SUCCESS();
            }/// if we here the key is not in the tree
            delete new_node;
            *value = nullptr;
            throw dataStructure::FAILURE();
        }
    }

    void Add(int key, void *value, void **node) {
        if (node == nullptr)
            throw dataStructure::INVALID_INPUT();
        NodeAvl<TKey, TValue> *new_node;
        try {
            new_node = new NodeAvl<TKey, TValue>(0, 0,
                                                 key,
                                                 value,
                                                 nullptr,
                                                 nullptr,
                                                 nullptr);
        }
        catch (std::bad_alloc &e) {
            throw dataStructure::ALLOCATION_ERROR();
        }
        this->itr = this->root;
        int result = 0;
        while (itr != nullptr) {
            result = this->compare(itr, new_node);
            if (result < 0) {
                new_node->parent = itr;
                itr = itr->getrighttree;
            } else if (result > 0) {
                new_node->parent = itr;
                itr = itr->getlefttree;
            }
        }
        if (result < 0) {
            (new_node->nodeAvlGetParent())->nodeAvlSetRightChild(new_node);
        } else {
            (new_node->nodeAvlGetParent())->nodeAvlSetLeftChild(new_node);
        }
        while (new_node != this->root) {
            NodeAvl<TKey, TValue> *p = new_node->nodeAvlGetParent();
            if (p->nodeAvlGetHeight() >= new_node->nodeAvlGetHeight() + 1) {
                this->tree_size++;
                throw dataStructure::SUCCESS();
            }
            p->nodeAvlSetHeight(new_node->nodeAvlGetHeight() + 1);
            setFactorBalance(p);
            bool roll = checkRollForP(p);

            if (roll == true) {
                this->tree_size++;
                throw dataStructure::SUCCESS();
            }
            new_node = p;
        }//finish while
        this->tree_size++;
    }


    bool checkRollForP(NodeAvl<TKey, TValue> *p) {

        if (p->nodeAvlGetBalanceFactor() == -2 &&
            p->nodeAvlGetRightChild()->nodeAvlGetBalanceFactor() == 1) {
            RLroll(p);
            return true;
        } else if (p->nodeAvlGetBalanceFactor() == 2 &&
                   p->nodeAvlGetLeftChild()->nodeAvlGetBalanceFactor() == -1) {
            LRroll(p);
            return true;
        } else if (p->nodeAvlGetBalanceFactor() == -2 &&
                   p->nodeAvlGetRightChild()->nodeAvlGetBalanceFactor() <= 0) {
            RRroll(p);
            return true;
        } else if (p->nodeAvlGetBalanceFactor() == 2 &&
                   p->nodeAvlGetLeftChild()->nodeAvlGetBalanceFactor() >= 0) {
            LLroll(p);
            return true;
        }
        return false;
    }

    void RRRoll( NodeAvl<TKey, TValue> * node_avl) {

        NodeAvl<TKey, TValue> *right_left_tree;
        NodeAvl<TKey, TValue> *right_tree = node_avl->nodeAvlGetLeftChild();
        if (this->root == node_avl) {
            this->root = right_tree;
        }
        if (node_avl->nodeAvlGetRightChild() == nullptr)
            right_left_tree = nullptr;
        else
            right_left_tree = node_avl->nodeAvlGetRightChild()->nodeAvlGetLeftChild();

        node_avl->nodeAvlSetRightChild(right_left_tree);
        if (node_avl->nodeAvlGetParent() == nullptr) {
            right_tree->nodeAvlSetparent(nullptr);
        } else {
            if (node_avl->nodeAvlGetParent()->nodeAvlGetLeftChild() == node_avl) {
                node_avl->nodeAvlGetParent()->nodeAvlSetLeftChild(right_tree);
            } else {
                node_avl->nodeAvlGetParent()->nodeAvlSetRightChild(right_tree);
            }//finish else
        }//finish if
        right_tree->nodeAvlSetLeftChild(node_avl);
        fixHeight(right_tree);
        fixHeight(node_avl);
        setFactorBalance(right_tree);
        setFactorBalance(node_avl);
    }





    void LLRoll( NodeAvl<TKey, TValue> * node_avl) {

        NodeAvl<TKey, TValue> *left_right_tree;
        NodeAvl<TKey, TValue> *left_tree = node_avl->nodeAvlGetLeftChild();
        if (this->root == node_avl) {
            this->root = left_tree;
        }
        if (node_avl->nodeAvlGetLeftChild() == nullptr)
            left_right_tree = nullptr;
        else
            left_right_tree = node_avl->nodeAvlGetLeftChild()->nodeAvlGetRightChild();

        node_avl->nodeAvlSetLeftChild(left_right_tree);
        if (node_avl->nodeAvlGetParent() == nullptr) {
            left_tree->nodeAvlSetparent(nullptr);
        } else {
            if (node_avl->nodeAvlGetParent()->nodeAvlGetRightChild() == node_avl) {
                node_avl->nodeAvlGetParent()->nodeAvlSetRightChild(left_tree);
            } else {
                node_avl->nodeAvlGetParent()->nodeAvlSetLeftChild(left_tree);
            }//finish else
        }//finish if
        left_tree->nodeAvlSetRightChild(node_avl);
        fixHeight(left_tree);
        fixHeight(node_avl);
        setFactorBalance(left_tree);
        setFactorBalance(node_avl);
    }

    void LRroll(NodeAvl<TKey, TValue> * node_avl)
    {
        RRroll(node_avl->left);
        LLroll(node_avl);
    }


    void RLroll(NodeAvl<TKey, TValue> * node_avl)
    {
        LLroll(node_avl->right);
        RRroll(node_avl);
    }




};

#endif //HW2_TREE_TREEAVL_H