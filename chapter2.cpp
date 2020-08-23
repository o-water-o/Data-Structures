//
// Created by tom on 2020/7/31.
//
#include "chapter2.h"
#include <iostream>
#include "string"
using namespace std;

int get_head_array_length(LinkList &head){
    /*
     * 链表*/
    auto p = head->next;
    int i;
    for (i = 1; p->next!= nullptr ; p=p->next,++i);
    return i;
}
template <class T> int get_array_len(T& array){
    return sizeof(array)/sizeof(array[0]);

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
template <class T> bool array_insert(T L[],int len, int index, T value){
    if (index >len +1 || index <1)
        return false;
    for (int i = len-1; i >=index-1 ; --i) {
        L[i+1] = L[i];
    }
    L[index-1] = value;
    return true;
}
template <typename T> LinkList CreateSingleList(T array[], int length, bool is_head, bool is_cycle){
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
        if (is_cycle)
            p->next=head;
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
        if (is_cycle){
            p->next=head;
        }
        return head;
    }


}

template <typename T> LinkCharList CreateSingleCharList(T array[], int length, bool is_head, bool is_cycle){
    if (is_head) {
        auto head = new LCharNode;
        auto p = head;
        head->next = nullptr;
        for (int i = 0; i < length; i++, p = p->next) {
//            cout<<array[i]<<"$$$$\t";
            auto temp = new LCharNode;
            temp->next = nullptr;
            temp->data = array[i];
            p->next = temp;
        }
        if (is_cycle)
            p->next=head;
        return head;

    } else{
        if (!length)
            return nullptr;
        auto head = new LCharNode{.data=array[0], .next=nullptr};
        auto p=head;
        for (int i = 1; i < length ; ++i,p=p->next) {
            auto temp = new LCharNode;
            temp->data = array[i];
            temp->next = nullptr;
            p->next = temp;
        }
        if (is_cycle){
            p->next=head;
        }
        return head;
    }


}
void print_singlelist(LinkList &L, bool is_head, bool address,bool  is_cycle){
    LinkList p,end;
    if (is_head) p=L->next; else p=L;
    if (is_cycle) end = L;else end= nullptr;
    for (; p!= end ; p=p->next) {
           cout<<p->data;
           if (address) cout<<" "<<p;
           if (p->next!=end) cout<<" -> ";
    }
    cout<<endl;
}
void print_singlecharlist(LinkCharList &L, bool is_head, bool address,bool  is_cycle){
    LinkCharList p,end;
    if (is_head) p=L->next; else p=L;
    if (is_cycle) end = L;else end= nullptr;
    for (; p!= end ; p=p->next) {
        cout<<p->data;
        if (address) cout<<" "<<p;
//        if (p->next!=end) cout<<" -> ";
    }
    cout<<endl;
}




template<typename T>void reverse_array(T &array, int start, int end){
    /*
     * start: 1~n
     * end:1~n
     */
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

//双向链表
PDLinkList CreateDoublyLinkList(const int x[],int rows, bool is_cycle){
    auto head = new DLinkList{nullptr, nullptr,0};
    PDLinkList p=head;
    for (int i=0;i<rows;i++){
        auto temp = new DLinkList{.llink=p,.rlink=nullptr,.data=x[i]};
        p->rlink = temp;
        p = p->rlink;
    }
    if (is_cycle){
        p->rlink = head;
        head->llink = p;
    }
    return head;
}
void print_doubly_list(PDLinkList&L, bool is_cycle){
    auto p = L->rlink;
    PDLinkList end= nullptr;
    if (is_cycle) end=L;
    cout<<"双向链表：";
    while (p!=end){
        cout<<p->data<<"\t";
        p=p->rlink;
    }
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
    return L;//        if (is_cycle){
//            p->next->next=head;
//        }
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
    }
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
            p->next = t;print_singlelist(A);
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

void ex16(LinkList &A,LinkList& B){
    LinkList a=A->next,b=B->next,p=A;
    p->next= nullptr;
    while (a&&b){
        if (a->data==b->data){
            a = a->next;
            b = b->next;
        } else if (a->data<b->data){
            p->next = a;
            p=a;
            a =a->next;
            p->next= nullptr;
        } else{
            b = b->next;
        }


    }
    while (a){
        p->next = a;
        p=a;
        a=a->next;
        p->next= nullptr;
    }
    print_singlelist(A);
}
LinkList ex17(LinkList& L1,LinkList& L2,int L1_LEN, int L2_LEN){
    LinkList short_head,long_head,p;
    if (L1_LEN<L2_LEN){
        short_head=L1;
        long_head = L2;
    }
    else{
        short_head=L2;
        long_head=L1;
    }

    for (p=short_head->next; p->next!=short_head;p=p->next);
    p->next = long_head->next;
    long_head->next = short_head->next;
    print_singlelist(long_head, true, false, true);
    return long_head;

}
void ex18(LinkList& ha,LinkList&hb){
    //ha 为单项链表
    //hb 为单向循环列表
    auto t = new LNode;
    t->next = hb->next;
    hb->next = ha->next->next;
    hb->data = ha ->next->data;
    delete ha;
    print_singlelist(t);
}
void ex19(LinkList& A,LinkList& B,LinkList &C){
    LinkList pa,pb,pc,pre;
    pa=A->next;
    while (pa->next){
        if (pa->data == pa->next->data){
            auto t = pa->next;
            pa->next = t->next;
            delete t;
        } else{
            pa = pa->next;
        }
    }

    pb=B->next;
    while (pb->next){
        if (pb->data == pb->next->data){
            auto t = pb->next;
            pb->next = t->next;
            delete t;
        } else{
            pb = pb->next;
        }
    }

    pc=C->next;
    while (pc->next){
        if (pc->data == pc->next->data){
            auto t = pc->next;
            pc->next = t->next;
            delete t;
        } else{
            pc = pc->next;
        }
    }
    pa->next = B->next;
    delete B;
    pb->next = C->next;
    delete C;
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
//    char str11[] = "loading";    while (A != nullptr){

//    char str22[] = "being";
//    LinkList str1 = CreateSingleList(str11,7);
//    LinkList str2 = CreateSingleList(str22,5);
//    cout<<ex5(str1,str2)->data;
//    int x[] = {21,-15,-15,-7,15,8,-21,5};
//    LinkList L = CreateSingleList(x,get_array_len(x));
//    ex6(L,50);    while (A != nullptr){

}
void main2_7(){
    int x1[] = {2,4,6,8,11};
    int x2[] = {1,3,14,16,17};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1));
    LinkList l2 = CreateSingleList(x2,get_array_len(x2));
    ex7(l1,l2);
    print_singlelist(l1);
}
void main2_8() {
    int x1[] = {1, 3, 5, 6, 7, 8};
    int x2[] = {33, 32, 21, 20, 19, 14, 13, 2};
    LinkList l1 = CreateSingleList(x1, get_array_len(x1), true);
    LinkList l2 = CreateSingleList(x2, get_array_len(x2), true);
    ex8(l1, l2);
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
void main2_16(){
    int x1[] = {1,3,5,7,8,9,90};
    int x2[] = {2,4,7,9,11,14,32};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1), true);
    LinkList l2 = CreateSingleList(x2,get_array_len(x2), true);
    ex16(l1,l2);
}
void main2_17(){
    int x1[] = {1,3,5,7,9};
    int x2[] = {2,4,6,8};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1), true,true);
    LinkList l2 = CreateSingleList(x2,get_array_len(x2), true, true);
