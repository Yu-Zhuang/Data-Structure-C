# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

# define AND &&
# define OR ||
# define IS ==
# define IS_NOT !=

typedef struct t{
	int val;
	struct t *left, *right;	
}BST_NODE;

// create a file which contain 500 interger
void FILE_CREATE(char *file, int N){
	FILE *fptr = fopen(file, "w");
	if(fptr){
		int cnt[2] = {1,-1};
		for(int i=0;i<N;i++)
			fprintf(fptr,"%d\n", rand()%10001*cnt[rand()%2]);
	}
	else
		printf("\t[ warning : can't open the file ]\n");
	fclose(fptr);
}

void* HEAD_CREATE(int chose, int N){
	switch(chose){
		// (1) create array
		case 1: { int *ret = (int*)malloc(sizeof(int)*N); return ret; }
		// (2) create BST
		case 2: { BST_NODE *ret = (BST_NODE*)malloc(sizeof(BST_NODE));\
				ret->left = NULL; ret->right = NULL; return ret; }

		default: printf("\t[ warning : wrong input ]\n"); break;
	}
	return NULL;
}

void ARRAY_CREATE(void *nums, int N, int element){
	int *array = (int*)nums;
	int i = 0, tmp = 0;
	static int cp = 0, mv = 0;
	// find the site to insert
	for(i=0;i<N;i++,cp++)
		if(element < array[i]) break;
	cp++;
	// insert element
	if(i == N)
		{ mv++; array[i-1] = element; }
	else{
		for(int j=i;j<N;j++,mv++,cp++){
			tmp = array[j];
			array[j] = element;
			element = tmp;
		}
	}
	// output comparison and movement times
	for(int k=0;k<N;k++)
		{ printf("%5d,", array[k]); if((k+1)%10 IS 0 AND k IS_NOT 0) printf("\n"); }
	printf("\n=============== \tcp:%d\tmv:%d\t=====================\n\n", cp, mv);
}

BST_NODE* BST_NODE_CREATE(int element){
	BST_NODE *ret = (BST_NODE*)malloc(sizeof(BST_NODE));
	ret->val = element; ret->left = NULL; ret->right = NULL;
	return ret;
}
void BST_IN_ORDER(BST_NODE *root){
	if(root){
		BST_IN_ORDER(root->left);
		printf("%d,", root->val);
		BST_IN_ORDER(root->right);
	}
}
void BST_CREATE(void *root, int N,int element){
	BST_NODE *tree = (BST_NODE*)root;
	static int cp = 0, mv = 0;
	cp+=1; // 判斷
	if(N IS 1)
		tree->val = element;
	else{
		while(true){
			cp+=3;
			if(element < tree->val){
				if(tree->left IS NULL){
					tree->left = BST_NODE_CREATE(element);
					break;
				}
				else
					tree = tree->left;
			}
			else{
				if(tree->right IS NULL){
					tree->right = BST_NODE_CREATE(element);
					break;
				}
				else
					tree = tree->right;
			}
		}
	} 
	mv++;
	BST_IN_ORDER((BST_NODE*)root);
	printf("\n=============== \tcp:%d\tmv:%d\t=====================\n\n", cp, mv);
}

void INSERT(void *ret, int chose, int N, int element){
	switch(chose){
		case 1: ARRAY_CREATE(ret, N, element); break;
		case 2: BST_CREATE(ret, N, element); break;
		default: printf("\t[ warning : 404 ]\n"); break;
	}
}

void* FILE_GET(char *file, int N, int chose){
	FILE *fptr = fopen(file, "r");
	void *ret = HEAD_CREATE(chose, N);

	if(fptr){
		int take = 0;

		for(int i=0;i<N;i++){
			fscanf(fptr,"%d", &take);
			INSERT(ret, chose, i+1, take);
		}
	}
	else
		printf("\t[ warning : can't open the file ]\n");
	return ret;
}

bool ARRAY_BI_SEARCH(void *nums, int start, int end, int target){
	static int cp = 0, ret = 0;
	int *array = (int*)nums;
	cp++;
	while(start IS_NOT (start+end)/2){
		cp++;
		if(array[(start+end)/2] IS target)
			{ ret = 1; break; }
		else if(array[(start+end)/2] < target)
			start = (start+end)/2;
		else
			end = (start+end)/2;
	}
	printf("========= Comparison times of biSearchArray: %d ============\n\n", cp);
	return ret;
}

int main(void){
	srand(time(NULL));
	char file[] = "DB.cpp";
	int chose = 1;
	int intergerNum = 500;
	void *data = NULL;

	//FILE_CREATE(file, intergerNum);
	data = FILE_GET(file, intergerNum, chose);
	if(ARRAY_BI_SEARCH(data, 0, intergerNum-1, 4933))
		printf("find\n");
	else
		printf("not found\n");

	free(data);
	return 0;
}