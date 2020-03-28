#include<stdio.h>
#include<stdlib.h>
void quickSort(int* nums, int left, int right);
void Quick(int *nums, int l, int r);

int main(void){
    int list[7]={5,4,6,2,8,3,9},list_2[7]={5,4,6,2,8,3,9};
    
    printf("standard quick sort:\n");
    Quick(list,0,6);
    printf("\nmy quick sort:\n");
    quickSort(list_2,0,6);
    
    printf("reulst:\n");for(int i=0;i<7;i++) printf("%d,",list[i]);
    
    printf("\n");
    return 0;
}
void quickSort(int *nums, int left, int right){
    if(left>=right) return;
    int base=nums[left], i=left, j=right;
    
    while(i<j){
        while(nums[i]<=base&&i<j) i++;
        while(nums[j]>base&&i<=j) j--;
        if(i<j&&nums[i]!=nums[j]){
            nums[i]^=nums[j]; nums[j]^=nums[i]; nums[i]^=nums[j];
        }
        printf("(%d,%d)\n",i,j);
    }
    if(nums[left]!=nums[j]){ //兩數相同 而以此方式交換 數值為 0;
        nums[left]^=nums[j];nums[j]^=nums[left];nums[left]^=nums[j];
    }
    for(int i=0;i<7;i++) printf("%d,",nums[i]);printf("\n");
    quickSort(nums,left,j-1);
    quickSort(nums,j+1,right);
}

void Quick(int *nums, int left, int right){
    int i=left, j=right+1, base=nums[left];
    
    if(left<right){
        do{
            do i++; while(nums[i]<base&&i<j-1);
            do j--; while(nums[j]>base&&i<=j);
            if(i<j) {nums[i]^=nums[j];nums[j]^=nums[i];nums[i]^=nums[j];}
            printf("(i=%d, j=%d)\n",i,j);
        }while(i<j);
        
        if(nums[left]!=nums[j]){ //兩數相同 而以此方式交換 數值為 0;
            nums[left]^=nums[j];nums[j]^=nums[left];nums[left]^=nums[j];
        }
        for(int k=0;k<7;k++) printf("%d ",nums[k]);printf("\n"); //
        Quick(nums, left, j-1);
        Quick(nums, j+1, right);
    }
}
