#include<stdio.h>
#include<stdlib.h>
//define size of nums
#define SIZE 7
//funciton
void QUICK_SORT(int *nums, int left, int right);
void PRINT_NUMS(int *nums, int numsSize) { for(int i=0;i<numsSize;i++) printf("%d ", nums[i]); printf("\n");}
void SWAP(int *a, int *b) { a[0]=b[0]+a[0]-(b[0]=a[0]); }
// MAIN
int main(void){
	int list[SIZE]={3,7,1,8,4,2,6};

	PRINT_NUMS(list,SIZE); 
	QUICK_SORT(list,0,SIZE);
	PRINT_NUMS(list,SIZE);

	return 0;
}
//quick sort function
void QUICK_SORT(int *nums, int left, int right){
	int base=left, i=left, j=right;
	if(i>=j) return;
	while(i<j){
		if(nums[i]>nums[base]&&nums[j]<nums[base]) SWAP(&nums[i], &nums[j]);
		do i++; while(nums[i]<nums[base]);
		do j--; while(nums[j]>nums[base]);
	}
	SWAP(&nums[base], &nums[j]);
	QUICK_SORT(nums, left, j-1);
	QUICK_SORT(nums, j+1, right);
}
