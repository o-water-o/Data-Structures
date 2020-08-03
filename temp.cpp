//
// Created by tom on 2020/8/1.
//

#include<iostream>
#include <stack>
#include<stdlib.h>
#include<time.h>

using namespace std;

typedef struct node
{
    int data;
    struct node *next;
}Node;

/*     创建含有n个结点的单链表    */
Node *CreateListHead(int n)
{
    Node *head;
    head=(Node *)malloc(sizeof(Node)); /*创建头结点*/
    Node *q = head;

    /* 初始化随机数种子 */
    srand(time(0));  //srand函数在stdlib.h头文件中，time函数在time.h头文件中

    for(int i=0; i < n; i++)
    {
        Node *p = (Node *)malloc(sizeof(Node));
        p->data = rand()%100+1;  //随机生成100以内的数字
        p->next = q->next;
        q->next = p;
        q = p;
    }
    q->next = NULL;

    return head;
}
/*     用栈实现从尾到头打印单链表    */
void ReversePrintLinkListbystack(Node *head)
{
    Node *p = head->next;
    stack<int> s;
    while(head != NULL && p != NULL)   //入栈
    {
        s.push(p->data);
        p = p->next;
    }

    while(! s.empty())  //出栈
    {
        cout << s.top() << " ";
        s.pop();
    }

    cout << endl;
}

/*     用递归实现从尾到头打印单链表    */
void ReversePrintLinkListbyRecursionk(Node *head)
{
    Node *p;

    if(head==NULL || head->next==NULL)
        return;
    else
    {
        p=head->next;
        ReversePrintLinkListbyRecursionk(p);
        cout << p->data <<" ";
    }
}

/****打印单链表******/
void print(Node *head)
{
    Node *p;
    if(head->next==NULL)
    {
        cout << "The LinkList is Empty !" <<endl;
        return;
    }
    p=head->next;
    while(p!=NULL)
    {
        cout << p->data << " " ;
        p=p->next;
    }
}
int main()
{
    Node *SingleLinkList = NULL;
    int length;

    cout << "Please input the length of LinkList: ";
    cin >> length;
    SingleLinkList = CreateListHead(length);
    cout << "The new created LinkList as below: " ;
    print(SingleLinkList);
    cout << endl;

    cout << "Reverse Print LinkList by Recursion: " ;
    ReversePrintLinkListbyRecursionk(SingleLinkList);
    cout << endl;

//    cout << "Reverse Print LinkList by stack: " ;
//    ReversePrintLinkListbystack(SingleLinkList);

//    system("pause");
    return 0;
}