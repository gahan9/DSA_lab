//
// Created by Gahan Saraiya on 1/10/18.
// Implementing Krushkal's Algorithm for minimum spanning tree with disjoint set data structure

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void DisjointStructure(int *array, int number_of_nodes){
    for(int i=0; i < number_of_nodes; i++){
        *(array + i) = i;
    }
}

bool Find(int *array, int node1, int node2)
{
    if(*(array + node1) == *(array + node2))
        return true;
    else
        return false;
}

//change all entries from arr[ A ] to arr[ B ].
void Union(int *array, int number_of_nodes, int node1, int node2) {
    int TEMP = *(array + node1);
    for(int i = 0; i < number_of_nodes; i++){
        if(*(array + i) == TEMP)
            *(array + i) = *(array + node2);
    }
}