//
// Created by tom on 2020/7/31.
//

#ifndef STUDY_CHAPTER2_H
#define STUDY_CHAPTER2_H
#include <iostream>
using namespace std;
typedef int Elem;
typedef struct TNode{
    struct TNode *next;
}TNode,LTNode;
typedef struct LNode{
    Elem data;
    struct LNode * next;
}LNode,*LinkList;

typedef struct LCharNode{
    char data;
    LCharNode *next;
}LCharNode,*LinkCharList;

template <class T> int get_array_len(T& array);
template <class T> bool array_insert(int L[],int len, int index, int value);
template <typename T> LinkList CreateSingleList(T array[], int length, bool is_head=true, bool is_cycle=false);
template <typename T> LinkCharList CreateSingleCharList(T array[], int length, bool is_head=true, bool is_cycle=false);

void print_singlelist(LinkList &L,bool is_head=true, bool address=false, bool is_cycle=false);
void print_singlecharlist(LinkCharList &L,bool is_head=true, bool address=false, bool is_cycle=false);
int get_head_array_length(LinkList &head);
int main2();

//双向链表
typedef struct DLinkList{
    struct DLinkList *llink,*rlink;
    int data;
}DLinkList, *PDLinkList;
PDLinkList CreateDoublyLinkList(const int x[],int len, bool is_cycle=false);
void print_doubly_list(PDLinkList&L,bool is_cycle=false);

#endif //STUDY_CHAPTER2_H
