//  Copyright © 2019 Yu-Zhuang Lin. All rights reserved.
//鏈結串列 (資料結構)
==============================================================================
//完整演練:
#include<stdio.h>
#include<stdlib.h>
typedef struct ListNode {
     int data;
     struct ListNode *next;
}List;

List* createList(int*,int); //建立
void printList(List*); //印出
List* reverseList(List*); //反轉
List* insertList(List*,int Nth,int num); //Nth 插入位置, num插入元素;
List* deleteList(List*,int Nth); // Nth 刪除位置;

int main(void){ //main
    int nums[10];
    for(int i=1;i<11;i++) nums[i-1]=i;
    
    List *one=createList(nums,10); //create linked list
    printList(one); //print
    
    printf("\nafter reverse:\n");
    
    List *two=reverseList(one); //reverse linked list
    printList(two); //print
    
    printf("\nafter insert:\n");
    List *three=insertList(two,1,7); //insert num in linked list
    printList(three); //print
    
    printf("\nafter delete:\n");
    printList(deleteList(three,2)); //delete num in linked list //print
    
    return 0;
}

List* createList(int* nums,int numsSize){ //用Stack的方式建立linked list~
    List *first=(List*)malloc(sizeof(List));
    first->next=NULL;
    for(int i=numsSize-1;i>=0;i--){ //~因此將資料陣列nums "反著" 存入(負負得正);
        List *newnode=(List*)malloc(sizeof(List));
        newnode->data=nums[i];
        newnode->next=first->next;
        first->next=newnode;
    }
    first=first->next;
    return first;
}

void printList(List* L){ //print linked list
    while(L!=NULL) {printf("%d ",L->data); L=L->next;}
}

List* reverseList(List* L){ //reverse linked list
    List *last=NULL,*tmp=L;
    while(L!=NULL){
        tmp=tmp->next;
        L->next=last;
        last=L;
        L=tmp;
    }
    L=last;
    return last;
}

List* insertList(List* L,int Nth,int num){ //insert: Nth 插入位置, num插入元素;
    List *tmp=L, *newnode=(List*)malloc(sizeof(List));
    newnode->data=num;
    if(Nth<=0);
    else if(Nth==1) {newnode->next=tmp;return newnode;}
    else{
        while(Nth!=2){Nth--; tmp=tmp->next;}
        newnode->next=tmp->next;
        tmp->next=newnode;
    }
    return L;
}

List* deleteList(List* L,int Nth){ //delete: Nth 刪除位置;
    if(Nth==1) {L=L->next;return L;}
    List *ptr=L;
    while(Nth>2){
        Nth--;
        ptr=ptr->next;
    }ptr->next=ptr->next->next;
    return L;
}

==============================================================================
==============================================================================

#include<stdio.h>
#include<stdlib.h>
int main(void){
    typedef struct node{
        int data;
        struct node *next; //鏈結下一個 結構資料
    }NODE; //定義 NODE 資料型態為一個結構資料
    
    NODE a,b,c;
    NODE *ptr=&a; //指向第一個鏈結
    
    a.data=2;
    a.next=&b; //a的next為b
    b.data=30;
    b.next=&c;
    c.data=64;
    c.next=NULL; //c接地
    
    while(ptr!=NULL){
        printf("address=%p, data=%d, next=%p\n", ptr, ptr->data,ptr->next);
        ptr=ptr->next; //往下一個鏈結
    }
    
    return 0;
}

//動態記憶體配置串列
//建立與走訪 鏈結串列
#include<stdio.h>
#include<stdlib.h>
int main(void){
    typedef struct node{
        int data;
        struct node *next;
    }NODE; //宣告
    
    int i,num;
    NODE *first,*current,*previous; //
    
    printf("number of nodes: ");
    scanf("%d", &num); //input 要產生幾個節點
    
    for(i=0;i<num;i++){ //建立鏈結串列
        current=(NODE*)malloc(sizeof(NODE));  //建立新的節點
        printf("data for node %d: ",i+1);
        scanf("%d",&current->data);
        if(i==0){ //
            first=current;
        }
        else  //
            previous->next=current;
        current->next=NULL; //
        previous=current; //
    }
    
    current=first;
    
    while(current!=NULL){ //走訪 印出 鏈結串列
        printf("address=%p, data=%d, next=%p\n",current,current->data,current->next);
        current=current->next;
    }
    
    return 0;
}
=====================function====================
// 建立 鏈結串列
NODE* creatList(int* arr,int len){ //arr: 欲存入資料陣列, len: 欲建立節點長度
    int i;
    NODE *first,*previous,*current;
    for(i=0;i<len;i++){
        current=(NODE*)malloc(sizeof(NODE));
        current->data=arr[i];
        if(i==0)
            first=current;
        else
            previous->next=current;
        current->next=NULL;
        previous=current;
    }
    return first;
}

//印出鏈結串列
void printList(NODE* list){
    NODE* ptr=list;
    if(ptr==NULL)
        printf("List is empty.");
    
    while(ptr!=NULL){
        printf("%d ", ptr->data);
        ptr=ptr->next;
    }
}

//釋放列捷串列記憶體
void freeList(NODE* List){
    NODE* ptr=List;
    while(List!=NULL){
        ptr=List;
        List=List->next;
        free(ptr);
    }
}

//搜尋列捷串列
NODE* searchList(NODE* first, int item){
    NODE *ptr=first;
    while(ptr!=NULL){
        if(ptr->data==item)
            return ptr;
        ptr=ptr->next;
    }
    return NULL;
}

//插入鏈結串列
void insertList(NODE *node, int item){ //將newnode插入node之後
    NODE *newnode;
    newnode=(NODE*)malloc(sizeof(NODE));
    newnode->data=item;
    newnode->next=node->next;
    node->next=newnode;
}

//刪除鏈結串列
NODE* deleteNODE(NODE *first, NODE *node){
    NODE *ptr=first;
    if(ptr==NULL){
        printf("nothing to delete.");
        return NULL;
    }
    if(first==node){
        first=first->next;
        return first;
    }
    while(ptr->next!=node){
        ptr=ptr->next;
    }
    ptr->next=node->next;
    free(ptr);
    return first;
}

