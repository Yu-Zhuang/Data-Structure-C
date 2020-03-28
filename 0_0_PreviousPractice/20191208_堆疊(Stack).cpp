//  Copyright © 2019 Yu-Zhuang Lin. All rights reserved.

//用 結構(中的陣列) 進行 堆疊
#include<stdio.h>
#include<stdlib.h>
#define MAX 5 //儲存空間
typedef struct list{ //宣告定義NODE
    int Top=-1; //頂端元素位置
    int Item[MAX]; //儲存元素資料
}Stack;

bool Push(Stack*,int);
bool Pop(Stack*, int*X);

int main(void){
    int input[5]={1,3,7,8,9};
    int output[5],i;
    Stack S;

    for(i=0;i<5;i++){ //放入資料
        Push(&S,input[i]);
    }
    printf("\n");
    for(i=0;i<5;i++){
        Pop(&S, &output[i]);
        printf("%d ",output[i]); //拿出資料 並印出(9 8 7 3 1
    }
    printf("\n");
    return 0;
}
bool Push(Stack* data,int input){ //放入元素 函數
    if(data->Top==MAX-1) //已滿
        return false;
    data->Top+=1;
    data->Item[data->Top]=input; //未滿 放入
    return true;
}

bool Pop(Stack* data, int* output){ //拿出元素 函數
    if(data->Top==-1) //已空
        return false;
    *output=data->Item[data->Top]; //未空 拿出
    data->Top-=1;
    return true;
}
/*stack用指標寫
typedef struct list{
    int Top; //+頂端元素位置, Top不用先給粗初值+
    int Item[MAX];
}Stack;

int main(void){ //main
    int input[5]={1,3,7,8,9};
    int output[5],i;
    Stack *S;                        //宣告指標
    S=(Stack*)malloc(sizeof(Stack)); //指派空間
    S->Top=-1;                       //+這邊再給初值+
    printf("%d\n", S->Top);
    for(i=0;i<5;i++){
        Push(S,input[i]);
        printf("%d ",S->Item[S->Top]);
    }
    printf("\n");
    for(i=0;i<5;i++){
        Pop(S, &output[i]);
        printf("%d ",output[i]);
    }
    printf("\n");
    return 0;
}
*/
==========================================================
// 用 鏈結結構 進行堆疊
#include<stdio.h>
#include<stdlib.h>
typedef struct tagStackList{
    int data;
    struct tagStackList *next;
}StackList; //結構宣告
bool Push(StackList *S, int X);//函數
bool Pop(StackList *S, int *X);

int main(){ //main
    int input[5]={1,3,2,6,9},i; //欲放入資料
    StackList *S;
    S=(StackList*)malloc(sizeof(StackList));
    S->next=NULL; //第一個節點
    for(i=0;i<5;i++){ //使用Push函數將陣列資料放入堆疊結構
        Push(S,input[i]);
    }
/*    while(S){ //這時印出S資料會是:0 9 6 2 3 1 (堆疊會先進後出
        printf("%d ",S->data);
        S=S->next;}
 */
    for(i=4;i>=0;i--){ //使用Pop函數拿出資料 放入陣列
        Pop(S,&input[i]);
        printf("%d ", input[i]);
    } //output:9 6 2 3 1
    return 0;
}
bool Push(StackList *S, int X){
    StackList *p;
    p=(StackList*)malloc(sizeof(StackList));
    if(p==NULL)
        return false; //配置失敗
    p->data=X;
    p->next=S->next;
    S->next=p;
    return true;
}

bool Pop(StackList *S, int *X){
    StackList *p=S->next;
    if(p==NULL)
        return false;
    *X=p->data;
    S->next=p->next;
    free(p);
    return true;
}
