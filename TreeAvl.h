#ifndef HW2_TREE_TREEAVL_H
#define HW2_TREE_TREEAVL_H

#include "NodeAvl.h"
#include "Exception.h"
#include <stdexcept>
template<class TKey, class TValue>
class TreeAvl {
    NodeAvl<TKey, TValue> *root;
    NodeAvl<TKey, TValue> *itr;
    //CompareFun compare;
    int tree_size;

public:

    //לבדוק האם צריך לאתחל את הcompare
    //constractor of the class TreeAvl
    TreeAvl() :root(nullptr),itr(nullptr),
               tree_size(0){};
    ~TreeAvl() = default;

    TreeAvl(const TreeAvl &tree_avl) = default;

    TreeAvl &operator=(const TreeAvl &tree_avl) = default;

    NodeAvl<TKey,TValue>* TreeAvlRoot(){
        return this->root;
    };

/**
 * the function get a node and fix his balce factor
 * @param node_avl - from type pointer to NodeAvl
 */
    void setFactorBalance(NodeAvl<TKey, TValue> *node_avl) {
        int right_height, left_height;
        if ((node_avl->nodeAvlGetRightChild()) == nullptr)
            right_height = -1;
        else {
            right_height = (node_avl->nodeAvlGetRightChild())->nodeAvlGetHeight();
        }
        if ((node_avl->nodeAvlGetLeftChild()) == nullptr)
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



    /**
 * the function add node to his place in the avl tree and fix him to be a correct
 * avltree.
 * @param key
 * @param value
 * @param node
 */
    void Add(int key, void *value, void **node) {
        if (node == nullptr)
            throw dataStructure::INVALID_INPUT();
        NodeAvl<TKey, TValue> *new_node;

        TValue* temp_value = (TValue*)value;
        try {
            new_node = new NodeAvl<TKey, TValue>((TKey) key, (*temp_value));
        }
        catch (std::bad_alloc &e) {
            throw dataStructure::ALLOCATION_ERROR();
        }
        *node=new_node;
        this->itr = this->root;
        if(this->root== nullptr){//new node is the root;
            this->root=new_node;
            this->tree_size++;
            throw dataStructure::SUCCESS();
        }


        int result = 0;
        while (itr != nullptr) {
            if(itr->nodeAvlGetKey()<new_node->nodeAvlGetKey())
                result = -1;
            else
                result = 1;
            if (result < 0) {
                new_node->nodeAvlSetparent(itr);
                itr = itr->nodeAvlGetRightChild();
            } else if (result > 0) {
                new_node->nodeAvlSetparent(itr);
                itr = itr->nodeAvlGetLeftChild();
            }
        }
        if (result < 0) {
            (new_node->nodeAvlGetParent())->nodeAvlSetRightChild(new_node);
        } else if(result>0) {
            (new_node->nodeAvlGetParent())->nodeAvlSetLeftChild(new_node);
        }
        while (new_node != this->root) {
            NodeAvl<TKey, TValue> *p = new_node->nodeAvlGetParent();
            if (p->nodeAvlGetHeight() >= new_node->nodeAvlGetHeight() + 1) {
                this->tree_size++;
                setFactorBalance(p);
                throw dataStructure::SUCCESS();
            }
            p->nodeAvlSetHeight(new_node->nodeAvlGetHeight() + 1);
            setFactorBalance(p);
            bool roll = checkRollForP(p);
            if (roll == true) {
                this->tree_size++;
                // fixHeight(p->nodeAvlGetParent());
                throw dataStructure::SUCCESS();
            }
            new_node = p;
        }//finish while
        this->tree_size++;
        throw dataStructure::SUCCESS();
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
            RRRoll(p);
            return true;
        } else if (p->nodeAvlGetBalanceFactor() == 2 &&
                   p->nodeAvlGetLeftChild()->nodeAvlGetBalanceFactor() >= 0) {
            LLRoll(p);
            return true;
        }
        return false;
    }


    void RRRoll( NodeAvl<TKey, TValue> * node_avl) {

        NodeAvl<TKey, TValue> *right_left_tree;
        NodeAvl<TKey, TValue> *right_tree = node_avl->nodeAvlGetRightChild();
        if (this->root == node_avl) {
            this->root = right_tree;
        }
        if (node_avl->nodeAvlGetRightChild() == nullptr)
            right_left_tree = nullptr;
        else
            right_left_tree = node_avl->nodeAvlGetRightChild()->nodeAvlGetLeftChild();

        node_avl->nodeAvlSetRightChild(right_left_tree);
        if(right_left_tree!= nullptr)
            right_left_tree->nodeAvlSetparent(node_avl);
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
        right_tree->nodeAvlSetparent(node_avl->nodeAvlGetParent());
        node_avl->nodeAvlSetparent(right_tree);
        fixHeight(node_avl);
        fixHeight(right_tree);
        setFactorBalance(node_avl);
        setFactorBalance(right_tree);
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
        if(left_right_tree!= nullptr)
            left_right_tree->nodeAvlSetparent(node_avl);
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
        left_tree->nodeAvlSetparent(node_avl->nodeAvlGetParent());
        node_avl->nodeAvlSetparent(left_tree);
        fixHeight(node_avl);
        fixHeight(left_tree);
        setFactorBalance(node_avl);
        setFactorBalance(left_tree);
    }




