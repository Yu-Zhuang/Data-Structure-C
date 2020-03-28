#include<stdio.h>
#include<stdlib.h>
int cnt=0;

void bubble(int*,int); // if(numsSize==10) -> cnt==45;
void selection(int*,int); // if(numsSize==10) -> cnt==45;
void quickSort(int* nums, int, int);

int main(void){
    int nums[10]={0},j=0;
    for(int i=10;i>0;i--) {nums[j]=i;j++;}
    for(int i=0;i<10;i++) printf("%d ",nums[i]);printf("\n");
    
    quickSort(nums,0,9);
    
    printf("count=%d\n",cnt);
    printf("finished:");
    for(int i=0;i<10;i++) printf("%d ",nums[i]);printf("\n");
    
    return 0;
}

void quickSort(int * nums, int left, int right){
    int i=left, j=right+1, base=nums[left];
    
    if(left<right){
        do{
            do i++; while(nums[i]<base&&i<j-1);
            do j--; while(nums[j]>base&&i<=j);
            if(i<j) {nums[i]^=nums[j];nums[j]^=nums[i];nums[i]^=nums[j];}
            cnt++;
        }while(i<j);
        printf("(i=%d, j=%d)\n",i,j); //
        if(nums[left]!=nums[j]){ //兩數相同 而以此方式交換 數值為 0;
            nums[left]^=nums[j];nums[j]^=nums[left];nums[left]^=nums[j];
        }
        for(int k=0;k<10;k++) printf("%d ",nums[k]);printf("\n"); //
        quickSort(nums, left, j-1);
        quickSort(nums, j+1, right);
    }
}

void selection(int* nums,int numsSize){
    int flag=1;
    for(int j=0;j<numsSize-1&&flag;j++){
        flag=0;
        for(int i=j+1;i<numsSize;i++){
            cnt++;
            if(nums[j]>nums[i]){
                flag=1;
                nums[i]^=nums[j];
                nums[j]^=nums[i];
                nums[i]^=nums[j];
            }
        }
        for(int k=0;k<10;k++) printf("%d ",nums[k]);printf("\n");
    }
}

void bubble(int* nums,int numsSize){
    int flag=1;
    for(int i=0;i<numsSize&&flag;i++){
        flag=0;
        for(int j=0;j<numsSize-1-i;j++){
            cnt++;
            if(nums[j]>nums[j+1]){
                flag=1;
                nums[j]^=nums[j+1];
                nums[j+1]^=nums[j];
                nums[j]^=nums[j+1];
            }
        }
        for(int k=0;k<numsSize;k++) printf("%d ",nums[k]);printf("\n");
    }
}
