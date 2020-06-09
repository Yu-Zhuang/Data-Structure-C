# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define IS ==
# define IS_NOT !=
# define AND &&
# define OR ||

void GET_CHOSE(int *chose){
    printf("\n\n\t@ Sorting @\n(1) Quick sort (rand 1 pivot)\n(2) Quick sort (check 3 item to get pivot)\n(3) Merge sort\n(4) Bubble sort\n(5) Shell sort\n(6) Heap sort\n(7) Compare each method\n(8) Change condition\n(0) END\nEnter chose: ");
    scanf("%d", chose); 
    getchar();
}

void CHANGE_CONDITION(int *max, int *min, int *arraySize){
    do{
        printf("enter new \"min\" \"max\" \"arraySize\" : ");
        scanf("%d %d %d", min, max, arraySize);
        if(max[0] <= min[0])
            printf("\t[ \"max\" should larger than \"min\" ! ]\n");
    }while(max[0] <= min[0]);
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
        if((i+1)%10 IS 0)
            printf("\n");
    }
}

void RESULT_PRINT(int *arrayA, int arraySize, int cTimes, int max, int min, int chose){
    ARRAY_PRINT(arrayA, arraySize);
    printf("\n\t# Condition:\n\t\t* array size: %d\n\t\t* number range: %d ~ %d\n\t\t* sorting method: ", arraySize, min, max);
    switch(chose){
        case 1: printf("Quick sort (rand 1 pivot)\n"); break;
        case 2: printf("Quick sort (check 3 item to get pivot)\n"); break;
        case 3: printf("Merge sort\n"); break;
        case 4: printf("Bubble sort\n"); break;
        case 5: printf("Shell sort\n"); break;
        case 6: printf("Heap sort\n"); break;
        default: break;
    }
    printf("\n\t# Result: \n\t\t* Comparison times: %d\n", cTimes);
}

