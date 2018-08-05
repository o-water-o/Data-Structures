# include <stdio.h>
# include <malloc.h>
# include <stdlib.h> //包含了 exit（）函数 
//定义了 一个数据类型，该数据类型的名字叫做  struct Arr 
struct Arr //结构体是自定义的数据类型 
{
	int * pBase; //存储数组的第一个元素的地址
	int len;//数组所能容纳的最大元素的个数
	int cnt; //当前数组有效元素的个数
	int incretment;//自动增长因子 
};
void init_arr(struct Arr *pArr,int length);
bool append_arr(struct Arr *pArr,int val);//追加
bool insert_arr(struct Arr *pArr,int pos,int val);//插入 pos 的值从1开始
bool delete_arr(struct Arr *pArr,int pos,int *pVal);
bool is_empty(struct Arr * pArr);
bool is_full(struct Arr * pArr);
int get();
void sort_arr(struct Arr *pArr);
void show_arr(struct Arr *pArr);
void inversion_arr(struct Arr * pArr);
int input();
  
/*int main()
{
	struct Arr arr;
	init_arr(&arr,4);
	//printf("%d",arr.len);
	show_arr(&arr);	
	for (int j;j<10;j++)
	{
		append_arr(&arr,input());
		show_arr(&arr) ;
		if (arr.cnt == arr.len)
			{
			printf("数组已满，不能再追加，即将退出。。。\n\n");
			break;
		}
	}
	
	show_arr(&arr) ;
	return 0;
}
*/


//初始化函数 
void init_arr(struct Arr *pArr,int length)
{
	//(*pArr).len=90;
	pArr->pBase=(int *)malloc(sizeof(int)*length);
	if(NULL == pArr->pBase)
	{
		printf("动态函数内存分配失败！\n");
		exit(-1);
		 
	}
	else
	{
		pArr->len = length;
		pArr->cnt = 3;
		pArr->pBase[0] = 10;
		pArr->pBase[1] = 5;
		pArr->pBase[2] = 8;
		
	}
	return;
}


//判断数组是否为空 
bool is_empty(struct Arr * pArr)
{
	if(0 == pArr->cnt)
	{
		 return true;
	}
	else
	{
		return false;
	}
}


//判断数组是否满员 
bool is_full(struct Arr * pArr)
{
	if (pArr->len==pArr->cnt)
		return true;
	else
		return false;
}


//输出数组值 
void show_arr(struct Arr *pArr)
{
	if (is_empty(pArr))
	{
		printf("数组为空\n");
	}
	else
	{
		for(int i=0;i<pArr->cnt;i++)
			printf("%d\t",pArr->pBase[i]);
		printf("(cnt：%d\tlen: %d)",pArr->cnt,pArr->len);
		printf("\n");
	}
}


//追加元素
bool append_arr(struct Arr *pArr,int val)
{
	if (is_full(pArr))
		{
		printf("数组已满员，不能再增加\n");
		return false;}
	else
		{
			pArr->pBase[pArr->cnt] = val;
			pArr->cnt++;
			return true;
		 } 
 } 
 
 //接受键盘输入
 int input()
 {
 	printf("请输入需要的元素： ");
 	int x;
	scanf("%d",&x);
	return x;
  } 


//插入
 bool insert_arr(struct Arr *pArr,int pos,int val)//插入 pos 的值从1开始
 {
	 if (is_full(pArr))
		 return false;
	 if (pos<1 || pos>pArr->cnt+1)
		 return false;

	 for(int i=pArr->cnt-1;i>=pos-1;--i)
	 {
		 pArr->pBase[i+1] =pArr->pBase[i];
	 }
	 pArr->pBase[pos-1] = val;
	 pArr->cnt++;
	 printf("\nappeng_arr() 插入成功！\n");
	 return true;
 }

 //删除元素并返回值
 bool delete_arr(struct Arr *pArr,int pos,int *pVal)
 {
	 if (is_empty(pArr))
		 return false;
	 if (pos<1 || pos>pArr->cnt)
		 return false;
	 *pVal = pArr->pBase[pos-1];
	 for (int i=pos;i<pArr->cnt;++i)
		 pArr->pBase[i-1] = pArr->pBase[i];
	 pArr->cnt--;
	 printf("\ndelete_arr() 删除成功！\n");
	 return true;

 
 }


 //倒置
 void inversion_arr(struct Arr * pArr)
 {
	 int i=0;
	 int j=pArr->cnt-1;
	 int t;
	 while (i<j)
	 {
		 t = pArr->pBase[i];
		 pArr->pBase[i] = pArr->pBase[j];
		 pArr->pBase[j] = t;
		 ++i;
		 --j;
		 //printf("i=%d j=%d\t",i,j);
		 
	 }
	 return;
 }


 //冒泡排序
 void sort_arr(struct Arr *pArr)
 {
	 int i,j,t;
	 for(i=0;i<pArr->cnt;++i)
	 {
		 for(j=i+1;j<pArr->cnt;++j)
			 if (pArr->pBase[i] > pArr->pBase[j])
			 {
				 t=pArr->pBase[i];
				 pArr->pBase[i] = pArr->pBase[j];
				 pArr->pBase[j] = t;

			 }
			 				 				
	 }
 }