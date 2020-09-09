//
// Created by Tom on 2020/8/25.
//

#ifndef STUDY_CHAPTER3_H
#define STUDY_CHAPTER3_H


void chapter3();

#define  MaxSize 50
typedef int ElemType;
//顺序栈
typedef struct {
    ElemType data[MaxSize];
    int top;
}SqStack;

SqStack InitStack();
bool isEmpty(SqStack &S);
bool Push(SqStack&S,ElemType x);
bool Pop(SqStack&S,ElemType &x, bool output=false);
bool GetTop(SqStack S,ElemType &x);
//顺序队列
typedef struct {
    ElemType data[MaxSize];
    int front,rear; //front 队头，rear 队尾
}SqQueue;
void InitQueue(SqQueue &Q);
bool isEmpty(SqQueue Q);
bool EnQueue(SqQueue& Q, ElemType x);
bool DeQueue(SqQueue& Q, ElemType& x);
//链队
typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;
typedef struct {
    LinkNode*front,*rear;
}LinkQueue;
void InitQueue(LinkQueue &Q);
bool isEmpty(LinkQueue Q);
void EnQueue(LinkQueue & Q, ElemType x);
bool DeQueue(LinkQueue & Q, ElemType& x);

//链栈
typedef struct linklist{
    int data;
    struct linklist * next;
} StackLinkList,*StackLinkListPoint;
StackLinkListPoint InitStackLinkList();
bool Push(StackLinkListPoint &S,int value,bool output=false);
bool Pop(StackLinkListPoint &S, int & e,bool output= false);
bool isEmpty(StackLinkListPoint &S);
#endif //STUDY_CHAPTER3_H
