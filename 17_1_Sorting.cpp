# include <stdio.h>
# include <stdlib.h>
# include <time.h>

void GET_CHOSE(int *chose){
    printf("\n\t@ Sorting @\n(1) Quick sort (rand 1 pivot)\n(2) Quick sort (check 5 item to get pivot)\n(3) Merge sort\n(4) Bubble sort\nEnter chose: ");
    scanf("%d", chose);
}

void RESULT_PRINT(int *arrayA, int arraySize, int cTimes, int max, int min, int chose){
    ARRAY_PRINT(arrayA, arraySize);
    printf("\n\t# Condition:\n\t\t* array size: %d\n\t\t* number range: %d ~ %d\n\t\t* sorting method: ", arraySize, min, max);
    switch(chose){
        case 1: printf("Quick sort (rand 1 pivot)\n"); break;
        case 2: printf("Quick sort (check 5 item to get pivot)\n"); break;
        case 3: printf("Merge sort\n"); break;
        case 4: printf("Bubble sort\n"); break;
        default: break;
    }
    printf("\n\t# Result: \n\t\t* Comparison times: %d\n", cTimes);
}

void SWAP(int *num_1, int *num_2){
    num_1[0] = num_2[0] + (num_2[0] = num_1[0]) - num_1[0];
}

int* ARRAY_GENERATOR(int max, int min, int numsSize){
    int *ret = (int*)malloc(sizeof(int)*numsSize);
    for(int i=0; i<numsSize; i++)
        ret[i] = rand()%(max-min+1)+min;
    return ret;
}

void ARRAY_PRINT(int *nums, int numsSize){
    printf("\n\t\t========= SORTED_ARRAY_PRINT ===========\n");
    for(int i=0;i<numsSize;i++){
        printf("%7d ", nums[i]);
        if((i+1)%10 == 0)
            printf("\n");
    }
}

void BUBBLE_SORT(int *nums, int left, int right, int *cp){
    bool flag = 1;
    for(int i=left;i<right&&flag;i++){
        flag = 0;
        for(int j=i;j<right+1;j++){
            if(cp != NULL)
                cp[0] ++;
            if(nums[i] > nums[j])
                { SWAP(&nums[i], &nums[j]); flag = 1; }
        }
    }
}

void PIVOT_SET(int *nums, int left, int right, int chose){
    int pivot = 0;
    if(chose == 1)
        pivot = rand()%(right-left+1)+left;
    else{
        if(right - left > 5)
            BUBBLE_SORT(nums, (right+left)/2-2, (right+left)/2+2, NULL);
        pivot = (right+left)/2;
    }
    SWAP(&nums[left], &nums[pivot]);
}

void QUICK_SORT(int *nums, int left, int right, int *ct, int chose){
    if(left < right){
        PIVOT_SET(nums, left, right, chose);  // set pivot to left
        int base=left, i=left, j=right+1;
        do{
            do {i++; ct[0]++;} while(nums[i]<nums[base] && i<=right); 
            do {j--; ct[0]++;} while(nums[j]>nums[base] && j>left); 
            if(i<j) SWAP(&nums[i], &nums[j]);
        }while(i<j);
        SWAP(&nums[base], &nums[j]);
        QUICK_SORT(nums, left, j-1, ct, chose);
        QUICK_SORT(nums, j+1, right, ct, chose);
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
    srand(time(NULL));  
    int max = 32768, min = -32767, arraySize = 1000, cTimes = 0, chose = 1;
    int *arrayA = ARRAY_GENERATOR(max, min, arraySize), *tmp;

    while(chose != 0){
        GET_CHOSE(&chose);
        switch(chose){
            case 0: printf("\n\t[ END ]\n"); break;
            case 1: case 2: QUICK_SORT(arrayA, 0, arraySize-1, &cTimes, chose); break;
            case 3: MERGE_SORT(arrayA, 0, arraySize-1, &cTimes); break;
            case 4: BUBBLE_SORT(arrayA, 0, arraySize-1, &cTimes); break;
            default: printf("\t[ warning : wrong input ]\n"); break;
        }
        if(chose>0 && chose<5){
            RESULT_PRINT(arrayA, arraySize, cTimes, max, min, chose);
            tmp = arrayA;
            arrayA = ARRAY_GENERATOR(max, min, arraySize);
            free(tmp);
            cTimes = 0;
        }
    }

    free(arrayA);
    return 0;
}