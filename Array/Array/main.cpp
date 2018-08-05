#include<stdio.h>
#include<stdlib.h>
#include"base.h"
 int main()
 {
	 struct Arr arr;
	 init_arr(&arr,6);
	 for (int i=2;i<4;i++)
		append_arr(&arr,i);
	 show_arr(&arr);
	 //insert_arr(&arr,4,4);
	 //show_arr(&arr);
	 //int val;
	 //delete_arr(&arr,2,&val);
	 //printf("É¾³ýµÄÔªËØÎª£º %d\n",val);show_arr(&arr);
	 inversion_arr(&arr);
	 show_arr(&arr);
	 printf("Ã°ÅÝÅÅÐò\n");
	 sort_arr(&arr);
	 show_arr(&arr);

	 system("pause");
	 return 0;
 }