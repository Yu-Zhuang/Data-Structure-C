#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// ***** DEFINE *****
#define MAX_SIZE 200
#define MAX_ID_SIZE 5
#define ROUTE_NUM 5
enum color{
   RED, YELLOW, BLUE, GREEN, BROWN
}; 
typedef struct route{
   int name;
   int color[ROUTE_NUM];
   struct route *B, *F;
   struct route *S, *N;
}NODE;
typedef struct map{
   NODE *red;
   NODE *yellow;
   NODE *blue;
   NODE *green;
   NODE *brown;
}MAP;
typedef struct table{
   int name;
   int color[ROUTE_NUM];
   NODE *site;
}TABLE; 
typedef struct q{
   int val;
   struct q *next;
}QUEUE;
// ***** FUNCTION ANNOUNCEMENT *****
void FILE_GET(char *file, int *input, int *size);

void TABLE_INIT(TABLE *list, int size);
void TABLE_PRINT(TABLE *list, int size);

void MAP_INIT(MAP *map);

void ROUTE_INSERT(TABLE *DB, int *route, int routeSize, int color, MAP *map);
NODE* ROUTE_SELETION(MAP *map, int color);
void ROUTE_PRINT(NODE *route);
int ROUTE_FIND(TABLE *DB, int start, int end);

void ENQUEUE(QUEUE *head, int element);
int DEQUEUE(QUEUE *head);
void QUEUE_PRINT(QUEUE *head);

void CTABLE_PRINT(int *table);
// ***** MAIN *****
int main(void){
   // VARIABLE announcement
   char file[ROUTE_NUM][6]={"1.cpp", "2.cpp", "3.cpp", "4.cpp", "5.cpp"};
   int input[ROUTE_NUM][MAX_SIZE], size[ROUTE_NUM]={0}, total=0;
   TABLE DB[MAX_SIZE];
   MAP map;
   
   // INITIALIZATION
   MAP_INIT(&map);
   TABLE_INIT(DB, MAX_SIZE);
   
   // COMPUTION
      //get file
   for(int i=0;i<ROUTE_NUM;i++) 
      FILE_GET(file[i],input[i], &size[i]);
      //put data to DB and map
   for(int i=0;i<ROUTE_NUM;i++) 
      ROUTE_INSERT(DB, input[i], size[i], i, &map);
      //print map

   //OUTPUT
   int flag=1;
   while(flag){
      printf("\t@主選單@\n(1)印出資料庫與地圖\n(2)查詢車站\n(3)查詢兩站距離\n(0)結束\n請輸入: "); scanf("%d", &flag);
      if(flag==0) break;
      if(flag==1){
         TABLE_PRINT(DB, MAX_SIZE);

         printf("\n\t=====[ RED LINE ]=====\n");
         ROUTE_PRINT(map.red);
         ROUTE_PRINT(DB[8].site);
         printf("\n\t=====[ YELLOW LINE ]=====\n");
         ROUTE_PRINT(DB[29].site);
         ROUTE_PRINT(map.yellow);
         printf("\n\t=====[ BLUE LINE ]=====\n");
         ROUTE_PRINT(map.blue);
         printf("\n\t=====[ GREEN LINE ]=====\n");
         ROUTE_PRINT(map.green);
         ROUTE_PRINT(DB[77].site);
         printf("\n\t=====[ BROWN LINE ]=====\n");
         ROUTE_PRINT(map.brown);        
      }else if(flag==2){
         int target=-1;
         printf("欲查詢車站: "); scanf("%d", &target);
         if(DB[target].name==-1) printf("查無此站!\n");
         else{
            if(DB[target].color[1]==-1) printf("車站顏色: %d\n", DB[target].color[0]);
            else printf("車站顏色: %d, %d\n", DB[target].color[0], DB[target].color[1]);            
         }
      }else if(flag==3){
         int start=-1, end=-1;
         printf("起點站: "); scanf("%d", &start);
         printf("終點站: "); scanf("%d", &end);
         if(DB[start].name==-1||DB[end].name==-1) printf("輸入錯誤!\n");
         else{
            printf("\n*************************\n*\t總共要搭: %d 站\t*\n", ROUTE_FIND(DB,start,end));
            printf("*************************\n");
         }
      }
   }
   // END
   return 0;
}