//    print_singlelist(l1, true, false, true);
    LinkList p = ex17(l1,l2,5,4);
}
//        if (is_cycle){
//            p->next->next=head;
//        }
void main2_18(){
    int x1[] = {1,3,5,7,9};
    int x2[] = {2,4,6,8};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1), true, false);
    LinkList l2 = CreateSingleList(x2,get_array_len(x2), true, true);
    ex18(l1,l2);
}
void main2_19(){
    int x1[] = {1,3,3,5,5,5};
    int x2[] = {2,4,6,6,};
    int x3[] = {7,10,10,11,11};
    LinkList l1 = CreateSingleList(x1,get_array_len(x1), true, false);
    LinkList l2 = CreateSingleList(x2,get_array_len(x2), true, false);
    LinkList l3 = CreateSingleList(x3,get_array_len(x3), true, false);
    ex19(l1,l2,l3);
}
void ex20(int x1[],int x1_len,const int x2[],int x2_len){
    int i,j,all_len = x1_len+x2_len,q=all_len-1;

    for (i = x1_len-1,j=x2_len-1; i >-1&& j>-1 ;) {
        if (x1[i] >x2[j]){
            x1[q] = x1[i];
            --i;
        } else{
            x1[q] = x2[j];
            --j;
        }
        --q;
        print_array(x1,15);
    }

}
void main2_20(){
    int x1[15] = {1,3,3,5,5,5};
    int x2[] = {2,4,6,6,};
    ex20(x1,6,x2,4);
}
void ex21(int x[],int len){
    int p=0;
    for (int i = 1; i <len &&p< len-1; ++i) {

        if (x[i]<0){
            int temp,t2;
            temp = x[p];
            x[p] = x[p+1];
            x[p+1] = temp;
            t2 = x[p];
            x[p] = x[i];
            x[i] = t2;
            ++p;
        }
    }
    print_array(x,len);
}
void main2_21(){
    int x[] = {-2,3,-5,9,3,-4,3,-3,-2,12,34,-1};
    ex21(x,get_array_len(x));
}
void ex22(int x[], int len){
    int p=0;
    for (int i = 1; i <len &&p <len-1 ; ++i) {
        cout<<x[p]<<endl;
        if (x[i]<19){
            int t1;
            t1 = x[p];
            x[p] = x[p+1];
            x[p+1] = t1;

            t1 = x[p];
            x[p] = x[i];
            x[i] = t1;
            ++p;
        }

    }
    print_array(x,len);
}
void main2_22(){
    int x[] = {1,3,5,67,81,44,4,5,6,8,3,4,55,14,15,18,-1};
    ex22(x,get_array_len(x));
}

