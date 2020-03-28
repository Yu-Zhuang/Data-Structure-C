#include<stdio.h>
#include<stdlib.h>

typedef struct tree{ //tree
    int val, lbit, rbit;
    struct tree *lchild, *rchild;
}BiTree;
typedef struct quene{ //quene
    int data;
    struct quene *next;
}Quene;

void insertTree (BiTree*,Quene*,int); //insert element in tree;
void PreorderSearch (BiTree*, int); //search element in tree (Preorder;
void PrintTree (BiTree*); //print tree (preorder, inorder, postorder);
void preorder(BiTree*);void inorder(BiTree*);void postorder(BiTree*);

void Enquene (Quene*,int); //enquene;
void Dequene (Quene*); //dequene;

BiTree* ptr; //ptr==current (當前要加入element的parent);

int main(void){ //main
    BiTree *root=(BiTree*)malloc(sizeof(BiTree));
    Quene *quene=(Quene*)malloc(sizeof(Quene));
    int list[7],i;
    
    for(i=0;i<7;i++) list[i]=1+i; //初始化要存入binary tree的資料list[];

    quene->data=NULL; quene->next=NULL; //初始化 quene and root;
    root->val=-1;
    
    for(i=0;i<7;i++) insertTree(root,quene,list[i]);//construct binary tree;
    PrintTree(root);//print binary tree (preorder, inorder, postorder);

    return 0; //end;
}
//function:
void insertTree(BiTree* tree,Quene* Q,int num){//insert element in tree
    int flag=1;
    if(tree->val==-1){ //if tree is empty;
        tree->val=num;
        tree->lbit=0; tree->rbit=0;
        tree->lchild=NULL; tree->rchild=NULL;
        Enquene(Q,num);
    }else{
        while(flag){ //執行至 已加入element後才停止;
            PreorderSearch(tree, Q->next->data);//找要加element的parent;
            if(ptr->lbit==0){ //左子樹empty 時執行;
                BiTree* newchild=(BiTree*)malloc(sizeof(BiTree));
                newchild->val=num; //建新樹;
                newchild->lbit=0; newchild->rbit=0;
                newchild->lchild=NULL; newchild->rchild=NULL;
                ptr->lchild=newchild; //左子樹接newchild;
                ptr->lbit=1;
                Enquene(Q,num); //將element也放入quene中 待之後搜尋current;
                flag=0;
            }else if(ptr->rbit==0){ //右子樹empty 時執行;
                BiTree* newchild=(BiTree*)malloc(sizeof(BiTree));
                newchild->val=num;
                newchild->lbit=0; newchild->rbit=0;
                newchild->lchild=NULL; newchild->rchild=NULL;
                ptr->rchild=newchild;
                ptr->rbit=1;
                Enquene(Q,num);
                flag=0;
            }else Dequene(Q); //左右皆有子樹, 則dequene, 往下尋找;
        }
    }
}
void PreorderSearch (BiTree* tree, int num){ //search tree
    if(tree!=NULL){
        if(tree->val==num) {ptr=tree;goto end;}
        PreorderSearch(tree->lchild,num);
        PreorderSearch(tree->rchild,num);
    }
    end: ;
}
void PrintTree (BiTree* tree){ //print tree (preorder
    printf("preorder: "); preorder(tree);
    printf("\ninorder: "); inorder(tree);
    printf("\npostorder: "); postorder(tree); printf("\n");
}
//quene
void Enquene (Quene* Q,int n){
    Quene *newnode=(Quene*)malloc(sizeof(Quene));
    newnode->data=n;
    while(Q->next!=NULL) Q=Q->next;
    newnode->next=Q->next;
    Q->next=newnode;
}
void Dequene (Quene* Q){
    Q->next=Q->next->next;
}
//order
void preorder(BiTree* tree){
    if(tree!=NULL){
        printf("%d ",tree->val); preorder(tree->lchild); preorder(tree->rchild);
    }
}
void inorder(BiTree* tree){
    if(tree!=NULL){
        inorder(tree->lchild); printf("%d ",tree->val); inorder(tree->rchild);
    }
}
void postorder(BiTree* tree){
    if(tree!=NULL){
        postorder(tree->lchild); postorder(tree->rchild); printf("%d ",tree->val);
    }
}

