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
   int color;
   struct route *B, *F;
   struct route *W, *S;
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
// ***** FUNCTION ANNOUNCEMENT *****
void FILE_GET(char *file, int *input, int *size);

void IOTA(char *string, int *interget);

void TABLE_INSERT(TABLE *list, int element, int color, int *total, MAP *map);
void TABLE_INIT(TABLE *list, int size);
void TABLE_PRINT(TABLE *list, int total);

NODE* MAP_INSERT(MAP *map, int name, int color, NODE *site);
// ***** MAIN *****
int main(void){
   // varialbe announcement
   char file[ROUTE_NUM][6]={"1.cpp", "2.cpp", "3.cpp", "4.cpp", "5.cpp"};
   int input[ROUTE_NUM][MAX_SIZE], size[ROUTE_NUM]={0}, total=0;
   TABLE DB[MAX_SIZE];
   TABLE_INIT(DB, MAX_SIZE);
   MAP map;
   map.red=(NODE*)malloc(sizeof(NODE)); map.red->F=NULL;
   map.yellow=(NODE*)malloc(sizeof(NODE)); map.yellow->F=NULL;
   map.blue=(NODE*)malloc(sizeof(NODE)); map.blue->F=NULL;
   map.green=(NODE*)malloc(sizeof(NODE)); map.green->F=NULL;
   map.brown=(NODE*)malloc(sizeof(NODE)); map.brown->F=NULL;
   // CONPITION
   // get file
   for(int i=0;i<ROUTE_NUM;i++) FILE_GET(file[i],input[i], &size[i]);
   // put file in to table and add to map
   for(int i=0;i<ROUTE_NUM;i++)
      for(int j=0;j<size[i];j++) TABLE_INSERT(DB, input[i][j], i, &total, &map);
   //print table
   TABLE_PRINT(DB, total);
   // print map
   //MAP_PRINT(&map);
   //END
   return 0;
}
// ***** FUNCTION *****
NODE* MAP_INSERT(MAP *map, int name, int color, NODE *site){
   NODE *ptr, *pre;
   switch(color){
      case 0: ptr = map->red; break;
      case 1: ptr = map->yellow; break;
      case 2: ptr = map->blue; break;
      case 3: ptr = map->green; break;
      case 4: ptr = map->brown; break;
      default: break;
   }
   if(site==NULL){
      NODE *newnode = (NODE*)malloc(sizeof(NODE));
      newnode->name=name; newnode->color=color;
      newnode->W=NULL; newnode->S=NULL; newnode->F=NULL; newnode->B=NULL;
      //if pedigree is empty
      //else
      int deri=0;
      while(ptr){
         pre=ptr;
         ptr=ptr->F; 
         deri=0;
         if(ptr!=NULL && ptr->color!=color) { ptr = pre->W; deri=1; }
      }
      if(deri == 0){
         newnode->F = pre->F;
         pre->F = newnode;
         newnode->B = pre;
         return newnode;          
      }
      else if(deri==1){
         newnode->F = pre->W;
         pre->W = newnode;
         newnode->B = pre;
         return newnode; 
      }
   }
   else{
      int flag=0;
      while(ptr!=NULL) { 
         pre=ptr; 
         ptr=ptr->F; 
         if(ptr!=NULL && ptr->color!=color) { ptr = pre->W; flag=1; }
      }
      pre->F = site;
      site->S = pre;  
   }

   return site;
}
// TABLE
void TABLE_INSERT(TABLE *list, int element, int clr, int *total, MAP *map){
   if(list[element].name == -1){
      list[element].name = element;
      list[element].color[0] = clr;
      list[element].site = MAP_INSERT(map, element, clr, NULL);
      total[0]+=1;
   }else{
      list[element].name = element;
      list[element].color[1] = clr;
      MAP_INSERT(map, element, clr, list[element].site);
   }
}
//  table_print
void TABLE_PRINT(TABLE *list, int total){
   for(int i=0;i<total;i++){
      if(list[i].name == -1) { printf("%d.\t{ (empty) }\n", i); total++; }
      else if(list[i].color[1]!=-1) printf("%d.\t{ name:%d, color:%d %d,\tsite:%p }\n", i, list[i].name, list[i].color[0], list[i].color[1], list[i].site);
      else printf("%d.\t{ name:%d, color:%d,\tsite:%p }\n", i, list[i].name, list[i].color[0], list[i].site);
   }
}
void TABLE_INIT(TABLE *list, int size){
   for(int i=0;i<size;i++){
      list[i].name = -1;
      for(int j=0;j<ROUTE_NUM;j++) list[i].color[j] = -1;
   }
}
// FILE
void FILE_GET(char *file, int *input, int *size){
   FILE *fptr = fopen(file, "r");
   char ch, str[MAX_SIZE][MAX_ID_SIZE];
   int j=0, i=0, flag=0;
   if(fptr){
      while( (ch=getc(fptr))!= EOF ){
         while( ch>='0'&&ch<='9'&&ch!=EOF) { str[j][i]=ch; i++; ch=getc(fptr); flag=1; }
         if(flag) { str[j][i]='\0'; IOTA(str[j], &input[j]); j++; flag=0; i=0; }
      }
   }else printf("\n\tfaild to open the file!\n");
   size[0]=j;
   fclose(fptr);
}
// string to interger
void IOTA(char *string, int *interget){
   int str_len = strlen(string);
   int ten=1, i=0;
   interget[0] = 0;
   for(int i=1;i<str_len;i++) ten*=10;
   while(ten) { interget[0]+=ten*(string[i]-'0'); i++; ten/=10; }  
}


