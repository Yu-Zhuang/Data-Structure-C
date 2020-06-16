# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

# define TRUE 1
# define FALSE 0
# define IS ==
# define OR ||
# define AND &&
# define IS_NOT !=

void DB_GENERATOR(char *file, int max, int min, int numsSize){
	FILE *fptr = fopen(file, "wb");
	if(fptr IS_NOT NULL){
		int take = 0;
	    for(int i=0; i<numsSize; i++){
	    	take = rand()%(max-min+1)+min;
	    	fwrite(&take, sizeof(take), 1, fptr);
	    }
	}
	else
		printf("Can't open %s\n", file);
    fclose(fptr);
}

void DB_SUB_GENERATOR(char *DB, char *subDB){
	FILE *db = fopen(DB, "rb");
	FILE *sub = fopen(subDB, "wb");
	if(db IS_NOT NULL AND sub IS_NOT NULL){
		int take = 0;
		while( fread(&take, sizeof(take),1,db) IS 1){
			fprintf(sub, "%d\n", take);
		}
	}
	else
		printf("can't open the file\n");
	fclose(db);
	fclose(sub);
}

void SWAP(int *n1, int *n2){
	n1[0] = n2[0] + (n2[0] = n1[0]) - n1[0];
}

void FILE_READ(char *file){
	FILE *fptr = fopen(file,"r");
	int take = 0;
	while( fscanf(fptr, "%d", &take) IS_NOT EOF)
		printf("%d\n", take);
}

void RE_HEAP_DOWN(int *heap, int parent, int heapSize){
    while(parent < heapSize){
        int leftChild = parent*2+1,\
            rightChild = parent*2+2,\
            smallerChild = 0;
        // find bigger child
        if(leftChild < heapSize AND rightChild < heapSize)
            smallerChild = (heap[leftChild] < heap[rightChild]) ? leftChild : rightChild;
        else if(leftChild < heapSize)
            smallerChild = leftChild;
        else
            break;
        // if child > parent => exchange(child, parent)
        if(smallerChild < heapSize AND heap[parent] > heap[smallerChild]){
            SWAP(&heap[parent], &heap[smallerChild]);
            parent = smallerChild;
        }
        else
            break;
    }
}

void RE_HEAP_UP(int *heap, int targetSite){
    while(targetSite IS_NOT 0){
        int parent = (targetSite-1)/2;
        if(heap[parent] > heap[targetSite])
            SWAP(&heap[parent], &heap[targetSite]);
        else
            break;
        targetSite = parent; 
    }
}

void HEAP_SORT(int *heap, int heapSize){       
    for(int i=1;i<heapSize;i++){
        SWAP(&heap[0], &heap[heapSize-i]);
        RE_HEAP_DOWN(heap, 0, heapSize-i);
    }
}

char* FILE_NAME_GET(int *fileNum){
	char *file = (char*)malloc(sizeof(char)*25);
	char subTitle[] = ".cpp";
	sprintf(file, "%d", fileNum[0]);
	strcat(file, subTitle);
	return file;
}

void MERGE_N_FILE(int N){
	if(N>1){
		int tn;
		for(int i=0;i<N;i+=2){
			int tx = i, ty = i+1;
			char *f1 = FILE_NAME_GET(&tx), \
				 *f2 = FILE_NAME_GET(&ty);
			FILE *F1 = fopen(f1, "r"), *F2 = fopen(f2, "r"), *F3 = fopen("F3.cpp", "w");
			if(F1 IS_NOT NULL AND F2 IS_NOT NULL){
				int flag_1 = 1, flag_2 = 1;
				int num_1=0, num_2=0;
				if(fscanf(F1, "%d", &num_1) IS EOF)
					flag_1 = 0;
				if(fscanf(F2, "%d", &num_2) IS EOF)
					flag_2 = 0;
				while(flag_1 OR flag_2){
					if(flag_1 AND flag_2){
						if(num_1 < num_2){
							fprintf(F3, "%d\n", num_1);
							if(fscanf(F1, "%d", &num_1) IS EOF)
								flag_1 = 0;							
						}
						else{
							fprintf(F3, "%d\n", num_2);
							if(fscanf(F2, "%d", &num_2) IS EOF)
								flag_2 = 0;								
						}
					}else if(flag_1){
						fprintf(F3, "%d\n", num_1);
						if(fscanf(F1, "%d", &num_1) IS EOF)
							flag_1 = 0;						
					}
					else if(flag_2){
						fprintf(F3, "%d\n", num_2);
						if(fscanf(F2, "%d", &num_2) IS EOF)
							flag_2 = 0;							
					}
				}
			}
			if(F2 IS NULL){
				fclose(F1);
				fclose(F2);
				fclose(F3);
				remove(f2);
				tn = i/2;
				const char *newFile = FILE_NAME_GET(&tn);
				if(rename(f1, newFile) IS_NOT 0)
					printf("rename failed\n");				
			}
			else{
				fclose(F1);
				fclose(F2);
				fclose(F3);
				remove(f1);
				remove(f2);
				tn = i/2;
				const char *newFile = FILE_NAME_GET(&tn);
				const char oldFile[] = "F3.cpp";
				if(rename(oldFile, newFile) IS_NOT 0)
					printf("rename failed\n");					
			}			
		}
		MERGE_N_FILE(N/2+N%2);
	}
}

