#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "GenericHashTable.h"

#define SUCCESS 0
#define FAILURE -1

/*UN-COMMENT TO RUN DEBUG PRINTS*/
//#define DEBUG_INT
//#define DEBUG_STR

/*
 * Author: Daniel Gabay
 * EX1
 *
 * This is an implementation of "Hash Tables".
 * The table supports the folowing actions:
 * I)Adding data
 * II)Searching Data
 * III)Deleting Data
 *
 * The table data is generic and can hold the following types: int, char* (string)
 *
 * */


/**
* The function gets the original size and the type of the data in the table elements.
* it initializes the Table struct members.
* On success, the function returns a pointer to the new created Table, otherwise, it return NULL.
*/
Table* createTable(int size, int dType, int listLength){
    if(size < 0 || listLength < 0 || (dType != STR_TYPE && dType != INT_TYPE)) { //check for legal size
        perror("\ninvalid param/s\n");
        return NULL;
    }
    /*initializing*/
    Table* t = (Table*)malloc(sizeof(Table));
    if(t == NULL) {
        perror("\nmalloc for create table failed\n");
        return NULL;
    }
    t->origSize = size;
    t->currSize = size;
    t->dType = dType;
    t->listLength = listLength;
    t->arr = (Object**)malloc(size *sizeof(Object*));
    if(t->arr == NULL)
        return NULL;
    for(int i = 0; i < size; i++)
        t->arr[i] = createObject(NULL);
    return t;
}

/**
* The function release all the allocated members of struct Table.
*/
void freeTable(Table* table){
    if(table == NULL) {
        perror("\ntable is NULL\n");
        return;
    }
    for(int i = 0; i < table->currSize; i++){
        Object * currObj = table->arr[i]; //holds the first obj of cell i
        while(currObj != NULL){
            Object * next = currObj->next; //keep the next object
            freeObject(currObj,table->dType); //free curr obj
            currObj = next; //promote currObj to next obj
        }
    }
    free(table->arr);
    free(table);
}

/**
* The function adds data to the hashtable (as described in the exe definition)
* On success, the function returns the array index of the added data, otherwise, it return -1.
*/
int add(Table* table, void* data){
    if(table == NULL || data == NULL) {
        perror("\nparam/s is NULL\n");
        return FAILURE;
    }
    Object * obj = NULL;
    if(table->dType == STR_TYPE){
        char * temp = (char*)malloc(sizeof(data)+1);
        strcpy(temp,(char*)data);
        obj = createObject(temp);
    }
    if(table->dType == INT_TYPE)
        obj = createObject(data); //create new (int as data) object
    if(obj == NULL) {
        perror("\nFailed to create object\n");
        return FAILURE;
    }
    int d = table->currSize/table->origSize;
    int index = getHash(table,data,d);
    if(insert(table,obj,index) == SUCCESS) { //try to insert obj to table at cell index
#ifdef DEBUG_INT
        int hash = getHash(table,data,d);
        printf("\nAdded: %d Hash: %d \n", *(int*)data,hash);
        printTable(table);
        printf("\n");
#endif
#ifdef DEBUG_STR
        int h = getHash(table,data,d);
        printf("\nAdded: %s Hash: %d \n", (char*)data,h);
        printTable(table);
        printf("\n");
#endif
        return index;
    }
    else { // no place to insert obj
        if (expandArr(table) == FAILURE) { //expand array
            perror("\nExpand table failed\n");
            return FAILURE;
        }
        if(shiftListIndexes(table) == FAILURE) { //shift every list at index i to index i*2
            perror("\nShift Indexes table failed\n");
            return FAILURE;
        }
        if(insert(table,obj,index*2+1) == SUCCESS) { //insert obj to the expanded table
#ifdef DEBUG_INT
            int hash = getHash(table,data,table->currSize/table->origSize);
            printf("\nAdded: %d Hash: %d \n", *(int*)data,hash);            printTable(table);
            printf("\n");
#endif
#ifdef DEBUG_STR
            int h = getHash(table,data,d);
            printf("\nAdded: %s Hash: %d \n", (char*)data,h);
            printTable(table);
            printf("\n");
#endif
            return index;
        }
    }
    //in case of any error
    perror("\nERROR\n");
    return FAILURE;

}

/*expand table arr by 2*currSize. return 0 if succeed, -1 o.w*/
int expandArr(Table * table){
    int arrNewSize = table->currSize*2;
    table->arr = (Object**)realloc(table->arr,sizeof(Object*)*arrNewSize); //increase table size by mult of 2
    if(table->arr == NULL)
        return FAILURE;
    table->currSize = arrNewSize;
    for(int i = table->currSize/2; i < table->currSize; i++)
        table->arr[i] = createObject(NULL); //initialize all new pointers
    return SUCCESS;
}

/*shift each cell i in prev table into cell i*2 in the new table(after expanded)*/
int shiftListIndexes(Table * t) {
    //Run from the middle of the array down, and shift each list to 2*index
    for (int i = t->currSize / 2 - 1; i >= 0; i--){
        t->arr[i * 2]->next = t->arr[i]->next;
        if(i % 2 != 0) //for each odd index also assign next to NULL (after expand all odd indexes will be empty)
            t->arr[i]->next = NULL;
    }
    return SUCCESS;
}

