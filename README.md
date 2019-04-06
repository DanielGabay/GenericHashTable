Authored by: Daniel Gabay.
"ex1"

==Description==
This is an implementation of "HashTable".
The table supports the folowing actions:
	I)Adding data
	II)Searching Data
	III)Deleting Data
The table data is generic and can hold the following types: int, char* (string)
The table is actualy array of linked list (each cell of the array is an object * that is pointing to the next object)
Each data gets an hash value in the following forlumas:
	for int -> index = d*(data%originalSize)
	for string -> index = d*[(sum of ascii values)%originalSize)]
	where d is the value of currentSize/originalSize of the table.
Creating table must contain the wanted original size of the array, the type (int/string), the size of the linked lists.
We'll handel collisions with the linked list (until the maximum length) and with expanding the table if needed.

==Program Files==
GerericHashTable.c , GenericHashTable.h

==How to compile?==
save the files into the same folder (including Makefile).
open terminal and navigate to the folder that contains the files.
type "make" to compile
Run: ./tester

==Functions:==
There are 5 ("public") main methods for the user needs to manage the HashTable:
1)	Creating table -> Table* createTable(int size, int dType, int listLength)
	The function gets the original size and the type of the data in the table elements.
	it initializes the Table struct members.
	On success, the function returns a pointer to the new created Table, otherwise, it return NULL.
2)	Adding data -> 	int add(Table* table, void* data)
	The function adds data to the hashtable.
	On success, the function returns the array index of the added data, otherwise, it return -1.
3)	Serach Data -> Object* search(Table* table, void* data)
	The function search for an object that its data is equal to data and returns a pointer to that object.
	If there is no such object or in a case of an error, NULL is returned.
4)	Remove data -> int removeObj(Table* table, void* data)
	The function removes the Object which its data equals to data, if there are more than one, it removes the first one.
	On success, the function returns the array index of the removed data, otherwise, it returns -1.
	-1 is also returned in the case where there is no such object.
5)	Free Table -> void freeTable(Table* table)
	The function release all the allocated members of struct Table.

The rest of the functions is "private" and used by the main methods for assistance.
For more information about them, read the comments at the file.


==Input:==
All of the inputs need to be written in a main.c file.
After creating table with the wanted parameters, you can add/search/remove data using the functions above.

==Output:==
Depends of the main, the only visual output is done by printTable function (printing table..)

==Output files==
no output files