# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include "subFunc.h"

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

void BST_CREATE(void *root, int N, int element){
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

void M_TREE_CREATE(void *root, int N, int element){
	printf("\n=====\tM_TREE_CREATE: %d| target: %d\t=====\n", N, element);
	M_TREE_NODE *tree = (M_TREE_NODE*)root;
	if(N IS_NOT 1){
		while(true){
			// print node
			M_TREE_NODE_PRINT(tree);
			if(tree->val[0] < 2){ 
				if(tree->val[0] IS 1){
					tree->val[2] = element;
					if(tree->val[1] > element)
						SWAP(&tree->val[1], &tree->val[2]);
				}
				else
					tree->val[1] = element; 
				tree->val[0]++; 
				M_TREE_NODE_PRINT(tree);
				return; 
			}
			else{ //  if(root->val[0] IS 2)
				if(tree->val[1] > element){
					printf("\t: go to left\n");
					if(tree->left IS NULL){
						tree->left = M_TREE_NODE_CREATE(element);
						M_TREE_NODE_PRINT(tree->left);
						return;
					}
					else
						tree = tree->left;
				}
				else if(tree->val[1] <= element AND tree->val[2] > element){
					printf("\t: go to mid\n");
					if(tree->mid IS NULL){
						tree->mid = M_TREE_NODE_CREATE(element);
						M_TREE_NODE_PRINT(tree->mid);
						return;
					}
					else
						tree = tree->mid;
				}
				else{
					printf("\t: go to right\n");
					if(tree->right IS NULL){
						tree->right = M_TREE_NODE_CREATE(element);
						M_TREE_NODE_PRINT(tree->right);
						return;
					}
					else
						tree = tree->right;
				}
			}
		}
	}
	else
		{ tree->val[0] += 1; tree->val[1] = element; M_TREE_NODE_PRINT(tree); return; }
	printf("\t[ warning : m-tree add false ]\n");
}

void INSERT(void *ret, int chose, int N, int element){
	switch(chose){
		case 1: ARRAY_CREATE(ret, N, element); break;
		case 2: BST_CREATE(ret, N, element); break;
		case 3: M_TREE_CREATE(ret, N, element); break;
		default: printf("\t[ warning : 404 ]\n"); break;
	}
}
void* FILE_GET(char *file, int N, int chose){
	FILE *fptr = fopen(file, "r");
	void *ret = HEAD_CREATE(chose, N);
	int take = 0;

	if(fptr)
		for(int i=0;i<N;i++){
			fscanf(fptr,"%d", &take);
			INSERT(ret, chose, i+1, take);
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
		cp+=3;
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

bool BST_BI_SEARCH(void *root, int target){
	BST_NODE *tree = (BST_NODE*)root;
	static int cp = 0;
	int ret = 0;
	cp++;
	while(tree IS_NOT NULL){
		cp+=3;
		if(tree->val IS target)
			{ ret = 1; break; }
		else if(tree->val > target)
			tree = tree->left;
		else
			tree = tree->right;
	}
	printf("========= Comparison times of biSearchBST: %d ============\n\n", cp);
	return ret;
}

M_TREE_NODE* M_TREE_MAX(M_TREE_NODE *node){
	M_TREE_NODE *ret = node;
	while(ret->right IS_NOT NULL)
		if(ret->right)
			ret = ret->right;
	return ret;
}
M_TREE_NODE* M_TREE_MIN(M_TREE_NODE *node){
	M_TREE_NODE *ret = node;
	while(ret->left IS_NOT NULL)
		if(ret->left)
			ret = ret->left;
	return ret;
}
void M_TREE_DELETE(M_TREE_NODE *node, int target){
	printf("Before delete: "); M_TREE_NODE_PRINT(node);
	// if node is not leaf
	if(node->left IS_NOT NULL){
		M_TREE_NODE *maxNode = M_TREE_MAX(node->left);
		for(int i=0;i<node->val[0];i++)
			if(node->val[i+1] IS target)
				node->val[i+1] = maxNode->val[maxNode->val[0]];
		if(node->val[1] > node->val[2]) 
			SWAP(&node->val[1], &node->val[2]);
		M_TREE_DELETE(maxNode, maxNode->val[maxNode->val[0]]);
	}	
	else if(node->right IS_NOT NULL){
		M_TREE_NODE *minNode = M_TREE_MIN(node->right);
		for(int i=0;i<node->val[0];i++)
			if(node->val[i+1] IS target)
				node->val[i+1] = minNode->val[1];
		if(node->val[1] > node->val[2]) 
			SWAP(&node->val[1], &node->val[2]);
		M_TREE_DELETE(minNode, minNode->val[1]);
	}
	else if(node->mid IS_NOT NULL){
		M_TREE_NODE *mxnNode;
		if(node->val[1] IS target){ // target is small one
			mxnNode = M_TREE_MIN(node->mid);
			for(int i=0;i<node->val[0];i++)
				if(node->val[i+1] IS target)
					node->val[i+1] = mxnNode->val[mxnNode->val[0]];
		}
		else{
			mxnNode = M_TREE_MAX(node->mid);
			for(int i=0;i<node->val[0];i++)
				if(node->val[i+1] IS target)
					node->val[i+1] = mxnNode->val[1];			
		}
		if(node->val[1] > node->val[2]) 
			SWAP(&node->val[1], &node->val[2]);
		M_TREE_DELETE(mxnNode, mxnNode->val[1]);
	}
	// if node is leaf
	else{
		if(node->val[0] IS 1){
			M_TREE_NODE *tmp = node;
			TO_NULL(&node);
			free(tmp);
		}
		else{
			node->val[0] -= 1;
			if(node->val[1] IS target)
				node->val[1] = node->val[2];
		}
	}
	printf("After delete: "); M_TREE_NODE_PRINT(node);
}

bool M_TREE_SEARCH(void *root, int target){
	M_TREE_NODE *tree = (M_TREE_NODE*)root;
	static int cp = 0;
	int ret = 0;
	while(tree IS_NOT NULL){
		cp ++;
		for(int i=0;i<tree->val[0];i++)
			if(tree->val[i+1] IS target)
				{ ret = 1; M_TREE_DELETE(tree, target); break; }
		if(tree->val[1] > target)
			tree = tree->left;
		else if(tree->val[1] <= target AND tree->val[2] > target)
			tree = tree->mid;
		else
			tree = tree->right;
	}
	printf("========= Comparison times of serch_M_Tree: %d ============\n\n", cp);
	return ret;
}

int main(void){
	srand(time(NULL));
	char file[] = "DB.cpp";
	int chose = 3;
	int intergerNum = 500;
	void *data = NULL;

	//FILE_CREATE(file, intergerNum);
	data = FILE_GET(file, intergerNum, chose);

	if(M_TREE_SEARCH(data, -473))
		printf("find\n");
	else
		printf("not found\n");

	free(data);
	return 0;
}