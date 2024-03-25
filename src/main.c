/**
 * @Author Panagiotis Berberidis
 * @Lesson HY-255
 * @Assignment 3
 * @AM 4376
 * @File_name main.c
 */
#include "symtable.h"
#include <stdio.h> 

void print(const char *pcKey, void *pvValue,void *pvExtra)
{
    printf("Entry %s -> %s\n",pcKey,(char *)pvValue);
}

int main()
{
    SymTable_T names = SymTable_new();
    int i;
    char result[50];

    if(SymTable_put(names, "panos", "476"))
    {
        printf("You just added one element\n");
    }
    else
    {
        printf("SymTable_put has a problem\n");
    }

    if(!SymTable_put(names, "panos", "476"))
    {
        printf("It works, it did not add a second instance\n");
    }
    else
    {
        printf("SymTable_put duplicates an entry\n");
    }

    if(SymTable_put(names, "aspasia", "427"))
    {
        printf("You just added a second element\n");
    }
    else
    {
        printf("SymTable_put has a problem\n");
    }

    if(SymTable_put(names, "mitsos", "467"))
    {
        printf("You just added a third element\n");
    }
    else
    {
        printf("Problem at SymTable_put\n");
    }

    if(SymTable_remove(names, "aspasia"))
    {
        printf("Removed the second element\n");
    }
    else
    {
        printf("SymTable_remove failed\n");
    }

    for(i = 0; i < 500; i++)
    {
        sprintf(result, "name%d", i);
        SymTable_put(names, result ,"value");
    }

    if(SymTable_remove(names, "name85"))
    {
        printf("Removed the name85 element\n");
    }
    else
    {
        printf("SymTable_remove failed\n");
    }

    if(!SymTable_get(names, "name85"))
    {
        printf("Removed the name85 element\n");
    }
    else
    {
        printf("SymTable_remove function failed\n");
    }

    if(SymTable_get(names, "name55"))
    {
        printf("Got the name55 element: %s\n", (char*)SymTable_get(names, "name55"));
    }
    else
    {
        printf("SymTable_get function failed\n");
    }

    SymTable_free(names);

    return 0;
}
