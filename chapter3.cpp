//
// Created by Tom on 2020/8/25.
//

#include <iostream>
#include <string>
#include <cstring>
#include "chapter3.h"
using namespace std;
SqStack InitStack(){
    auto S = SqStack{.top=-1};
    return S;
}
bool isEmpty(SqStack &S){
    return S.top == -1;
}
bool Push(SqStack&S,ElemType x){
    if (S.top == MaxSize-1)
        return false;
    else {
        S.data[++S.top] = x;
        return true;
    }
}
bool Pop(SqStack&S,ElemType &x, bool output){
    if (S.top == -1) {
        cout << "-->栈空<--" << endl;
        return false;
    }
    else{
        if (output)
            cout<<"出栈："<<S.data[S.top]<<endl;
        x = S.data[S.top--];
        return true;
    }
}
bool GetTop(SqStack S,ElemType &x){
    if (S.top == -1)
        return false;
    x = S.data[S.top];
    return true;
}
//顺序队列
void InitQueue(SqQueue &Q){
    Q.front=Q.rear=0;
}
bool isEmpty(SqQueue Q){
    return Q.front == Q.rear;
}
bool EnQueue(SqQueue& Q, ElemType x){
    //队尾指针指向最后一个元素的后一个位置
    if ((Q.rear+1%MaxSize) == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1)%MaxSize;
    return true;
}
bool DeQueue(SqQueue& Q, ElemType& x){
    if (Q.rear == Q.front)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1)% MaxSize;
    return true;
}

//链队
void InitQueue(LinkQueue &Q){
    Q.front = new LinkNode;
    Q.front->next = nullptr;
    Q.rear = Q.front;
}
bool isEmpty(LinkQueue Q){
    return Q.front == Q.rear;
}
void EnQueue(LinkQueue & Q, ElemType x){
    auto temp = new LinkNode {.data=x, .next=nullptr};
    Q.rear->next = temp;
    Q.rear = temp;
}
bool DeQueue(LinkQueue&Q,ElemType& x){
    if (Q.front==Q.rear)
        return false;
    else{
        auto temp = Q.front->next;
        Q.front->next = temp->next;
        x = temp->data;
        if (Q.rear == temp)
            Q.rear = Q.front;
        delete temp;
    }
    return true;
}
//

//链栈
StackLinkListPoint InitStackLinkList(){
    auto head = new StackLinkList {0, nullptr};
    return head;
}
bool Push(StackLinkListPoint &S,int value,bool output){
    auto temp = new StackLinkList {.data=value,.next=S->next};
    if (output)
        cout<<"入栈："<<temp->data<<endl;
    S->next = temp;
    return true;
}
bool Pop(StackLinkListPoint &S, int & e,bool output){
    if (!S->next){
        cout<<"栈空！！！！！";
        return false;
    }
    auto temp = S->next;
    e = temp->data;
    if (output)
        cout<<"出栈："<<e<<endl;
    S->next = temp->next;
    delete temp;
    return true;
}
bool isEmpty(StackLinkListPoint &S){
    return S->next == nullptr;
}

typedef struct stk{
    int stack[MaxSize];
    int top0,top1;
    struct stk * next;
}stk;
bool ex1_push(stk &S, int type, int value){
    if (S.top1 - S.top0 == 1)
    {
        cout<<"栈已满";
        return false;
    }
    switch (type){
        case 0:
            S.stack[++S.top0] = value;
            break;
        case 1:
            S.stack[--S.top1] = value;
            break;
        default:
            break;

    }
    return true;
}
bool ex1_pop(stk&S,int type, int &e){
    switch (type) {
        case 0:
            if (S.top0 == -1) {
                cout<<"栈空";
                return false;
            }else{
                cout<<S.stack[S.top0];
                e = S.stack[S.top0--];
            }
            break;
        case 1:
            if (S.top1 == MaxSize+1){
                cout<<"栈空";
                return false;
            }else{
                cout<<S.stack[S.top1];
                e = S.stack[S.top1++];
            }
            break;
        default:
            return false;
    }
    cout<<endl;
    return true;
}
void run_ex1(){
    auto S  = stk {.top0=-1,.top1=MaxSize+1};
    int temp;
    ex1_push(S,1,1);
    ex1_push(S,1,2);
    ex1_pop(S,1,temp);
    ex1_pop(S,1,temp);
    ex1_pop(S,1,temp);
}
void ex2(SqStack& S,int value){
    if (value != -1){
        Push(S,value);
    }else{
     int temp;
     Pop(S,temp);
     cout<<temp<<endl;
    }
}
void ex21(SqStack &S){
    for (int i=0;i>-1;i++){
        int in;
        cout<<"请输入数值:";
        cin>>in;
        if (in == 0)
            break;
        ex2(S,in);
        cout<<endl;
    }
}
void run_ex2(){
    auto S = InitStack();
    ex21(S);

}

