# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define IS ==
# define IS_NOT !=
# define AND &&
# define OR ||

void CHANGE_CONDITION(int *max, int *min, int *arraySize, int *round){
    do{
        printf("enter new \"min\" \"max\" \"arraySize\" \"round\": ");
        scanf("%d %d %d %d", min, max, arraySize, round);
        if(max[0] <= min[0])
            printf("\t[ \"max\" should larger than \"min\" ! ]\n");
        if(round[0] < 1)
            printf("\t[ \"round\" should larger than 0 ! ]\n");
    }while(max[0] <= min[0] || round[0] < 1);
}

void ARRAY_PRINT(int *nums, int numsSize){
    printf("\n\t\t========= SORTED_ARRAY_PRINT ===========\n");
    for(int i=0;i<numsSize;i++){
        printf("%7d ", nums[i]);
        if((i+1)%10 IS 0)
            printf("\n");
    }
}

void RESULT_PRINT(int *arrayA, int arraySize, int cTimes, int max, int min){
    ARRAY_PRINT(arrayA, arraySize);
    printf("\n\t# Condition:\n\t\t* array size: %d\n\t\t* number range: %d ~ %d\n\t\t* sorting method: Heap sort\n", arraySize, min, max);
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

void RUN(int max, int min, int arraySize, int cTimes, int round){
    int *Array;
    long long int totolTimes = 0;
    for(int i=0;i<round;i++){
        Array = ARRAY_GENERATOR(max, min, arraySize);
        HEAP_SORT(Array, arraySize, &cTimes);
        RESULT_PRINT(Array, arraySize, cTimes, max, min);
        totolTimes += cTimes;
        cTimes = 0;
    }
    printf("\n\t================================================================\n");
    printf("\n\t# Result in %d round:\n\t\t* average comparison times: %lf\n", round, (double)totolTimes/round);
    free(Array);
}

int main(void){
    srand(time(NULL));  
    int max = 32768, min = -32767, arraySize = 10, cTimes = 0, chose = 1, round = 1;

    while(chose){
        printf("\n\t@ Heap Sort @\n(1) change condition\n(2) run\n(0) END\nenter chose: ");
        scanf("%d", &chose);
        switch(chose){
            case 1: CHANGE_CONDITION(&max, &min, &arraySize, &round); break;
            case 2: RUN(max, min, arraySize , cTimes, round); break;
            case 0: printf("\n\t[ end experiment ]\n"); break;
            default: printf("\n\t[ wrong input ! ]\n"); break;
        }
    }

	return 0;
}

