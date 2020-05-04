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
    char file[] = "graph.cpp",
         tmp[MAX]={'\0'}, //for input chose;
         start[]="John",
         end[]="Mary";
    LIST DB[DB_MAX];
    int DB_size=0, chose=1;

    FILE_GET(file, DB, &DB_size);
    while(chose){
        printf("\n\t@主選單@\n(1)顯示圖\n(2)BFS\n(3)DSF\n(4)找距該點2層的所有點\n(5)找2點的一個路徑與距離(非最短)\n輸入選擇: ");
        scanf("%s", tmp);
        if(tmp[0]<'0'||tmp[0]>'9') { printf("[ 輸入錯誤! ]\n"); continue; }
        sscanf(&tmp[0], "%d", &chose);

        if(chose == 1)
            DB_PRINT(DB, DB_size);  
        else if(chose == 2)
            DB_BSF(DB, start, DB_size);
        else if(chose == 3)
            DB_DSF(DB, start, DB_size);
        else if(chose == 4)
            DB_BSF_SECOND(DB, start, DB_size);
        else if(chose == 5)
            DB_DSF_FIND_PATH(DB, start, end, DB_size);
        else if(chose != 0)
            { printf("[ 輸入錯誤! ]\n"); continue; }
        DB_RECORD_CLEAR(DB, DB_size);
    }
    
    return 0;
}
// ================ FUNCTION ===============
void DB_DSF_FIND_PATH(LIST *DB, char *start, char *end, int DB_size){
    NODE *stack = (NODE*)malloc(sizeof(NODE)); // stack
    stack->next = NULL;
    int flag=0, find=0, count=0; // flag:紀錄該路是否已到終點; find:紀錄是否能從start到end
    LIST *tmp=NULL;
    printf("FIND %s -> %s :\n\t", start, end);
    PUSH(stack, start);
    while(stack->next){ // stack is empty or not?
        if( ! strcmp(stack->next->name, end) ){ //找到 end 
            find = 1; // record: 該圖start可到end 
            // print result
            while(stack->next){
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
            tmp = DB_FIND(DB, stack->next->name, DB_size);
            tmp->status = 1;
            NODE *nodePtr = tmp->next;
            while(nodePtr){
                //周遭是否還有未拜訪的點
                if( DB_FIND(DB, nodePtr->name, DB_size)->status == 0 ){
                    PUSH(stack, nodePtr->name);
                    flag = 1;
                }
                nodePtr = nodePtr->next;
            }
            if(!flag){ //該路已到終點, 回到分支點
                while(stack->next && DB_FIND(DB,stack->next->name,DB_size)->status ) DB_FIND(DB, POP(stack), DB_size)->status=0;
                // 如果走完
                if(! stack->next) break;      
            }
            DB_FIND(DB,stack->next->name,DB_size)->status = 1; // 將stack.top 改為 造訪中狀態
        }
    }
    printf("[ 未找到 ]\n"); 
}
void DB_BSF_SECOND(LIST *DB, char *start, int DB_size){
    NODE *S = (NODE*)malloc(sizeof(NODE));
    S->next = NULL;
    LIST *site = DB_FIND(DB, start, DB_size);
    site->status = 1;
    printf("Node that have two distance from [%s]:\n\t", site->name);
    NODE *tmp = site->next;
    while(tmp){
        PUSH(S, tmp->name);
        DB_FIND(DB, tmp->name, DB_size)->status = 2;
        tmp = tmp->next;
    }
    while(S->next){
        site = DB_FIND(DB, POP(S), DB_size);
        if(site->status == 0 || site->status==2){
            if(site->status==0) site->status = 1;
            //printf("[%s]-", site->name);
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
    QUEUE *Q = (QUEUE*)malloc(sizeof(QUEUE));
    Q->next = NULL; Q->rear = NULL;
    LIST *site = DB_FIND(DB, start, DB_size);
    site->status = 1;
    printf("BFS start [%s]:\n\t", site->name);
    NODE *tmp = site->next;
    while(tmp){
        EN_QUEUE(Q, tmp->name);
        tmp = tmp->next;
    }
    while(Q->next){
        site = DB_FIND(DB, DE_QUEUE(Q), DB_size);
        if( ! site->status){
            site->status = 1;
            printf("[%s]-", site->name);
            tmp = site->next;
            while(tmp){
                EN_QUEUE(Q, tmp->name);
                tmp = tmp->next;
            }          
        }
    }
    printf("|END\n");
}
void DB_DSF(LIST *DB, char *start, int DB_size){
    NODE *S = (NODE*)malloc(sizeof(NODE));
    S->next = NULL;
    LIST *site = DB_FIND(DB, start, DB_size);
    site->status = 1;
    printf("DFS start [%s]:\n\t", site->name);
    NODE *tmp = site->next;
    while(tmp){
        PUSH(S, tmp->name);
        tmp = tmp->next;
    }
    while(S->next){
        site = DB_FIND(DB, POP(S), DB_size);
        if( ! site->status){
            site->status = 1;
            printf("[%s]-", site->name);
            tmp = site->next;
            while(tmp){
                PUSH(S, tmp->name);
                tmp = tmp->next;
            }          
        }
    }
    printf("|END\n");    
}
LIST* DB_FIND(LIST *DB, char *target, int DB_size){
    for(int i=0;i<DB_size;i++)
        if(strcmp(DB[i].name, target) == 0)
            return &DB[i];
    printf("[ Not Find: %s ]\n", target);
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
    if( !newnode ) {printf("[ QUEUE is full ]"); return; } 
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
    if( !head->next ) { printf("[ QUEUE is empty ]\n"); return ret; }
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
            if( isspace(ori[0]) ) continue;
            strcpy(copy,ori);
            char *take = strtok(copy," \n");
            DB_INIT(DB, take, DB_size[0]);
            take = strtok(NULL, " ");
            while(take){ DB_INSERT(DB, take, DB_size[0]); take = strtok(NULL," \n"); }
            DB_size[0]+=1;
        }
    }
    else printf("can't open the file\n");
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
    if( ! DB[site].next) { DB[site].next = newnode; return; }
    NODE *tmp = DB[site].next;
    while(tmp->next) tmp = tmp->next;
    tmp->next = newnode; 
}
void DB_PRINT(LIST *DB, int DB_size){
    NODE *tmp = NULL;
    for(int i=0;i<DB_size;i++){
        if(DB[i].next){
            tmp = DB[i].next;
            printf("%3d. %s:\t",i+1, DB[i].name);
            while(tmp){
                printf("[%s]-", tmp->name);
                tmp = tmp->next;
            }
            printf("|END\n");
        }
    }
}
void DB_RECORD_CLEAR(LIST *DB, int DB_size){
    for(int i=0;i<DB_size;i++)
        DB[i].status = 0;
}
