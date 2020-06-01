# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void SWAP(int *num_1, int *num_2){
    num_1[0] = num_2[0] + (num_2[0] = num_1[0]) - num_1[0];
}

int* ARRAY_GENERATOR(int max, int min, int numsSize){
    int *ret = (int*)malloc(sizeof(int)*numsSize);
    for(int i=0; i<numsSize; i++)
        ret[i] = rand()%(max-min+1)+min;
    return ret;
}

void MERGE(int *nums, int s1, int e1, int s2, int e2){
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
    free(ret);
}

void MERGE_SORT(int *nums, int start, int end){
    if(start >= end)
        return;
    else if(start+1 == end){
        if(nums[start] > nums[end])
            SWAP(&nums[start], &nums[end]);
    }
    else{
        MERGE_SORT(nums, start, (start+end)/2 );
        MERGE_SORT(nums, (start+end)/2+1, end );
        MERGE(nums, start, (start+end)/2, (start+end)/2+1, end);
    }
}

int main(void){
    srand(time(NULL));
    int max = 32768, min = -32767, arraySize = 300;
    int *arrayA = ARRAY_GENERATOR(max, min, arraySize);

    MERGE_SORT(arrayA, 0, arraySize-1);

    for(int i=0;i<arraySize;i++)
        printf("%d, ", arrayA[i]);

    free(arrayA);
    return 0;
}