int EXTERNAL_METHOD(char *file, int fileSize, int heapSize){
	if(fileSize <= heapSize){
		printf("size of file is too small\n");
		return 0;
	}
	int *heap = (int*)malloc(sizeof(int)*heapSize);
	int progress = 100, fileNum = 0, take = 0, pre = 0, flag = 1, end = 0, oriSize = heapSize;
	char *newFile;
	FILE *fptr = fopen(file, "rb");
	if(fptr IS_NOT NULL){
		// initial heap
		for(int i=0;i<heapSize;i++){
			if( fread(&take, sizeof(int), 1, fptr) IS 1){
				heap[i] = take;
				RE_HEAP_UP(heap, i);
			}
			else
				printf("can't read file\n");
		}
		// make initial file
		newFile = FILE_NAME_GET(&fileNum);
		FILE *nfptr = fopen(newFile, "w");
		if(nfptr){ // put first element to file
			fprintf(nfptr, "%d\n", heap[0]);
			pre = heap[0];
		}
		else
			printf("can't create new file\n");
		// get every num in DB
		while( end IS_NOT TRUE){
			fread(&take, sizeof(int), 1, fptr);
			progress ++;
			if(progress IS fileSize){ //讀檔結束
				heap[0] = take;
				heapSize = oriSize;
				for(int i=0;i<heapSize;i++) // 調整成完整heap
					RE_HEAP_UP(heap, i);
				HEAP_SORT(heap, heapSize); // 排序 (大->小);
				if(heap[heapSize-1] >= pre){		
					for(int i=heapSize-1;i>=0;i--)
						fprintf(nfptr, "%d\n", heap[i]);
				}
				else{
					fclose(nfptr);
					fileNum++;
					newFile = FILE_NAME_GET(&fileNum);
					nfptr = fopen(newFile, "w");
					for(int i=heapSize-1;i>=0;i--)
						fprintf(nfptr, "%d\n", heap[i]);
				}
				end = 1;
			}
			else{
				heap[0] = take;
				RE_HEAP_DOWN(heap, 0, heapSize);
				while(flag IS_NOT 0){
					if(heap[0] >= pre){
						fprintf(nfptr,"%d\n", heap[0]);
						pre = heap[0];
						flag = 0;
					}
					else{
						SWAP(&heap[0], &heap[heapSize-1]);
						heapSize -= 1;
						if(heapSize IS_NOT 0)
							RE_HEAP_DOWN(heap, 0, heapSize);
						else{
							fclose(nfptr);
							fileNum ++;
							newFile = FILE_NAME_GET(&fileNum);
							nfptr = fopen(newFile, "w");	
							heapSize = oriSize;
							for(int i=0;i<heapSize;i++)
								RE_HEAP_UP(heap, i);
							fprintf(nfptr,"%d\n", heap[0]);
							pre = heap[0];
							flag = 0;										
						}
					}
				}
				flag = 1;
			}
		}
		fclose(nfptr);		
	}
	else
		printf("can't open %s\n", file);
	fclose(fptr);
	return fileNum+1;
}

void INTERNAL_METHOD(char *file, int fileSize, int heapSize){
	if(fileSize <= heapSize){
		printf("size of file is too small\n");
		return ;
	}
	int *heap = (int*)malloc(sizeof(int)*heapSize);
	FILE *fptr = fopen(file, "rb");
	int progress = 0, take = 0;
	char *newFile;
	if(fptr){
		for(int i=0;i<fileSize;i+=heapSize){
			for(int j=0;j<heapSize;j++){
				if( fread(&take, sizeof(int), 1, fptr) IS 1){
					heap[j] = take;
					RE_HEAP_UP(heap, j);
				}
				else
					printf("can't read file\n");
			}
			HEAP_SORT(heap, heapSize);
			newFile = FILE_NAME_GET(&progress);
			progress ++;
			FILE *nfptr = fopen(newFile, "w");
			if(nfptr){
				for(int m=heapSize-1;m>=0;m--)
					fprintf(nfptr, "%d\n", heap[m]);
			}else{
				printf("can't create new file\n");
				break;
			}
			fclose(nfptr);
		}		
	}
	else{
		printf("can't open %s\n", file);
	}
	fclose(fptr);
}

int main(void){
	char DB[] = "DB.cpp", subDB[]="subDB.cpp";
	double START = 0, MED = 0, END = 0;
	int max = 32767, min = -32768, numsSize = 5000;
	int heapSize = 100;
	int fileNum = numsSize/heapSize;

	DB_GENERATOR(DB, max, min, numsSize);
	//DB_SUB_GENERATOR(DB, subDB);

	START = clock();
	INTERNAL_METHOD(DB, numsSize, heapSize);
	MED = clock();
	// merge all file
	MERGE_N_FILE(fileNum);
	END = clock();
	printf("\n\t@ internal @\n\t\t# heap spend:  %lf s\n\t\t# merge spend: %lf s\n\t\t# total spend: %lf s\n\t\t# file num: %d\n", (MED-START)/CLOCKS_PER_SEC,(END-MED)/CLOCKS_PER_SEC,(END-START)/CLOCKS_PER_SEC, fileNum );

	START = clock();
	fileNum = EXTERNAL_METHOD(DB, numsSize, heapSize);
	MED = clock();
	// merge all file
	MERGE_N_FILE(fileNum);
	END = clock();
	printf("\n\t@ external @\n\t\t# heap spend:  %lf s\n\t\t# merge spend: %lf s\n\t\t# total spend: %lf s\n\t\t# file num: %d\n", (MED-START)/CLOCKS_PER_SEC,(END-MED)/CLOCKS_PER_SEC,(END-START)/CLOCKS_PER_SEC, fileNum );
	return 0;
}