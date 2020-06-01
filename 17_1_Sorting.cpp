# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void SWAP(int *num_1, int *num_2){
    num_1[0] = num_2[0] + (num_2[0] = num_1[0]) - num_1[0];
}

int* ARRAY_GENERATOR(int max, int min, int numsSize){
    srand(time(NULL));
    int *ret = (int*)malloc(sizeof(int)*numsSize);
    for(int i=0; i<numsSize; i++)
        ret[i] = rand()%(max-min+1)+min;
    return ret;
}

void ARRAY_PRINT(int *nums, int numsSize){
    printf("\n\t========= ARRAY_PRINT ===========\n");
    for(int i=0;i<numsSize;i++){
        printf("%7d ", nums[i]);
        if((i+1)%10 == 0)
            printf("\n");
    }
}

void BUBBLE_SORT(int *nums, int left, int right){
    for(int i=left;i<right-1;i++){
        for(int j=i;j<right;j++){
            if(nums[i] > nums[j])
                nums[i] = nums[j] - (nums[i] = nums[j]) + nums[j];
        }
    }
}

void PIVOT_SET(int *nums, int left, int right, int chose){
    srand(time(NULL));
    int pivot = 0;
    if(chose == 1)
        pivot = rand()%(right-left+1)+left;
    else{
        if(right - left > 5)
            BUBBLE_SORT(nums, (right+left)/2-2, (right+left)/2+2);
        pivot = (right+left)/2;
    }
    nums[left] = nums[pivot] - (nums[pivot] = nums[left]) + nums[left];
}

void QUICK_SORT(int *nums, int left, int right, int *ct){
    if(left < right){
        PIVOT_SET(nums, left, right, 0);  // set pivot to left
        int base=left, i=left, j=right+1;
        do{
            do {i++; ct[0]++;} while(nums[i]<nums[base] && i<=right); 
            do {j--; ct[0]++;} while(nums[j]>nums[base] && j>left); 
            if(i<j) SWAP(&nums[i], &nums[j]);
        }while(i<j);
        SWAP(&nums[base], &nums[j]);
        QUICK_SORT(nums, left, j-1, ct);
        QUICK_SORT(nums, j+1, right, ct);
    }
}

void MERGE(int *nums, int s1, int e1, int s2, int e2, int *ct){
    int *ret = (int*)malloc(sizeof(int)*(e2-s1+1));
    int len_1 = e1 - s1 + 1, len_2 = e2 - s2 + 1;
    int i=0, j=0, n=0;
    while(i<len_1 || j<len_2){
        if( (i<len_1 && j<len_2 && nums[s1+i] < nums[s2+j]) || (i<len_1&&j==len_2)){
            ret[n] = nums[s1+i];
            i++;
        }
        else{
            ret[n] = nums[s2+j];
            j++;            
        }
        n++;             
    }
    for(int m=0;m<e2-s1+1; m++)
        nums[s1+m] = ret[m];
    ct[0] += n;
    free(ret);
}

void MERGE_SORT(int *nums, int start, int end, int *ct){
    if(start >= end)
        return;
    MERGE_SORT(nums, start, (start+end)/2, ct);
    MERGE_SORT(nums, (start+end)/2+1, end, ct);
    MERGE(nums, start, (start+end)/2, (start+end)/2+1, end, ct);
}

int main(void){    
    int max = 32768, min = -32767, arraySize = 1000, cTimes = 0;
    int *arrayA = ARRAY_GENERATOR(max, min, arraySize);

    QUICK_SORT(arrayA, 0, arraySize-1, &cTimes);

    ARRAY_PRINT(arrayA, arraySize);
    printf("\n\tComparison times: %d\n", cTimes);

    free(arrayA);
    return 0;
}