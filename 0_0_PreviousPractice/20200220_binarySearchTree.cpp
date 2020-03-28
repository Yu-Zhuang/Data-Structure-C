#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct BiTr{
    int val;
    struct BiTr *right, *left;
}BiTree;

void insertTree(BiTree*,int);
void printTree(BiTree*);

int main(void){
    srand(time(NULL));
    int list[7]={0};
    BiTree *root=(BiTree*)malloc(sizeof(BiTree));
    root->val=NULL; root->right=NULL; root->left=NULL;

    printf("list: ");
    for(int i=0;i<7;i++) {list[i]=rand()%10; printf("%d ",list[i]);}
    printf("\n");

    printf("tree: ");
    for(int i=0;i<7;i++) insertTree(root,list[i]);
    printTree(root);

    return 0;
}
void insertTree(BiTree* tree,int num){
    if(!tree->val) tree->val=num;
    else{
        BiTree *newnode=(BiTree*)malloc(sizeof(BiTree));
        newnode->val=num; newnode->left=NULL; newnode->right=NULL;
        int flag=1;
        while(flag){
            if(num > tree->val && tree->right) tree=tree->right;
            else if(num <= tree->val && tree->left) tree=tree->left;
            else if(num > tree->val && !tree->right) {tree->right=newnode; flag=0;}
            else {tree->left=newnode; flag=0;}
        }
    }
    
}

void printTree(BiTree *tree){
    if(tree){
        printTree(tree->left);
        printf("%d ",tree->val);
        printTree(tree->right);
    }
}
