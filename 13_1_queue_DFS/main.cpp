/* 
* Date: 2020.05.05;
* Intro: 17個人的關係圖, 人名最長10個字元, 圖最多容納20人的資料;
* func: 可透過BFS, DSF走訪圖以及找出兩人間的關係隔多少距離(非最短距離);
*/
// =============== HEADER_FILE ==================
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
// =============== DEFINE ==================
#define MAX 11
#define DB_MAX 20
typedef struct node{
    char name[MAX];
    struct node *next;
}NODE;
typedef struct list{
    char name[MAX];
    int status;
    NODE *next;
}LIST;
typedef struct queueHead{
    char name[MAX];
    NODE *rear;
    NODE *next;
}QUEUE;
// ============= FUNCTION_ANNOUCEMENT ===============
void FILE_GET(char *file, LIST *DB, int *DB_size);
void GET_CHOSE(int *chose);
void GET_START_END(char *start, char *end, int chose);

void DB_INIT(LIST *DB, char *element, int site);
void DB_INSERT(LIST *DB, char *element, int site);
void DB_PRINT(LIST *DB, int DB_size);
void DB_BSF(LIST *DB, char *start, int DB_size);
void DB_BSF_SECOND(LIST *DB, char *start, int DB_size);
void DB_DSF(LIST *DB, char *start, int DB_size);
LIST* DB_FIND(LIST *DB, char *target, int DB_size);
void DB_RECORD_CLEAR(LIST *DB, int DB_size);
void DB_DSF_FIND_PATH(LIST *DB, char *start, char *end, int DB_size);

