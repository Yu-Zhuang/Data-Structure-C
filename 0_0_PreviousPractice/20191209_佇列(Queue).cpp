//  Copyright © 2019 Yu-Zhuang Lin. All rights reserved.
//佇列(Queue)
//先進先出 (除了優先佇列priority queue是有優先權的值先出外)

//用 結構(中的陣列) 進行 環形佇列
#include<stdio.h>
#include<stdlib.h>
#define MAX 5
typedef struct tagQueue{
    int item[MAX]; //資料欄位
    int front=-1; //若有資料 則front+=1; 讀出 item[front];
    int rear=-1; //若有空間 則rear+=1; 存入 item[rear];
}Queue;
bool Enqueue(Queue*,int);
bool Dequeue(Queue*, int*);
int main(void){
    int input[8]={1,2,3,4,5,6,7,8};
    int i;
    Queue q;
    for(i=0;i<8;i++){
        Enqueue(&q,input[i]);
        printf("(%d,%d) ", q.item[q.rear],q.rear);
    }
    return 0;
}

bool Enqueue(Queue *Q, int data){
    if((Q->rear+1)%MAX==Q->front) //空間已滿
        return false;
    Q->rear=(Q->rear+1)%MAX; //將空間推一格
    Q->item[Q->rear]=data; //儲存資料
    return true;
}

bool Dequeue(Queue *Q, int *nums){
    if(Q->front==Q->rear)
        return false;
    Q->front=(Q->front+1)%MAX;
    *nums=Q->item[Q->front];
    return true;
}

====================================
//用 鏈結做 佇列
#include<stdio.h>
#include<stdlib.h>

typedef struct quene{
    int data;
    struct quene *next;
}Quene;

void Enquene (Quene*,int);
void Dequene (Quene*,int*);
void PrintQuene (Quene*);

int main(void){
    int list[10],newlist[10]={0};
    for(int i=0;i<10;i++) list[i]=1+i;
    Quene *team=(Quene*)malloc(sizeof(Quene));
    team->next=NULL; team->data=NULL;
    printf("Enquene:\n"); //en
    for(int i=0;i<10;i++) Enquene(team,list[i]);
    PrintQuene(team);
    printf("\n");
    
    printf("Dequene:\n"); //de
    for(int i=0;i<5;i++) {Dequene(team,&newlist[i]);}
    PrintQuene(team);
    printf("\nnewlist:\n");
    for(int i=0;i<10;i++) printf("%d ",newlist[i]);
    
    return 0;
}

void Enquene (Quene* Q,int n){
    Quene *newnode=(Quene*)malloc(sizeof(Quene));
    newnode->data=n;
    while(Q->next!=NULL) Q=Q->next;
    newnode->next=Q->next;
    Q->next=newnode;
}
void Dequene (Quene* Q,int* num){
    Quene* clear=Q;
    *num=Q->next->data;
    Q->next=Q->next->next;
    clear=NULL;
}

void PrintQuene(Quene* Q){
    while(Q->next!=NULL) {printf("%d ",Q->next->data); Q=Q->next;}
}



