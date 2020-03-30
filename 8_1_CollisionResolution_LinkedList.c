#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
// DEFINE SIZE
#define SPACE_SIZE 50
#define INPUT_SIZE 72
#define TEST_SIZE 48
#define STR_LEN 7
// TYPE DEFINE
typedef struct node{
	char val[STR_LEN];
	struct node *next;
}NODE;
typedef struct array{
	int N;
	int max;
	int min;
	NODE *next;
}TABLE;
// FUNCTION ANNOUCEMENT
void GET_FILE(char str[][STR_LEN], char *file);

void DB_INSERT(TABLE *DB, char *element);
void DB_PRINT(TABLE *DB, int DBsize);

int HASH(char *element);
int HASH_ORIGIN(char *element);
//void CRS(TABLE *DB, char *element);
// MAIN
int main(void){
//variable;

	TABLE DB[SPACE_SIZE]; for(int i=0;i<SPACE_SIZE;i++) DB[i].N=0; //data base table;
	char input[INPUT_SIZE][STR_LEN], target[TEST_SIZE][STR_LEN];
	char Ifile[]="1.cpp", Tfile[]="2.cpp";
//compution
	//get input file
	GET_FILE(input, Ifile);
	//get test file
	GET_FILE(target, Tfile);
	//
	for(int i=0;i<INPUT_SIZE;i++) DB_INSERT(DB, input[i]);
	//
	DB_PRINT(DB, SPACE_SIZE);
//end
	return 0;
}
//FUNCTION

//insert element to DB
void DB_INSERT(TABLE *DB, char *element){
// HASH()
	int address = HASH(element);
// new node
	int i=0, origin=HASH_ORIGIN(element);
	NODE *newnode = (NODE*)malloc(sizeof(NODE)), *ptr;
	if(newnode==NULL) { printf("記憶體已滿\n"); return; }

	strcpy(newnode->val, element); newnode->next=NULL;
//compution
	if(DB[address].N){
		ptr = DB[address].next;
		// insert (sorted)
		if(DB[address].N==1 && origin<HASH_ORIGIN(DB[address].next->val)){
			newnode->next = DB[address].next;
			DB[address].next = newnode;
		}
		if(DB[address].N>1){
			while(ptr->next!=NULL && origin>HASH_ORIGIN(ptr->next->val)) ptr=ptr->next;
			if(ptr->next) newnode->next=ptr->next;
			ptr->next=newnode;
		}
		// max and min;
		if(origin<DB[address].min) DB[address].min=origin;
		if(origin>DB[address].max) DB[address].max=origin;
	}
	else{
		DB[address].next=newnode;
		DB[address].min=origin;
		DB[address].max=origin;
	}
	DB[address].N++;
}
// hash()
int HASH(char *element){
	int ret=0;
	ret=element[0];
	ret+=element[2]%10*7;
	ret+=(element[5]*10+element[6])*111;
	return ret%(SPACE_SIZE-1);
}
int HASH_ORIGIN(char *element){
	int ret=0, i=0;
	while(element[i]!='\0') { ret+=element[i]-'0'; i++; }
	return ret;
}
// print data base
void DB_PRINT(TABLE *DB, int DBsize){
	printf("\n************** DB_PRINT ****************\n");
	NODE *ptr;
	int count=0;
	printf("[No.]\t[STATUS]\t[Value]\n");
	printf(" \tN|max|min\tval|num\n");
	printf("-------------------------------------------\n");
	for(int i=0;i<DBsize;i++){
		if( ! DB[i].N ) printf("%d\t%s \t%s\n\n", i, "(empty)","(empty)"); 
		else{
			count++;
			printf("%d\t%d/%d/%d\t\t", i, DB[i].N,DB[i].max, DB[i].min);
			ptr=DB[i].next;
			while(ptr!=NULL) { printf("[%s]->", ptr->val); ptr=ptr->next; }
			printf("|\n");
			// print origin 
			ptr=DB[i].next;
			printf(" \t \t \t");
			while(ptr!=NULL) { printf("[%d]->", HASH_ORIGIN(ptr->val)); ptr=ptr->next; }
			printf("|\n");
		}
	}
	printf("-------------------------------------------\n");
	printf("\t==================================\n");
	printf("\t= #Theoretical Load Factor: %.2lf =\n", (double)INPUT_SIZE/SPACE_SIZE);
	printf("\t= #Real Load Factor: %.2lf        =\n", (double)count/SPACE_SIZE);
	printf("\t==================================\n");
	printf("\n************** END DB_PRINT ****************\n");
}
// get value from file
void GET_FILE(char str[][STR_LEN], char *file){
	FILE *fptr=fopen(file,"r");
	char ch;
	int i=0, j=0, flag=0;

	while((ch=getc(fptr))!=EOF){
		while(ch>='0'&&ch<='9'&&ch!=EOF) { str[i][j]=ch; j++; flag=1; ch=getc(fptr); }	
		if(flag) { str[i][j]='\0'; j=0; i++; flag=0; }
	}
	fclose(fptr);
}