char* DE_QUEUE(QUEUE *head);
void EN_QUEUE(QUEUE *head, char *element);
char* POP(NODE *head);
void PUSH(NODE *head, char *element);
// ============= MAIN ===============
int main(void){
    char file[] = "graph.cpp", start[MAX]="John", end[MAX]="Mary";
    int DB_size=0, chose=1;
    LIST DB[DB_MAX];

    FILE_GET(file, DB, &DB_size);

    while(chose){
        GET_CHOSE(&chose);
        GET_START_END(start, end, chose);
        switch(chose){
            case 0: break;
            case 1: DB_PRINT(DB, DB_size); break;
            case 2: DB_BSF(DB, start, DB_size); break;
            case 3: DB_DSF(DB, start, DB_size); break;
            case 4: DB_BSF_SECOND(DB, start, DB_size); break;
            case 5: DB_DSF_FIND_PATH(DB, start, end, DB_size); break;
            default: printf("\t[ 輸入錯誤! ]\n"); break;
        }
        DB_RECORD_CLEAR(DB, DB_size);
    }
    printf("\t[ 程式結束 ]\n");
    return 0;
}
// ================ FUNCTION ===============
void DB_DSF_FIND_PATH(LIST *DB, char *start, char *end, int DB_size){
    if( ! DB_FIND(DB, start, DB_size) ) 
        { printf("\t[ 沒有該起點! ]\n"); return; }
    printf("FIND \"%s\" -> \"%s\":\n\t", start, end);
    int flag=0, count=0; // flag:紀錄該路是否已到終點; 
    LIST *tmp=NULL;
    NODE *stack = (NODE*)malloc(sizeof(NODE)); // stack
    stack->next = NULL;

    PUSH(stack, start);
    DB_FIND(DB,stack->next->name,DB_size)->status = 1; // 將stack.top 改為 造訪中狀態
    while(stack->next){ // stack is empty or not?
        if( ! strcmp(stack->next->name, end) ){ //找到 end 
            while(stack->next){ // print result
                tmp = DB_FIND(DB, POP(stack), DB_size);
                if(tmp->status){
                    printf("[%s]<-", tmp->name);
                    DB_FIND(DB, tmp->name, DB_size)->status = 0;
                    count+=1;
                }
            }
            printf("|START\nCount: %d\n", count-1);
            return;
        }
        else{ // 未找到 end
            flag = 0;
            NODE *nodePtr = DB_FIND(DB, stack->next->name, DB_size)->next;
            while(nodePtr){
                //周遭是否還有未拜訪的點
                if( DB_FIND(DB, nodePtr->name, DB_size)->status == 0 ){
                    PUSH(stack, nodePtr->name);
                    flag = 1;
                }
                nodePtr = nodePtr->next;
            }
            if(!flag){ //該路已到終點, 回到分支點
                while(DB_FIND(DB,stack->next->name,DB_size)->status &&\
                    stack->next)
                    DB_FIND(DB, POP(stack), DB_size)->status=0;
                // 如果走完
                if(! stack->next) break;      
            }
            DB_FIND(DB,stack->next->name,DB_size)->status = 1; // 將stack.top 改為 造訪中狀態
        }
    }
    printf("\t[ 未找到 ]\n"); 
}
void DB_BSF_SECOND(LIST *DB, char *start, int DB_size){
    if( ! DB_FIND(DB, start, DB_size) )
        { printf("\t[ 沒有該起點! ]\n"); return; }
    QUEUE *Q = (QUEUE*)malloc(sizeof(QUEUE));
    Q->next = NULL; Q->rear = NULL;
    LIST *site = DB_FIND(DB, start, DB_size);
    site->status = 1;
    printf("Node that have two distance from [%s]:\n\t", site->name);
    NODE *tmp = site->next;
    while(tmp){
        EN_QUEUE(Q, tmp->name);
        DB_FIND(DB, tmp->name, DB_size)->status = 2;
        tmp = tmp->next;
    }
    while(Q->next){
        site = DB_FIND(DB, DE_QUEUE(Q), DB_size);
        if(site->status == 0 || site->status==2){
            if(site->status==0) site->status = 1;
            tmp = site->next;
            LIST *second = NULL;
            while(tmp){
                second = DB_FIND(DB, tmp->name, DB_size);
                if(!second->status){
                    second->status = 1;
                    printf("[%s], ", second->name);
                }
                tmp = tmp->next;
            }          
        }
    } 
    printf("|END\n");     
}
void DB_BSF(LIST *DB, char *start, int DB_size){
    if( ! DB_FIND(DB, start, DB_size) )
        { printf("\t[ 沒有該起點! ]\n"); return; }
    QUEUE *Q = (QUEUE*)malloc(sizeof(QUEUE));
    Q->next = NULL; Q->rear = NULL;
    LIST *site = DB_FIND(DB, start, DB_size);
    site->status = 1;
    printf("BFS start: [%s]-", site->name);
    NODE *tmp = site->next;
    int cnt = 1;
    while(tmp)
        { EN_QUEUE(Q, tmp->name); tmp = tmp->next; }
    while(Q->next){
        site = DB_FIND(DB, DE_QUEUE(Q), DB_size);
        if( ! site->status){
            cnt += 1;
            if( ! (cnt%9)) printf("\n\t");
            site->status = 1;
            printf("[%s]-", site->name);
            tmp = site->next;
            while(tmp)
                { EN_QUEUE(Q, tmp->name); tmp = tmp->next; }          
        }
    }
    printf("|END\n");
}
void DB_DSF(LIST *DB, char *start, int DB_size){
    if( ! DB_FIND(DB, start, DB_size) ) 
        { printf("\t[ 沒有該起點! ]\n"); return; } 
    NODE *S = (NODE*)malloc(sizeof(NODE));
    S->next = NULL;
    LIST *site = DB_FIND(DB, start, DB_size);
    site->status = 1;
    printf("DFS start: [%s]-", site->name);
    NODE *tmp = site->next;
    int cnt = 1;
    while(tmp)
        { PUSH(S, tmp->name); tmp = tmp->next; }
    while(S->next){
        site = DB_FIND(DB, POP(S), DB_size);
        if( ! site->status){
            cnt += 1;
            if( ! (cnt%9)) printf("\n\t");
            site->status = 1;
            printf("[%s]-", site->name);
            tmp = site->next;
            while(tmp)
                { PUSH(S, tmp->name); tmp = tmp->next; }          
        }
    }
    printf("|END\n");    
}
LIST* DB_FIND(LIST *DB, char *target, int DB_size){
    for(int i=0;i<DB_size;i++)
        if(strcmp(DB[i].name, target) == 0)
            return &DB[i];
    printf("\t[ Not Find: %s ]\n", target);
    return NULL;
}
char* POP(NODE *head){
    NODE *tmp = head->next;
    char *ret = (char*)malloc(sizeof(char)*MAX);
    strcpy(ret, tmp->name);
    head->next = head->next->next;
    free(tmp);
    return ret;
}
void PUSH(NODE *head, char *element){
    NODE *newnode = (NODE*)malloc(sizeof(NODE));
    strcpy(newnode->name, element);
    newnode->next = head->next;
    head->next = newnode;
}
void EN_QUEUE(QUEUE *head, char *element){
    NODE *newnode = (NODE*)malloc(sizeof(NODE));
    if( !newnode ) 
        { printf("\t[ QUEUE is full ]"); return; } 
    strcpy(newnode->name, element);
    newnode->next = NULL;
    if(head->next)
        head->rear->next = newnode;
    else
        head->next = newnode;
    head->rear = newnode;
}
char* DE_QUEUE(QUEUE *head){
    char *ret = (char*)malloc(sizeof(char)*MAX);
    memset(ret,'\0',MAX);
    NODE *tmp=NULL;
    if( !head->next ) 
        { printf("\t[ QUEUE is empty ]\n"); return ret; }
    strcpy(ret, head->next->name);
    tmp = head->next;
    head->next = head->next->next;
    free(tmp);
    return ret;
}
void FILE_GET(char *file, LIST *DB, int *DB_size){
    FILE *fptr = fopen(file, "r");
    char ori[MAX*20]={'\0'};
    char copy[MAX*20]={'\0'};
    if(fptr){
        while( fgets(ori,MAX*20,fptr) ){
            if( isspace(ori[0]) ) 
                continue;
            strcpy(copy,ori);
            char *take = strtok(copy," \n");
            DB_INIT(DB, take, DB_size[0]);
            take = strtok(NULL, " ");
            while(take)
                { DB_INSERT(DB, take, DB_size[0]); take = strtok(NULL," \n"); }
            DB_size[0]+=1;
        }
    }
    else 
        printf("can't open the file\n");
    fclose(fptr);
}
void DB_INIT(LIST *DB, char *element, int site){
    strcpy(DB[site].name, element); 
    DB[site].status = 0;
    DB[site].next = NULL;
}
void DB_INSERT(LIST *DB, char *element, int site){
    NODE *newnode = (NODE*)malloc(sizeof(NODE));
    strcpy(newnode->name, element);
    newnode->next = NULL;
    if( ! DB[site].next) 
        { DB[site].next = newnode; return; }
    NODE *tmp = DB[site].next;
    while(tmp->next) 
        tmp = tmp->next;
    tmp->next = newnode; 
}
void DB_PRINT(LIST *DB, int DB_size){
    NODE *tmp = NULL;
    for(int i=0;i<DB_size;i++)
        if(DB[i].next){
            tmp = DB[i].next;
            printf("%3d. %s:\t",i+1, DB[i].name);
            while(tmp)
                { printf("[%s]-", tmp->name); tmp = tmp->next; }
            printf("|END\n");
        }
}
void DB_RECORD_CLEAR(LIST *DB, int DB_size){
    for(int i=0;i<DB_size;i++)
        DB[i].status = 0;
}
void GET_CHOSE(int *chose){
    char tmp[MAX]={'\0'}; //for input chose;
    char hint[]="\n\t@主選單@\n (1) 顯示圖\n (2) BFS\n (3) DFS\n (4) 找距該點2層的所有點\n (5) 找2點的一個路徑與距離(非最短)\n (0) 結束\n輸入選擇: ";
    while(1){
        printf("%s", hint);
        scanf("%[^\n]", tmp); getchar();
        if(tmp[0]<'0'||tmp[0]>'9') 
            { printf("\t[ 輸入錯誤! ]\n"); continue; }
        else 
            { sscanf(&tmp[0], "%d", chose); break; }
    }  
}
void GET_START_END(char *start, char *end, int chose){
    if(chose >= 2 && chose <=4){
        printf("請輸入起點: ");
        scanf("%s", start); getchar();
    }
    else if(chose == 5){
        printf("請依序輸入 起點 終點: ");
        scanf("%s %s", start, end); getchar();
    }
}