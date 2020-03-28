#include<stdio.h>
#include<stdlib.h>

typedef struct bitree{//binary search tree;
    int val;
    struct bitree *left,*right;
}BiTree;

void insertBiTree(BiTree*,int); //big'one put in right,small'one put in left;
void printBiTree(BiTree*); //preorder;
void findBiTree(BiTree*,int); //output use ? step to find;

int main(void){
    BiTree *root=(BiTree*)malloc(sizeof(BiTree)); //variable annoucement;
    int list[7]={7,5,9,4,8,6,10}; //要存入樹中的資料;
    
    root->val=NULL; root->left=NULL; root->right=NULL; //initialization;
    for(int i=0;i<7;i++) printf("%d ",list[i]);printf("\n");
    
    for(int i=0;i<7;i++) insertBiTree(root,list[i]); //create a binary search tree;
    printBiTree(root);printf("\n"); //print tree;
    
    findBiTree(root,8); //find element;
    
    return 0;
}
void insertBiTree(BiTree* tree,int num){ //insert element in tree;
    if(!tree->val) tree->val=num; //if tree is empty;
    else{
        int flag=0; //用來判定往parent node的右或左加子樹;
        BiTree *ptr=NULL, *newnode=(BiTree*)malloc(sizeof(BiTree));
        newnode->val=num; newnode->left=NULL; newnode->right=NULL;
        
        while(tree){ //搜尋後以ptr指向欲加子樹的parent node;
            if(num==tree->val) {flag=0;break;} //已有該元素則跳出;
            else if(num>tree->val) {flag=1;ptr=tree;tree=tree->right;}
            else if(num<tree->val) {flag=2;ptr=tree;tree=tree->left;}
        }
        if(flag==1) ptr->right=newnode;
        else if(flag==2) ptr->left=newnode;
    }
}
void findBiTree(BiTree* tree,int num){ //find element in tree;
    int count=0;
    while(tree){
        if(num==tree->val) {printf("use %d step find it.\n", count);break;}
        else if(num>tree->val) tree=tree->right;
        else if(num<tree->val) tree=tree->left;
        count++;
    }
    if(!tree) printf("not found.\n"); //樹中都沒有該元素;
}
void printBiTree(BiTree* tree){ //print tree (preorder);
    if(tree){
        printf("%d ", tree->val);
        printBiTree(tree->left);
        printBiTree(tree->right);
    }
}