/*
利用quene照順序儲存 要加入element的parent node;
需改進空間:
 1. quene沒有真的dequene, 因此每次加element後還需再從頭dequene;
 2. 函數: PreorderSearch 要如何在找到node後 即停止繼續尋找;
 3. 每次PreorderSearch都要從頭開始找;
 4. 二元樹的刪除函數;
已解決:
 1. 因為Q=Q->next無法作用, 只有Q->next=Q->next->next可以作用,
 因此將quene第一個位置不要存資料, 讀取也從第二個開始;
 2. 用goto end; (end設在if外面)便可解決,
 以此例為例呼叫PreorderSearch次數從66次降為36次;

 
 */

============ 做修改後版本 =================
#include<stdio.h>
#include<stdlib.h>

typedef struct tree{ //tree
    int val; //值;
    struct tree *lchild, *rchild; //左右子樹;
}BiTree;
typedef struct quene{ //quene
    int data;
    struct quene *next;
}Quene;

void insertTree (BiTree*,Quene*,int); //insert element in tree;
void PreorderSearch (BiTree*, int); //search element in tree (Preorder;
void PrintTree (BiTree*); //print tree (preorder, inorder, postorder);
void preorder(BiTree*);void inorder(BiTree*);void postorder(BiTree*); //for print;

void Enquene (Quene*,int); //enquene;
void Dequene (Quene*); //dequene;

BiTree* ptr=NULL; //ptr==current (ptr用來指向:當前要加入element的parent);

int main(void){ //main
    BiTree *root=(BiTree*)malloc(sizeof(BiTree));
    Quene *quene=(Quene*)malloc(sizeof(Quene));
    int list[7],i;
    for(i=0;i<7;i++) list[i]=1+i; //初始化要存入binary tree的資料list[];
    quene->next=NULL; //初始化 quene;
    
    for(i=0;i<7;i++) insertTree(root,quene,list[i]);//construct binary tree;
    PrintTree(root);//print binary tree (preorder, inorder, postorder);

    return 0; //end;
}
//insertTree function;
void insertTree(BiTree* tree,Quene* Q,int num){//insert element in tree
    if(ptr==NULL){ //if tree is empty;
        ptr=tree;
        tree->val=num;
        tree->lchild=NULL; tree->rchild=NULL;
        Enquene(Q,num);
    }else{
        PreorderSearch(tree, Q->next->data);//將ptr指向要加element的parent;
        if(ptr->lchild==NULL){ //左子樹empty 時執行;
            BiTree* newchild=(BiTree*)malloc(sizeof(BiTree)); //建新樹;
            newchild->val=num; newchild->lchild=NULL; newchild->rchild=NULL;
            ptr->lchild=newchild; //左子樹接newchild;
            Enquene(Q,num); //將element也放入quene中 待之後搜尋current;
        }else if(ptr->rchild==NULL){ //右子樹empty 時執行;
            BiTree* newchild=(BiTree*)malloc(sizeof(BiTree));
            newchild->val=num; newchild->lchild=NULL; newchild->rchild=NULL;
            ptr->rchild=newchild;
            Enquene(Q,num);
            Dequene(Q); //右子樹接完後左右皆有子樹,則dequene,往下一個要加子樹的parent;
        }
    }
}
void PreorderSearch (BiTree* tree, int num){ //將ptr指向要加element的parent;
    if(tree!=NULL){
        if(tree->val==num) {ptr=tree;goto end;} //找到後將ptr指向欲加子樹的node 並跳出遞迴;
        PreorderSearch(tree->lchild,num);
        PreorderSearch(tree->rchild,num);
    }
    end: ;
}
//quene;
void Enquene (Quene* Q,int n){
    Quene *newnode=(Quene*)malloc(sizeof(Quene));
    newnode->data=n;
    while(Q->next!=NULL) Q=Q->next;
    newnode->next=Q->next;
    Q->next=newnode;
}
void Dequene (Quene* Q){
    Q->next=Q->next->next;
}
//PrintTree
void PrintTree (BiTree* tree){ //print tree (preorder
    printf("preorder: "); preorder(tree);
    printf("\ninorder: "); inorder(tree);
    printf("\npostorder: "); postorder(tree); printf("\n");
}
void preorder(BiTree* tree){
    if(tree!=NULL){
        printf("%d ",tree->val); preorder(tree->lchild); preorder(tree->rchild);
    }
}
void inorder(BiTree* tree){
    if(tree!=NULL){
        inorder(tree->lchild); printf("%d ",tree->val); inorder(tree->rchild);
    }
}
void postorder(BiTree* tree){
    if(tree!=NULL){
        postorder(tree->lchild); postorder(tree->rchild); printf("%d ",tree->val);
    }
}
