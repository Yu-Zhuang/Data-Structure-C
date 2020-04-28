#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*
* 每個邊權重範圍: 1~10
* 規定 不能有名稱為 0 的點
* 函數: 找出 起點 至 終點 最短路徑 與其權重和
*/
#define MAX 21 //資料為 幾乘幾 的矩陣
#define MAX_WEIGHT 21*10 //最大權重為10 再乘以 矩陣行列數
typedef struct s{ //stack資料定義
	int val;
	struct s *next;
}STACK;
// FUNCTION_ANNOUNCEMENT
	//檔案讀取與創造 的函數
void FILE_GENERATOR(char *file);
void FILE_GET(char *file, int input[][MAX]);
	//找 最短路徑 與 權重 相關的函數
bool FIND(int map[][MAX], int start, int end, int *path, int *pathSize, int *pathWeight);
int* PATH_RECORD(STACK *s, int map[][MAX], int *weight, int *pathSize);
void STACK_PUSH(STACK *s, int element);
int STACK_POP(STACK *s);
	//顯示資料的函數
void MAP_PRINT(int input[][MAX]);
void PATH_PRINT(STACK *s);
void STACK_PRINT(STACK *s);
// MAIN
int main(void){
	char file[]="map.txt";
	int input[MAX][MAX]={0}; //存檔案的 矩陣(map) 
	int path[MAX]={0}, pathSize=0, pathWeight=0; //存最短路徑 與 權重
	int start = 0, end = 0; //存 起始 點
	//FILE_GENERATOR(file);
	
 // 讀檔, 顯示讀檔結果
	FILE_GET(file, input);
	MAP_PRINT(input); 
 // 由鍵盤讀入 起點 終點
	printf("請依序輸入 起點 終點: "); scanf("%d %d", &start, &end);
 // FIND()運算 -> 判斷 是否有找到 -> 輸出結果
	if( FIND(input, start, end, path, &pathSize, &pathWeight) ){
		printf("執行結果:\n\t# 最短路徑: ");
		for(int i=pathSize-1;i>=0;i--){
			if(i!=0) printf("%d -> ", path[i]);
			else printf("%d\n", path[i]);
		}
		printf("\t# 該路徑權重: %d\n", pathWeight);			
	}
	else printf("\t# 沒有路徑 從%d到%d\n", start, end);
	
 // END
	return 0;
}
// FUNCTION
bool FIND(int map[][MAX], int start, int end, int *path, int *pathSize,int *pathWeight){
	STACK *stack = (STACK*)malloc(sizeof(STACK)); // stack
	stack->val = 0; stack->next = NULL;
	int check[MAX]={0}; // check array
	int *min_path=NULL, minpath_Size=0, min_weight=MAX_WEIGHT; // min_path
	int flag=0, find=0; // flag:紀錄該路是否已到終點; find:紀錄是否能從start到end

	STACK_PUSH(stack, start);
	while(stack->next){ // stack is empty or not?
		if(stack->next->val == end){ //找到 end 
			find = 1; // record: 該圖start可到end 
			int *tmp_path, tmp_weight=0, tmp_pathSize=0;
			// record: Npath and Nweight;
			tmp_path = PATH_RECORD(stack, map, &tmp_weight, &tmp_pathSize);
			printf("===================================================\n=\t\t[ FIND ! ]\n=\t*找到的路徑: ");
			for(int i=tmp_pathSize-1;i>=0;i--) printf("%d >> ", tmp_path[i]); printf("\n");
			printf("=\t*該路徑權重: %d\n", tmp_weight);
			printf("===================================================\n\n");
			// 是否為 較短路徑
			if(min_weight > tmp_weight){
				int *tmp = min_path;
				min_path = tmp_path;
				if(tmp) free(tmp); 
				minpath_Size = tmp_pathSize;
				min_weight = tmp_weight;
			}
			// 回分支點
			while(stack->next && stack->next->val >= 0) check[STACK_POP(stack)]=0; 
			// 如果走完
			if(! stack->next)
				{ for(int i=0;i<minpath_Size;i++) path[i]=min_path[i]; pathSize[0]=minpath_Size; pathWeight[0]=min_weight; return find; }
			// 將stack.top 改為 造訪中狀態
			stack->next->val *= -1;
		}
		else{ // 未找到 end
			flag = 0; //判斷是否已達終點
			int temp = stack->next->val;
			for(int i=0;i<MAX;i++){
				//周遭是否還有未拜訪的點
				if( !check[i] && map[temp][i]<11 && map[temp][i]>0 ){ 
					STACK_PUSH(stack,-i); 
					flag = 1;				
				}
			}
			if(!flag){ //該路已到終點, 回到分支點
				while(stack->next && stack->next->val >= 0 ) check[STACK_POP(stack)]=0;
				// 如果走完
				if(! stack->next)
					{ for(int i=0;i<minpath_Size;i++) path[i]=min_path[i]; pathSize[0]=minpath_Size; pathWeight[0]=min_weight; return find; }		
			}
			stack->next->val *= -1;	// 將stack.top 改為 造訪中狀態
			STACK *tmp = stack; 
			// 將造訪中的點 紀錄至 check[] 
			while(tmp->next) { if(tmp->next->val>=0) check[tmp->next->val]=1; tmp = tmp->next; }
		}
		printf("STACK狀態: "); STACK_PRINT(stack); 
		printf("正在走的路徑: "); PATH_PRINT(stack); 
		printf("*******************\n");
	}
	return find;
}
// RECORD_PATH_WEIGHT
int* PATH_RECORD(STACK *s, int map[][MAX], int *weight, int *pathSize){
	int *path = (int*)malloc(sizeof(int)*MAX);
	for(int i=0;i<MAX;i++) path[i]=0;
	int size=0, w=0;
	while(s->next){	
		if(s->next->val < 0) { s=s->next; continue; }	
		path[size] = s->next->val; //路徑
		size++;
		s = s->next;
	}
	for(int i=0;i<size-1;i++)
		w+=map[path[i]][path[i+1]];
	weight[0] = w;
	pathSize[0] = size;
	return path;
}
// STACK
void STACK_PUSH(STACK *s, int element){
	STACK *newnode = (STACK*)malloc(sizeof(STACK));
	newnode->val = element;
	newnode->next = s->next;
	s->next = newnode;
}
int STACK_POP(STACK *s){
	if(s->next){
		int ret = s->next->val;
		STACK *tmp = s->next;
		s->next = s->next->next;
		free(tmp);
		return ret;
	}
	return 0;
}
// PRINT
void PATH_PRINT(STACK *s){
	if(!s || !s->next) return;
	int path[MAX+1]={-1}, count=0;
	while(s->next){ 
		if(s->next->val>0){ path[count]=s->next->val; count++; } 
		s=s->next; 
	}
	for(int i=count-1; i>=0; i--) printf("(%d)->", path[i]);
	printf("|END\n");
}
void STACK_PRINT(STACK *s){
	if(!s || !s->next) return;
	while(s->next){
		printf("[%d]_", s->next->val);
		s = s->next;
	}printf("|BOTTOM\n");
}
void MAP_PRINT(int input[][MAX]){
	printf("_______________________[ MAP ]________________________\n");
	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++)
			printf("[%d] ", input[i][j]);
		printf("\n");
	}
	printf("____________________________________________________\n\n");
}
// FILE
void FILE_GET(char *file, int input[][MAX]){
	FILE *fptr = fopen(file, "r");
	if(fptr){
		int count = 0, i = 0;
		while( !feof(fptr)){
			fscanf(fptr,"%d", &input[count][i++]);
			if(i==MAX) { i=0; count++; }
		}		
	}else printf("can't open the file\n");
	fclose(fptr);
}
//
void FILE_GENERATOR(char *file){
	FILE *fptr = fopen(file,"w");
	if(fptr){
		int count=0, i=0;
		int list[MAX][MAX]={0}, ary[MAX+1]={0};
		for(int i=1;i<MAX+1;i++) { ary[i]=rand()%2; printf("%d,", ary[i]); }
		printf("\n");
		for(int m=0;m<MAX+1;m++){
			for(int n=0;n<MAX+1;n++){
				if( (m==0||n==0) && n!=MAX-1) fprintf(fptr,"%d ", 0);
				else if( (m==0||n==0) && n==MAX-1) fprintf(fptr,"%d\n", 0);
				else if( m==n ) fprintf(fptr,"%d ", 0);
				else if( (ary[n]&&ary[m]) && n!=MAX-1) fprintf(fptr,"%d ", 0); 
				else if(!(ary[n]&&ary[m]) && n!=MAX-1) fprintf(fptr,"%d ", 0);
				else if((ary[n]&&ary[m]) && n==MAX-1)fprintf(fptr,"%d\n", 0);
				else fprintf(fptr,"%d\n", 0);
			}
		}
	}else printf("can't open the file\n");
	fclose(fptr);
}