void ex23(int A[], int size, int num, int x){

    if (x>A[num-1])
    {
        A[size] = x;
    }
    else {
        int start = 0, end = num - 1, mid;
        while (start < end) {
            mid = end / 2;
            if (x <= A[mid])
                if (A[mid - 1] <= x) {
                    array_insert(A, size, mid+1, x);
                    break;
                } else {
                    end = mid;
                }
            else if (A[mid + 1] >= x) {
                array_insert(A, size, mid+2, x);
                break;
            } else {
                start = mid;
            }

        }
    }
    print_array(A,size+1);
}
void main2_23(){
    int x[20] = {1,2,3,5,6,7,8,30,11,12,13,};
    ex23(x,20,7,4);
//    int x1[10] = {1,2,3,5,6};
//    array_insert(x1,10,4,4);
//    print_array(x1,6);
}
void ex24(int x[], int len){
    int number;
    cout<<"enter number: ";
    cin>>number;
    if (number>x[len-1]){
        x[len] = number;
//        return;
    } else {
        int start = 0, end = len - 1, mid;
        while (start < end) {
            mid = end / 2;
            if (number < x[mid]) {
                if (x[mid - 1] < number) {
                    array_insert(x, len, mid + 1, number);
                    break;
                } else if (number < x[mid - 1]) {
                    end = mid;
                } else
                    break;
            } else if (number > x[mid]) {
                if (x[mid + 1] > number) {
                    array_insert(x, len, mid + 2, number);
                    break;
                } else {
                    if (x[mid + 1] < number) {
                        start = mid;
                    } else
                        break;
                }
            } else
                break;
            cout << start << "\t" << end << endl;
            print_array(x, 10);

        }
    }
    print_array(x,10);
}
void main2_24(){
    int x[50] = {1,4,6,7};
    ex24(x,4);
}
void ex25(int x[], int len, int item){
    int j=-1,i=0;
    while (i<len){
        if (x[i]==item)
            i++;
        else{
            x[++j] = x[i++];
        }
    }
    print_array(x,j+1);
}
void main2_25(){
    int x[14] = {1,2,3,4,5,5,6,5,7,8,9,9,10};
    ex25(x,13,5);
}
void ex26(int x[],int len, int k){
    reverse_array(x,len-k+1,len);
    reverse_array(x,1,len-k);
    reverse_array(x,1,len);
    print_array(x,len);
}
void main2_26(){
    int x[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14},k=4;
//    cout<<get_array_len(x);
    ex26(x,14,k);
}
void ex27(int x){
    int qian = x/1000;
    int bai = (x -qian*1000)/100;
    int shi = (x - qian*1000-bai*100)/10;
    int yuan = x - qian*1000-bai*100-shi*10;
    cout<<qian<<"千 "<<bai<<"百 "<<shi<<"十 "<<yuan<<"元  "<<endl;


}
void main2_27(){
    int x = 123456;
    ex27(x);
}
void ex28(LinkList& L){
    //不带头节点单链表插入排序
    LinkList p,pre,q=L->next,r=q->next;
    L->next = nullptr;
    auto head = new LNode;
    head->next = L;
    while (q){
        p=head;
        while (p->next){
            if (p->next->data > q->data){
                q->next = p->next;
                p->next = q;
                break;
            }
            p=p->next;

        }
        if (!p->next){
            p->next = q;
            q->next = nullptr;
        }
        q = r;
        if (q) r = r->next;

    }
    delete head;
    print_singlelist(L,false);

}
void main2_28(){
    int x[12] = {1,3,20,6,4,6,32,5,8,90,3,};
//    cout<<get_array_len(x);
    LinkList l1 = CreateSingleList(x,11, false);
    ex28(l1);
}
void ex29(LinkList &L){
    //带头结点的单链表排序
    LinkList p,q=L->next->next,r=q->next;
    L->next->next= nullptr;
    while (q){
        p=L;
        while (p->next){
            if (p->next->data > q->data){
                q->next = p->next;
                p->next=q;
                break;
            }
            p = p->next;
        }
        if (!p->next){
            p->next = q;
            q->next = nullptr;
        }
        q = r;
        if (r) r = r->next;
//        print_singlelist(L);
    }
}
void main2_29(){
    int x[11] = {1,4,3,67,43,23,23,14,36,18};
//    cout<<get_array_len(x);
    LinkList l = CreateSingleList(x,10);
    ex29(l);
}
void main2_30(){
    //同29题
}
void ex31(LinkList & L){
    //单循环列表去重排序
    LinkList p,q = L->next->next,r=q->next;
    L->next->next = L;
    while (q != L){
        p=L;
        while (p->next){
            if (p->next->data > q->data){
                q ->next = p->next;
                p->next = q;
                break;
            } else if (p->next->data == q->data){
                delete q;
                break;
            }
            p = p->next;
        }
        if (!p->next){
            p->next = q;
            q->next = L;
        }
        q = r;
        if (r!=L) r = r->next;
        print_singlelist(L,true,false,true);
    }
}
void main2_31(){
    int x[17] = {1,3,6,9,2,4,7,15,12,43,25,3,4,6,42,4,33,};
//    cout<<get_array_len(x);
    LinkList l = CreateSingleList(x,16, true,true);
    ex31(l);
}
void ex32(LinkList& L){
    ex29(L);
    print_singlelist(L, true,true);
    LinkList P= nullptr,Q= nullptr,p=P,q=Q,p1=L->next,r1 = p1->next;
    while (p1){
        //偶数
        cout<<"p1 "<<p1<<"\t"<<p1->data<<"\t"<<" r1 "<<r1<<endl;
        if (p1->data%2==0){
            if (!q){
                q=Q=p1;
                q->next= nullptr;
            } else{
                q->next = p1;
                q = p1;
                q->next = nullptr;
            }
        } else {
            //奇数
            if (!p){
                p = P=p1;
                p1->next = nullptr;
            }else{
                p->next = p1;
                p = p1;
                p->next = nullptr;
            }
        }
        p1 = r1;
        if (p1) r1 = r1->next;

    }
    print_singlelist(Q, false);
    print_singlelist(P, false);

}
void main2_32(){
    int x[] = {2,4,3,5,7,8,1,9,6,10};
    LinkList l = CreateSingleList(x,10);
    ex32(l);
}
void ex33(LinkList &L){
    auto B = new LNode{0, nullptr};
    auto C = new LNode{0, nullptr};
    LinkList p=L->next,b=B,c=C;
    while (p){
        if (p->data < 0){
            b->next = p;
            p = p->next;
            b=b->next;
            b->next= nullptr;
        }else if (p->data >0){
            c->next=p;
            p=p->next;
            c = c->next;
            c->next=nullptr;
        } else
            continue;
    }
    print_singlelist(B);
    print_singlelist(C);
}
void main2_33(){
    int x[] = {-1,-2,-3,-4,-5,1,2,3,4,5};
    LinkList l = CreateSingleList(x,10);
    ex33(l);
}
void ex34(LinkList& L){
    auto B = new LNode {0, nullptr};
    auto A=L;
    LinkList p=L->next,b=B,a=A;
    A->next= nullptr;
    B->next= nullptr;
    while (p){
        cout<<p->data%2<<"\t"<<endl;
        if(p->data%2 == 0){
            a->next = p;
            p=p->next;
            a = a->next;
            a->next=nullptr;
            print_singlelist(A);
        }else{
            b->next=p;
            p=p->next;
            b = b->next;
            b->next=nullptr;
        }
        print_singlelist(A);
        print_singlelist(B);
    }

}
void main2_34(){
    int x[] = {1,2,3,4,5,6,7,8,9};
    LinkList l = CreateSingleList(x,9);
    ex34(l);
}
void ex35(LinkCharList& L){
    auto A = new LCharNode {'\0', nullptr};
    auto B = new LCharNode {'\0', nullptr};
    auto C = new LCharNode {'\0', nullptr};
    LinkCharList p=L->next,a=A,b=B,c=C;
    while (p){
        if (isalpha(p->data)){
            a->next = p;
            p = p->next;
            a=a->next;
            a->next= nullptr;
        } else if (isdigit(p->data)){
            b->next=p;
            p=p->next;
            b = b->next;
            b->next= nullptr;
        }else{
            //其他字符
            c ->next = p;
            p = p->next;
            c = c->next;
            c->next = nullptr;
        }
    }
    print_singlecharlist(A);
    print_singlecharlist(B);
    print_singlecharlist(C);
}
void main2_35(){
    char x[] = "Hellp12345,!!!!oooo";
    LinkCharList l = CreateSingleCharList(x,19);
//    print_singlecharlist(l);
    ex35(l);
}
void ex36(LinkList& L){
    auto L2 = new LNode{0,nullptr};
    auto L1 = L;
    LinkList p=L->next,r=p->next,l1 = L1,l2 = L2;
    L1->next = nullptr;
    int num=0;
    while (p){
        num++;
        if (num%2==0){
            //偶数
            p->next = L2->next;
            L2->next = p;
            p =r;
            if (p) r = r->next;
        } else{
            //奇数
            l1->next = p;
            l1 = p;
            p = r;
            if (r) r=r->next;
            l1->next=nullptr;

        }
    }
    print_singlelist(L1);
    print_singlelist(L2);
}
void main2_36(){
    int x[] = {1,2,3,4,5,6,7,8,9};
    LinkList l = CreateSingleList(x,9);
    ex36(l);
}
void ex37(LinkList& L){
    LinkList min_ptr= L,temp= nullptr; // min_ptr保存最小值的前一节点
    auto p=L->next;//从 第二个节点开始
    while (p->next){
        if (min_ptr->next->data > p->next->data){
            min_ptr = p;
        }
        p =p->next;
    }
    temp = min_ptr->next;
    min_ptr->next = temp->next;
    cout<<temp->data<<endl;
    delete temp;
    print_singlelist(L);

}
void main2_37(){
    int x[] = {2,1,-3,5,-9,6,4,-10,3};
    LinkList L = CreateSingleList(x,9);
    ex37(L);
}
void ex38(LinkList& L){
    LinkList p = L->next,min_pre=L,min = min_pre->next;
    while (p->next){
        if (p->next->data<min->data){
            min_pre = p;
            min = min_pre->next;
        }
        p = p->next;
    }
    cout<<min->data<<endl;
    min_pre->next = min->next;
    min->next = L->next;
    L->next = min;
    print_singlelist(L);
}
void main2_38(){
    int x[] = {3,4,5,6,1,2,-2,9,19};
    LinkList L = CreateSingleList(x,9);
    ex38(L);
}
void ex39(PDLinkList& L){
    auto max=L->rlink,p=L->rlink->rlink;
    while (p){
        if (p->data > max->data){
            max = p;
        }
        p = p->rlink;
    }
    cout<<max->data<<endl;
    max->llink->rlink = max->rlink;
    max->rlink->llink = max->llink;
    max->rlink = L->rlink;
    L->rlink = max;
    max->llink = L;
    print_doubly_list(L);
}
void main2_39(){
    int x[] = {1,2,3,4,55,6,7,8};
    auto L =CreateDoublyLinkList(x,8);
    ex39(L);
}
void ex40(int x[], int len, int num){
    int start=0,end=len-1,mid,num_index=-1;
    while (start<=end){
        mid = (start + end)/2;
        if (x[mid] == num){
            num_index = mid;
            break;
        } else if (x[mid]< num){
            start = mid +1;
        }else{
            end = mid-1;
        }
    }
    if (num_index == -1){
        start = 0;end = len-1;
        while (start<end){
            mid = (start + end)/2;
            if (num < x[mid]){
                if (x[mid-1] < num){
                    array_insert(x,len,mid+1,num);
                    break;
                } else{
                    end = mid-1;
                }
            }else {
                if (num < x[mid+1]){
                    array_insert(x,len,mid+2,num);
                    break;
                }else{
                    start = mid+1;
                }
            }
            cout<<start<<"~"<<end<<endl;
        }
        if (end<=start){
            x[len] = num;
        }
    } else{
        if(num_index!=len-1){
            int temp = x[num_index];
            x[num_index] = x[num_index+1];
            x[num_index+1] = temp;
        }
    }
   print_array(x,len+1);
}
void main2_40(){
    int x[20] = {-1,2,3,5,7,8};
    ex40(x,6,3);
}
bool ex41(PDLinkList & L){
    auto head = L->rlink,tail= L->llink;
    while (true){
        cout<<head->data<<"\t"<<tail->data<<endl;
        if (head == tail){
            if (head->data == tail->data){
                return true;
            }
            else{
                cout<<"false"<<endl;
                return false;
            }
        }else {
            if (head->rlink == tail or tail->llink == head){
                if (head->data == tail->data){
                    return true;
                }
                else{
                    cout<<"false"<<endl;
                    return false;
                }
            }
        }
        if (head->data == tail->data){
            head = head->rlink;
            tail = tail->llink;
        }
        else{
            cout<<"false"<<endl;
            return false;
        }

    }
//    return true;
}
void main2_41(){
    int x1[] = {1,2,3,4,3,2,1};
    int x2[] = {1,2,3,4,4,3,2,1};
    auto L = CreateDoublyLinkList(x1,7,true);
    cout<<ex41(L);
}
void test(){
    int x[] = {1,2,3,4,5,6,7,8,9};
    auto L = CreateDoublyLinkList(x,9,true);
    print_doubly_list(L,false);
}
void ex42(LinkList& A,LinkList& B, int i,int len, int j){
    int count=0,dcount=0,flag=-1;
    LinkList a=A->next,a_pre=A,b=B->next;
    while (a){
        count++;
        if (count==i){
            flag = 1;
        }
        if (dcount<len && flag==1){
            dcount ++;
            a_pre->next = a->next;
            delete a;
            a = a_pre->next;
//            print_singlelist(A);
        }else{
            a_pre = a;
            a = a->next;
        }
    }
    count = 0;
    while (b){
       count++;
       if (count == j-1){
           a_pre->next = b->next;
           b->next = A->next;
       }else{
           b = b->next;
       }
    }
    print_singlelist(A);
    print_singlelist(B);

}
void main2_42(){
    int a[] = {1,2,3,4,5,6,7,8,9};
    int b[] = {11,12,13,14,15,16,17,18,19};
    auto A = CreateSingleList(a,9);
    auto B = CreateSingleList(b,9);
    int i=2,j=4,len=3;
    ex42(A,B,i,len,j);

}
PDLinkList create_linklist_43(const int x[], int len){
    auto L = new DLinkList {nullptr, nullptr,0},p=L;
    for (int i = 0; i <len ; ++i) {
        auto temp = new DLinkList {nullptr, nullptr,x[i]};
        p->rlink = temp;
        p = p->rlink;
    }
    p->rlink = L;
    return L;
}
void ex43(PDLinkList& L){
    PDLinkList pre=L,p=L->rlink;
    while (p!=L){
        p->llink = pre;
        pre = p;
        p=p->rlink;
    }
    L->llink = pre;
    p = pre;
    while (p!=L){
        cout<<p->data<<"\t";
        p =p->llink;
    }
}
void main2_43(){
    int x[] = {1,2,3,4,5,6,7};
    auto L = create_linklist_43(x,7);
    ex43(L);
//    print_doubly_list(L,true);
}
bool ex44(LinkList& L){
    int count=0,flag=-1;
    LinkList p=L->next,pre=L;
    while (p){
        count ++;
        if (count == 2){
            flag = 1;
        }
        if (flag==1){
            if (count*count-pre->data == p->data ){
                pre = p;
                p = p->next;
            }else{
                return false;
            }
        }else{
            pre=p;
            p=p->next;
        }
    }
    return true;
}
void main2_44(){
    int x[] = {1,3,6,10,15,21};
    auto L = CreateSingleList(x,6);
    cout<<ex44(L);
}
bool ex45(LinkList&A, LinkList&B){
    LinkList a=A->next,b=B->next,p;
    while (b&&a){
        if (a->data == b->data){
            a = a->next;
            b = b->next;
        }else{
            a = a->next;
        }
    }
    return b == nullptr;
}
void main2_45(){
    int a[] = {1,2,3,5,6,7,8,9};
    int b[] = {1,2,3,6,8};
    auto A = CreateSingleList(a,get_array_len(a));
    auto B = CreateSingleList(b,get_array_len(b));
    cout<<ex45(A,B);
}
void ex46(LinkCharList& A,LinkCharList& B){
    LinkCharList a=A->next,b=B->next,a_pre=A,pre= nullptr,s= nullptr,p,r;
    int flag=-1;
    while (a){
        if (a->data == b->data&&flag==-1){
            pre = a_pre;
            flag = 1;
        }
        if (flag==1&& a->data!=b->data){
            s = a;
            break;
        }else if (flag==1&& a->data==b->data){
            a_pre = a;
            a = a->next;
            b = b->next;
        }else{
            a_pre = a;
            a = a->next;
        }
//        cout<<a->data<<endl;
    }
    cout<<pre->data<<endl;
    cout<<s->data<<endl;
    // 从第二个元素开始插入倒置
    p = pre->next->next;r = p->next;
    pre->next->next = s;
    while (p!=s){
        p->next = pre->next;
        pre->next = p;
        p =r;
        if (r) r = r->next;
    }
    print_singlecharlist(A);
}
void main2_46(){
    char a[] = "hello,world!how are you?";
    char b[] = "world";
    auto A = CreateSingleCharList(a,get_array_len(a));
    auto B = CreateSingleCharList(b,get_array_len(b));
    ex46(A,B);
//    print_singlecharlist(A);
}
LinkList create_list_ex47(const int x[],int len,int i){
    if (len<=3)
        return nullptr;
    LinkList head = new LNode{0, nullptr},p=head,q= nullptr;
    for (int j=0;j<len;j++){
        auto temp = new LNode{x[j], nullptr};
        p->next = temp;
        p = temp;
        if (i==j+1)
            q = temp;
    }
    p->next = q;
    return head;
//    print_singlelist(head);
}
void ex47(LinkList& L,int i){
    LinkList p= L->next,pre = L,tail= nullptr,mid_pre= nullptr,mid;
    for (int j=1;!mid_pre or p->next!=mid_pre->next;pre = p,p=p->next,j++){
        if (i==j)
            mid_pre = pre;
    };
    tail = p;
    cout<<mid_pre->data<<"\t"<<tail->data<<endl;
    //从mid->next节点开始倒置
    tail->next = nullptr;
    mid = mid_pre->next; // mid子序列第一个节点
    p = mid->next; // p 初始化为子序列第二个节点
    mid->next = nullptr;
    auto r=p->next; //r为p节点的后继节点
    while (p){
        p->next = mid_pre->next;
        mid_pre->next = p;
        p=r;
        if (r) r = r->next;
    }
    mid ->next = mid_pre->next;
//    cout<<mid->data<<endl;
    print_singlelist(L);
}
void main2_47(){
    int x[] = {1,2,3,4,5,6,7,8,9};
    auto L = create_list_ex47(x,9,3);
    ex47(L,3);
}
void main2_48(){
    int x[] = {1,2,3,4,5,6,7,8,9};
    reverse_array(x,1,9);
    print_array(x,9);
}
void ex49(LinkList& L, int type=1){
    //就地逆置无头节点单链表
    /*
     * type=1 需要O(1)空间复杂度
     * type=2 无须空间复杂度*/
    switch (type) {
        case 1:{
            auto head = new LNode {0, L};
            LinkList p= head->next->next,r= nullptr;
            head->next->next= nullptr;
            while (p){
                r = p->next;
                p->next = head->next;
                head->next = p;
                p = r;
//                if (r) r = r->next;
            }
            print_singlelist(head->next, false);
            delete head;
            break;
        }
        case 2:{
            LinkList p=L,q=nullptr,r;
            while (p){
                r = p->next;
                p->next = q;
                q = p;
                p =r;
            }
            L=q;
            print_singlelist(L, false);
            break;
        }
        default:{
            break;
        }

    }
}
void main2_49(){
    int x[] = {1,2,3,4,5,6,7,8,9};
    auto L = CreateSingleList(x,9, false);
    ex49(L,1);
}
LinkList ex50(const int x[], int len){
    LinkList p,q=nullptr;
    for (int i = 0; i <len ; ++i) {
        auto temp = new LNode{x[i],q};
        q = temp;
    }
    print_singlelist(q,false);
    return q;
}
void main2_50(){
    int x[] = {1,2,3,4,5,6,7,8,9};
    ex50(x,9);
}
void ex51(LinkList & L){
    //带头节点单链表排序
    LinkList p=L->next->next,q,r= nullptr;
    L->next->next= nullptr;
    while (p){
        r = p->next;
        p->next = L->next;
        L->next = p;
        p = r;
    }
    print_singlelist(L);
}
void main2_51(){
    int x[] = {1,2,3,4,5,6,7,8,9};
    auto L = CreateSingleList(x,9);
    ex51(L);
}
void ex52(LinkList& L){
    //逆置单循环链表
    LinkList p=L->next->next,r= nullptr;
    L->next->next = L;
    while (p!=L){
        r = p->next;
        p->next = L->next;
        L->next = p;
        p=r;
    }
    print_singlelist(L,true,false,true);
}
void main2_52(){
    int x[] = {1,2,3,4,5,6,7,8,9};
    auto L = CreateSingleList(x,get_array_len(x),true,true);
    ex52(L);
}
void ex53(LinkList& L){
    LinkList tail=L,p= nullptr,r= nullptr;
    for(;tail->next!=L;tail=tail->next);
    auto a1=tail->next->next;//从第一个节点开始
    p = a1->next;
    auto a1n = new LNode {a1->data,nullptr};
    a1n->next = L;
    tail->next=a1n;
    while (p!=tail){
        auto temp =new LNode {p->data,tail->next};
        tail->next = temp;
        p=p->next;
    }
    print_singlelist(L,true,false,true);
}
void main2_53(){
    int x[] = {1,2,3,4,5};
    auto L = CreateSingleList(x,get_array_len(x),true,true);
    ex53(L);
}
void ex54(LinkList& L){
    if (!L){
        return;
    }
    ex54(L->next);
    cout<<L->data<<"\t";
}
void main2_54(){
    int x[] = {1,2,3,4};
    auto L = CreateSingleList(x,get_array_len(x), false);
    ex54(L);
}
void ex55(LinkList& L){
    auto min=L->next,p=L->next->next;
    while (p){
        if (p->data<min->data){
            min = p;
        }
        p =p->next;
    }
    cout<<min->data<<endl;
    if (min->data%2==0){
        auto after=min->next;
        min->next = after->next;
        delete after;
    }else{
        auto after = min->next->data;
        min->next->data = min->data;
        min->data = after;
    }
    print_singlelist(L);
}
void main2_55(){
    int x[] = {11,10,2,4,5,8};
    auto L = CreateSingleList(x,get_array_len(x));
    ex55(L);
}
void ex56(LinkList& L){
    LinkList p=L->next;
    while (p){
        if (p->next&&p->data == p->next->data){
            auto temp = p->next;
            p->next = temp->next;
            delete temp;
        }else{
            p = p->next;
        }
    }
    print_singlelist(L);
}
void main2_56(){
    int x[] = {7,10,10,21,30,42,42,42,51,70};
    auto L = CreateSingleList(x,get_array_len(x));
    ex56(L);
}
void main2_57(){
    //同ex56
}
void ex58(LinkList& L, int value){
    LinkList p=L->next,pre=L;
    int count =0;
    while (p){
        if (p->data>value && pre->data != p->data){
            count++;
        }
        pre=p;
        p=p->next;
    }
    cout<<"(1)："<<count<<endl;
    //(2)
    auto a1=L->next;
    p=a1->next;
    LinkList r= nullptr;
    a1->next = nullptr;
    while (p){
        if (p->data<value){
            r = p->next;
            p->next =L->next;
            L->next =p;
            p=r;
        } else{
            break;
        }
    }
    cout<<a1->data<<endl;
    a1->next = p;
    cout<<"(2):";
    print_singlelist(L);
    //(3)
    p=L->next;
    pre=L;
    while (p){
        if (p->data>value&&p->data%2==0){
            pre->next = p->next;
            delete p;
            p=pre->next;
        }else{
            pre=p;
            p=p->next;
        }
    }
    print_singlelist(L);
}
void main2_58(){
    int x[] = {20,20,17,16,15,15,11,10,8,7,7,5,4};
    reverse_array(x,1,13);
//    print_array(x,get_array_len(x));
    auto L = CreateSingleList(x,get_array_len(x));
    ex58(L,10);
};
void ex59(LinkList& L, LinkList &P){
    cout<<P->data<<endl;
    LinkList p=L->next;
    for (;p->next!=P;p=p->next);
    auto after = p->next,after1 = after->next;
    after->next = after1->next;
    after1->next = after;
    p->next =after1;
    print_singlelist(L);
}
void main2_59(){
    int x[] = {1,2,3,4,5,6,7,8,9};
    auto L = CreateSingleList(x,get_array_len(x));
    ex59(L,L->next->next->next);
}
typedef struct StringNode{
    string data;
    int count;
    struct StringNode *next;
} StringNode,*PStringNode;
void print_PStringNode(PStringNode& L){
    for(auto pp=L->next;pp;pp=pp->next){
        cout<<"data:"<<pp->data<<" count:"<<pp->count;
        if (pp->next) cout<<" -> ";
    }
    cout<<"\n---"<<endl;
}
void ex60(){
    PStringNode head = new StringNode {"",0, nullptr};
    int k=2;
    while (true){
        int flag=-1;
        auto p=head->next,pre=head;
        string x,_exit="exit";
        cout<<"Please enter word: ";
        cin>>x;
        if (x == _exit)
            break;
        //遍历链表查看有无数据相同的节点
        while (p){
           if (x == p->data){
               p->count++;
               flag=1;
               break;
           } else{
               pre=p;
               p = p->next;
           }
        }
        //没有相同的节点
        if (p== nullptr) {
            auto temp = new StringNode{x, 1, nullptr};
            pre->next = temp;
        }
    }
    print_PStringNode(head);
    /*输出出现次数最多的前k个单词*/
    //按照出现次数从到小排序链表
    PStringNode p=head->next->next,q,qpre,r= nullptr;
    head->next->next= nullptr;
    while (p){
        qpre=head;
        q = qpre->next;
        r = p->next;
        while (q){
            if (p->count>q->count){
                p->next = qpre->next;
                qpre->next = p;
                break;
            }
            qpre=q;
            q = q->next;
//            print_PStringNode(head);
        }
        if (q== nullptr){
            qpre->next = p;
            p->next= nullptr;
        }
        p=r;
    }
    print_PStringNode(head);
    p=head->next;
    for(int i=0;p;p=p->next,i++){
        if (i<k){
            cout<<p->data<<"\t";
        }
    }

};

