#include <iostream>
void chapter1(){
    for (int x=1;x<20;x++)
        for (int y=1;y<=34;y++)
            for (int z=1;z<=100;z++){
                if ((15*x + 9*y +z ==300)&& (x+y+z==100)){
                    printf("%d,%d,%d\n",x,y,z);
                }
            }
}


int main1() {
    printf("Hello, World!\n");
    chapter1();
    return 0;
}


