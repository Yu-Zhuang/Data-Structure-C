/*
*	Adjacent Linked List implement Graph data structure.
*	graph:
*		[vertex]	[adjacent]
*   		1		|-[2]-[5]-|END
*   		2		|-[1]-[3]-[5]-[4]-|END
*   		3		|-[2]-[4]-[6]-|END
*   		4		|-[2]-[3]-[5]-[6]-|END
*   		5		|-[1]-[2]-[4]-[6]-|END
*   		6		|-[3]-[4]-[5]-|END
*	Date: 2020.4.12
*/
// *** HEADER file ***
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// *** DEFINE ***
#define MAX 100
typedef struct nd{
	int val;
	struct nd *next;
}NODE;
// *** FUNCTION_ANNOUNCEMENT ***
	//FILE()
void FILE_GET(char *file, int input[][2], int *inputSize);
	//HASH_TABLE() 
void TABLE_INIT(NODE *table, int size);
	//GRAPH()
void GRAPH_INSERT(NODE *table, int input[][2], int iSize);
void GRAPH_PRINT(NODE *table, int iSize);
void GRAPH_BSF(NODE *table, int start);
void GRAPH_DSF(NODE *table, int start);
	//QUEUE(), STACK()
void QUEUE_ENQUEUE(NODE *Q, int element); 
int QUEUE_DEQUEUE(NODE *Q);
void STACK_PUSH(NODE *S, int element); 
int STACK_POP(NODE *S);
	//LINK()
void LINK_PRINT(NODE *link);
int LINK_FIND(NODE *link, int target); // find return 1, not find return 0;
// *** MAIN ***
int main(void){
	// variable
	char file[]="graph.cpp";
	int input[MAX][2], iSize=0;
	NODE table[MAX];
	// conpution
	FILE_GET(file, input, &iSize);
	TABLE_INIT(table,MAX);
	GRAPH_INSERT(table, input, iSize);
	GRAPH_PRINT(table, iSize);
	GRAPH_BSF(table,1);
	GRAPH_DSF(table,1);
	// end
	return 0;
}
// *** FUNCTION ***
void GRAPH_BSF(NODE *table, int start){
	NODE *q=(NODE*)malloc(sizeof(NODE));
	q->next=NULL;
	int target=start, check[MAX]={0}, flag=1;
	if(table[start].val){
		printf("********* GRAPH_BSF *********\n");
		do{
			if(check[target]==0){
				check[target]=1;
				printf("on: %d\nadjacent: ", target);
				NODE *ptr=table[target].next;
				while(ptr){
					printf("[%d]-", ptr->val);
					if(check[ptr->val]==0 && LINK_FIND(q,ptr->val)==0) 
						QUEUE_ENQUEUE(q, ptr->val);
					ptr=ptr->next;
				}printf("|\nQueue: ");
				LINK_PRINT(q);
			}
			(q->next!=NULL) ? target=QUEUE_DEQUEUE(q):flag=0;
		}while(flag);
		printf("********* END_GRAPH_BSF *********\n\n");
	}
}
void GRAPH_DSF(NODE *table, int start){
	NODE *s=(NODE*)malloc(sizeof(NODE));
	s->next=NULL;
	int target=start, check[MAX]={0}, flag=1;
	if(table[start].val){
		printf("********* GRAPH_DSF *********\n");
		do{
			if(check[target]==0){
				check[target]=1;
				printf("on: %d\nadjacent: ", target);
				NODE *ptr=table[target].next;
				while(ptr){
					printf("[%d]-", ptr->val);
					if(check[ptr->val]==0 && LINK_FIND(s,ptr->val)==0) 
						STACK_PUSH(s, ptr->val);
					ptr=ptr->next;
				}printf("|\nStack: "); 
				LINK_PRINT(s);
			}
			(s->next!=NULL) ? target=STACK_POP(s):flag=0;
		}while(flag);
		printf("********* END_GRAPH_DSF *********\n\n");
	}	
}
void GRAPH_INSERT(NODE *table, int input[][2], int iSize){
	for(int i=0;i<iSize;i++){
		//create newnode(鄰邊) 
		NODE *newnode=(NODE*)malloc(sizeof(NODE));
		newnode->val=input[i][1]; newnode->next=NULL;
		//沒有該元素
		if( ! table[input[i][0]].val){
			table[input[i][0]].val=1;
		}
		//將鄰邊加入
		NODE *pre=&table[input[i][0]];
		while(pre->next) pre=pre->next; 
		pre->next=newnode;
	}
}
void GRAPH_PRINT(NODE *table, int iSize){
	printf("********* GRAPH_PRINT *********\n");
	printf("[vertex]\t[adjacent]\n");
	for(int i=0;i<iSize;i++){
		if(table[i].val){
			printf("%4d\t\t|-", i);
			NODE *ptr=table[i].next;
			while(ptr){ printf("[%d]-", ptr->val); ptr=ptr->next; }
			printf("|END\n");
		}
	}
	printf("********* END_GRAPH_PRINT *********\n\n");
}
void TABLE_INIT(NODE *table, int size){
	for(int i=0;i<size;i++){
		table[i].val=0; // 0: empty, 1: have element
		table[i].next=NULL;
	}
}
void QUEUE_ENQUEUE(NODE *Q, int element){
	if(Q){
		NODE *newnode=(NODE*)malloc(sizeof(NODE));
		newnode->val=element; newnode->next=NULL;
		while(Q->next) Q=Q->next;
		Q->next=newnode;
	}
}
int QUEUE_DEQUEUE(NODE *Q){
	if(Q->next){
		NODE *tmp;
		tmp=Q->next;
		int ret=Q->next->val;
		Q->next=Q->next->next;
		free(tmp);
		return ret;
	}
	return 0;
}
void STACK_PUSH(NODE *S, int element){
	if(S){
		NODE *newnode=(NODE*)malloc(sizeof(NODE));
		newnode->val=element;
		newnode->next=S->next;
		S->next=newnode;
	}
}
int STACK_POP(NODE *S){
	if(S->next){
		NODE *tmp;
		tmp=S->next;
		int ret=S->next->val;
		S->next=S->next->next;
		free(tmp);
		return ret;
	}
	return 0;
}
int LINK_FIND(NODE *link, int target){
	if(link){
		link=link->next;
		while(link){
			if(target == link->val) return 1;
			link=link->next;
		}
	}
	return 0;
}
void LINK_PRINT(NODE *link){
	if(link->next){
		link=link->next;
		while(link){
			printf("[%d]-", link->val);
			link=link->next;
		}
		printf("|END\n\n");
	}else printf("(empty)\n");
}
void FILE_GET(char *file, int input[][2], int *inputSize){
	FILE *fptr=fopen(file,"r");
	char str[MAX], copy[MAX], *token;
	int i=0, j=0;

	while( fgets(str,MAX,fptr) ){
		j=0;
		strcpy(copy,str);	
		token=strtok(copy," ");	
		while(token){ 
			sscanf(token,"%d", &input[i][j]); 
			j++; 
			token=strtok(NULL," "); 
		}
		i++;
	}
	inputSize[0]=i;
	fclose(fptr);
}