void main2_60(){
    ex60();
}
void ex61(PDLinkList& L){
    auto a1 = L->rlink;
    //删除第一个节点
    L->rlink = a1->rlink;
    a1->rlink->llink = L;

    PDLinkList p=L->rlink;//第二个节点开始递增
    while (p!=L){
        if (p->data > a1->data){
            a1->rlink = p;
            a1->llink = p->llink;
            p->llink = a1;
            a1->llink->rlink = a1;
            break;
        }
        p = p->rlink;
    }
    if (p==L){
        p->llink->rlink=a1;
        a1->llink = p;
        a1->rlink = L;
    }
    print_doubly_list(L,true);
}
void main2_61(){
    int x[] = {60,2,3,5,8,10,12};
    auto L = CreateDoublyLinkList(x,get_array_len(x),true);
    ex61(L);
};
void main2_62(){
    //双链表插入，见ex61
}
typedef struct StaticNode{
    string data;
    int llink=0,rlink=0;
}StaticNode,*point_static_node;
void print_static_node(StaticNode L[],int len){
    int first=0;
    for (int i=1;i<=len;i++){
        if (L[i].llink == 0){
            first = i;
        }
    }
    int p = first;
    while (p!=0){
        cout<<L[p].data;
        p = L[p].rlink;
        if (p!=0)
            cout<<" -> ";
    }
    cout<<endl;
}
void ex63(StaticNode L[],int len, const string& name){
    int av = len+1,p=1,pre;
    L[av].data = name;
    if (L[p].data > name){
        while (p!=0){
            if (name> L[p].data){
                L[av].rlink = L[p].rlink;
                L[av].llink = p;
                L[pre].llink = av;
                L[p].rlink=av;
                break;
            }else{
                pre=p;
                p = L[p].llink;
            }
        }
        if (p==0){
            L[av].rlink = pre;
            L[av].llink = 0;
            L[pre].llink = av;
        }
        print_static_node(L,len+1);
    }else {
        while (p!=0){
            if (L[p].data >name){
                L[av].rlink = p;
                L[av].llink = pre;
                L[pre].rlink = av;
                L[p].llink = av;
                break;
            }else{
                pre=p;
                p = L[p].rlink;
            }
        }
        if (p==0){
            L[av].llink = pre;
            L[av].rlink = 0;
            L[pre].rlink = av;
        }
        print_static_node(L,len+1);
    }
}
void main2_63(){
    //静态链表
    StaticNode user[20];
    user[1] = {"Liu",6,5};
    user[2] = {"Chan",4,9};
    user[3] = {"Wang",5,7};
    user[4] = {"Bao",0,2};
    user[5] = {"Mai",1,3};
    user[6] = {"Dong",8,1};
    user[7] = {"Xi",3,0};
    user[8] = {"Deng",9,6};
    user[9] = {"Cuang",2,8};
    print_static_node(user,9);
    ex63(user,9,"Xa");
}
typedef struct ex64_double{
    string data;
    struct ex64_double *pred,*next;
    int freq=0;
}ex64_double,*ex64_point_double;
bool ex64_double_insert(ex64_point_double& L,const string& value,int freq){
    if (!L) return false;
    auto p = L;
    for(;p->next;p=p->next);
    auto temp = new ex64_double {value,p, nullptr,freq};
    p->next = temp;
    return true;
}
void ex64_double_print(ex64_point_double& L){
    if (!L) return;
    auto p=L->next;
    while (p){
        cout<<"data: "<<p->data<<" freq:"<<p->freq;
        p =p->next;
        if (p) cout<<" -> ";
    }
    cout<<endl;
}
ex64_point_double ex64(ex64_point_double & L,const string& value){

    // 查找 x，freq+1
    auto p=L->next;
    auto pre=L;
    bool flag=false;
    while (p){
        if (p->data == value){
            p->freq ++;
            flag=true;
            break;
        }else{
            pre=p;
            p=p->next;
        }
    }

    //对双向链表进行插入排序
    p=L->next->next;
    ex64_point_double q= nullptr,qpre= nullptr,r= nullptr;
    L->next->next = nullptr;
    while (p){
        q=L->next;
        r = p->next;
        qpre = L;
        while (q){
            if (p->freq>q->freq){
                p->next = q;
                qpre->next = p;
                p->pred = qpre;
                q->pred = p;
                break;
            }else{
                qpre=q;
                q = q->next;
            }
        }
        if (q== nullptr){
            qpre->next = p;
            p->next = nullptr;
            p->pred = qpre;
        }
        p=r;
    }

    if (!flag){
       pre->next = new ex64_double {value,pre, nullptr,1};
       p = pre->next;
    }
    ex64_double_print(L);

    return p;

}
void main2_64(){
    auto head = new ex64_double{"", nullptr, nullptr,0};
    ex64_double_insert(head,"a",2);
    ex64_double_insert(head,"b",3);
    ex64_double_insert(head,"c",1);
    ex64_double_insert(head,"d",1);
    ex64_double_print(head);
    ex64(head,"c");
    ex64(head,"c");
}
int main2(){
    main2_64();
//    test();
    return 0;
}
