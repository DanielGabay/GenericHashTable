//
// Created by daniel on 12/2/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GenericHashTable.h"


//gcc GenericHashTable.h GenericHashTable.c tester.c -o ex1 -Wvla -g -Wall
//valgrind ./ex1

int main1(){
    Table * t = createTable(6,STR_TYPE,5);
    add(t,"aa");
    add(t,"aa");
    add(t,"aa");
    add(t,"b");
    add(t,"c");
    add(t,"d");
    add(t,"e");
    add(t,"f");
    add(t,"gg");/*
    printf("\n**********PRINT FIRST TABLE**************\n");
    printTable(t);*/
    add(t,"gg");

    add(t,"gg");
    /*printf("\n**********PRINT SECOND TABLE**************\n");
    printTable(t);*/


    removeObj(t,"aa");
    removeObj(t,"aa");
    removeObj(t,"aa");
    removeObj(t,"b");
    removeObj(t,"c");
    removeObj(t,"d");
    removeObj(t,"e");
    removeObj(t,"f");
    removeObj(t,"gg");
    removeObj(t,"gg");
    removeObj(t,"gg");

    add(t,"daniel");
    printTable(t);
    freeTable(t);
}



int main() {
    Table *t = createTable(4, INT_TYPE, 2);
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr2[] = {13, 19, 25, 31, 37, 43, 49, 55, 61, 67, 73, 79, 85, 91, 97, 103, 109, 115, 121, 127, 133, 139};
    for (int i = 0; i < 9; i++) {
        add(t, &arr[i]);
    }
    /*
    printf("\n**********PRINT FIRST TABLE**************\n");
    printTable(t);*/
    for (int i = 0; i < 22; i++) {
       /* if (i == 6) {
            printf("\n***********PRINT FIRST EXPAND*************\n");
            printTable(t);
            printf("\n************************\n");

        }
        if (i == 3) {
            printf("\n***********PRINT DANIEL EXPAND*************\n");
            printTable(t);
            printf("\n************************\n");
        }

        if (i == 18) {
            printf("\n***********PRINT SECOND EXPAND*************\n");
            printTable(t);
        }*/
        add(t, &arr2[i]);

    }
/*
    printf("\n***********PRINT THIRD EXPAND*************\n");
    printTable(t);

    printf("\n************************\n");
*/

    int index = 0;


    for (int i = 0; i < 9; i++) {
        index = removeObj(t, &arr[i]);
        //printf("%d %d\n", index, i);
    }

    printf("\n*************FIRST REMOVE***********\n");

    printTable(t);
    printf("\n************************\n");


    for (int i = 0; i < 22; i++) {
        index = removeObj(t, &arr2[i]);
        //printf("%d %d\n", index, i);
    }


    printTable(t);
    freeTable(t);
}
