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
6. 自動寫入並搜尋
7. 自動寫入並刪除
8. 自動刪一增一
9. 清空資料庫
10. 產隨機檔執行n次統計
*/
// DEFINE SIZE
#define SPACE_SIZE 50	//size of table 
#define INPUT_SIZE 72	//size of input
#define TEST_SIZE 48	//size of testFile
#define STR_LEN 7	//size of each element
// TYPE DEFINE
typedef struct node{
	char val[STR_LEN];
	struct node *next;
}NODE;
typedef struct array{
	int N; //numbers of element in the pedigree
	int max; 
	int min;
	NODE *next;
}TABLE;
// FUNCTION ANNOUCEMENT
void DB_INSERT(TABLE *DB, char *element);
int DB_PRINT(TABLE *DB, int DBsize);
int DB_FIND(TABLE *DB, char *target, int *Ctimes);
int DB_DELETE(TABLE *DB, char *target, int *Ctimes);
void DB_INIT(TABLE *DB, int DBsize);

int HASH(char *element);
int HASH_ORIGIN(char *element);
void GET_FILE(char str[][STR_LEN], char *file);	// get file content
void GENERATE_FILE(char *file, int size); //generate a file
bool STR_SAME(char *templet, char *test); //whether str1 and str2 is the same
// MAIN
int main(void){
	srand(time(NULL));
//variable;
	TABLE DB[SPACE_SIZE]; for(int i=0;i<SPACE_SIZE;i++) DB[i].N=0; //data base;
	char input[INPUT_SIZE][STR_LEN], target[TEST_SIZE][STR_LEN]; //input and test file;
	char Ifile[]="1.cpp", Tfile[]="2.cpp"; // file;
	int Ctimes=0, Total=0, Ftimes=0, flag=1; //comparison times, total number of element in DB;
//compution
	while(flag){
		printf("\n\t**************************************\n");
		printf("\t*  Linked List Collision Resolution  *\n");
		printf("\t**************************************\n");
		printf("\t\t\t@主選單@\n"); 
		printf("\t(1) 讀檔並寫入檔案\n\t(2) 搜尋資料\n\t(3) 新增資料\n\t(4) 刪除資料\n\t(5) 顯示資料庫狀態\n\t(6) 自動寫入並搜尋\n\t(7) 自動寫入並刪除\n\t(8) 自動刪一增一\n\t(9) 清空資料庫\n\t(10) 產隨機檔執行n次統計\n\t(0) 結束程式\n");
		printf("\t請輸入選擇: "); scanf("%d", &flag);
		Ctimes=0; Total=0; Ftimes=0;
	//結束程式
		if(flag == 0 ) break;
	//讀檔並寫入檔案
		else if(flag == 1){
			GET_FILE(input, Ifile); GET_FILE(target, Tfile);
			for(int i=0;i<INPUT_SIZE;i++) DB_INSERT(DB, input[i]);
			DB_PRINT(DB,SPACE_SIZE);
	//搜尋資料
		}else if(flag == 2){
			char str[STR_LEN];
			printf("請輸入欲搜尋ID: "); getchar(); scanf("%[^\n]", str); 
			Ftimes+=DB_FIND(DB, str, &Ctimes);
			printf("#Ctimes: %d\n", Ctimes);
	//新增資料
		}else if(flag == 3){
			char str[STR_LEN];
			printf("請輸入欲新增ID: "); getchar(); scanf("%[^\n]", str);
			DB_INSERT(DB, str);	
	//刪除資料	
		}else if(flag == 4){
			char str[STR_LEN];
			printf("請輸入欲刪除ID: "); getchar(); scanf("%[^\n]", str);
			DB_DELETE(DB, str, &Ctimes);	
	//顯示資料庫狀態	
		}else if(flag == 5) DB_PRINT(DB, SPACE_SIZE);
	//自動寫入並搜尋
		else if(flag == 6){
			GET_FILE(input, Ifile); GET_FILE(target, Tfile);
			for(int i=0;i<INPUT_SIZE;i++) DB_INSERT(DB, input[i]);
			DB_PRINT(DB, SPACE_SIZE);
			for(int i=0;i<TEST_SIZE;i++) Ftimes+=DB_FIND(DB, target[i], &Ctimes);
			printf("\n==========================================\n");
			printf("#Ctimes: %lf\n#Ftimes: %d\n#NFtimes: %d\n", (double)Ctimes/TEST_SIZE, Ftimes, TEST_SIZE-Ftimes);
			printf("==========================================\n");
	//自動寫入並刪除
		}else if(flag == 7){
			GET_FILE(input, Ifile); GET_FILE(target, Tfile);
			for(int i=0;i<INPUT_SIZE;i++) DB_INSERT(DB, input[i]);
			DB_PRINT(DB, SPACE_SIZE);
			for(int i=0;i<INPUT_SIZE;i++){
				if(DB_DELETE(DB, input[i], &Ctimes)) DB_PRINT(DB,SPACE_SIZE);
			}
	//自動刪一增一
		}else if(flag == 8){
			GET_FILE(input, Ifile); GET_FILE(target, Tfile);
			for(int i=0;i<INPUT_SIZE;i++) DB_INSERT(DB, input[i]);
			DB_PRINT(DB,SPACE_SIZE);
			for(int i=0;i<INPUT_SIZE;i++) { DB_DELETE(DB, input[i], &Ctimes); DB_INSERT(DB, input[i]); }
			DB_PRINT(DB,SPACE_SIZE);
			// total 
			int Total=0;
			for(int i=0;i<SPACE_SIZE;i++) Total+=DB[i].N;
			printf("Total: %d\n", Total);
		}
	//清空資料庫
		else if(flag == 9){
			DB_INIT(DB, SPACE_SIZE);
	//跑n次 執行統計
		}else if(flag == 10){
			char str1[]="3.cpp", str2[]="4.cpp";
			int str1_size=0, str2_size=0, run=0, TLF=0; //TLF (total load factor)
		//input 
			printf("請輸入執行次數: "); scanf("%d", &run);
			printf("請輸入Input File大小: "); scanf("%d", &str1_size);
			printf("請輸入Test File大小: "); scanf("%d", &str2_size);
		// compution
			for(int i=0;i<run;i++){
			//initialize
				DB_INIT(DB, SPACE_SIZE);
				for(int i=0;i<str1_size;i++) memset(input[i],'\0',STR_LEN);
				for(int i=0;i<str2_size;i++) memset(target[i],'\0',STR_LEN);
			//compution
				GENERATE_FILE(str1, str1_size); //input file size
				GENERATE_FILE(str2, str2_size); //test file size
				GET_FILE(input, str1); 
				GET_FILE(target, str2);
				for(int i=0;i<INPUT_SIZE;i++) DB_INSERT(DB, input[i]);
				TLF+=DB_PRINT(DB, SPACE_SIZE);
				for(int i=0;i<TEST_SIZE;i++) Ftimes+=DB_FIND(DB, target[i], &Ctimes);
			}
			
			printf("\n==========================================\n");
			printf("\t \t[ Average ]\n");
			printf("\t#Ctimes: %.2lf\n\t#Ftimes: %.2lf\n\t#Theoretical Load Factor: %.2lf\n\t#Real Load Factor: %.2lf\n", (double)Ctimes/(TEST_SIZE*run), (double)Ftimes/run, (double)str1_size/SPACE_SIZE, (double)TLF/(SPACE_SIZE*run));
			printf("==========================================\n");
		}
		printf("繼續按 1, 結束按 0 : "); scanf("%d", &flag);
	}
//end
	return 0;
}
//FUNCTION
void DB_INIT(TABLE *DB, int DBsize){
	for(int i=0;i<DBsize;i++){
		if(DB[i].N>1){
			NODE *ptr=DB[i].next, *tmp;
			while(ptr!=NULL) { tmp=ptr; ptr=ptr->next; if(tmp) free(tmp); }
			DB[i].next=NULL;
			DB[i].N=0; DB[i].max=0; DB[i].min=0;
		}else if(DB[i].N == 1){
			free(DB[i].next);
			DB[i].next=NULL;
			DB[i].N=0; DB[i].max=0; DB[i].min=0;
		}
	}
}
//delete element
int DB_DELETE(TABLE *DB, char *target, int *Ctimes){
	printf("*********** DB_DELETE ***********\n");
	int ret=0, address = HASH(target);
// if no target in DB
	if( (! DB_FIND(DB,target,Ctimes)) || DB[address].N==0) ret=0;
// has target in DB
	else{
		NODE *ptr, *pre, *tmp, *del;
		ptr=DB[address].next;
		pre=DB[address].next;
		while(ptr!=NULL) {
			if(STR_SAME(target, ptr->val)){ 
				ret=1; 
			// delete element
				if(DB[address].N==1) { DB[address].next=NULL; free(ptr); } 
				else if(ptr == DB[address].next) 
					{ DB[address].next=ptr->next; free(ptr); }
				else { pre->next = ptr->next; free(ptr); }
				DB[address].N--;
			// adjust DB[address]. min max
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
	printf("Target: %s (%d)\n", target, HASH(target));
	printf("Result: ");
	int num = HASH_ORIGIN(target),
		address = HASH(target), flag=0;
	NODE *ptr;

	while(DB[address].N){ 
		if(num>DB[address].max||num<DB[address].min) break; //not find
		ptr=DB[address].next;
		while(ptr!=NULL){	
			Ctimes[0]+=1; //comparison times
			if(STR_SAME(ptr->val, target)) { printf("#Find at %d\n\n", address); return 1; }//find
			ptr=ptr->next;
			if(ptr&&num<HASH_ORIGIN(ptr->val)) break;	
		}
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
int DB_PRINT(TABLE *DB, int DBsize){
	printf("\n************** DB_PRINT ****************\n");
	NODE *ptr;
	int count=0, total=0; //count: 放到 table 無CRS的數量, total:總放入數量;
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
			// print origin num
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
	return count;
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
void GENERATE_FILE(char *file, int size){
	FILE *fptr=fopen(file,"w");
	char str[STR_LEN]="801017";
	for(int i=0;i<size;i++){
		str[0]=(rand()%5+5)+'0';
		str[1]=(rand()%4)+'0';
		str[2]=rand()%6+'0';
		str[3]=rand()%2+'0';
		str[4]=rand()%2+'0';
		str[5]=rand()%10+'0';
		fputs(str,fptr);
		fputc('\n',fptr);
	}
	fclose(fptr);
}