void SWAP(int *num_1, int *num_2){
    num_1[0] = num_2[0] + (num_2[0] = num_1[0]) - num_1[0];
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

void MERGE(int *nums, int s1, int e1, int s2, int e2, int *ct){
    int *ret = (int*)malloc(sizeof(int)*(e2-s1+1));
    int len_1 = e1 - s1 + 1, len_2 = e2 - s2 + 1;
    int i=0, j=0, n=0;
    while(i<len_1 OR j<len_2){
        if(j IS len_2){
            ret[n] = nums[s1+i];
            i++;            
        }
        else if(i IS len_1){
            ret[n] = nums[s2+j];
            j++; 
        }
        else if(nums[s1+i] < nums[s2+j]){
            ret[n] = nums[s1+i];
            i++;
            if(ct)
                ct[0]++;
        }
        else if(nums[s1+i] >= nums[s2+j]){
            ret[n] = nums[s2+j];
            j++;
            if(ct)   
                ct[0]++;         
        }
        n++;             
    }
    for(int m=0;m<e2-s1+1; m++)
        nums[s1+m] = ret[m];
    
    free(ret);
}

void MERGE_SORT(int *nums, int start, int end, int *ct){
    if(start >= end)
        return;
    MERGE_SORT(nums, start, (start+end)/2, ct);
    MERGE_SORT(nums, (start+end)/2+1, end, ct);
    MERGE(nums, start, (start+end)/2, (start+end)/2+1, end, ct);
}

void PIVOT_SET(int *nums, int left, int right, int chose, int *ct){
    int pivot = 0;
    if(chose IS 1)
        pivot = rand()%(right-left+1)+left;
    else{
        if(right - left > 3)
            MERGE_SORT(nums, (right+left)/2-1, (right+left)/2+1, ct);
        pivot = (right+left)/2;
    }
    SWAP(&nums[left], &nums[pivot]);
}

void QUICK_SORT(int *nums, int left, int right, int *ct, int chose){
    if(left < right){
        PIVOT_SET(nums, left, right, chose, ct);  // set pivot to left
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

void SHELL_SORT(int *nums, int numsSize, int *cTimes){
    int space = numsSize/2;
    while(space IS_NOT 1){
        for(int i=0;i<numsSize-space;i++,cTimes[0]++){
            if(nums[space+i] < nums[i])
                SWAP(&nums[space+i], &nums[i]);
        }
        space /= 2;
    }
    int tmp = 0;
    for(int i=1;i<numsSize;i++){
        tmp = i;
        for(int j=i-1;j>=0;j--, cTimes[0]++){
            if(nums[tmp] < nums[j])
                { SWAP(&nums[tmp], &nums[j]); tmp = j; }
            else
                break;
        }
    }
}

void RE_HEAP_UP(int *heap, int targetSite, int *cTimes){
    while(targetSite IS_NOT 0){
        if(cTimes)
            cTimes[0]++;
        int parent = (targetSite-1)/2;
        if(heap[parent] < heap[targetSite])
            SWAP(&heap[parent], &heap[targetSite]);
        else
            break;
        targetSite = parent; 
    }
}
void RE_HEAP_DOWN(int *heap, int parent, int heapSize, int *cTimes){
    while(parent < heapSize){
        int leftChild = parent*2+1,\
            rightChild = parent*2+2,\
            biggerChild = 0;
        if(cTimes)
            cTimes[0]++;
        // find bigger child
        if(leftChild < heapSize AND rightChild < heapSize)
            biggerChild = (heap[leftChild] > heap[rightChild]) ? leftChild : rightChild;
        else if(leftChild < heapSize)
            biggerChild = leftChild;
        else
            break;
        // if child > parent => exchange(child, parent)
        if(biggerChild < heapSize AND heap[parent] < heap[biggerChild]){
            SWAP(&heap[parent], &heap[biggerChild]);
            parent = biggerChild;
        }
        else
            break;
    }
}

void HEAP_SORT(int *nums, int numsSize, int *cTimes){
    // adjust array to heap
    for(int i=1;i<numsSize;i++)
        RE_HEAP_UP(nums, i, cTimes);          
    // heap sort
    for(int i=1;i<numsSize;i++){
        SWAP(&nums[0], &nums[numsSize-i]);
        RE_HEAP_DOWN(nums, 0, numsSize-i, cTimes);
    }
}

void COMPARE_RUN(int max, int min, int arraySize){
    int QS_1=0, QS_2=0, MS=0, BS=0, SS=0, HS=0;
    long long int BS_T = 0;
    double QS_1_R=0, QS_2_R=0, MS_R=0, BS_R=0, SS_R=0, HS_R=0;
    int round = 0;
    printf("how many round: ");
    scanf("%d", &round);
    for(int i=0;i<round;i++){
        int *arrayA = ARRAY_GENERATOR(max, min, arraySize);
        QUICK_SORT(arrayA, 0, arraySize-1, &QS_1, 1);
        free(arrayA);
    }
    for(int i=0;i<round;i++){
        int *arrayA = ARRAY_GENERATOR(max, min, arraySize);
        QUICK_SORT(arrayA, 0, arraySize-1, &QS_2, 2);
        free(arrayA);
    }
    for(int i=0;i<round;i++){
        int *arrayA = ARRAY_GENERATOR(max, min, arraySize);
        MERGE_SORT(arrayA, 0, arraySize-1, &MS);
        free(arrayA);
    }
    for(int i=0;i<round;i++){
        int *arrayA = ARRAY_GENERATOR(max, min, arraySize);
        BUBBLE_SORT(arrayA, 0, arraySize-1, &BS);
        BS_T += BS;
        BS = 0;
        free(arrayA);
    }
    for(int i=0;i<round;i++){
        int *arrayA = ARRAY_GENERATOR(max, min, arraySize);
        SHELL_SORT(arrayA, arraySize, &SS);
        free(arrayA);
    }
    for(int i=0;i<round;i++){
        int *arrayA = ARRAY_GENERATOR(max, min, arraySize);
        HEAP_SORT(arrayA, arraySize, &HS);
        free(arrayA);
    }
    QS_1_R=(double)QS_1/round; QS_2_R=(double)QS_2/round; MS_R=(double)MS/round; BS_R=(double)BS_T/round;
    SS_R=(double)SS/round; HS_R=(double)HS/round; 
    printf("\n\t# Condition:\n\t\t* array size: %d\n\t\t* number range: %d ~ %d\n\t\t* sorting method: compare each sorting method\n\t\t* round: %d\n", arraySize, min, max, round);
    printf("\n\t# Result (average comparison times):\n\t\t* Quick sort (rand 1 pivot): %25lf\n\t\t* Quick sort (check 3 item to get pivot): %12lf\n\t\t* Merge sort: %40lf\n\t\t* Bubble sort: %39lf\n\t\t* Shell sort: %40lf\n\t\t* Heap sort: %41lf\n", QS_1_R, QS_2_R, MS_R, BS_R, SS_R, HS_R);
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
            case 5: SHELL_SORT(arrayA, arraySize, &cTimes); break;
            case 6: HEAP_SORT(arrayA, arraySize, &cTimes); break;
            case 7: COMPARE_RUN(max, min, arraySize); break;
            case 8: CHANGE_CONDITION(&max, &min, &arraySize); break;
            default: printf("\t[ warning : wrong input ]\n"); break;
        }
        if(chose>0 && chose<9){
            if(chose IS_NOT 7 AND chose IS_NOT 8){
                RESULT_PRINT(arrayA, arraySize, cTimes, max, min, chose);
                cTimes = 0;
            }
            tmp = arrayA;
            arrayA = ARRAY_GENERATOR(max, min, arraySize);
            free(tmp);
        }
    }

    free(arrayA);
    return 0;
}