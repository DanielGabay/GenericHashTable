tester: tester.o GenericHashTable.o
	gcc tester.o GenericHashTable.o -o tester -Wvla -g -Wall

tester.o: tester.c GenericHashTable.h
	gcc -c tester.c

GenericHashTable.o: GenericHashTable.c GenericHashTable.h
	gcc -c GenericHashTable.c
