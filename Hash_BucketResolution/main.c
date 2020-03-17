#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "hash.h"
//def 
#define NUM 31 // 預設幾個學生資料;
#define SIZE 34 // hash()後能發散的空間;
#define BSIZE 10 // 預設bucket空間;
int max=0, totalMax=0; //紀錄bucket最大需要多少空間
//def bucket struct
typedef struct bucket{
	int val[BSIZE];
}Bucket;
//function
void GetData(int *nums, int numsSize, int chose);
void PutDataByHash(Bucket* B, int* nums, int numsSize, int Hchose);
void CResulotion(Bucket* B, int adr, int num);
void ChoseHash(int Key, int numsSize, int Hchose, int *adress);
void NumGenerator(int N);
void printBucket(Bucket* B);
//main()
int main(void){
	srand(time(NULL));
	int list[100000]={0}; //存學生號碼;
	int chose=1, times=0, N=0, Hchose=0;
	Bucket data[SIZE];
	//start
	while(chose){
		printf("\t======================================\n"); 
		printf("\t=    Bucket collision resolution     =\n"); 
		printf("\t======================================\n");
		//input
		printf("\t\t@主 選 單@\n");
		printf("\t(0) 結束程式\n\t(1) 標準品測試\n\t(2) 產隨機檔測試\n\t(3) 做n次隨機檔測試\n\t請輸入選擇: "); 
		scanf("%d", &chose);
		while(chose<0||chose>3) { printf("輸入錯誤! 請重新輸入: "); scanf("%d", &chose); }
		// chose == 0 : 結束程式;
		if(chose == 0) break; 
		//input chose hash
		printf("\n\t\t$選擇使用之Hash函數$\n");
		printf("\t(1) Modulo\n\t(2) Digital extraction\n\t(3) Midsquare\n\t(4) Folding\n\t(5) Rotation\n\t(6) Pseudorandom\n\t請輸入選擇: ");
		scanf("%d", &Hchose);
		while(Hchose<1||Hchose>6) { printf("輸入錯誤! 請重新輸入: "); scanf("%d", &Hchose); }
		// chose == 3 : 做n次隨機檔測試;
		if(chose == 3){
			//input size
			printf("\n\t*幾個學生(0<N<=100000): ");
			scanf("%d", &N);
			while(N<1||N>100000) { printf("輸入錯誤! 請重新輸入: "); scanf("%d", &N); }
			//input run times
			printf("\n\t*要跑幾回: ");
			scanf("%d", &times);
			while(times<1) { printf("輸入錯誤! 請重新輸入: "); scanf("%d", &times); }
			//compution and output
			for(int i=0;i<times;i++){
				//initialize data/list
				for(int i=0;i<SIZE;i++) for(int j=0;j<BSIZE;j++) data[i].val[j]=0;
				for(int i=0;i<N;i++) list[i]=0;
				//run function
				GetData(list, N, chose-1);
				PutDataByHash(data,list, N, Hchose);
				printBucket(data);
				totalMax+=max;
				max=0;
				printf("\n");
			} 
			printf("*Average max size of Bucket: %lf\n\n", (double)totalMax/times); 
			printf("**********************************E N D*****************************************\n\n");
			max=0; totalMax=0;
		}
		// chose == 2 : 產隨機檔測試
		else if(chose == 2){
			//input size;
			printf("\n\t*幾個學生(0<N<=100000): ");
			scanf("%d", &N);
			while(N<1||N>100000) { printf("輸入錯誤! 請重新輸入: "); scanf("%d", &N); }
			//initialize data/list
			for(int i=0;i<SIZE;i++) for(int j=0;j<BSIZE;j++) data[i].val[j]=0;
			for(int i=0;i<N;i++) list[i]=0;
			//run function
			GetData(list, N, chose);
			PutDataByHash(data,list, N, Hchose);
			printBucket(data);
			max=0; totalMax=0;
			printf("\n\n");
		}// chose == 1 : 擇標準品測試
		else if(chose == 1){
			//initialize data/list
			for(int i=0;i<SIZE;i++) for(int j=0;j<BSIZE;j++) data[i].val[j]=0;
			for(int i=0;i<NUM;i++) list[i]=0;
			//run function
			GetData(list, NUM, chose);
			PutDataByHash(data,list, NUM, Hchose);
			printBucket(data);
			max=0; totalMax=0;
			printf("\n\n");
		}
	}
	printf("\t=============程式結束=============\n");
	return 0;
}
void GetData(int *nums, int numsSize, int chose){
	printf("\n================GetData================\n");
	FILE *fptr;
	char ch;
	int i=0, ten=100000000;
	//chose == 1 : 打開預設檔;
	if(chose == 1) fptr=fopen("/Users/yuzhuanglin/Desktop/F1.cpp","r");
	//chose == 2 or 3 : 以 genetator()將F檔複寫新資料 後, 再打開該檔案;
	else { NumGenerator(numsSize); fptr=fopen("/Users/yuzhuanglin/Desktop/F.cpp","r"); }
	if(fptr != NULL){
		while((ch=getc(fptr)) != EOF){
			if(ch>='0'&&ch<='9'){
				if(ten == 0) { i++; ten=100000000; }
				if(ten != 0){ nums[i]+=ten*(ch-'0'); ten/=10; }	
			}			
		}
	}
	fclose(fptr);
	for(int i=0;i<numsSize;i++) printf("%d.\t%d\n", i+1, nums[i]);
	printf("================END GetData================\n");
}
void PutDataByHash(Bucket* B, int* nums, int numsSize, int Hchose){
	double Lfactor=(double)numsSize/SIZE;
	printf("\n================PutDataByHash================\n");
	printf("\n*Load factor: %lf\n", Lfactor); //load facter;

	int list[SIZE]={0}, adr=0;
	printf("\n[KEY]\t\t[ADDRESS]\n\n");
	for(int i=0;i<numsSize;i++){
		ChoseHash(nums[i], SIZE, Hchose, &adr); //hash compution
		printf("%d\t%d\n",nums[i],adr);
		list[adr]++;
		if(B[adr].val[0] == 0) B[adr].val[0]=nums[i]; //put key in data;
		else CResulotion(B, adr, nums[i]); //collision resolution;
	}
	printf("\n-----------Collision-----------\n"); //Collision analysis
	int count=0;
	int ct=0;
	for(int i=0;i<SIZE;i++){
		if(list[i]>1){
			count+=list[i]-1;
			ct++;
			if(list[i]>max) max=list[i]; //紀錄bucket最大需用多少;
			printf("%d.adress %d:\t", ct, i);
			for(int j=0;j<list[i]-1;j++) printf("*");
			printf("\n");
		}
	}
	printf("\n#Total collision times: %d\n",count);
	printf("#Bucket最大需要 %d 個空間才夠\n", max);
	printf("__________END analysis_________\n\n");
	printf("================END PutDataByHash================\n");
}
void ChoseHash(int Key, int dataSize, int Hchose, int* adress){
	switch (Hchose){
		case 1:
			*adress=ModuloHash(Key, dataSize);
			break;
		case 2:
			*adress=DigitExtractHash(Key, dataSize);
			break;
		case 3:
			*adress=MidSqrHash(Key, dataSize);
			break;
		case 4:
			*adress=FoldHash(Key, dataSize);
			break;
		case 5:
			*adress=RotateHash(Key, dataSize);
			break;
		case 6:
			*adress=PseuRandHash(Key, dataSize);
			break;			
	}
}
void CResulotion(Bucket* B, int adr, int num){
	for(int i=1;i<BSIZE;i++){
		if(B[adr].val[i] == 0) { B[adr].val[i]=num; break; }
	}
}
void NumGenerator(int N){
	char str[10]="106316101";
	int a[3]={4,5,6}, b[2]={3,5}, c[3]={3,4,6};
	FILE *fptr;
	fptr=fopen("/Users/yuzhuanglin/Desktop/F.cpp","w");

	for(int i=0;i<N;i++){
		str[2]=a[rand()%3]+'0';
		str[3]=b[rand()%2]+'0';
		str[5]=c[rand()%3]+'0';
		str[6]=rand()%2+1+'0';		
		str[7]=rand()%6+1+'0';
		str[8]=rand()%9+1+'0';
		fputs(str,fptr);
		fputc('\n',fptr);
	}
	fclose(fptr);
}
void printBucket(Bucket* B){
	printf("\n================printBucket================\n");
	printf("\n[BUCKET]\t[STATUS]\n\n");
	for(int i=0;i<SIZE;i++){
		printf("Bucket %d\t",i);
		if(B[i].val[0]!=0){
			for(int j=0;j<BSIZE;j++){
				if(B[i].val[j]!=0){
					printf("[%d] ",j+1);
					printf("%d \t",B[i].val[j]);
					if(((j+1)%5==0)&&B[i].val[j+1]!=0) printf("\n\t\t");
				}
			}
		}
		else printf("(empty)");
		printf("\n");
	}
	printf("================END printBucket================\n");
}

