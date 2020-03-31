#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/*
功能:
1. 讀檔並寫入檔案
2. 搜尋資料
3. 新增資料
4. 刪除資料
5. 顯示資料庫狀態
*/
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
int DB_FIND(TABLE *DB, char *target, int *Ctimes);
int DB_DELETE(TABLE *DB, char *target, int *Ctimes);

int HASH(char *element);
int HASH_ORIGIN(char *element);
bool STR_SAME(char *templet, char *test);
// MAIN
int main(void){
//variable;
	TABLE DB[SPACE_SIZE]; for(int i=0;i<SPACE_SIZE;i++) DB[i].N=0; //data base;
	char input[INPUT_SIZE][STR_LEN], target[TEST_SIZE][STR_LEN]; //input and test file;
	char Ifile[]="1.cpp", Tfile[]="2.cpp"; // file;
	int Ctimes=0, Total=0, Ftimes=0, flag=1; //comparison times, total number of element in DB;
//compution
	while(flag){
		printf("\n\t@主選單@\n"); 
		printf("(1) 讀檔並寫入檔案\n(2) 搜尋資料\n(3) 新增資料\n(4) 刪除資料\n(5) 顯示資料庫狀態\n(6) 自動寫入並搜尋\n(7) 自動寫入並刪除\n(8) 自動刪除全部資料\n(0) 結束程式\n");
		printf("請輸入選擇: "); scanf("%d", &flag);
		Ctimes=0; Total=0; Ftimes=0;
		if(flag == 0 ) break;
		else if(flag == 1){
			GET_FILE(input, Ifile); GET_FILE(target, Tfile);
			for(int i=0;i<INPUT_SIZE;i++) DB_INSERT(DB, input[i]);
			DB_PRINT(DB,SPACE_SIZE);
		}else if(flag == 2){
			char str[STR_LEN];
			printf("請輸入欲搜尋ID: "); scanf("%[^\n]", str);
			Ftimes+=DB_FIND(DB, str, &Ctimes);
			printf("#Ctimes: %d\n", Ctimes);
		}else if(flag == 3){
			char str[STR_LEN];
			printf("請輸入欲新增ID: "); scanf("%[^\n]", str);
			DB_INSERT(DB, str);		
		}else if(flag == 4){
			char str[STR_LEN];
			printf("請輸入欲刪除ID: "); scanf("%[^\n]", str);
			DB_DELETE(DB, str, &Ctimes);			
		}else if(flag == 5) DB_PRINT(DB, SPACE_SIZE);
		else if(flag == 6){
			GET_FILE(input, Ifile); GET_FILE(target, Tfile);
			for(int i=0;i<INPUT_SIZE;i++) DB_INSERT(DB, input[i]);
			DB_PRINT(DB, SPACE_SIZE);
			for(int i=0;i<TEST_SIZE;i++) Ftimes+=DB_FIND(DB, target[i], &Ctimes);
			printf("\n==========================================\n");
			printf("#Ctimes: %lf\n#Ftimes: %d\n#NFtimes: %d\n", (double)Ctimes/TEST_SIZE, Ftimes, TEST_SIZE-Ftimes);
			printf("==========================================\n");
		}else if(flag == 7){
			GET_FILE(input, Ifile); GET_FILE(target, Tfile);
			for(int i=0;i<INPUT_SIZE;i++) DB_INSERT(DB, input[i]);
			DB_PRINT(DB, SPACE_SIZE);
			for(int i=0;i<TEST_SIZE;i++){
				if(DB_DELETE(DB, target[i], &Ctimes)) DB_PRINT(DB,SPACE_SIZE);
			}
		}else if(flag == 8){
			for(int i=0;i<INPUT_SIZE;i++) DB_DELETE(DB, input[i], &Ctimes);
			DB_PRINT(DB,SPACE_SIZE);
		}
		printf("繼續按 1, 結束按 0 : "); scanf("%d", &flag);
	}
//end
	return 0;
}
//FUNCTION
//delete element
int DB_DELETE(TABLE *DB, char *target, int *Ctimes){
	printf("*********** DB_DELETE ***********\n");
	int ret=0, address = HASH(target);
	if( (! DB_FIND(DB,target,Ctimes)) || DB[address].N==0) ret=0;
	else{
		NODE *ptr, *pre, *tmp;
		ptr=DB[address].next;
		pre=DB[address].next;
		//if(STR_SAME(target, ptr->val))
		while(ptr!=NULL) {
			if(STR_SAME(target, ptr->val)){ 
				ret=1; 
				if(DB[address].N==1) pre = NULL;
				else if(ptr == DB[address].next) DB[address].next = ptr->next;
				else pre->next = ptr->next;
				DB[address].N--;
				if(DB[address].N>0 &&(HASH_ORIGIN(ptr->val)==DB[address].max ||HASH_ORIGIN(ptr->val)==DB[address].min)){
					tmp = DB[address].next;
					DB[address].min = HASH_ORIGIN(tmp->val);
					DB[address].max = HASH_ORIGIN(tmp->val);
					while(tmp){
						if(HASH_ORIGIN(tmp->val)>DB[address].max) DB[address].max = HASH_ORIGIN(tmp->val);
						if(HASH_ORIGIN(tmp->val)<DB[address].min) DB[address].min = HASH_ORIGIN(tmp->val);
						tmp = tmp->next;
					}
				}
				break;
			}
			pre = ptr;
			ptr = ptr->next;
		}
	}
	printf("*********** END DB_DELETE ***********\n");
	return ret;
}
// find element
int DB_FIND(TABLE *DB, char *target, int *Ctimes){
	printf("Find target: %s (%d)\n", target, HASH(target));
	printf("Result: ");
	int num = HASH_ORIGIN(target),
		address = HASH(target), flag=0;
	NODE *ptr;

	Ctimes[0]+=1; //comparison times
	while(DB[address].N){
		Ctimes[0]+=2; //comparison times
		if(num>DB[address].max||num<DB[address].min) break; //not find
		ptr=DB[address].next;
		while(ptr!=NULL && num>=HASH_ORIGIN(ptr->val)){
			if(STR_SAME(ptr->val, target)) { printf("#Find at %d\n\n", address); return 1; }//find
			ptr=ptr->next;
			Ctimes[0]+=1; flag=1; //comparison times
		}
		if( ! flag) Ctimes[0]+=1; //comparison times
		break;
	}
	printf("( Not Find )\n\n");
	return 0;
}
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
		if(origin<HASH_ORIGIN(DB[address].next->val)){
			newnode->next = DB[address].next;
			DB[address].next = newnode;				
		}
		else if(DB[address].N==1) DB[address].next->next = newnode;	
		else if(DB[address].N>1){
			if(origin<HASH_ORIGIN(DB[address].next->val)){
				newnode->next = DB[address].next;
				DB[address].next = newnode;				
			}
			else{
				while(ptr->next!=NULL && origin>HASH_ORIGIN(ptr->next->val)) ptr=ptr->next;
				if(ptr->next) newnode->next=ptr->next;
				ptr->next=newnode;
			}
		}
		// max and min;
		if(origin<DB[address].min) DB[address].min=origin;
		if(origin>DB[address].max) DB[address].max=origin;
		DB[address].N++;
	}
	else{
		DB[address].next=newnode;
		DB[address].min=origin;
		DB[address].max=origin;
		DB[address].N++;
	}
}
// print data base
void DB_PRINT(TABLE *DB, int DBsize){
	printf("\n************** DB_PRINT ****************\n");
	NODE *ptr;
	int count=0, total=0;
	printf("[No.]\t[STATUS]\t[Value]\n");
	printf(" \tN|min|max\tval|num\n");
	printf("-------------------------------------------\n");
	for(int i=0;i<DBsize;i++){
		if( ! DB[i].N ) printf("%d\t%s \t%s\n\n", i, "(empty)","(empty)"); 
		else{
			count++;
			total+=DB[i].N;
			printf("%d\t%d/%d/%d\t\t", i, DB[i].N,DB[i].min, DB[i].max);
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
	printf("\t= #Theoretical Load Factor: %.2lf =\n", (double)total/SPACE_SIZE);
	printf("\t= #Real Load Factor: %.2lf        =\n", (double)count/SPACE_SIZE);
	printf("\t==================================\n");
	printf("\n************** END DB_PRINT ****************\n");
}
// hash()
int HASH(char *element){
	int ret=0;
	ret=element[0];
	ret+=element[2]%10*7;
	ret+=(element[5]*10+element[6])*111;
	return ret%(SPACE_SIZE-1);
}
// 排序用
int HASH_ORIGIN(char *element){
	int ret=0, i=0;
	while(element[i]!='\0') { ret+=element[i]-'0'; i++; }
	return ret;
}
// whether str1 and str2 has the same value
bool STR_SAME(char *templet, char *test){
	int templet_len = strlen(templet),
		test_len = strlen(test);
	int i=0;
	while(templet[i]==test[i]&&templet[i]!='\0'&&test[i]!='\0') i++;
	if(i==test_len&&i==templet_len) return true;
	return false;
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