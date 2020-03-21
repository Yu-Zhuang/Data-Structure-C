#include<stdio.h>
#include<stdlib.h>
//Binary search tree struct 
typedef struct BT{
	int val;
	struct BT *left;
	struct BT *right;
}BiTree;
//function
void insertBT(BiTree *BT, int element);
void printBT(BiTree *BT); //inorder
//main ()
int main(void){
	int list[7]={3,5,2,7,1,4,9};
	BiTree *root=(BiTree*)malloc(sizeof(BiTree));
	root->val=NULL; root->left=NULL; root->right=NULL;
	//insert element to tree
	for(int i=0;i<7;i++) insertBT(root, list[i]);
	//print tree
	printBT(root); printf("\n");

	return 0;
}
void insertBT(BiTree *BT, int element){
	BiTree *Tptr=BT, *newnode=(BiTree*)malloc(sizeof(BiTree));
	newnode->val=element; newnode->right=NULL; newnode->left=NULL;
	if( ! BT->val) { BT->val=element; return; }
	else{
		while(1){
			if(element>Tptr->val && Tptr->right!=NULL) Tptr=Tptr->right;
			else if(element<Tptr->val && Tptr->left!=NULL) Tptr=Tptr->left;
			else if(element>Tptr->val) { Tptr->right=newnode; break; }
			else if(element<Tptr->val) { Tptr->left=newnode; break; }
			else break;
		}
	}
}
void printBT(BiTree *BT){
	if(BT!=NULL){
		printBT(BT->left);
		printf("%d->", BT->val);
		printBT(BT->right);
	}
}



