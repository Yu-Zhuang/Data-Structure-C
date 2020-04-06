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
typedef struct map{
   struct map *red;
   struct map *yellow;
   struct map *blue;
   struct map *green;
   struct map *brown;
}MAP;
typedef struct route{
   int name;
   int color;
   struct route *B, *F;
}NODE;
typedef struct table{
   int name;
   int color;
   NODE *site;
}TABLE; 
// ***** FUNCTION ANNOUNCEMENT *****
void FILE_GET(char *file, int *input, int *size);

void IOTA(char *string, int *interget);

void TABLE_INSERT(TABLE *list, int element, int color, int *total);
void TABLE_INIT(TABLE *list, int size);
void TABLE_PRINT(TABLE *list, int total);
// ***** MAIN *****
int main(void){
   // varialbe announcement
   char file[ROUTE_NUM][6]={"1.cpp", "2.cpp", "3.cpp", "4.cpp", "5.cpp"};
   int input[ROUTE_NUM][MAX_SIZE], size[ROUTE_NUM]={0}, total=0;
   TABLE DB[MAX_SIZE];
   TABLE_INIT(DB, MAX_SIZE);
   MAP map;
//compution
   // get file
   for(int i=0;i<ROUTE_NUM;i++) FILE_GET(file[i],input[i], &size[i]);
   // put file in to table
   for(int i=0;i<ROUTE_NUM;i++)
      for(int j=0;j<size[i];j++) TABLE_INSERT(DB, input[i][j], i, &total);


   TABLE_PRINT(DB, total);
   //END
   return 0;
}
// ***** FUNCTION *****

void TABLE_INSERT(TABLE *list, int element, int clr, int *total){
   if(! list[element].name){
      list[element].name = element;
      list[element].color = clr;
      total[0]+=1;
   }
}
// print
void TABLE_PRINT(TABLE *list, int total){
   for(int i=0;i<total;i++){
      if(list[i].name == 0) { printf("%d.\t{ (empty) }\n", i); total++; }
      else printf("%d.\t{ name:%d,\tcolor:%d }\n", i, list[i].name, list[i].color);
   }
}
void TABLE_INIT(TABLE *list, int size){
   for(int i=0;i<size;i++){
      list[i].name = 0;
      list[i].color = 0;
   }
}
//
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
void IOTA(char *string, int *interget){
   int str_len = strlen(string);
   int ten=1, i=0;
   interget[0] = 0;
   for(int i=1;i<str_len;i++) ten*=10;
   while(ten) { interget[0]+=ten*(string[i]-'0'); i++; ten/=10; }  
}

