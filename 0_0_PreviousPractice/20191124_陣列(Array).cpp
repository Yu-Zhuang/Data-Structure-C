//  Copyright © 2019 Yu-Zhuang Lin. All rights reserved.
// 陣列刪除元素
#include<stdio.h>
void arrayDelete(int* list,int listSize,int i);
int main(void){
    int nums[8]={5,11,25,36,49,56,77,120};
    
    arrayDelete(nums,8,3);
    //有8個元素的nums陣列的i(3)位置刪除資料,其餘後面資料往前;
    printf("\n");
    return 0;
}

void arrayDelete(int* list,int listSize,int i){
    int j;
    for(j=i;j<listSize;j++){
        list[j]=list[j+1];
    }
    list[listSize-1]=0;
    
    for(i=0;i<listSize;i++){
        printf("%d ",list[i]);
    }
    return;
}

//陣列插入元素
#include<stdio.h>
void arrayInsert(int* list,int n,int value,int i);
int main(void){
    int nums[8]={5,11,25,36,49,56,77,120};
    
    arrayInsert(nums,8,27,3);
    //有8個元素的nums陣列的i(3)位置插入元素49;
    printf("\n");
    return 0;
}

void arrayInsert(int* list,int n,int value,int i){
    int j;
    for(j=n-1;j>i;j--){
        list[j]=list[j-1];
    }
    list[i]=value;
    for(j=0;j<n;j++){
        printf("%d ", list[j]);
    }
    return;
}