// ***** FUNCTION *****
int ROUTE_FIND(TABLE *DB,int start, int end){
   printf("\n========== 搜尋起止站距離 ==========\n");
   if(start==end) return 0;
   int ret=0, fd=0;
   int table[MAX_SIZE]={0};
   int fold[MAX_SIZE]={0}; 
   QUEUE *Q=(QUEUE*)malloc(sizeof(QUEUE));
   NODE *pre, *pos=DB[start].site, *target=DB[end].site;

   // BSF找最短路徑
   do{       
      //該站未被拜訪
      if(table[pos->name]==0) table[pos->name]=1;
      //該站已被拜訪
      else { pos=DB[DEQUEUE(Q)].site; continue; }
      //find
      if(pos==target) break; 
      
      //找附近車站 並放入Q
      printf("搜尋站: [[%d]]\n", pos->name); //print status
      printf("已搜尋站: "); CTABLE_PRINT(table); //print status
      
      //enqueue and calculate fold
      if((pos->B&&fold[pos->B->name]==0) || (pos->F&&fold[pos->F->name]==0) || (pos->S&&fold[pos->S->name]==0) || (pos->N&&fold[pos->N->name]==0)){
         //計算第幾層 
         fd=fold[pos->name]+1;
      }
      if(pos->B&&fold[pos->B->name]==0) { fold[pos->B->name]=fd;  if(pos->B==target) {ret+=1; break;}  ENQUEUE(Q,pos->B->name); }    
      if(pos->F&&fold[pos->F->name]==0) { fold[pos->F->name]=fd; if(pos->F==target) {ret+=1; break;} ENQUEUE(Q,pos->F->name); }
      if(pos->S&&fold[pos->S->name]==0) { fold[pos->S->name]=fd; if(pos->S==target) {ret+=1; break;} ENQUEUE(Q,pos->S->name); }
      if(pos->N&&fold[pos->N->name]==0) { fold[pos->N->name]=fd; if(pos->N==target) {ret+=1; break;} ENQUEUE(Q,pos->N->name); }  
      printf("QUEUE: "); QUEUE_PRINT(Q); //print status
      
      //找下一車站;
      pos=DB[DEQUEUE(Q)].site;

   }while(1);

   printf("\n========== END_搜尋起止站距離 ==========\n");
   return fd;
}
void QUEUE_PRINT(QUEUE *head){
   head=head->next;
   while(head){
      printf("[%d]-", head->val);
      head=head->next;
   }printf("\n\n");
}
void ENQUEUE(QUEUE *head, int element){
   QUEUE *newnode=(QUEUE*)malloc(sizeof(QUEUE));
   newnode->val=element; newnode->next=NULL;
   while(head->next) head=head->next;
   head->next=newnode;
}
int DEQUEUE(QUEUE *head){
   int ret=head->next->val;
   head->next= head->next->next;
   return ret;
}
void CTABLE_PRINT(int *table){
   printf("|");
   for(int i=0;i<MAX_SIZE;i++){
      if(table[i]) printf("%d, ", i);
   }printf("|\n");
}
void ROUTE_INSERT(TABLE *DB, int *route, int routeSize, int color, MAP *map){
   int flag=0; // flag==1: start, flag==0: end;
   NODE *pStart=ROUTE_SELETION(map,color);
   NODE *preNode=pStart;
   int preNum=route[0];
   for(int i=0;i<routeSize;i++){
      if(route[i]==0 && flag==0) { flag=1; continue; }//start
      else if(route[i]==0 && flag==1) { flag=0; continue; } //end
      // new element
      if(DB[route[i]].name==-1){
         // create newnode
         NODE *newnode = (NODE*)malloc(sizeof(NODE));
         newnode->F=NULL; newnode->B=NULL; newnode->N=NULL; newnode->S=NULL;
         newnode->name=route[i]; newnode->color[0]=color;
         // put into DB
         DB[route[i]].name=route[i]; DB[route[i]].color[0]=color; DB[route[i]].site=newnode;
         // put into map
            //if its MAIN route
         if(flag){
               // if pedigree is NULL and 
            if( ! pStart->F) pStart->F=newnode;
            else{
                  //if preNode is on MAIN
               if(preNode->color[0]==color){
                  preNode->F=newnode;
                  newnode->B=preNode;

               }  //if preNode is sub
               else{
                  preNode->N=newnode;
                  newnode->B=preNode;
               }
            }
            //record pre element
            preNode=newnode;
            preNum=route[i];
         }//if its sub route
         else{
            // and its head of sub route
            if( ! route[i-1]){
               preNode=newnode;
               preNum=route[i];              
            }else{
               preNode->F=newnode;
               newnode->B=preNode;
            }
            //record pre element
            preNode=newnode;
            preNum=route[i];
         }
      }
      // if element already exist
      else{
         //if its MAIN
         if(flag){
            // if preNode is MAIN element
            if(preNode->color[0]==color){
               preNode->F=DB[route[i]].site;
               DB[route[i]].site->S=preNode;             
            }
            else{
               preNode->N=DB[route[i]].site;
               DB[route[i]].site->S=preNode;         
            }
            DB[route[i]].color[1]=color;
            DB[route[i]].site->color[1]=color;   
         }
         //if its sub route
         else{
            preNode->F=DB[route[i]].site;
            DB[route[i]].site->S=preNode;
            DB[route[i]].color[1]=color;
            DB[route[i]].site->color[1]=color;  
         }
         //record preNode
         preNode=DB[route[i]].site;
         preNum=route[i];   
      }
   }
}
void ROUTE_PRINT(NODE *route){
   if(route->name==-1) route=route->F;
   NODE *preNode;
   int color = route->color[0];
   printf("START |-");
   while(route){
      printf("[%d", route->name); 
      if(route->N) printf("(N:%d)", route->N->name);
      if(route->S) printf("(S:%d)", route->S->name);
      printf("]-");
      
      if(color == route->color[0])
         { preNode=route; route=route->F; }
      else
         { preNode=route; route=route->N; }
   }
   printf("| END\n");
}
NODE* ROUTE_SELETION(MAP *map, int color){
   NODE *ret;
   switch(color){
      case 0: ret=map->red; break;
      case 1: ret=map->yellow; break;
      case 2: ret=map->blue; break;
      case 3: ret=map->green; break;
      case 4: ret=map->brown; break;
      default: break;
   }
   return ret;
}
void FILE_GET(char *file, int *input, int *size){
   FILE *fptr = fopen(file, "r");
   char ch, str[MAX_SIZE][MAX_ID_SIZE];
   int j=0, i=0, flag=0;
   if(fptr){
      while( (ch=getc(fptr))!= EOF ){
         while( ch>='0'&&ch<='9'&&ch!=EOF) { str[j][i]=ch; i++; ch=getc(fptr); flag=1; }
         if(flag) { str[j][i]='\0'; sscanf(str[j],"%d",&input[j]); j++; flag=0; i=0; }
      }
   }else printf("\n\tfaild to open the file!\n");
   size[0]=j;
   fclose(fptr);
}
void TABLE_PRINT(TABLE *list, int size){
   printf("[NAME]\t[COLOR]\t[SITE]\n");
   for(int i=0;i<size;i++){
      if(list[i].name!=-1){
         if(list[i].color[1]==-1) printf("%d\t%d\t%p\n", list[i].name, list[i].color[0], list[i].site);
         else printf("%d\t(%d,%d)\t%p\n", list[i].name, list[i].color[0], list[i].color[1], list[i].site);
      }
   }
}
void MAP_INIT(MAP *map){
   map->red=(NODE*)malloc(sizeof(NODE)); map->red->name=-1; map->red->F=NULL;
   map->yellow=(NODE*)malloc(sizeof(NODE)); map->yellow->name=-1; map->yellow->F=NULL;
   map->blue=(NODE*)malloc(sizeof(NODE)); map->blue->name=-1; map->blue->F=NULL;
   map->green=(NODE*)malloc(sizeof(NODE)); map->green->name=-1; map->green->F=NULL;
   map->brown=(NODE*)malloc(sizeof(NODE)); map->brown->name=-1; map->brown->F=NULL;   
}
void TABLE_INIT(TABLE *list, int size){
   for(int i=0;i<size;i++){
      list[i].name = -1;
      for(int j=0;j<ROUTE_NUM;j++) list[i].color[j] = -1;
   }
}
