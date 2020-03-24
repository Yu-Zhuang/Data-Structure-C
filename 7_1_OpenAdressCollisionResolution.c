#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*
一個空間為30的array
@放入30個random數字 (-32786~32767)
用hash()去放
@collinsion resolution: open address;
@search: use the same hash(); input: element; output: comparison times and address;
@delete element: input element, output: comparison times and adress;
@print table status;
*功能:
1. 選擇查找元素 (找的到or找不到);
2. 選擇執行次數, 統計平均比較次數;
3. 刪除元素;
4. 新增元素;
*/
// difine
#define DBSIZE 30 //size of database 
#define NSIZE 30 //size of origin input
#define MAX 32767 // max of data range
typedef struct table{
	int val;
	int start;
	int next;
}TABLE;
//function annoucement
void initDB(TABLE *DB, int size); //initialize DB;
void insertDB(TABLE *DB, int DBsize, int element, int *site); //insert element to databse;
int findDB(TABLE *DB, int DBsize, int element, int* Ctimes); //conparison times
void deleteDB(TABLE *DB, int DBsize, int element);  //delete element in database
void printDB(TABLE *DB, int DBsize); //print database status

int Hash(int element, int DBsize); //hash function
int CRS(TABLE *DB, int adress, int DBsize); //collision resolution

void createInput(int *nums, int numsSize); //create new input nums[];
int checkArray(int *nums, int numsSize); //check each element is unique in array
//main 
int main(void){
	srand(time(NULL));
//variable
	TABLE DB[DBSIZE];
	int input[NSIZE], site[NSIZE], Ctimes=0, Nfind=0, flag=1;
	double Ctotal=0;
	for(int i=0;i<NSIZE;i++) site[i]=-1;
//compution
	while(flag){
		printf("\t=====================================\n");
		printf("\t==Open Address Collision Resolution==\n");
		printf("\t=====================================\n");
		printf("\t\t@程式主選單@\n");
		printf("\t(1)執行一次.\n\t(2)執行n次,統計平均查找次數.\n\t(3)查詢元素.\n\t(4)刪除元素.\n\t(0)結束程式.\n\t請輸入: ");
		scanf("%d", &flag);
		if(flag == 0) break;
		else if(flag==3 || flag==4){
		//find element
			if(flag==3){
				printf("輸入欲查找元素: ");	scanf("%d", &flag);
				printf("\n************* Find Element **************\n");
				Nfind+=findDB(DB, DBSIZE, flag, &Ctimes);
				printf("comparison times: %d\n", Ctimes);
				printf("\n************* END Find **************\n");
			}
		//delete element
			if(flag==4){
				printf("輸入欲刪除元素: ");	scanf("%d", &flag);
				deleteDB(DB, DBSIZE, flag);
				printDB(DB, DBSIZE);
			}
		}
		else if(flag==1 || flag==2){
			Ctotal=0; Nfind=0; 
			int times=1; 
			if(flag == 2){ printf("執行次數: "); scanf("%d", &times); }
			for(int i=0;i<times;i++){
				Ctimes=0; 
			//generate input[];
				createInput(input, NSIZE);
			//initialize database[];
				initDB(DB,DBSIZE);
			//insert input[] to database[] use hash() and CRS();
				printf("\n************* InsertElement **************\n");
				printf("[No.]\t[VALUE]\t[SITE]\n");
				for(int i=0;i<NSIZE;i++){
					insertDB(DB, DBSIZE, input[i], &site[i]);
					printf("%d\t%d\t%d\n", i+1, input[i], site[i]);
				}
				// check whether each element/site is unique or not in array;
				if(checkArray(site, NSIZE)==0) printf("site[]中沒有重複元素\n");
				else printf("site有 %d 個重複元素\n", checkArray(site, NSIZE));
				if(checkArray(input, NSIZE)==0) printf("input[]中沒有重複元素\n");
				else printf("input[]有 %d 個重複元素\n", checkArray(input, NSIZE));
				printf("\n************* END InsertElement **************\n");
			// print database status;
				printDB(DB, DBSIZE);
			//find element;
				if(flag==2){
					printf("\n************* Find Element **************\n");
					int tmp=input[rand()%30];
					Nfind+=findDB(DB, DBSIZE, tmp, &Ctimes);
					printf("comparison times: %d\n", Ctimes);
					Ctotal += Ctimes; 
					printf("\n************* END Find **************\n");	
				}
			}
		// 統計comparison times;
			if(flag==2){
				printf("沒找到次數: %d\n", Nfind);
				printf("平均查找次數: %lf\n", (double)Ctotal/times);
			}
		}
		printf("\n繼續請按 1 , 結束請按0 : "); scanf("%d", &flag);
	}
//end
	return 0;
}
//delete element in data base
void deleteDB(TABLE *DB, int DBsize, int element){
	int adress= Hash(element, DBsize), tmp=0, preadress=0;
	printf("Target: %d\nPrimary ddress: %d\n", element, adress);
	if( (DB[adress].val==element) && (DB[adress].start!=adress) ) 
		{ printf("Find at: %d\n", adress); DB[adress].next=-2; return ; }
	if(DB[adress].start>-1 || DB[adress].next>-1){
		//find through pedigree
		if(DB[adress].start>-1){
			preadress = adress;
			tmp = DB[adress].start;
			if(DB[tmp].val == element){
				printf("Find at: %d\n", tmp);
				if(DB[tmp].next <0) {DB[tmp].next=-2; DB[preadress].start=-1; return; } //delete pedigree;
				else if(DB[tmp].next >-1) { DB[preadress].start=DB[tmp].next; DB[tmp].next=-2; return; } //change start to tmp.next;
			}
			while(DB[tmp].next>-1){
				preadress = tmp;
				tmp = DB[tmp].next;
				if(DB[tmp].val == element){ 
					printf("Find at: %d\n", tmp);
					if(DB[tmp].next > -1) { DB[preadress].next=DB[tmp].next; DB[tmp].next=-2; return; }
					else { DB[preadress].next=-1; DB[tmp].next=-2; return; }
				}
			}
		}
		//find through next
		tmp=adress;
		while(DB[tmp].next>-1){
			preadress = tmp;
			tmp = DB[tmp].next;
			if(DB[tmp].val == element){ 
				printf("Find at: %d\n", tmp);
				if(DB[tmp].next > -1) { DB[preadress].next=DB[tmp].next; DB[tmp].next=-2; return; }
				else { DB[preadress].next=-1; DB[tmp].next=-2; return; }
			}
		}

	}
	printf("Not find!\n");
}

