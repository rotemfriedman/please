#include <cstring>
#include <iostream>
//#include "library1.h"
#include "Map.h"
#include <iostream>


Map::Map():size(0) {
    this->head =NULL;
}

int Map::MapSize ()const{
    return this->size;
}


Map::Node<int>* Map::returnHead(){
    return this->head;
}





template <class T>
Map::Node<T> ::Node(T key,  void* value): key(key),value(value),next(NULL),prev(NULL){

}
template <class T>
Map::Node<T>* Map::Node<T>:: nodeGetNext(){
    return this->next;
}

template <class T>
Map::Node<T>* Map::Node<T>:: nodeGetPrev(){
    return this->prev;
}

template <class T>
void Map::Node<T>::nodesetNext(Node* node){
    this->next=node;
}




template <class T>
void Map::Node<T>::nodesetprev(Node* node){
    this->prev=node;
}

template <class T>
void Map::Node<T>:: setKey(T key){
    this->key=key;
}


template <class T>
void Map::Node<T>::setValue( void *value) {
    this->value=value;
}

template <class T>
T  Map::Node<T>::getKey(){
    return this->key;
}


template <class T>
void* Map::Node<T>::getValue(){
    return this->value;
}


//the complexity is O(1)
void Map::Add(int key, void* value, void** node){
    if (node == NULL)
        throw dataStructure::INVALID_INPUT();
    int copy_key=key;
    void* copy_value=value;
    Node<int>* new_node;
    try {
        new_node=new Node<int>(copy_key,copy_value);
    }
    catch (std::bad_alloc &e) {
        throw dataStructure::ALLOCATION_ERROR();
    }
    if(this->head==NULL){    //the map is empty in this case
        head=new_node;
        size++;
        *node=new_node;
        throw dataStructure::SUCCESS();
    }
    new_node->nodesetNext(this->head);
    this->head->nodesetprev(new_node);
    new_node->setKey(key);
    new_node->setValue(value);
    this->head=new_node;
    this->size++;
    *node=new_node;
    throw dataStructure::SUCCESS();
}


void Map::DeleteByPointer(void* p){
    if(p==NULL)
        throw dataStructure::INVALID_INPUT();
    Node<int>* convert_p=(Node<int>*)p;
    if(size==1){
        this->head=convert_p->nodeGetNext();
        delete (convert_p);
        size--;
        throw dataStructure::SUCCESS();
    }
    if(convert_p->nodeGetPrev()==NULL) { //p is the first Node
        this->head=convert_p->nodeGetNext();
        convert_p->nodeGetNext()->nodesetprev(NULL);
        delete (convert_p);
        size--;
        throw dataStructure::SUCCESS();
    }
    if(convert_p->nodeGetNext()==NULL){                  //p is the last Node
        convert_p->nodeGetPrev()->nodesetNext(NULL);
        delete (convert_p);
        size--;
        throw dataStructure::SUCCESS();
    }
    convert_p->nodeGetPrev()->nodesetNext(convert_p->nodeGetNext());
    convert_p->nodeGetNext()->nodesetprev(convert_p->nodeGetPrev());
    delete (convert_p);
    size--;
    throw dataStructure::SUCCESS();
}


void Map::Find(int key, void** value) {
    if (value == NULL)
        throw dataStructure::INVALID_INPUT();
    Node<int>* itr=(Node<int>*)this->head;
    //*value=(void*)NULL;
    while (itr != NULL) {
        if (itr->getKey() == key) {
            *value = itr->getValue();
            throw dataStructure::SUCCESS();
        }
        itr = itr->nodeGetNext();
    }
    *value=NULL;
    throw dataStructure::FAILURE();             // if we here the system didnt fint the right key
}



void  Map::Delete(int key) {
    Node<int> *itr = (Node<int>*) head;
    if (itr->getKey() == key) {         //first node
        if(itr->nodeGetNext()!=NULL) {
            this->head = itr->nodeGetNext();
            this->head->nodesetprev(NULL);
            delete itr;
            size--;
            throw dataStructure::SUCCESS();
        }else{
            this->head=NULL;
            size--;
            delete itr;
            throw dataStructure::SUCCESS();
        }
    } else {             //finish eith the case of the first node
        itr = itr->nodeGetNext();
        while (itr->nodeGetNext() != NULL) {
            if (itr->getKey() == key) {
                if (itr->nodeGetNext() != NULL) {  //not the last node
                    itr->nodeGetNext()->nodesetprev(itr->nodeGetPrev());
                    itr->nodeGetPrev()->nodesetNext(itr->nodeGetNext());
                    delete itr;
                    size--;
                    throw dataStructure::SUCCESS();
                }
            }
            itr = itr->nodeGetNext();
        }//we are in the last node
        if (itr->getKey() == key) {
            itr->nodeGetPrev()->nodesetNext(NULL);
            delete itr;
            size--;
            throw dataStructure::SUCCESS();
        }
    }
    //didnt find any node if we here
    throw dataStructure::FAILURE();
}



void Map::Size(int *n){
    if(n==NULL)
        throw dataStructure::INVALID_INPUT();

    *n=this->size;
    throw dataStructure::SUCCESS();
}


void Map::Quit(void **DS){
    Node<int>* save_itr=this->head;
    Node<int>* itr=save_itr;
    for(; itr!=NULL; itr=save_itr){
        save_itr=itr->nodeGetNext();
        delete itr;
    }
}