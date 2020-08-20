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
int main2(){
    main2_46();
//    test();
    return 0;
}
