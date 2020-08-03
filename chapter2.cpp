//
// Created by tom on 2020/7/31.
//
#include "chapter2.h"
#include <iostream>
using namespace std;

int get_head_array_length(LinkList &head){
    auto p = head->next;
    int i;
    for (i = 1; p->next!= nullptr ; p=p->next,++i);
    return i;
}
template <class T> int get_array_len(T& array){
    return sizeof(array)/sizeof(array[0]);
}
template <typename T> LinkList CreateSingleList(T array[], int length, bool is_head){
    if (is_head) {
        auto head = new LNode;
        LinkList p = head;
        head->next = nullptr;
        for (int i = 0; i < length; i++, p = p->next) {
            auto temp = new LNode;
            temp->next = nullptr;
            temp->data = array[i];
            p->next = temp;
        }
//            p = head->next;
//    cout<<"生成的单链表为：\t";
//    while (p){
//        cout<<p->data<<" "<<p;
//        p = p->next;
//        if (p) cout<<" -> ";
//    }
//    cout<<endl;
//        delete p;
        return head;

    } else{
        if (!length)
            return nullptr;
        auto head = new LNode{.data=array[0], .next=nullptr};
        LinkList p=head;
        for (int i = 1; i < length ; ++i,p=p->next) {
            auto temp = new LNode;
            temp->data = array[i];
            temp->next = nullptr;
            p->next = temp;
        }
        return head;
    }


}
void print_singlelist(LinkList &L, bool is_head, bool address){
    LinkList p;
    if (is_head) p=L->next; else p=L;
    for (; p!= nullptr ; p=p->next) {
           cout<<p->data;
           if (address) cout<<" "<<p;
           if (p->next) cout<<" -> ";
    }
    cout<<endl;
}

template<class T> void print_array(T array[], int len=0){
    int length;
    if (!len)
        length = get_array_len(array);
    else
        length = len;
    for (int i = 0; i < length; ++i) {
        cout<<array[i]<<"\t";
    }
    cout<<endl;
}


template<typename T>void reverse_array(T &array, int start, int end){
    if (start < 1||start > end) return;
    int mid = (end+start)/2;
    for (int i = start-1,j=end-1; i < mid ; ++i,--j) {
        auto temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
//递归反向输出
void r_print(LinkList &L) {
    if (L->next != nullptr)
        r_print(L->next);
    cout<<L->data<<"\t";
}
LinkList ex1(LinkList &L,int n){
    LinkList p = L->next, befor, after;
    int i;
    for (i = 1; i < n/2; ++i,p = p->next);
    if (n%2 == 0) // n为偶数
    {
        after = p->next;
        p->next = nullptr;
    }
    else //n为奇数
    {
        after = p->next->next;
        p->next->next = nullptr;
    }
    befor = L->next;
    // 将after逆置
    LinkList p2=nullptr,q=after,r=q->next;
    while (r) {
            q->next = p2;
            p2 = q;
            q = r;
            r = r->next;
    }
    //处理最后的连接
    q->next =p2;
    after = q;

    //将after插入到before中
    print_singlelist(befor, false);
    while (after){
        auto temp_before = befor->next;
        auto temp_after = after->next;
        befor->next = after;
        after->next = temp_before;
        after = temp_after;
        befor = temp_before;
    }
    cout<<"%%%%%"<<endl;
    print_singlelist(L);
    return L;
}

int ex2(LinkList &L, int k){
    if (k<=0)
        return 0;
    LinkList p,q=L->next;
    int i;
    for (i = 0; i < k && p!= nullptr; ++i)
        p = p->next;
    if (p== nullptr) return 0;
    while(p->next!= nullptr){
        cout<<p->data<<"\t"<<q->data<<endl;
        p=p->next;
        q=q->next;

    }
    cout<<q->data<<endl;
    return 1;
}

template<class T>void ex3(T &array, int len, int p){
    if (p>len) return;
    reverse_array(array,1,p);
    reverse_array(array,p+1,len);
    reverse_array(array,1,len);
    print_array(array);
//    int B_len = get_array_len(array)-p;

}

int ex4(const int A[], const int B[], int len){
    int C[len];
    for (int i=0,j=0,q = 0; q<len; ++q) {
        if (A[i]<B[j]) {
            C[q] = A[i];
            ++i;
        } else{
            C[q] = B[j];
            ++j;
        }
    }
//    print_array(C,len);
    return C[len-1];
}

int main2(){
    Elem x[] = {1,2,3,4,5,6,7};
    int a[] = {11,13,15,17,19};
    int b[] = {2,4,30,8,20};
    LinkList L = CreateSingleList(x, get_array_len(x));
//    r_print(head->next);
//    print_singlelist(L, true);
//    reverse_array(x,1,3);
//    for (int i = 0; i < get_array_len(x); ++i) cout<<x[i];
//    ex1(L,get_head_array_length(L));
//    cout<<ex2(L,2);
//    ex3(x,get_array_len(x),3);
    cout<<ex4(a,b,5);
//    print_array(x,7);
    return 0;
}
