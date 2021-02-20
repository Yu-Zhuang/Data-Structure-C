# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define MAX 1000

void swap(int *a, int *b){
	int tmp = a[0];
	a[0] = b[0];
	b[0] = tmp;
}

void printArray(int *nums, int numsSize){
	for(int i=0;i<numsSize; i++){
		printf("%d\t", nums[i]);
		if((i+1) %10 == 0)
			printf("\n");
	}
	printf("\n");
}

void arrayGenerate(int *nums, int numsSize){
	for(int i=0;i<numsSize;i++){
		nums[i] = rand()%MAX;
	}
}

void QuickSort(int *nums, int left, int right){
	if(left >= right)
		return;

	int b = left, l = left, r = right+1;
	while(r > l){
		do l++; while(nums[l] < nums[b] && l<r);
		do r--; while(nums[r] > nums[b] && r>=l);
		if(r > l)
			swap(&nums[r], &nums[l]);
	}
	swap(&nums[b], &nums[r]);
	QuickSort(nums, left, r-1);
	QuickSort(nums, l, right);
}

void sort(int *nums, int numsSize){
	QuickSort(nums, 0, numsSize-1);
}

int main(void){
	srand(time(NULL));
	int numsSize = rand()%MAX;
	int *nums = (int*)malloc(sizeof(int)*numsSize);
	
	printf("\n\t~ before sort ~\n");
	arrayGenerate(nums, numsSize);
	printArray(nums, numsSize);
	sort(nums, numsSize);

	printf("\n\t~ after sort ~\n");
	printArray(nums, numsSize);

	return 0;
}