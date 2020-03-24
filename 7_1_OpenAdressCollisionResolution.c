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
1. 產隨機值並放入database
2. 選擇執行次數, 統計平均比較次數 (可選一定找的到or一定找不到);
3. 查找元素 (可輸入找的到的or找不到的);
4. 刪除元素;
5. 新增元素;
6. 查一元素並刪掉 (automatically run through all database);
7. 刪一元素 並 新增回來 (automatically run through all database)；
*/
// difine
#define DBSIZE 30 //size of database 
#define NSIZE 30 //size of origin input
#define MAX 32768 // max of data range
typedef struct table{
	int val;
	int start;
	int next;
}TABLE;
//function annoucement
void initDB(TABLE *DB, int size); //initialize DB;
void insertDB(TABLE *DB, int DBsize, int element, int *site); //insert element to databse;
int findDB(TABLE *DB, int DBsize, int element, int* Ctimes); //conparison times
int deleteDB(TABLE *DB, int DBsize, int element, int *site);  //delete element in database
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
	int input[NSIZE], site[NSIZE], Ctimes=0, Nfind=0, flag=1, DBstatus=0;
	double Ctotal=0;
	for(int i=0;i<NSIZE;i++) site[i]=-1;
	initDB(DB,DBSIZE);
//compution
	while(flag){
		printf("\t=====================================\n");
		printf("\t= Open Address Collision Resolution =\n");
		printf("\t=====================================\n");
		printf("\t\t@程式主選單@\n");
		printf("\t(1) 自動產檔並放入資料庫.\n\t(2) 執行n次,統計平均查找次數.\n\t(3) 查詢元素.\n\t(4) 刪除元素.\n\t(5) 新增元素.\n\t(6) 依序刪除全部(要先按1產檔)\n\t(7) 依序增刪全部(要先按1產檔)\n\t(0) 結束程式.\n\t請輸入: ");
		scanf("%d", &flag);
		Nfind=0; Ctotal=0; Ctimes=0;
	//程式結束
		if(flag == 0) break;
	//依序增刪全部 (刪一增一);
		else if(flag == 7){
			for(int i=0;i<NSIZE;i++){
				int tmp;
			//delete one
				tmp=deleteDB(DB, DBSIZE, DB[i].val, site);
			//insert one
				insertDB(DB, DBSIZE, DB[i].val, site);
			}	
			printDB(DB, DBSIZE);		
		}
	//依序查找並刪全部 (查一刪一);
		else if(flag == 6){
			for(int i=0;i<NSIZE;i++){
				int temp, tmp;
			//find element
				temp=findDB(DB, DBSIZE, DB[i].val, &Ctimes);
				Nfind+=temp;
				Ctotal+=Ctimes;
			//delete element
				if(temp==0) tmp=deleteDB(DB, DBSIZE, DB[i].val, site);
				DBstatus-=tmp;
			}
			printf("\n============= 統計 ============\n");
			printf("\n沒找到次數: %d\n\n", Nfind);
			printf("總共查找:%lf\n平均查找:%lf\n", Ctotal, (double)Ctotal/NSIZE);
			printf("=================================\n");
		}
	//find or delete
		else if(flag==3 || flag==4){
		//find element
			if(flag==3){
				int tmp;
				printf("輸入欲查找元素: "); scanf("%d", &tmp);
				printf("\n************* Find Element **************\n");
				Nfind+=findDB(DB, DBSIZE, tmp, &Ctimes);
				Ctotal+=Ctimes;
				printf("comparison times: %d\n", Ctimes);
				printf("\n************* END Find **************\n");
			}
		//delete element
			if(flag==4){
				int tmp, temp;
				printf("輸入欲刪除元素: ");	scanf("%d", &tmp);
				temp=deleteDB(DB, DBSIZE, tmp, site);
				DBstatus-=temp; 
				if(temp) printDB(DB, DBSIZE);
			}
		}
	//insert element
		else if(flag==5){
			int tmp=1;
			if(DBstatus==NSIZE){
				printf("資料庫 已滿!\n");
				tmp=0;
			}
			if(tmp){
				printf("輸入欲新增元素: "); scanf("%d", &tmp);
				insertDB(DB, DBSIZE, tmp, site);
				printDB(DB, DBSIZE);
				DBstatus+=1;
			}
		}
	// normal run
		else if(flag==1 || flag==2){
			Ctotal=0; Nfind=0; 
			DBstatus=NSIZE;
			int times=1; 
			if(flag == 2){ 
				printf("執行次數: "); scanf("%d", &times); 
				printf("查找 (3)有的元素 or (4)沒有的元素: "); scanf("%d", &flag);
			}
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
				int check=checkArray(site, NSIZE);
				printf("\nsite[]有無重複確認: ");
				if(check==0) printf("\nsite[]中沒有重複元素\n");
				else printf("\nsite有 %d 個重複元素\n", check);
				check=checkArray(input, NSIZE);
				printf("input[]有無重複確認: ");
				if(check==0) printf("\ninput[]中沒有重複元素\n");
				else printf("\ninput[]有 %d 個重複元素\n", check);
				printf("\n************* END InsertElement **************\n");
			// print database status;
				printDB(DB, DBSIZE);
			//find element;
				if(flag==3 || flag==4){
					printf("\n************* Find Element **************\n");
					int tmp;
					if(flag==3) tmp=input[rand()%30];
					else tmp=MAX+1;
					Nfind+=findDB(DB, DBSIZE, tmp, &Ctimes);
					printf("comparison times: %d\n", Ctimes);
					Ctotal += Ctimes; 
					printf("\n************* END Find **************\n");	
				}
			}
		// 統計comparison times;
			if(flag==3 || flag==4){
				printf("\n=========== 統計結果 =============\n");
				printf("\t#沒找到次數: %d\n", Nfind);
				printf("\t#平均查找次數: %lf\n", (double)Ctotal/times);
				printf("\n=================================\n");
			}
		}
		printf("\n繼續請按 1 , 結束請按0 : "); scanf("%d", &flag);
	}