//find element
int findDB(TABLE *DB, int DBsize, int element, int* Ctimes){
	int adress= Hash(element, DBsize), tmp=0;
	printf("Target: %d\nPrimary adress: %d\n", element, adress);
	if(DB[adress].val == element) { printf("find at: %d\n", adress); *Ctimes=1; return 0; }
	if(DB[adress].start>-1 || DB[adress].next>-1){
		tmp=adress;
		while(DB[tmp].next>-1){
			*Ctimes+=1;
			tmp = DB[tmp].next;
			if(DB[tmp].val == element) { printf("find at: %d\n", tmp); return 0; }
		}
		if(DB[adress].start>-1){
			tmp = DB[adress].start;
			if(DB[tmp].val == element) { printf("find at: %d\n", adress); *Ctimes=1; return 0; }
			while(DB[tmp].next>-1){
				*Ctimes+=1;
				tmp = DB[tmp].next;
				if(DB[tmp].val == element) { printf("find at: %d\n", tmp); return 0; }
			}
		}
	}
	printf("Not find!\n");
	return 1;
}
// hash function();
int Hash(int element, int DBsize){
	if(element < 0) return (element*-1)%DBsize;
	return element%DBsize;
}
// collision resolution ;
int CRS(TABLE *DB, int adress, int DBsize){
	while(DB[adress].next!=-2) adress=(adress+1)%DBsize;
	return adress;
}
//insert element to databse;
void insertDB(TABLE *DB, int DBsize, int element, int *site){
	//hash 
	int adress = Hash(element, DBsize);
	// if start is empty;
	if(DB[adress].start == -1){
		if(DB[adress].next == -2)
			{ DB[adress].val=element; DB[adress].next=-1; DB[adress].start=adress; *site=adress;}
		else{
			int newadress = CRS(DB, adress, DBsize);
			DB[adress].start = newadress;
			DB[newadress].val = element; DB[newadress].next = -1;
			*site=newadress;
		}
	}
	else{
		adress = DB[adress].start;
		while(DB[adress].next>-1) adress = DB[adress].next;	
		if(DB[adress].next == -2) { DB[adress].val = element; *site=adress; }
		else if(DB[adress].next == -1){
			int newadress = CRS(DB, adress, DBsize);
			DB[adress].next = newadress;
			DB[newadress].val = element; DB[newadress].next = -1;	
			*site=newadress;		
		}
	}
}
//print database;
void printDB(TABLE *DB, int DBsize){
	printf("\n************* Print DataBase **************\n");
	printf("[No.]\t[VALUE]\t[START]\t[NEXT]\n");
	int tmp=0;
	for(int i=0;i<DBsize;i++){
		if(DB[i].next == -2) printf("%d\t(empty)\t%d\t%d\n", i, DB[i].start, DB[i].next);
		else printf("%d\t%d\t%d\t%d\n", i, DB[i].val, DB[i].start, DB[i].next);
	}
	printf("\n============= END Print DataBase =============\n");
}
//initialize database;
void initDB(TABLE* DB, int size){
	for(int i=0;i<size;i++) {  DB[i].start=-1; DB[i].next=-2; }
}
//create input data;
void createInput(int *nums, int numsSize){
	printf("\n************* Create Input **************\n");
	printf("[No.]\t[Data]\n");
	int charge[2]={1,-1};
	for(int i=0;i<numsSize;i++){
		if( ! (i%5) ) printf("\n%d.", i+1);
		nums[i]=(rand()%(MAX+1))*charge[rand()%2];
		printf("\t%d",nums[i]);
	}
	printf("\n============= END Create Input =============\n");
}
// check each element of array is unique or not 
int checkArray(int *nums, int numsSize){
	int ret=0;
	for(int i=0;i<numsSize-1;i++){
		for(int j=i+1;j<numsSize;j++){
			if(nums[i] == nums[j]) ret++;
		}
	}
	return ret;
}

