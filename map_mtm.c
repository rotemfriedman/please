#include "map_mtm.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Map_t{
    int size_map;                         //count how many node we have
    Node iterator;
    Node first_pointer;
    copyMapDataElements copy_data;
    copyMapKeyElements copy_key;
    freeMapDataElements free_data_map;
    freeMapKeyElements  free_key_map;
    compareMapKeyElements compare_key;
};


//Allocates a new empty map
Map mapCreate(copyMapDataElements copyDataElement, copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement, freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements) {
    if(copyDataElement == NULL || copyKeyElement == NULL ||
            freeDataElement == NULL || freeKeyElement == NULL ||
            compareKeyElements == NULL){
        return NULL;
    }
    Map new_map = malloc(sizeof(*new_map));
    if (new_map == NULL) {
        return NULL;
    }
    new_map->copy_data = copyDataElement;
    new_map->copy_key = copyKeyElement;
    new_map->free_data_map = freeDataElement;
    new_map->free_key_map = freeKeyElement;
    new_map->compare_key = compareKeyElements;
    new_map->size_map = 0;
    new_map->iterator = NULL;
    new_map->first_pointer = NULL;
    return new_map;
}

//reates a copy of target map.
//Iterator values for both maps is undefined after this operation.
Map mapCopy(Map map) {
    NodeResult status_node;
    Map new_map = mapCreate(map->copy_data, map->copy_key, map->free_data_map,
                            map->free_key_map, map->compare_key);
    if (new_map == NULL) {
        return NULL;
    }
    MapKeyElement key_first = nodeReturnKey(map->first_pointer,&status_node);
    if (status_node == NODE_NULL_ARGUMENT) {
        return new_map;                   // its mean that we dont have a nodes
    }
    MapDataElement data_first= nodeReturnData(map->first_pointer,&status_node);
    //no need to check if status is NULL, already check for first pointer,
    Node node_first = createNode(key_first,data_first);
    Node previous_node = node_first;
    new_map->first_pointer=node_first;
    new_map->size_map+=1;
    new_map->iterator=node_first;

    MAP_FOREACH(Node,iterator, map){
        MapKeyElement new_key = nodeReturnKey(map->iterator,&status_node);
        MapDataElement new_data = nodeReturnData(map->iterator,&status_node);
        Node new_node = createNode(new_key, new_data);
        Node next= nodeGetNextIteration( previous_node,&status_node);
        next=new_node;
        new_map->size_map += 1;
        previous_node = new_node;
    }
    new_map->iterator = NULL;
    map->iterator = NULL;
    return new_map;
}


//Deallocates an existing map
void mapDestroy(Map map){
    if (map == NULL)
        return;
    MapResult status = mapClear(map);                  //here the status isn't relavant, because we allready check if map is NULL
    if(status == MAP_NULL_ARGUMENT){
        return;
    }
    free(map);
}

//return the number of elements in a map.
//return -1 if a NULL pointer was sent.
int mapGetSize(Map map) {
    if (map == NULL) {
        return -1;
    } else {
        return map->size_map;
    }
}

//Sets the internal iterator (also called current key element) to
//the first key element in the map
MapKeyElement mapGetFirst(Map map) {
    if (map == NULL) {
        return NULL;
    } else if (map->first_pointer == NULL) {          //check if map is empty;
        return NULL;
    }
    map->iterator = map->first_pointer;              //set the iterator in the first node;
    NodeResult *status;
    return nodeReturnKey(map->first_pointer,status);
}



//this function get a map. Advances the map iterator to the next key element and returns the key element
MapKeyElement mapGetNext(Map map){
if (map == NULL)
return NULL;
MapKeyElement next_key;
NodeResult node_status;
Node node_next=nodeGetNextIteration(map->iterator, &node_status);
if( node_status == NODE_NULL_PTR)
return NULL;
map->iterator=node_next;
next_key= nodeReturnKey(node_next,&node_status);
if(node_status == NODE_NULL_PTR)
return NULL;
return next_key;
}

//Removes all key and data elements from target map
MapResult mapClear(Map map){
        if (map == NULL){
            return MAP_NULL_ARGUMENT;
        }

    NodeResult node_status;
    node_status = nodeDestroy(map->first_pointer,map-> free_data_map, map-> free_key_map);
    if(node_status == NODE_NULL_PTR){
        return MAP_NULL_ARGUMENT;
    } else {
        return MAP_SUCCESS;
    }
}


//Returns the data associated with a specific key in the map.
//Iterator status unchanged
MapDataElement mapGet(Map map, MapKeyElement keyElement){
    if (map == NULL || keyElement == NULL){
        return NULL;
    }
    NodeResult *status=NULL;
    MAP_FOREACH(Node,iterator,map){
        if(map->compare_key(nodeReturnKey(map->iterator,status),keyElement)==0){

                return nodeReturnData(map->iterator, status);
            }
        }
        return NULL;
    }


//Checks if a key element exists in the map
bool mapContains(Map map, MapKeyElement element){
    if(map==NULL ||element==NULL)
        return NULL;
    NodeResult *status=NULL;
    MAP_FOREACH(Node,iterator,map){
        if(map->compare_key(nodeReturnKey(map->iterator,status),element)==0)
            return true;
    }
    return false;

}

// Removes a pair of key and data elements from the map
    MapResult mapRemove(Map map, MapKeyElement keyElement){
        if(map==NULL ||keyElement==NULL){
            return MAP_NULL_ARGUMENT;
        }
        Node nodeBefore = map->first_pointer;
        int success=0;                    //flag- 0 if not find the key else 1
    NodeResult *status=NULL;
    MAP_FOREACH(Node,iterator,map){
            if(map->compare_key(keyElement,nodeReturnKey(map->iterator,status))==0){
                success=1;
                nodeDestroyOne(nodeBefore, map-> free_data_map,map->free_key_map);
                break;
            }
            nodeBefore = map->iterator;
        }//end of the map_foreach
        map->iterator=NULL;
        if(success==0) //if we didnt found the right key in the map;
            return MAP_ITEM_DOES_NOT_EXIST;
        else
            return MAP_SUCCESS;

    }


//function that copy the data from type string
MapDataElement copyMapDataString(MapDataElement data) {
    char * new_string=malloc(sizeof(char)*strlen(data)+1);
    strcpy(new_string,((char *)data));
    return new_string;
}

//function that copy the key from type int
MapKeyElement copyMapKeyInt (MapKeyElement key) {
    int new_key=(int)key;
    return key;
}

//free a data from type string
void freeMapDataString(MapDataElement data){
    free(data);
}

//free a kew from type int
void freeMapKeyInt(MapKeyElement key){
    return;
}

//compare a  2 keys, values from int
int compareMapKeyInt(MapKeyElement key1, MapKeyElement key2) {
    if (key1 > key2) {
        return 1;
    } else if (key1 == key2) {
        return 0;
    } else {
        return -1;
    }
}