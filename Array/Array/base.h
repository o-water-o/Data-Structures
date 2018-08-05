#ifndef __base_h__
#define __base_h__

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
void inversion_arr(struct Arr * pArr);//倒置
int input();

#endif