#include<stdio.h>
#include<stdlib.h>

void QuickSort(int *nums, int left, int right); //small to big

int main(void){
	int list[7]={3,5,1,2,8,7,4};
	//print origin
	for(int i=0;i<7;i++) printf("%d ", list[i]); printf("\n");
	// quick sort
	QuickSort(list, 0, 6);
	// print after sort
	for(int i=0;i<7;i++) printf("%d ", list[i]); printf("\n");
	//end
	return 0;
}
void QuickSort(int *nums, int left, int right){
	if(left>=right) return;
	printf("===========QuickSort===================\n");
	int base=left, i=left, j=right+1;
	while(i<j){
		for(int a=0;a<7;a++) printf("%d ", nums[a]); printf("\n"); //(show list[] status)
		do i++; while(nums[i]<=nums[base]);
		do j--; while(nums[j]>nums[base]);
		printf("i:%d j:%d\n", i, j); //(show i,j status)
		if(nums[i]>nums[base] && nums[j]<nums[base] && i<j){
			nums[i]^=nums[j]; nums[j]^=nums[i]; nums[i]^=nums[j];
		}
	}
	if(nums[base] != nums[j]){
		nums[base]^=nums[j]; nums[j]^=nums[base]; nums[base]^=nums[j];
	}
	QuickSort(nums, left, j-1);
	QuickSort(nums, j+1, right);
	printf("===========END QuickSort===================\n");
}


