
# define AND &&
# define OR ||
# define IS ==
# define IS_NOT !=

typedef struct t{
	int val;
	struct t *left, *right;	
}BST_NODE;
typedef struct mt{
	int val[3]; // 0: how many value; 1,2: val;
	struct mt *left, *mid, *right;
}M_TREE_NODE;

void FILE_CREATE(char *file, int N){
	FILE *fptr = fopen(file, "w");
	if(fptr){
		int cnt[2] = {1,-1};
		for(int i=0;i<N;i++)
			fprintf(fptr, "%d\n", i+1);
			//fprintf(fptr,"%d\n", rand()%10001*cnt[rand()%2]);
	}
	else
		printf("\t[ warning : can't open the file ]\n");
	fclose(fptr);
}

BST_NODE* BST_NODE_CREATE(int element){
	BST_NODE *ret = (BST_NODE*)malloc(sizeof(BST_NODE));
	ret->val = element; ret->left = NULL; ret->right = NULL;
	return ret;
}

M_TREE_NODE* M_TREE_NODE_CREATE(int element){
	M_TREE_NODE *ret = (M_TREE_NODE*)malloc(sizeof(M_TREE_NODE));
	ret->val[0] = 1;
	ret->val[1] = element;
	ret->left = NULL; ret->mid = NULL; ret->right = NULL;
	return ret;
}

void* HEAD_CREATE(int chose, int N){
	switch(chose){
		// (1) create array
		case 1: { int *ret = (int*)malloc(sizeof(int)*N); return ret; }
		// (2) create BST
		case 2: { BST_NODE *ret = BST_NODE_CREATE(0); return ret; }
		// (3) create m-tree
		case 3: { M_TREE_NODE *ret = M_TREE_NODE_CREATE(0); ret->val[0]=0; return ret; }
		default: printf("\t[ warning : wrong input ]\n"); break;
	}
	return NULL;
}

void BST_IN_ORDER(BST_NODE *root){
	if(root){
		BST_IN_ORDER(root->left);
		printf("%d,", root->val);
		BST_IN_ORDER(root->right);
	}
}

void SWAP(int *num1, int *num2){
	num1[0] = num2[0] + (num2[0] = num1[0]) - num1[0];
}

void M_TREE_NODE_PRINT(M_TREE_NODE *tree){
	if(tree IS NULL)
		{printf(" (empty)\n"); return;}
	if(tree->val[0] IS 0)
		{printf(" (empty)\n"); return;}
	for(int i=0;i<tree->val[0];i++)
		printf(" | %5d", tree->val[i+1]);
	printf(" |\n");
}

void TO_NULL(M_TREE_NODE **tree){
	tree[0] = NULL;
}

M_TREE_NODE* M_TREE_MAX(M_TREE_NODE *node){
	M_TREE_NODE *ret = node;
	while(ret->right IS_NOT NULL){
		if(ret->right->val[0] IS 0)
			break;
		if(ret->right)
			ret = ret->right;
	}
	return ret;
}
M_TREE_NODE* M_TREE_MIN(M_TREE_NODE *node){
	M_TREE_NODE *ret = node;
	while(ret->left IS_NOT NULL){
		if(ret->left->val[0] IS 0)
			break;
		if(ret->left)
			ret = ret->left;
	}
	return ret;
}