typedef struct {
    char data[MaxSize];
    int top;
}ex3_stk;
bool ex3(ex3_stk& S, const char x[], int len){
    for (int i = 0; i <len && x[i]!='#'; ++i) {
        switch (x[i]) {
            case '(':
                S.data[++S.top] = '(';
                continue;
            case ')':
                if (S.top == -1)
                    return false;
                else{
                    cout<<S.data[S.top--]<<endl;
                    continue;
                }
            default:
                continue;
        }

    }
    return S.top == -1;
}
void run_ex3(){
    auto S = ex3_stk {.top=-1};
    char x[] = "*-((-)(+))#";
    cout<<ex3(S,x,10);

}
void run_ex4(){
    char x[] = "asdfgfdsa@";
    int n=0;
    while (x[n]!='@')
    {
//        cout<<n<<"\t"<<x[n]<<endl;
        n++;
    }
    n = n-1;
//    cout<<n<<endl;
    for(int i=0;i<n/2;i++,n--) {
//        cout<<x[i]<<"\t"<<x[n]<<endl;
        if (x[i]!=x[n]) {
            cout << "fail!";
            return;
        }
    }
    cout<<"success.";
}
typedef struct ex5_link{
    char ch;
    struct ex5_link * next;
}ex5_link,*ex5_link_point;
bool ex5_push(ex5_link_point& S, char x){
    auto temp = new ex5_link{.ch=x,.next=S->next};
    cout<<"入栈："<<temp->ch<<endl;
    S->next = temp;
    return true;
}
bool ex5_pop(ex5_link_point& S, char &e){
    if (!S->next){
        cout<<"栈空！！！！！";
        return false;
    }
    auto temp = S->next;
    e = temp->ch;
    cout<<"出栈："<<e<<endl;
    S->next = temp->next;
    delete temp;
    return true;

}
bool ex5(ex5_link_point&S, ex5_link_point &L){
    ex5_link_point p=L->next;
    while (p!=L){
        cout<<"--------> "<<p->ch<<endl;
        switch (p->ch) {
            case '(':
                ex5_push(S,p->ch);
                break;
            case ')':
                char t;
                if (!ex5_pop(S,t))
                    return false;
                if (t != '(')
                    return false;
                break;
        }
        p = p->next;
    }
    return S->next == nullptr;
}
void run_ex5(){
    char x[] = "-+((%^)())()***";
    auto L = new ex5_link,p=L;
    L->next = nullptr;
    for (int i=0;x[i]!='\0';i++){
        auto temp = new ex5_link {.ch=x[i],.next=nullptr};
        p ->next = temp;
        p = temp;
    }
    p->next = L;
    p = L->next;
    while (p!=L){
        cout<<p->ch<<"\t";
        p = p->next;
    }
    cout<<endl;
    auto S = new ex5_link;
    S->next = nullptr;
    cout<<ex5(S,L);

}
int ex6_max_value(int x[], int max_index){
    if (max_index==0)
        return x[0];
    else{
        if (x[max_index] > ex6_max_value(x,max_index-1))
            return x[max_index];
        else{
            return ex6_max_value(x,max_index-1);
        }
    }
}
void run_ex6(){
    int x[] = {2,4,16,8,-1,-4,11};
    cout<<ex6_max_value(x,6);
}

void ex7_max_min(int x[],int index,int &max,int &min){
    if (index>=0){
        if (x[index]>max)
            max = x[index];
        if (x[index]<min)
            min=x[index];
        ex7_max_min(x,index-1,max,min);
    }
}
void run_ex7(){
    int x[] = {2,4,16,8,-1,-4,11};
    int max = x[0],min = x[0];
    ex7_max_min(x,6,max,min);
    cout<<max<<"\t"<<min<<endl;
}
void ex8_1(int m,int n,int &common){
    if (n==0)
        common = m;
    else
        ex8_1(n, m < n ? m : m % n, common);
}
void run_ex8_1(){
    //递归算法
    int a = 12,b = 8;
    int common_factor;
    ex8_1(a,b,common_factor);
    cout<<common_factor;
}
void ex8_2(int m, int n){
    int common_factor;
    while (n!=0){
        int tmp;
        if (m<n){
            tmp = m;
            m = n;
            n = tmp;
        }
        else{
            tmp = m;
            m = n;
            n = tmp%n;
        }
    }
    cout<<m;
}
void run_ex8_2(){
    //非递归算法
    int a=9,b=12;
    ex8_2(a,b);
}
void ex9(int m,int n){
    auto sm = InitStackLinkList(),sn=InitStackLinkList();
    int res=0;
    Push(sm,m);
    Push(sn,n);

    while (true){
//        cout<<res<<endl;
        int im,jn;
        Pop(sm,im);
        Pop(sn,jn);
        if (im==0){
            res = jn+1;
            if (isEmpty(sm))
                break;
            else
                Push(sn,res);

        }
        else{
            if (jn==0){
                Push(sm,im-1);
                Push(sn,1);
            }
            else{
                Push(sm,im-1);
                Push(sm,im);
                Push(sn,jn-1);
            }
        }
    }
    cout<<res;

}
void run_ex9(){
    int m=2,n=1;
    ex9(m,n);
}
void chapter3(){
    run_ex9();
}