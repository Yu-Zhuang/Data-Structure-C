#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>
// DEFINE
#define VAL_SIZE 20
// STRUCT
typedef struct tr{
	char val[VAL_SIZE];
	struct tr *left, *right;
}NODE;
// FUNCTION ANNOUNCEMENT
void TREE_INIT_NODE(NODE **node);
void TREE_INSERT(NODE *root, char *element);
void TREE_PRINT(NODE *root);
// MAIN
int main(void){
// variable annoucement  
	char input[][VAL_SIZE]= { "321","543","123","765","234","432","756" };
	NODE *root;
// initialize root of tree
	TREE_INIT_NODE(&root);
// insert element to tree
	for(int i=0;i<7;i++) TREE_INSERT(root, input[i]);
// print tree
	TREE_PRINT(root);
// END
    return 0;  
}
// FUNCTION
// insert element to tree function
void TREE_INSERT(NODE *root, char *element){
	//tree is empty
	if( ! root->val[0]) strcpy(root->val, element);
	else{
		//variable annoucement
		int flag=1;
		NODE *newnode, 
			 *tmp=root; 
		// initialize variable
		TREE_INIT_NODE(&newnode);
		strcpy(newnode->val, element);
		// insert compution 
		while(flag){
			// if element > val
			if( strcmp(tmp->val, element) < 0 ){
				if(tmp->right == NULL) { tmp->right=newnode; return; }
				tmp=tmp->right; continue;
			// if element < val
			}else if( strcmp(tmp->val, element) > 0 ){
				if(tmp->left == NULL) { tmp->left=newnode; return; }
				tmp=tmp->left; continue;
			// if element == val
			}else printf("\n\t| Data already exist! |\n");
		}
	}
}
// initialize node
void TREE_INIT_NODE(NODE **node){
	*node=(NODE*)malloc(sizeof(NODE));
	memset((*node)->val,'\0',VAL_SIZE); (*node)->left=NULL; (*node)->right=NULL;
}
// inorder print tree
void TREE_PRINT(NODE *root){
	if(root!=NULL){
		TREE_PRINT(root->left);
		printf("[%s]->", root->val);
		TREE_PRINT(root->right);
	}
}