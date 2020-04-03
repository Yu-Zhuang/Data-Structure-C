#include<stdio.h>
#include<stdlib.h>

#define SIZE 7

void QUICK_SORT(int *nums, int left, int right);
void PRINT_NUMS(int *nums, int numsSize) { for(int i=0;i<numsSize;i++) printf("%d ", nums[i]); printf("\n"); }
void SWAP(int *a, int *b) { a[0]=b[0]+a[0]-(b[0]=a[0]); }

int main(void){
	int list[SIZE]={7,6,5,4,3,2,1};
 
	PRINT_NUMS(list,SIZE); 
	QUICK_SORT(list,0,SIZE-1);
	PRINT_NUMS(list,SIZE);

	return 0;
}
void QUICK_SORT(int *nums, int left, int right){
	int base=left, i=left, j=right+1;
	if(i<j){
		do{
			do i++; while(nums[i]<nums[base]); 
			do j--; while(nums[j]>nums[base]); 
			if(i<j) SWAP(&nums[i], &nums[j]);
		}while(i<j);
		SWAP(&nums[base], &nums[j]);
		QUICK_SORT(nums, left, j-1);
		QUICK_SORT(nums, j+1, right);
	}
}
