#ifndef EX1
#define EX1

#define INT_TYPE 0
#define STR_TYPE 1

/*Linked list Node*/
typedef struct Object {
    void* data;
    struct Object * next;
}Object;

typedef struct Table {
    Object** arr;
    int origSize; //original size of the table
    int currSize; //current size of the table
    int listLength; //linked list of each cell length
    int dType; //type of each Node data (int/char*)
}Table;

/**
* The function gets the original size and the type of the data in the table elements.
* it initializes the Table struct members.
* On success, the function returns a pointer to the new created Table, otherwise, it return NULL.
*/
Table* createTable(int size, int dType, int listLength);
/**
* The function release all the allocated members of struct Table.
*/
void freeTable(Table* table);

/**
* The function adds data to the hashtable (as described in the exe definition)
* On success, the function returns the array index of the added data, otherwise, it return -1.
*/
int add(Table* table, void* data);

/**
* The function removes the Object which its data equals to data, if there are more than one, it removes the first one.
* On success, the function returns the array index of the removed data, otherwise, it returns -1.
* -1 is also returned in the case where there is no such object.
*/
int removeObj(Table* table, void* data);

/**
* The function search for an object that its data is equal to data and returns a pointer to that object.
* If there is no such object or in a case of an error, NULL is returned.
*/
Object* search(Table* table, void* data);

/**
* The function print the table (the format is in the exe definition)
*/
void printTable(Table* table);

/**
* This function creates an object and return the pointer to it or NULL if there is some error.
*/
Object* createObject(void* data);

/**
* This function creates an object (STR_TYPE) and return the pointer to it or NULL if there is some error.
*/
Object * createStrObject(void * data);

/**
* This function frees an object,  note the in the case of STR_TYPE, the data
* of the object should also be freed.
*/
void freeObject(Object* obj, int type);

/**
* check the equality of the data of two objects. The implementation is different depending the type of the data.
* the function returns 0 if they are equal or some other value if they are not equal.
*/
int isEqual(int type, void* data1, void* data2);

/**
* returns the hash value of an integer, which is key mod origSize
*/
int intHashFun(int* key, int origSize);

/**
* returns the hash value of an string, which is m mod origSize, where m is the sum of the ascii value of all the
* character in key.
*/
int strHashFun(char* key, int origSize);

/*return the ascii sum of a given string*/
int sumAscii(const char * str);


/*return 0 when succeed to insert obj to cell i. return -1 otherwise*/
int insert(Table* table,Object * obj,int i);

/*expand table arr by 2*currSize. return 0 if succeed, -1 o.w*/
int expandArr(Table * table);

/*shift each cell i in prev table into cell i*2 in the new table(after expanded)*/
int shiftListIndexes(Table * t);

/*return hash key*/
int getHash(Table* table,void * data, int d);

#endif //EX1_EX_H