/*return 0 when succeed to insert obj to cell i. return -1 otherwise*/
int insert(Table* table,Object * obj,int i){
    int isExpandedArr = table->currSize/table->origSize;
    /*
     * isExpandedArr telling us how many cells we need to check for each hash.
     * for example: before expanding we need to check 1 cell, and after 3 expands we need to check 4 cells (0-3,4-7...)
     */
    while(isExpandedArr != 0){
        /*check if there is space in list of cell i*/
        Object * curr = table->arr[i];
        int counter = 0;
        while(curr != NULL && curr->next != NULL){
            counter++;
            curr = curr->next;
        }
        if(counter < table->listLength) {
            curr->next = obj;
            return 0;
        }
        /*if list of cell i iss full, move to the next cell*/
        isExpandedArr--;
        i++;
    }
    return FAILURE;
}


/**
* The function removes the Object which its data equals to data, if there are more than one, it removes the first one.
* On success, the function returns the array index of the removed data, otherwise, it returns -1.
* -1 is also returned in the case where there is no such object.
*/
int removeObj(Table* table, void* data){
    if(table == NULL || data == NULL) {
        perror("\nparam/s is NULL\n");
        return FAILURE;
    }
    int d = table->currSize/table->origSize;
    int index = getHash(table,data,d); //START LOOKING FROM CELL INDEX (FROM HASH FUNCTION)
    while(d != 0){
        Object * prev = table->arr[index]; //assign to the cell starting object
        Object * curr = table->arr[index]->next; //start from top of the list(next of the first object)
        while (curr != NULL) {
            if (isEqual(table->dType, data, curr->data) == SUCCESS) {
                prev->next = curr->next;
                freeObject(curr,table->dType);
                return index;
            }
            prev = curr;
            curr = curr->next;
        }
        d--;
        index++;
    }
    perror("\nERROR\n");
    return FAILURE;
}

/**
* The function search for an object that its data is equal to data and returns a pointer to that object.
* If there is no such object or in a case of an error, NULL is returned.
*/
Object* search(Table* table, void* data){
    if(table == NULL || data == NULL) {
        perror("\nparam/s is NULL\n");
        return NULL;
    }
    int d = table->currSize/table->origSize;
    int index = getHash(table,data,d);
    while(d != 0){
        Object * curr = table->arr[index]->next;
        while(curr != NULL){
            if(isEqual(table->dType,data,curr->data) == SUCCESS)
                return curr;
            curr = curr->next;
        }
        d--;
        index++;
    }
    return NULL;
}



/**
* The function print the table (the format is in the exe definition)
*/
void printTable(Table* table){
    if(table == NULL) {
        perror("\nparam is NULL\n");
        return;
    }
    for(int i = 0; i < table->currSize; i++){
        printf("[%d]" ,i);
        Object * curr = table->arr[i]->next;
        while(curr != NULL){
            printf("\t");
            if(table->dType == INT_TYPE)
                printf("%d",*(int*)curr->data);
            else //STR_TYPE
                printf("%s",(char*)curr->data);
            printf("\t-->");
            curr = curr->next;
        }
        printf("\n");
    }
}

/**
* This function creates an object and return the pointer to it or NULL if there is some error.
*/
Object* createObject(void* data){
    Object * obj = (Object*)malloc(sizeof(Object));
    if(obj == NULL) {
        perror("\ncreate object (malloc) failed\n");
        return NULL;
    }
    obj->data = data;
    obj->next = NULL;
    return obj;
}

/**
* This function creates an object (STR_TYPE, malloc is needed) and return the pointer to it or NULL if there is some error.
*/
Object * createStrObject(void * data){
    Object * obj = (Object*)malloc(sizeof(Object));
    if(obj == NULL) {
        perror("\ncreate object (malloc) failed\n");
        return NULL;
    }
    obj->data= (char*)malloc(sizeof(data)); //allocate memory
    strcpy(obj->data,(char*)data); //copy data
    obj->next = NULL;
    return obj;
}


/**
* This function frees an object,  note the in the case of STR_TYPE, the data
* of the object should also be freed.
*/
void freeObject(Object* obj, int type){
    if(obj == NULL || (type != STR_TYPE && type != INT_TYPE)){
        perror("\nparam/s is NULL\n");
        return;
    }
    if(type == STR_TYPE)
        free(obj->data); //free allocated memory for data
    free(obj);
}

/**
* check the equality of the data of two objects. The implementation is different depending the type of the data.
* the function returns 0 if they are equal or some other value if they are not equal.
*/
int isEqual(int type, void* data1, void* data2){
    if((type != STR_TYPE && type != INT_TYPE)) {
        perror("\nparam/s is invalid\n");
        return FAILURE;
    }
    if(type == INT_TYPE){
        if(*(int*)data1 == *(int*)data2)
            return 0;
        return -1;
    }
    else // type == STR_TYPE
        return strcmp((char*)data1,(char*)data2);
}

/**
* returns the hash value of an integer, which is key mod origSize
*/
int intHashFun(int* key, int origSize){
    return *(key) % origSize;
}

/*return the ascii sum of a given string*/
int sumAscii(const char * str) {
    if(*str == 0)
        return 0;
    return *str + sumAscii(str+1);
}

/**
* returns the hash value of an string, which is m mod origSize, where m is the sum of the ascii value of all the
* character in key.
*/
int strHashFun(char* key, int origSize){
    int m = sumAscii(key);
    return m % origSize;
}

/*return hash key for STR_TYPE or INT_TYPE*/
int getHash(Table* table,void * data, int d){
    int hash = -1;
    if(table->dType == STR_TYPE)
        hash = strHashFun((char*)data,table->origSize);
    else // dType == INT_TYPE
        hash = intHashFun((int*)data,table->origSize);
    return d*hash;
}