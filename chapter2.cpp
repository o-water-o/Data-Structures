//
// Created by tom on 2020/7/31.
//
#include "chapter2.h"
#include <iostream>
#include "string"
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
//            cout<<array[i]<<"$$$$\t";
            auto temp = new LNode;
            temp->next = nullptr;
            temp->data = array[i];
            p->next = temp;
        }
//            p = head->next;
//            cout<<"生成的单链表为：\t";
//            while (p){
//                cout<<p->data<<" "<<p;
//                p = p->next;
//                if (p) cout<<" -> ";
//            }
//            cout<<endl;
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
//Elem为char类型
LinkList ex5(LinkList &str1,LinkList &str2){
    LinkList long_list, short_list,p;
    int str1_len, str2_len,long_len,short_len;
    str1_len = get_head_array_length(str1);
    str2_len = get_head_array_length(str2);
    if (str1_len>str2_len){
        long_list = str1;
        short_list = str2;
        long_len = str1_len;
        short_len = str2_len;
    } else{
        long_list = str2;
        short_list = str1;
        long_len = str2_len;
        short_len = str1_len;
    }
    //找到长链表的里 与短链表长度相同的前一节点
    p = long_list;
    for (int i = 0; i <long_len-short_len ; ++i) {
        p = p->next;
    }

    //开始找两个链表的第一个相同节点
    while (p != nullptr){
        if (p->data == short_list->data)
            return p;
        else{
            p = p->next;
            short_list = short_list->next;
        }
    }
    return nullptr;

}

void ex6(LinkList &L, int max){
    int len = get_head_array_length(L);
    int array[max]={0};
    LinkList p=L->next,pre=L;
    int temp_num;
    while (p!= nullptr){
        temp_num = p->data;
        if (temp_num <0)
            temp_num = - temp_num;

        if (array[temp_num] == 0){
            array[temp_num] += 1;
            pre = p;
            p = p->next;
        }
        else{
            LinkList temp = p;
            pre->next = temp->next;
            delete temp;
            p = pre->next;
        }
    }

    print_singlelist(L);
}

void ex7(LinkList &A, LinkList &B){
    LinkList head = A;
    LinkList a,b,ar,br;
    A = A->next;
    B = B->next;
    head->next = nullptr;

    while (A!= nullptr && B!= nullptr){
//        print_singlelist(head);
        if (A->data <B->data){
            ar = A->next;
            a = head->next;
            head->next = A;
            A->next =a;
            A = ar;
        } else{
            br = B->next;
            b = head->next;
            head->next = B;
            B->next = b;
            B=br;
        }
    }
    while (A != nullptr){
        ar = A->next;
        a = head->next;
        head->next = A;
        A->next =a;
        A = ar;
    }
    while (B!= nullptr){
        br = B->next;
        b = head->next;
        head->next = B;
        B->next = b;
        B = br;
    }
    A = head;
}

void ex8(LinkList& l1,LinkList& l2){
    //l1升序  l2降序
/*    //将l2升序 插入排序
    LinkList p ,pre, q = l2->next->next, r= q->next;
    l2->next->next = nullptr;
    while (q!= nullptr){
        p = l2->next;
        pre = l2;

        while (p!= nullptr){
            if (p->data < q->data){
                p=p->next;
            } else {
                q->next = p;
                pre->next = q;
                break;
            }
        }
        if(p== nullptr)
            pre->next = q;
        q =r;
        if (r)
            r = r->next;
        print_singlelist(l2);
    }*/
    //将l2逆置
    LinkList p,q=l2->next->next,r=q->next;
    l2->next->next = nullptr;
    while (q!= nullptr){
        q->next = l2->next;
        l2->next = q;
        q = r;
        if (r)
            r = r->next;
    }
    //将l1 和l2归并排序print_singlelist(head);
    LinkList a=l1->next,b=l2->next,head=l1;
    head->next= nullptr;
    while (a!= nullptr && b!= nullptr){
        if (a->data<b->data){
            head->next = a;
            head = a;
            a = a->next;
            head ->next = nullptr;
        } else{
            head->next = b;
            head = b;
            b=b->next;
            head->next = nullptr;
        }
    }
    while (a){
        head->next = a;
        head = a;
        a = a->next;
    }
    while (b){
        head->next = b;
        head = b;
        b = b->next;
    }
    print_singlelist(l1);

}
void ex10(LinkList& ha,LinkList& hb){
    LinkList p1=ha,p2=hb;
    auto head = new LNode;
    head->next = nullptr;
    LinkList p=head;
    while (p1&&p2){
        if (p1->data < p2->data){
               p->next = p1;
               p = p1;
               p1 = p1->next;
               p->next = nullptr;

        } else if (p1->data == p2->data){
            p->next = p1;
            p = p1;
            p2 = p2->next;
            p1 = p1->next;
            p->next = nullptr;
        } else{
            p->next = p2;
            p = p2;
            p2 = p2->next;
            p->next = nullptr;
        }
    }
    while (p1){
        p->next = p1;
        p = p1;
        p1 = p1->next;
        p->next=nullptr;
    }忽略文件添加.idea目录
    while (p2){
        p->next = p2;
        p = p2;
        p2 = p2->next;
        p->next= nullptr;
    }
    ha = head->next;
    print_singlelist(ha, false);

}

