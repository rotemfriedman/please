#ifndef UNTITLED_MAP_H
#define UNTITLED_MAP_H

#include "Exception.h"
class Map{

    template <class T>
    class Node {
        T key;
        void* value;
        Node* next;
        Node* prev;

    public:
/**
 * constructor of Node  O(1)
 * @tparam T
 * @param key
 * @param value
 */
        Node(T key,  void* value);
/**
 * destructor 0(1)
 */
        ~Node()= default;
/**
 * copy constructor 0(1)
 * @param node
 */
        Node (const Node &node)= default;
/**
 * operator = ,0(1)
 * @param node
 * @return
 */
        Node &operator=(const Node &node)= default;

/**
 * return the next node of the input node
 * @param node
 * @return
 */
        Node* nodeGetNext();
        /**
         * return the prev node of the input node
         * @param node
         * @return
         */
        Node* nodeGetPrev();
        /**
         * set the next node to be the input node
         * @param node
         * @return
         */
        void nodesetNext(Node* node);
        /**
         * set the prev node to be the input node
         * @param node
         * @return
         */
        void nodesetprev(Node* node);


        /**
         * get a node and a key and set the key of the node to be the key of the
         * input node
         * @param node
         * @param key
         */
        void setKey(T key);
        /**
         * get a node and a value and set the value of the node to be the value
         * of the input node
         * @param node
         * @param value
         */
        void setValue(void* value);
        /**
         * get a node and return his key
         * @return
         */
        T getKey();
        /**
         * get a node and return his value
         * @return
         */
        void* getValue();

    };

    Node<int>* head;
    int size;

public:

    /**
  * constractur for the Map
  * @param name -
  * @param weapon -
   * the size will be zero when we will initial
  */
    Map();

    ~Map()= default;

    Map (const Map &map)= default;

    Map &operator=(const Map &map)= default;


    /**
     * the function returns the number of elements in the map
     * @param DS - the first pointer to the list of the map
     * @return the size of the map
     * the complexity is O(1)
     */
    int MapSize() const;

/**
 *  the function retuan the head in the map
 * @return
 */
    Node<int>* returnHead ();


/* Description:   Adds a new item to the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The key to add.
 *                value - A pointer to the value to add.
 				  node - A pointer to a place which will hold a pointer to the new node in the DS.
 * Output:        None.
 * Return Values: Node.
 */
    void Add(int key, void* value, void** node);


    /* Description:   Finds an item in the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The item to find.
 * Output:        value - a pointer to a variable which will contain the value of the element.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item does not exist in the DS.
 *                SUCCESS - If the item is found in the DS.
 */
    void Find(int key, void** value);





// the complexity is O(1)
/* Description:   Delete an item from the data structure.
 * Input:         DS - A pointer to the data structure.
 *                p - A pointer to the node to delete.
 * Return Values: None.
 */
    void DeleteByPointer(void* p);

    /* Description:   Delete an item from the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The item to delete.
 * Output:        None.
 */

    void Delete(int key);

/* Description:   Returns the current number of items in the data structure.
 * Input:         DS - A pointer to the data structure.
 * Output:        n - A pointer to a variable that should be updated to the number of items in the data structure.
 */
    void Size(int *n);

/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */

    void Quit(void **DS);
};

#endif //UNTITLED_MAP_H