    void LRroll(NodeAvl<TKey, TValue> * node_avl)
    {
        RRRoll(node_avl->nodeAvlGetLeftChild());
        LLRoll(node_avl);
    }


    void RLroll(NodeAvl<TKey, TValue> * node_avl)
    {
        LLRoll(node_avl->nodeAvlGetRightChild());
        RRRoll(node_avl);
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
    NodeAvl<TKey,TValue>* Find(int key) {
        //   if (value == nullptr) {
        //      throw dataStructure::INVALID_INPUT();
        //   }
        // TValue value;
        //  NodeAvl<TKey, TValue>* new_node;
        //  try{
        //      new_node=
        //              new NodeAvl<TKey, TValue>(key,value);
        // }
        //  catch (std::bad_alloc& e){
        //      throw dataStructure::ALLOCATION_ERROR();
        //  }
        this->itr=this->root;
        int result=3;
        while(itr!= nullptr) {
            if (itr->nodeAvlGetKey() < key)
                result = -1;
            else if (itr->nodeAvlGetKey() > key)
                result = 1;
            else if(itr->nodeAvlGetKey() == key)
                result = 0;
            if (result ==-1) {                       //itr->key < new_node->key
                itr = itr->nodeAvlGetRightChild();
            } else if (result ==1) {                      //itr->key > new_node->key
                itr = itr->nodeAvlGetLeftChild();
            } else if (result ==
                       0) {         //in this case result=0, and we found the node
                // *value = itr->nodeAvlGetValue();
                //delete new_node;
                return itr;
            }/// if we here the key is not in the tree
        }
        //delete new_node;
        // *value= nullptr;
        throw dataStructure::FAILURE();
    }








    /**
 * this function get a pointer to a node, that its not the root
 * @param node_avl - the node is a leaf. we are going to delete this node
 */
    void deleteLeaf(NodeAvl<TKey,TValue>* node_avl){
        NodeAvl<TKey,TValue>* parent=node_avl->nodeAvlGetParent();
        if(parent->nodeAvlGetLeftChild()==node_avl)
            parent->nodeAvlSetLeftChild(nullptr);
        else
            parent->nodeAvlSetRightChild(nullptr);
    }


    /**
     * this function get a pointer to a node.
     * @param node_avl - the node has one child, and its not the root
     */
    void deleteOneChild(NodeAvl<TKey,TValue>* node_avl){
        NodeAvl<TKey,TValue>* parent=node_avl->nodeAvlGetParent();
        if(node_avl->nodeAvlGetLeftChild()!= nullptr) {
            if (parent->nodeAvlGetLeftChild() == node_avl) {
                parent->nodeAvlSetLeftChild(node_avl->nodeAvlGetLeftChild());
                (node_avl->nodeAvlGetLeftChild())->nodeAvlSetparent(parent);
            }else {
                parent->nodeAvlSetRightChild(node_avl->nodeAvlGetLeftChild());
                (node_avl->nodeAvlGetLeftChild())->nodeAvlSetparent(parent);

            }
        }
        else{
            if(parent->nodeAvlGetLeftChild()==node_avl) {
                parent->nodeAvlSetLeftChild(node_avl->nodeAvlGetRightChild());
                (node_avl->nodeAvlGetRightChild())->nodeAvlSetparent(parent);
            }
            else{
                parent->nodeAvlSetRightChild(node_avl->nodeAvlGetRightChild());
                (node_avl->nodeAvlGetRightChild())->nodeAvlSetparent(parent);
            }
        }
    }


/**
     * this function get a pointer to a node.
     * @param node_avl - the node has one child, and the node is the root
     */
    void rootDeleteOneChild(NodeAvl<TKey,TValue>* node_avl){
        NodeAvl<TKey,TValue>* node_left=node_avl->nodeAvlGetLeftChild();
        NodeAvl<TKey,TValue>* node_right=node_avl->nodeAvlGetRightChild();
        if(node_right!= nullptr) {
            this->root = node_right;
            node_right->nodeAvlSetparent(nullptr);
            //node_right= nullptr //check if we need this
        }
        else {
            this->root = node_left;
            node_left->nodeAvlSetparent(nullptr);
            //node_left=nullptr //check if we need this
        }
    }



/**
 * the function get a node, and if the node have one chile or the node is a leaf,
 * the function will remove the node
 * @param node_avl
 * @return the original number if the children of node_avl
 */
    int DeleteOneChildOrLeaf(NodeAvl<TKey,TValue>* node_avl){
        int counter_left, counter_right;
        if (node_avl->nodeAvlGetLeftChild()== nullptr)
            counter_left = 0;
        else
            counter_left = 1;
        if (node_avl->nodeAvlGetRightChild() == nullptr)
            counter_right = 0;
        else
            counter_right = 1;
        //counter the number of child of the node_avl
        int counter_child = counter_right + counter_left;
        if (node_avl->nodeAvlGetParent()!= nullptr && counter_child == 0) {
            tree_size--;
            deleteLeaf(node_avl);
        }
        else if (counter_child == 0) {  //the node_avl is the root and dont have children
            tree_size--;
            this->root = nullptr;
        }
        else if (node_avl->nodeAvlGetParent()!= nullptr && counter_child == 1) {
            tree_size--;
            deleteOneChild(node_avl);
        }
        else if (counter_child == 1) { //the node_avl is the root and have 1 children
            tree_size--;
            rootDeleteOneChild(node_avl);
        }
        return counter_child;
    }



/**
 * the function delete the node p, that we get
 * @param p - this pointer to a type NodeAvl will remove
 */
    void DeleteByPointer(void* node) {
        NodeAvl<TKey,TValue> *node_avl = (NodeAvl<TKey,TValue>*) node;
        if (node_avl == nullptr)
            throw dataStructure::INVALID_INPUT();
        bool two_children=false; //if two_children=true its mean that the node
        // that we want to delete had 2 children
        NodeAvl<TKey,TValue>*save_parent = node_avl->nodeAvlGetParent();
        NodeAvl<TKey,TValue>*following_node;
        int counter_child=DeleteOneChildOrLeaf(node_avl);
        if (counter_child == 2) {
            two_children=true;
            following_node=node_avl->getFollowingNode();
            save_parent = following_node->nodeAvlGetParent();
//following the algoritem, we will change node_avl and following_node
            TValue& save_value = following_node->nodeAvlGetValue();
            node_avl->nodeAvlSetValue(save_value);
            //following_node->nodeAvlSetValue(save_value);

            TKey save_key = following_node->nodeAvlGetKey();
            node_avl->nodeAvlSetKey(save_key);
            //following_node->nodeAvlSetKey(save_key);
            counter_child=DeleteOneChildOrLeaf(following_node);
        }
        if(two_children==true)
            delete following_node;
        else
            delete node_avl;
        int old_height;
        if(save_parent==this->root && save_parent!= nullptr){
            fixHeight(root);
            setFactorBalance(root);
            checkRollForP(save_parent);
        }
        else {
            while (save_parent != this->root && save_parent != nullptr) {
                old_height=save_parent->nodeAvlGetHeight();
                fixHeight(save_parent);
                setFactorBalance(save_parent);
                bool roll = checkRollForP(save_parent);
                if(old_height==save_parent->nodeAvlGetHeight())
                    break;
                NodeAvl<TKey,TValue>* temp_parent=save_parent->nodeAvlGetParent();
                save_parent = temp_parent;
            }
        }
        if(root!= nullptr) {
            fixHeight(root);
            setFactorBalance(root);
        }
        throw dataStructure::SUCCESS();
    }



/* Description:   Delete an item from the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The item to delete.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item does not exist in the DS.
 *                SUCCESS - Otherwise.
 */
    void Delete(int key){
        //  void* value;
        NodeAvl<TKey,TValue>* pointer_node;
        try {
            pointer_node=Find(key);
        }
        catch (dataStructure::INVALID_INPUT  &e) {
            throw dataStructure::INVALID_INPUT();
        }
        catch (dataStructure::ALLOCATION_ERROR  &e) {
            throw dataStructure::ALLOCATION_ERROR();
        }
        catch (dataStructure::FAILURE  &e) { //the key doesnt find
            throw dataStructure::FAILURE();
        }
        try {
            DeleteByPointer((void*)pointer_node); //this is the node that we want to delete
        }
        catch (dataStructure::SUCCESS  &e) {
            throw dataStructure::SUCCESS();
        }
        catch (dataStructure::INVALID_INPUT  &e) {
            throw dataStructure::INVALID_INPUT();
        }
        catch (dataStructure::ALLOCATION_ERROR  &e) {  //maybe we dont have this catch
            throw dataStructure::ALLOCATION_ERROR();
        }
        catch (dataStructure::FAILURE  &e) { //maybe we dont have this catch
            throw dataStructure::FAILURE();
        }

    }




    /**
 * the function return the size of the tree, the number if the nodes in the tree
 * @param n
 */
    void Size(int *n){
        if(n== nullptr)
            throw dataStructure::INVALID_INPUT();
        *n=this->tree_size;
        throw dataStructure::SUCCESS();
    }

    void Quit(NodeAvl<TKey,TValue>* root){
        if(root== nullptr) //there is no nodes in the avl_tree
            return;
        Quit(root->nodeAvlGetRightChild());
        Quit(root->nodeAvlGetLeftChild());
        delete root;
    }


};




#endif //HW2_TREE_TREEAVL_H