//end
	return 0;
}
//delete element in data base
int deleteDB(TABLE *DB, int DBsize, int element, int *site){
// address = hash (element);
	int adress= Hash(element, DBsize), tmp=0, preadress=0;
	printf("Target: %d\nPrimary ddress: %d\n", element, adress);
// condition: delete the pedigree
	if( (DB[adress].val==element) && (DB[adress].start==adress) && (DB[adress].next<0) )
		{ printf("Find at: %d\n", adress); DB[adress].next=-2; DB[adress].start=-1 ;site[adress]=-1; return 1; }
// else
	if(DB[adress].start>-1 || DB[adress].next>-1){
	// find element through "start" to "the pedigree"
		if(DB[adress].start>-1){
			preadress = adress;
			tmp = DB[adress].start;
			//condition: element is head of the pedigree
			if(DB[tmp].val == element){
				printf("Find at: %d\n", tmp);
				// condition: and this pedigree have no more element;
				if(DB[tmp].next <0) {DB[tmp].next=-2; DB[preadress].start=-1; site[tmp]=-1; return 1; } //delete pedigree;
				// condition: this pedigree have other element;
				else if(DB[tmp].next >-1) 
					{ DB[preadress].start=DB[tmp].next; DB[tmp].next=-2; site[tmp]=-1; return 1; } //change start to tmp.next;
			}
			//condition: element "isn't" head of the pedigree
		//so find element through "next" 
			while(DB[tmp].next>-1){
				preadress = tmp;
				tmp = DB[tmp].next;
				//find element in the pedigree
				if(DB[tmp].val == element){ 
					printf("Find at: %d\n", tmp);
					//if element is end of the pedigree
					if(DB[tmp].next > -1) 
						{ DB[preadress].next=DB[tmp].next; DB[tmp].next=-2; site[tmp]=-1; return 1; }
					//if element isn't end of the pedigree
					else { DB[preadress].next=-1; DB[tmp].next=-2; site[tmp]=-1; return 1; }
				}
			}
		}
	//find element "directly through next"
		tmp=adress;
		while(DB[tmp].next>-1){
			preadress = tmp;
			tmp = DB[tmp].next;
			if(DB[tmp].val == element){ 
				printf("Find at: %d\n", tmp);
				if(DB[tmp].next > -1) 
					{ DB[preadress].next=DB[tmp].next; DB[tmp].next=-2; site[tmp]=-1; return 1; }
				else { DB[preadress].next=-1; DB[tmp].next=-2; site[tmp]=-1; return 1; }
			}
		}

	}
	printf("Not find!\n");
	return 0;
}
//find element
int findDB(TABLE *DB, int DBsize, int element, int* Ctimes){
	int adress= Hash(element, DBsize), tmp=0;
	*Ctimes=0;
	printf("Target: %d\nPrimary adress: %d\n", element, adress);
//first: find direct site 
	*Ctimes=1; //statistics of collision times 
	if(DB[adress].val == element && DB[adress].next!=-2) 
		{ printf("find at: %d\n", adress);  return 0; }
	*Ctimes+=1;
//find "start" or "next"
	if(DB[adress].start>-1 || DB[adress].next>-1){
		tmp=adress;
		// find through next
		while(DB[tmp].next>-1){
			*Ctimes+=1;
			tmp = DB[tmp].next;
			if(DB[tmp].val == element && DB[tmp].next!=-2) 
				{ printf("find at: %d\n", tmp); return 0; }
		}// find through start
		if(DB[adress].start>-1){
			// to the pedigree
			tmp = DB[adress].start;
			*Ctimes+=1;
			// whether element is head of pedigree or not
			if(DB[tmp].val == element && DB[tmp].next!=-2) 
				{ printf("find at: %d\n", tmp);  return 0; }
			// not head of pedigree, go find the pedigree 
			while(DB[tmp].next>-1){
				*Ctimes+=1;
				tmp = DB[tmp].next;
				if(DB[tmp].val == element && DB[tmp].next!=-2) 
					{ printf("find at: %d\n", tmp); return 0; }
			}
		}
	}
	printf("Not find!\n");
	return 1;
}
//insert element to databse;
void insertDB(TABLE *DB, int DBsize, int element, int *site){
	//hash 
	int adress = Hash(element, DBsize);
	// if start is empty;
	if(DB[adress].start == -1){
		// space empty too
		if(DB[adress].next == -2)
			{ DB[adress].val=element; DB[adress].next=-1; DB[adress].start=adress; *site=adress;}
		// space is not empty, so use CRS(collision resolution to find a space)
		else{
			int newadress = CRS(DB, adress, DBsize);
			DB[adress].start = newadress;
			DB[newadress].val = element; DB[newadress].next = -1;
			*site=newadress;
		}
	}
	// start isn't empty
	else{
		// go to the pedigree that belong to itself
		adress = DB[adress].start;
		// find space through next (see whether there is a space in the pedigree);
		while(DB[adress].next>-1) adress = DB[adress].next;	
		// if find a space 
		if(DB[adress].next == -2) { DB[adress].val = element; *site=adress; }
		// if no space in the pedigree, use CRS(collision resolution to find a space)
		else { 
			int newadress = CRS(DB, adress, DBsize);
			DB[adress].next = newadress;
			DB[newadress].val = element; DB[newadress].next = -1;	
			*site=newadress;		
		}
	}
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
		nums[i]=(rand()%(MAX))*charge[rand()%2];
		if(nums[i]<0) nums[i]-=rand()%2;
		printf("\t%d",nums[i]);
	}
	printf("\n============= END Create Input =============\n");
}
// check each element of array is unique or not 
int checkArray(int *nums, int numsSize){
	int ret=0;
	for(int i=0;i<numsSize-1;i++){
		for(int j=i+1;j<numsSize;j++){
			if(nums[i] == nums[j]) { ret++; printf("[%d] ", nums[i]); };
		}
	}
	return ret;
}

