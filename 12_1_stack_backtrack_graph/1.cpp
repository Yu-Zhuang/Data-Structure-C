#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 20
#define MAX_WEIGHT 20*10

typedef struct s{
	int val;
	struct s *next;
}STACK;

void FILE_GENERATOR(char *file);

void FILE_GET(char *file, int input[][MAX]);
void PRINT(int input[][MAX]);

bool FIND(int map[][MAX], int start, int end, int *path, int *pathSize);
int* PATH_RECORD(STACK *s, int map[][MAX], int *weight, int *pathSize);
void STACK_PUSH(STACK *s, int element);
int STACK_POP(STACK *s);
void STACK_PRINT(STACK *s);

int main(void){
	char file[]="map.txt";
	FILE_GENERATOR(file);
/*	
	int input[MAX][MAX]={0};
	int path[MAX]={0}, pathSize;

	FILE_GET(file, input);
	PRINT(input); printf("\n");

	int start = 1;
	int end = 6;

	FIND(input, start, end, path, &pathSize);

	for(int i=pathSize-1;i>=0;i--) printf("%d->", path[i]);
*/	
	return 0;
}
bool FIND(int map[][MAX], int start, int end, int *path, int *pathSize){
	STACK *stack = (STACK*)malloc(sizeof(STACK));
	stack->val = 0; stack->next = NULL;
	int check[MAX]={0};
	int *min_path=NULL, minpath_Size=0, min_weight=MAX_WEIGHT;
	int flag=0, find=0;

	STACK_PUSH(stack, start);
	//check[start] = 1;
	while(stack->next){
		STACK_PRINT(stack); //
		for(int i=0;i<MAX;i++) if(check[i]) printf("(%d)_", i); printf("\n");
		if(stack->next->val == end){ //找到 end
			printf("\t [ FIND ! ]\n"); //
			find = 1; // 該圖start可到target 
			int *tmp_path, tmp_weight=0, tmp_pathSize=0;
			// record Npath and Nweight;
			tmp_path = PATH_RECORD(stack, map, &tmp_weight, &tmp_pathSize);
			for(int i=0;i<tmp_pathSize;i++) printf("<<%d>>", tmp_path[i]); printf("\n");
			// 找到 較短路徑
			if(min_weight > tmp_weight){
				int *tmp = min_path;
				min_path = tmp_path;
				if(tmp) free(tmp); 
				minpath_Size = tmp_pathSize;
				min_weight = tmp_weight;
			}
			while(stack->next && stack->next->val >= 0) { check[STACK_POP(stack)]=0; printf("hi\n"); }
			if(! stack->next) { for(int i=0;i<minpath_Size;i++) path[i]=min_path[i]; pathSize[0]=minpath_Size; return find; }
			stack->next->val *= -1;
			//check[stack->next->val] = 1;

		}
		else{ // 未找到 end
			flag = 0;
			int temp = stack->next->val;
			for(int i=0;i<MAX;i++){
				if( !check[i] && map[temp][i]<11 && map[temp][i]>0 ){
					STACK_PUSH(stack,-i);
					//check[i] = 1;
					flag = 1;				
				}
			}
			if(flag){ //該路未到終點
				stack->next->val *= -1;
				//check[stack->next->val] = 1;	
			}else{ //到該路終點, track back回到分支點
				while(stack->next && stack->next->val >= 0 ) { check[STACK_POP(stack)]=0; printf("hilo\n"); }
				if(! stack->next) { for(int i=0;i<minpath_Size;i++) path[i]=min_path[i]; pathSize[0]=minpath_Size; return find; }
				stack->next->val *= -1;
				//check[stack->next->val] = 1;				
			}
			STACK *tmp = stack;
			while(tmp->next) { if(tmp->next->val>=0) check[tmp->next->val]=1; tmp = tmp->next; }
		}
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
	for(int i=0;i<size-1;i++){
		w+=map[path[i]][path[i+1]];
	}
	printf("{%d}\n", w);
	//w+=map[s->next->val][s->next->next->val];
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
	else return 0;
}
void STACK_PRINT(STACK *s){
	while(s->next){
		printf("[%d]_", s->next->val);
		s = s->next;
	}printf("|\n");
}
void PRINT(int input[][MAX]){
	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++)
			printf("[%d] ", input[i][j]);
		printf("\n");
	}
	
}
// FILE
void FILE_GET(char *file, int input[][MAX]){
	FILE *fptr = fopen(file, "r");
	int count = 0, i = 0;
	while( !feof(fptr)){
		fscanf(fptr,"%d", &input[count][i++]);
		if(i==MAX) { i=0; count++; }
	}
	fclose(fptr);
}
void FILE_GENERATOR(char *file){
	FILE *fptr = fopen(file,"w");
	int count=0, i=0;
	int list[MAX][MAX]={0};

	int ary[MAX]={0};
	for(int i=1;i<MAX;i++) { ary[i]=rand()%2; printf("%d,", ary[i]); }
	printf("\n");

	for(int m=0;m<MAX;m++){
		for(int n=0;n<MAX;n++){
			if( (m==0||n==0) && n!=MAX-1) fprintf(fptr,"%d ", 0);
			else if( (m==0||n==0) && n==MAX-1) fprintf(fptr,"%d\n", 0);
			else if( m==n ) fprintf(fptr,"%d ", 0);
			else if( (ary[n]&&ary[m]) && n!=MAX-1) fprintf(fptr,"%d ", 1); 
			else if(!(ary[n]&&ary[m]) && n!=MAX-1) fprintf(fptr,"%d ", 0);
			else if((ary[n]&&ary[m]) && n==MAX-1)fprintf(fptr,"%d\n", 1);
			else fprintf(fptr,"%d\n", 0);
		}
	}
}