//
// Created by tom on 2020/7/31.
//

#ifndef STUDY_CHAPTER2_H
#define STUDY_CHAPTER2_H
#include <iostream>
using namespace std;
typedef int Elem;
typedef struct LNode{
    Elem data;
    struct LNode * next;
}LNode,*LinkList;

typedef struct LCNode{
    char data;
    struct LCNode * next;
}LCNode,*LinkCList;

template <class T> int get_array_len(T& array);
template <class T> bool array_insert(int L[],int len, int index, int value);
template <typename T> LinkList CreateSingleList(T array[], int length, bool is_head=true, bool is_cycle=false);

void print_singlelist(LinkList &L,bool is_head=true, bool address=false, bool is_cycle=false);
int get_head_array_length(LinkList &head);
int main2();


#endif //STUDY_CHAPTER2_H