void ex12(LinkList& A,LinkList& B){
    LinkList a=A->next,b=B->next,head=A,p;
    head->next= nullptr;
    p=head;
    while (a&&b){
        if (a->data==b->data){
           p->next = a;
           p=a;
           a=a->next;
           b=b->next;
           p->next = nullptr;
        } else if (a->data < b->data)
        {
            a = a->next;
        } else{
            b=b->next;
        }
    }
    A=head;
    print_singlelist(A);
}
void ex14(LinkList& A,LinkList& B){
    LinkList a=A->next,b=B->next,C=new LNode,p=C;
    while (a&&b){
        if (a->data<b->data){
            auto t = new LNode;
            t->data=a->data;
            t->next= nullptr;
            p->next = t;
            p=t;
            a = a->next;
        } else{
            auto t = new LNode;
            t->data = b->data;
            t->next= nullptr;
            p->next = t;
            p=t;
            b = b->next;
        }
    }
    print_singlelist(C);

}

void ex15(LinkList& A, LinkList& B,LinkList& C){
    LinkList a=A->next,b=B->next,c=C->next,b_head=B,a_head=A;
    while (b&&c){
        if (b->data==c->data){
            b_head->next = b;
            b_head = b;
            b = b->next;
            c = c->next;
            b_head->next = nullptr;
        }else if (b->data<c->data){
            b = b->next;
        } else{
            c = c->next;
        }
    }
    print_singlelist(B);
    b = B->next;
    while (a&&b){
        if (a->data<b->data){
            a_head->next = a;
            a_head=a;
            a = a->next;
            a_head->next = nullptr;
//            cout<<'\t'<<a_head->data<<endl;
        } else if (a->data == b->data){
            a_head ->next =a;
            a_head = a;
            a = a->next;
            b = b->next;
            a_head ->next= nullptr;
        } else{
            a_head ->next = b;
            a_head = b;
            b = b->next;
            a_head->next = nullptr;
        }
    }
    while (a){
        a_head ->next =a;
        a_head = a;
        a = a->next;
    }
    while (b){
        a_head ->next = b;
        a_head = b;
        b = b->next;
    }
    print_singlelist(A);

}
void main_2_1_to_6(){
    //    Elem x[] = {1,2,3,4,5,6,7};
//    int a[] = {11,13,15,17,19};
//    int b[] = {2,4,30,8,20};
//    LinkList L = CreateSingleList(x, get_array_len(x));
//    r_print(head->next);
//    print_singlelist(L, true);
//    reverse_array(x,1,3);
//    for (int i = 0; i < get_array_len(x); ++i) cout<<x[i];
//    ex1(L,get_head_array_length(L));
//    cout<<ex2(L,2);
//    ex3(x,get_array_len(x),3);
//    cout<<ex4(a,b,5);
//    print_array(x,7);
//    char str11[] = "loading";
//    char str22[] = "being";
//    LinkList str1 = CreateSingleList(str11,7);
//    LinkList str2 = CreateSingleList(str22,5);
//    cout<<ex5(str1,str2)->data;
//    int x[] = {21,-15,-15,-7,15,8,-21,5};
//    LinkList L = CreateSingleList(x,get_array_len(x));
//    ex6(L,50);
}
void main2_7(){
    int x1[] = {2,4,6,8,11};
    int x2[] = {1,3,14,16,17};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1));
    LinkList l2 = CreateSingleList(x2,get_array_len(x2));
    ex7(l1,l2);
    print_singlelist(l1);
}
void main2_8(){
    int x1[] = {1,3,5,6,7,8};
    int x2[] = {33,32,21,20,19,14,13,2};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1), true);
    LinkList l2 = CreateSingleList(x2,get_array_len(x2), true);
    ex8(l1,l2);
}
void main_2_9(){
    //同ex8()
}
void main2_10(){
    int x1[] = {1,3,5,7,8,90};
    int x2[] = {2,4,7,9,14,32};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1), false);
    LinkList l2 = CreateSingleList(x2,get_array_len(x2), false);
    ex10(l1,l2);

}
void main2_11(){
    //同ex11()
}
void main2_12(){
    int x1[] = {1,3,5,7,8,9,90};
    int x2[] = {2,4,7,9,14,32};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1), true);
    LinkList l2 = CreateSingleList(x2,get_array_len(x2), true);
    ex12(l1,l2);
}
void main2_13(){
    //同ex12()
}
void main2_14(){
    int x1[] = {1,3,5,7,8,9,90};
    int x2[] = {2,4,7,9,14,32};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1), true);
    LinkList l2 = CreateSingleList(x2,get_array_len(x2), true);
    ex14(l1,l2);
}
void main2_15(){
    int x1[] = {1,3,5,7,8,9,90};
    int x2[] = {2,4,7,9,11,14,32};
    int x3[] = {6,8,11,25,32};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1), true);
    LinkList l2 = CreateSingleList(x2,get_array_len(x2), true);
    LinkList l3 = CreateSingleList(x3,get_array_len(x3), true);
    ex15(l1,l2,l3);
}

int main2(){
//    main2_8();
//    main2_12();
//    main2_14();
    main2_15();
    return 0;
}
